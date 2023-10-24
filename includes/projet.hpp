#ifndef PROJET_HPP
#define PROJET_HPP

#include "tache.hpp"
#include <cstdlib>
#include <ctime>

class Projet
{
	protected:
		std::vector <Tache*> taches;
	public:
		Projet();
		Projet(const Projet& other);
		Projet& operator=(const Projet& other);
		std::vector<Tache*> const consult_tasks() const;
		virtual ~Projet();
		std::pair<int,int> pick_two_random_tasks();
		Tache* contains(std::string name);
		Tache* contains(int id);
		void topological_sort();
		void cleanMarks();
	
};
std::ostream& operator<<( std::ostream &out , const Projet &x );

#endif