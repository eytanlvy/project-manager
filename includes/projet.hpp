# ifndef PROJET_HPP
# define PROJET_HPP

# include "tache.hpp"
#include <cstdlib>
#include <ctime>

class Projet
{
	protected:
		vector <Tache*> taches;
	public:
		Projet();
		Projet(const Projet& other);
		Projet& operator=(const Projet& other);
		vector<Tache*> const consult_tasks() const;
		virtual ~Projet();
		pair<int,int> pick_two_random_tasks();
		Tache* contains(string name);
		Tache* contains(int id);
		void topological_sort();
		void cleanMarks();
	
};
ostream& operator<<( ostream &out , const Projet &x );

# endif