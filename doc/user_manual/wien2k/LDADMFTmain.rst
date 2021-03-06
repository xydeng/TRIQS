.. index:: LDA+DMFT calculation

.. _LDADMFTmain:

The LDA+DMFT calculation
========================

After having set up the hdf5 arxive, we can now do our LDA+DMFT calculation. It consists of
initialisation steps, and the actual DMFT self consistency loop.

.. index:: initialisation of LDA+DMFT

Initialisation of the calculation
---------------------------------

Before doing the calculation, we have to intialize all the objects that we will need. The first thing is the 
:class:`SumK_LDA` class. It contains all basic routines that are necessary to perform a summation in k-space 
to get the local quantities used in DMFT. It is initialized by::

  from pytriqs.Wien2k.SumK_LDA import *
  SK = SumK_LDA(HDFfile = filename)

The only necessary parameter is the filename of the hdf5 archive. In addition, there are some optional parameters:

  * `mu`: The chemical potential at initialization. This value is only used, if there is no other value found in the hdf5 arxive. Standard is 0.0
  * `hfield`: External magnetic field, standard is 0.0
  * `UseLDABlocs`: If true, the structure of the density matrix is analysed at initialisation, and non-zero matrix elements 
    are identified. The DMFT calculation is then restricted to these matrix elements, yielding a more efficient solution of the 
    local interaction problem. Also degeneracies in orbital and spin space are recognised, and stored for later use. Standard value is `False`. 
  * `LDAdata`, `Symmcorrdata`, `ParProjdata`, `Symmpardata`, `Bandsdata`: These string variables define the subgroups in the hdf5 arxive,
    where the corresponding information is stored. The standard values are consistent with the standard values in :ref:`interfacetowien`.

At initialisation, the necessary data is read from the hdf5 file. If we restart a calculation from a previous one, also the information on
the degenerate shells, the block structure of the density matrix, the chemical potential, and double counting correction are read.

.. index:: Multiband solver

Setting up the Multi-Band Solver
--------------------------------

There is a module that helps setting up the multiband CTQMC solver. It is loaded and initialized by::

  from pytriqs.Wien2k.Solver_MultiBand import *
  S = Solver_MultiBand(Beta, U_interact, J_Hund, Norb)

The necessary parameters are the inverse temperature `Beta`, the Coulomb interaction `U_interact`, the Hund's rule coupling `J_Hund`,
and the number of orbitals `Norb`. There are again several optional parameters that allow to modify the local Hamiltonian to
specific needs. They are:

  * `GFStruct`: Contains the block structure of the local density matrix. Has to be given in the format as calculated by :class:`SumK_LDA`.
  * `map`: If `GFStruct` is given as parameter, also `map` has to be given. This is the mapping from the block structure to a general 
    up/down structure.
  * `useMatrix`: If `True`, the interaction matrix is calculated from Slater integrals, which are calculated from `U_interact` and 
    `J_Hund`. Otherwise, a Kanamori representation is used. Attention: We define the intraorbital interaction as 
    `U_interact+2J_Hund`, the interorbital interaction for opposite spins as `U_interact`, and interorbital for equal spins as 
    `U_interact-J_Hund`!
  * `T`: A matrix that transforms the interaction matrix from spherical harmonics, to a symmetry adapted basis. Only effective, if 
    `useMatrix=True`.
  * `l`: Orbital quantum number. Again, only effective for Slater parametrisation.
  * `deg_shells`: A list that gives the degeneracies of the orbitals. It is used to set up a global move of the CTQMC solver.
  * `use_spinflip`: If `True`, the full rotationally-invariant interaction is used. Otherwise, only density-density terms are
    kept in the local Hamiltonian.
  * `dimreps`: If only a subset of the full d-shell is used a correlated orbtials, one can specify here the dimensions of all the subspaces
    of the d-shell, i.e. t2g and eg. Only effective for Slater parametrisation.
  * `irep`: The index in the list `dimreps` of the subset that is used. Only effective for Slater parametrisation.

Most of above parameters can be taken directly from the :class:`SumK_LDA` class, without defining them by hand. We will see a specific example 
at the end of this tutorial.

After initialisation, several other CTQMC parameters can be set (see CTQMC doc). The most important are:

  * `S.N_Cycles`: Number of QMC cycles per node.
  * `S.N_Warmup_Cycles`: Number of iterations used for thermalisation




.. index:: LDA+DMFT loop, one-shot calculation

Doing the DMFT loop
-------------------

Having initialised the SumK class and the Solver, we can proceed with the DMFT loop itself. As explained in the tutorial, we have to 
set up the loop over DMFT iterations and the self-consistency condition::

  N_Loops = 5
  for IterationNumber in range(N_Loops) :            # start the DMFT loop

          SK.put_Sigma(Sigmaimp = [ S.Sigma ])       # Put self energy to the SumK class
          Chemical_potential = SK.find_mu()          # find the chemical potential for the given density
          S.G <<= SK.extract_Gloc()[0]               # extract the local Green function
          S.G0 <<= inverse(S.Sigma + inverse(S.G))   # finally get G0, the input for the Solver

          S.Solve()                                  # now solve the impurity problem

	  dm = S.G.density()                         # density matrix of the impurity problem  
          SK.SetDoubleCounting( dm, U_interact = U, J_Hund = J, useDCformula = DC_type)     # Set the double counting term
          SK.save()                                  # save everything to the hdf5 arxive

These basic steps are enough to set up the basic DMFT Loop. For a detailed description of the :class:`SumK_LDA` routines,
see the reference manual. After the self-consistency steps, the solution of the Anderson impurity problem is calculation by CTQMC. 
Different to model calculations, we have to do a few more steps after this, because of the double-counting correction. We first 
calculate the density of the impurity problem. Then, the routine `SetDoubleCounting` takes as parameters this density matrix, the 
Coulomb interaction, Hund's rule coupling, and the type of double-counting that should be used. Possible values for `useDCformula` are:

  * `0`: Full-localised limit
  * `1`: DC formula as given in K. Held, Adv. Phys. 56, 829 (2007).
  * `2`: Around-mean-field

At the end of the calculation, we can save the Greens function and self energy into a file::

  from pytriqs.Base.Archive import HDF_Archive
  import pytriqs.Base.Utility.MPI as MPI
  if MPI.IS_MASTER_NODE():
      R = HDF_Archive("SingleSiteBethe.h5",'w')
      R["G"] = S.G
      R["Sigma"] = S.Sigma

This is it! 

These are the essential steps to do a one-shot LDA+DMFT calculation. For full charge-self consistent calculations, there are some more things
to consider, which we will see later on.
