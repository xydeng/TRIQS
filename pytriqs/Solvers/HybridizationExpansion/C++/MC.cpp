
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

// include first because of a namespace clash.. to be fixed...
#include <triqs/arrays/h5/array_stack.hpp>
#include "MC.hpp"
#include <triqs/python_tools/IteratorOnPythonSequences.hpp>
 
using triqs::mc_tools::move_set;
using triqs::mc_tools::mcparams_python;
using python::extract;
using namespace triqs;

// The moves to insert and remove C, Cdagger operators
#include "Move_Insert_Remove_Cdag_C_Delta.hpp"
#include "Move_Insert_Remove_Cdag_C_Delta_SegmentPicture.hpp"

// The move to move operators
#include "Move_Move_CC_Delta.hpp"

// The Global moves
#include "Move_Global.hpp"

// The measures.
#include "Measures_G.hpp"
#include "Measures_F.hpp"
#include "Measures_OpAv.hpp"
#include "Measures_Legendre.hpp"
#include "Measures_Legendre_allseries.hpp"
#include "Measures_OpCorr.hpp"

template<typename T1> 
std::string make_string( T1 const & x1) { 
 std::stringstream fs; fs <<x1; return fs.str();
}
template<typename T1,typename T2> 
std::string make_string( T1 const & x1,T2 const & x2) { 
 std::stringstream fs; fs <<x1<<x2; return fs.str();
}


//-----------------------------------------------------

MC_Hybridization_Matsubara::MC_Hybridization_Matsubara(MC_Hybridization_Matsubara::parameters_type const & params, size_t rank) : 
 BaseType (params ,rank), 
 Config(params),
 G_tau (extract<GF_C<GF_Bloc_ImTime> > (params.dict()["G_tau"])),
 F_tau (extract<GF_C<GF_Bloc_ImTime> > (params.dict()["F_tau"])),
 G_legendre (extract<GF_C<GF_Bloc_ImLegendre> > (params.dict()["G_Legendre"])),
 Gc_w (extract<GF_C<GF_Bloc_ImFreq> > (params.dict()["G"])),
 TimeAccumulation (params["Time_Accumulation"]),
 LegendreAccumulation (params["Legendre_Accumulation"]),
 N_Frequencies_Accu (params["N_Frequencies_Accumulated"]),
 Freq_Fit_Start (params["Fitting_Frequency_Start"])

