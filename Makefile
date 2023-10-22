CPP = g++ -std=c++11 -Wall
OBJS = tache.o projet.o  # Liste de tous les fichiers objets nécessaires

all: tache

tache: $(OBJS)
	$(CPP) -o tache $(OBJS)

tache.o: tache.cpp
	$(CPP) -c tache.cpp

list.o: list.cpp
	$(CPP) -c list.cpp

clean:
	rm -f *.o

fclean: clean
	rm -f tache
