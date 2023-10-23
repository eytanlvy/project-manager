# ifndef TACHE_HPP
# define TACHE_HPP

# include <iostream>
# include <vector>
# include <string>
# include <cassert>  

using namespace std;

class Tache
{
	private:
		string nom;
		int id;
		int duree;
		bool realisee;
		vector<Tache*> dependances;

		static int lastId;
	public:
		Tache(const string& nom, int duree);
		Tache(const Tache& other);
		Tache& operator=(const Tache& other);
		string const getNom() const;
		int const getId() const;
		int const getDuree() const;
		bool const getRealisee() const;
		vector<Tache*> const getDependances() const;
		bool realise();
		bool depends_from(Tache & x);
		bool ajouteDependance(Tache & x);
		int dureeParal();
		virtual ~Tache();
};

ostream& operator<<( ostream &out , const Tache &x );

# endif