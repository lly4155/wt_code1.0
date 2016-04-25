
evgame : emain.o macro.o evgame.o ga.o network.o
	g++ -o mpgame -fopenmp  evgame.o  ga.o network.o macro.o  emain.o
# -fopenmp
emain.o: emain.cpp
#	g++ -c -g emain.cpp
	g++ -c  emain.cpp
evgame.o : evgame.cpp evgame.h 
#	g++ -c -g -fopenmp    evgame.cpp  
	g++ -c  -fopenmp    evgame.cpp  
ga.o : ga.cpp ga.h
#	g++ -c -g ga.cpp
	g++ -c  ga.cpp
network.o : network.cpp network.h
#	g++ -c -g  network.cpp
	g++ -c   network.cpp

macro.o: macro.cpp macro.h
#	g++ -c -g  macro.cpp 
	g++ -c   macro.cpp 
clean:
	rm *.o *.gch  *.txt *.mat  log mpgame


