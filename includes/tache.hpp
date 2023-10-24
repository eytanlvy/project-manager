#ifndef TACHE_HPP
#define TACHE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cassert>  

class Tache
{
	private:
		std::string nom;
		int id;
		int duree;
		bool realisee;
		std::vector<Tache*> dependances;
		static int lastId;
		bool marked{false};

	public:
		Tache(const std::string& nom, int duree);
		Tache(const Tache& other);
		const Tache& operator=(const Tache& other);
		std::string const getNom() const;
		int const getId() const;
		int const getDuree() const;
		bool const getRealisee() const;
		std::vector<Tache*> const getDependances() const;
		bool realise();
		void realise_cascade();
		bool depends_from(Tache & x);
		bool ajouteDependance(Tache & x);
		int dureeParal();
		virtual ~Tache();

		const bool is_marked() const;
		void mark(bool value);
		void PP_postfixe(std::vector<Tache*>& sortedTasks);

};

std::ostream& operator<<( std::ostream &out , const Tache &x );

#endif