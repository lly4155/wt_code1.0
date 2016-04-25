mix2x2 only handle the synchronous mode; 
with history initialize to 25%;


copy from c025/mix2x2   2013.6.07

delete the argc,agrv in emain.cpp, evgame.h evgame.cpp  0607

move incomeMatrix initialize to construct function 

0614
the IDY mode  ,pf has been divided by degree, so IDY do not concern the node  degree. change to the standard IDY
it do not affect the well-mixed network and lattice network, for agents have the same neighbors.

move mutation from all the update rule;

copyfrom mobile. 0620

change ga.cpp hsinit to hsinit(double rt=0.5),add the change of initatil cooperation  0620

copy from c01 . 0807
change ga.cpp mutation rate 0.01
change evgame.cpp hsinit only at the first generation.
add in ga.cpp gametype 24   in imitdyns()  game(); gameas();

copy from memgame/extend2x2\newmemcode


add node number >100, only  rand game 100 neighbors
20140303