{

 const bool UseSegmentPicture (params["Use_Segment_Picture"]);

 // register the moves
 double p_ir = params["Proba_Insert_Remove"];
 double p_mv = params["Proba_Move"];

 typedef move_set<SignType> move_set_type;
 move_set_type * AllInserts = new move_set_type(this->RandomGenerator);
 move_set_type * AllRemoves = new move_set_type(this->RandomGenerator);
 for (int a =0; a<Config.Na;++a) { 

  if (UseSegmentPicture) {
   AllInserts->add( new Insert_Cdag_C_Delta_SegmentPicture ( a, Config, Histograms, this->RandomGenerator), 1.0, make_string("Insert",a));
   AllRemoves->add( new Remove_Cdag_C_Delta_SegmentPicture ( a, Config, this->RandomGenerator), 1.0, make_string("Remove",a));
  }  
  else {  
   AllInserts -> add( new Insert_Cdag_C_Delta ( a, Config, Histograms, this->RandomGenerator), 1.0, make_string("Insert",a));
   AllRemoves -> add( new Remove_Cdag_C_Delta ( a, Config, this->RandomGenerator), 1.0, make_string("Remove",a));
  }
 }

 this->add_move(AllInserts, AllRemoves, p_ir,"INSERT","REMOVE");
 this->add_move(new Move_C_Delta(Config, this->RandomGenerator), p_mv,"Move C Delta");

 // Register the Global moves
 python::list GM_List = python::extract<python::list>(params.dict()["Global_Moves_Mapping_List"]);
 for (triqs::python_tools::IteratorOnPythonListOf3Tuples<double,python::dict,string> g(GM_List); !g.atEnd(); ++g) {
  assert (python::len(g->x2)== Config.H.N_Operators());
  // transform a python dict : name_of_operator -> name_of_operator into a  
  vector<const Hloc::Operator*> mapping(Config.H.N_Operators(), (const Hloc::Operator*)NULL);
  for (triqs::python_tools::IteratorOnPythonDict<string,string> p(g->x2); !p.atEnd(); ++p) {
   mapping[Config.H[p->key].Number] =& Config.H[p->val];
   //cout<< "MAP" << Config.H[p->key].Number<< "  "<<mapping[Config.H[p->key].Number]->Number<<endl<<
   //      Config.H[p->key].name<< "  "<<mapping[Config.H[p->key].Number]->name<<endl;
  }
  this->add_move(new Global_Move(g->x3 , Config, this->RandomGenerator, mapping), g->x1);
 }

 /*************

   Register the measures 

  ****************/

 for (int a =0; a<Config.Na;++a) { 
   if (LegendreAccumulation) {
     this->add_measure(new Measure_G_Legendre(Config, a, G_legendre[a]),make_string("G Legendre ",a));
     if (bool(params["Keep_Full_MC_Series"])) 
      this->add_measure(new Measure_G_Legendre_all(Config, a, G_legendre[a]),make_string("G Legendre (all) ",a));
   } else if (TimeAccumulation) {
     this->add_measure(new Measure_G_tau(Config, a, G_tau[a] ), make_string("G(tau) ",a));
   } else {
     assert(0);
   }
 }


 // register the measure of F
 if (bool(params["Use_F"]))
   for (int a =0; a<Config.Na;++a) 
     this->add_measure(new Measure_F_tau(Config, a, F_tau[a] ), make_string("F(tau) ",a));

 // register the measures of the average of some operators
 python::dict opAv_results = python::extract<python::dict>(params.dict()["Measured_Operators_Results"]);
 python::list opAv_List = python::extract<python::list>(params.dict()["Operators_To_Average_List"]);
 for (triqs::python_tools::IteratorOnPythonList<string> g(opAv_List); !g.atEnd(); ++g) {
  this->add_measure(new Measure_OpAv(*g, Config, opAv_results),*g);
 }

 // register the measures for the time correlators:
 python::list opCorr_List = python::extract<python::list>(params.dict()["OpCorr_To_Average_List"]);
 GF_C<GF_Bloc_ImTime> OpCorrToAverage(extract<GF_C<GF_Bloc_ImTime> > (params.dict()["Measured_Time_Correlators_Results"]));
 int a = 0;
 for (triqs::python_tools::IteratorOnPythonList<string> g(opCorr_List); !g.atEnd(); ++g, ++a) {
  string str1(*g);
  str1+= "OpCorr";
  this->add_measure(new Measure_OpCorr(str1, *g, Config, OpCorrToAverage[a], OpCorrToAverage[a].mesh.len()),str1);
 }

}


//********************************************************

void MC_Hybridization_Matsubara::finalize (boost::mpi::communicator const & c) { 

  // report the acceptance of the move
  report<<" Move acceptance probability"<<std::endl;
  this->AllMoves.print(report,c,"All moves");

  report<<"Monte-Carlo : Time measurements (cpu time) : "<<endl;
  report<<"   time elapsed total : " << this->Timer << " seconds" << endl;

 }

 using namespace std;

 //********************************************************

 namespace  MC_Hybridization_Matsu { 
  void solve (boost::python::object parent) {

   boost::mpi::communicator c; // i.e. world = all nodes

   MC_Hybridization_Matsubara::parameters_type parms(parent);
   triqs::mc_tools::mc_runner<MC_Hybridization_Matsubara> s(parms, c);

   s.run(mc_tools::clock_callback(parms.value_or_default("MAX_TIME",-1)));
   s.collect_results();

   s.finalize(c);

  }
 };


