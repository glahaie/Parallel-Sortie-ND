Parallel-Sortie-ND
==================

This was a project done for INF7235. We chose to analyse and parallelize
a part of the application [SORTIE-ND](http://www.sortie-nd.org/), an individual
forest simulator designed to study neighborhood processes. We worked on the
7.01 beta code for this project.

Since this is a proof of concept, we only implemented one change: we tried to
parallelize the basic light behavior, since this is the most important and, for
our test files, at least 50% of the computing time was used for this behavior.
Most of the changes are there in one file: [sortie_tbb/Core_Model/Behaviors/LightOrg.cpp](https://github.com/glahaie/Parallel-Sortie-ND/blob/master/sortie_tbb/Core_Model/Behaviors/LightOrg.cpp), in the
DoLightAssignments method.

Other modifications were mostly to be able to choose the method of
parallelization and to remove some race conditions. For some of the light
behaviors, the race conditions would require major changes to the code, so they
were not corrected.

We used [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/) to parallelize the light
behavior: three different approaches were tested: parallel_for (this required
first putting all trees in a vector), parallel_pipeline and task groups.

We used the unit tests written by the devs to check our changes. At the moment
it is only possible to run one test, running multiple tests causes problems with
some static fields in the simulations.
