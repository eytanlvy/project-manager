#ifndef RUN_PROJET_HPP
#define RUN_PROJET_HPP

#include "tache.hpp"
#include "projet.hpp"
#include "proto_projet.hpp"

class RunProjet : public Projet {
	private:
		bool run(Tache *tache, bool force_dependencies);
		bool run(std::vector<Tache*> taches, bool force_dependencies);
	public:
		RunProjet(ProtoProjet proto_projet);
		bool run(const int tache_id, bool force_dependencies);
		bool run(std::vector<int> taches_id, bool force_dependencies);
};

#endif