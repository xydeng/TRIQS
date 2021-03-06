
/*******************************************************************************
 *
 * TRIQS: a Toolbox for Research in Interacting Quantum Systems
 *
 * Copyright (C) 2011 by M. Ferrero, O. Parcollet
 *
 * TRIQS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * TRIQS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * TRIQS. If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#ifndef TRIQS_TOOLS_MC_GENERIC_H
#define TRIQS_TOOLS_MC_GENERIC_H

#include "mc_measure_set.hpp"
#include "mc_move_set.hpp"
#include "mc_basic_step.hpp"

#include <triqs/python_tools/improved_python_dict.hpp>
#include <boost/function.hpp>
#include "polymorphic_random_generator.hpp"
#include <math.h>
#include <triqs/utility/timer.hpp>
#include <triqs/utility/report_stream.hpp>
#include "call_backs.hpp"

namespace triqs { namespace mc_tools { 

 typedef triqs::python_tools::improved_python_dict mcparams_python; 
  
 /**
  * 
  */
 template<typename MCSignType, typename ParameterDictType = mcparams_python, typename MCStepType= Step::Metropolis<MCSignType> > 
 class mc_generic {
  public:

   typedef ParameterDictType parameters_type;
   /** 
     * \param[in] P  dictionnary parameters
     * \param[in] rank The rank of the process in mpi (why ?).
     * \param[in] AfterCycleDuty  a function bool() to be called after each QMC cycle
    */
   mc_generic(parameters_type const & P, size_t rank,  boost::function<bool()> AfterCycleDuty = boost::function<bool()>() ) : 
    RandomGenerator(P.value_or_default("Random_Generator_Name",""), P.value_or_default("Random_Seed",1)),
    report(&std::cout,int(P["Verbosity"])),
    Rank(rank),
    AllMoves(RandomGenerator), 
    AllMeasures(),
    Length_MC_Cycle(P["Length_Cycle"]),
    NWarmIterations(P["N_Warmup_Cycles"]),
    NCycles(P["N_Cycles"]),
    after_cycle_duty(AfterCycleDuty)
  {}

   /** 
    * Register move M with its probability of being proposed.
    * NB : the PropositionProbability needs to be >0 but does not need to be 
    * normalized. Normalization is automatically done with all the added moves
    * before starting the run
    *
      \rst
       .. warning::  
          
          The pointer is deleted automatically by the MC class at destruction. 
          Correct usage is therefore:
        
       .. code-block:: c  
      
             myMC.add_move( new myMOVE(...), Proba,Name);
    
       \endrst
    */
   template <typename MoveType>
    void add_move (MoveType *M, double PropositionProbability,std::string name ="") { AllMoves.add(M, PropositionProbability,name); }

    /** 
    * Add a couple of inverse moves (M1,M2) with their probability of being proposed.
    * Equivalent to two add_move(M1), add_move(M2), but it emphasizes the fact that inverse
    * moves **must** have the same PropositionProbability.
    */
    template <typename MoveType1,typename MoveType2>
    void add_move (MoveType1 *M1, MoveType2 *M2, double PropositionProbability, std::string name1="", std::string name2="") {
     AllMoves.add(M1,M2,PropositionProbability,name1,name2);
    }

   /**
    * Register the Measure M 
    *
      \rst
       .. warning::
   
          The pointer is deleted automatically by the MC class at destruction. 
          Correct usage is therefore:

       .. code-block:: c 
        
            myMC.add_measure( new myMEASURE(...), Name); 
 
      \endrst
    */
   template<typename MeasureType>
    void add_measure (MeasureType *M, std::string name="") {  AllMeasures.insert(name,M);} 

   // An access to the random number generator
   polymorphic_random_generator RandomGenerator;

  protected:
   /**
     Reimplement to have another thermalization criterion. 
     Default is # cycles > # Warming Iterations
     */
   virtual bool thermalized() const { return (NC>= NWarmIterations);}

   /**
     Reimplement to add a convergence criterion.
     Default is false.
     It is called before each cycle and if true, the computation will stop
     */
   virtual bool converged() const { return false;}

  public:

   ///
   bool run(boost::function<bool ()> const & stop_callback) {
    assert(stop_callback);
    Timer.start();
    signe=1; done_percent = 0; 
    bool stop_it=false, finished = false;
    uint64_t NCycles_tot = NCycles+ NWarmIterations;
    for (NC =0; !stop_it; ++NC) {
     for (uint64_t k=1; (k<=Length_MC_Cycle); k++) { MCStepType::do_it(AllMoves,RandomGenerator,signe); }
     if (after_cycle_duty) {after_cycle_duty();}
     if (thermalized()) AllMeasures.accumulate(signe);
     // recompute fraction done
     uint64_t dp = uint64_t(floor( ( NC*100.0) / NCycles_tot));  
     if (dp>done_percent)  { done_percent=dp; report << done_percent; report<<"%; "; report <<std::flush; }
     finished = ( (NC >= NCycles_tot -1) || converged () );
     stop_it = (stop_callback() || finished);
    }
    Timer.stop();
    return finished;
   }

   void collect_results (boost::mpi::communicator const & c) { AllMeasures.collect_results(c);} 

  protected:

   triqs::utility::report_stream report;
   size_t Rank;
   move_set<MCSignType> AllMoves;
   measure_set<MCSignType> AllMeasures;
   uint64_t Length_MC_Cycle;/// Length of one Monte-Carlo cycle between 2 measures
   uint64_t NWarmIterations,NCycles;
   triqs::utility::timer Timer;

  private: 
   boost::function<bool()> after_cycle_duty;
   MCSignType signe;
   uint64_t NC,done_percent;// NC = number of the cycle
 };

 // add the communicator
 template<typename MCG> class mc_runner : public MCG {
  boost::mpi::communicator communicator;
  public:
  typedef typename MCG::parameters_type parameters_type;

  mc_runner(parameters_type const & p, boost::mpi::communicator const & c) : MCG(p, c.rank()) , communicator(c) 
  { MPI_Errhandler_set(communicator, MPI_ERRORS_RETURN); }

  double fraction_completed() const { return boost::mpi::all_reduce(communicator, MCG::fraction_completed(), std::plus<double>()); }
  void collect_results() { MCG::collect_results(communicator);}
 };

}}// end namespace
#endif

