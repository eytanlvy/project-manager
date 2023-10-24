#ifndef RUN_PROJET_HPP
#define RUN_PROJET_HPP

#include "tache.hpp"
#include "projet.hpp"
#include "proto_projet.hpp"

class RunProjet : public Projet {
	private:
		void run(const Tache *tache);
		void run(std::vector<Tache*> taches);
	public:
		RunProjet(ProtoProjet proto_projet);
		void run(const int tache_id);
		void run(std::vector<int> taches_id);
};

#endif