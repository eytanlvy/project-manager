# ifndef PROJET_HPP
# define PROJET_HPP

# include "tache.hpp"

class Projet
{
	protected:
		vector <Tache*> taches;
	public:
		Projet();
		Projet(const Projet& other);
		Projet& operator=(const Projet& other);
		vector<Tache*> const getTaches() const;
		virtual ~Projet();
	
};
ostream& operator<<( ostream &out , const Projet &x );

# endif