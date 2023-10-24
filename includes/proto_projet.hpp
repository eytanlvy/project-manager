#ifndef PROTO_PROJET_HPP
#define PROTO_PROJET_HPP

#include "projet.hpp"

class RunProjet;

class ProtoProjet : public Projet {
	friend class RunProjet;
	private:
		void unsafe_hard_reset();
	public:
		ProtoProjet();
		bool ajoute (const std::string nom, const int duree);
		bool ajoute (const std::string nom, const int duree, const int tacheid);
		bool ajoute (const std::string nom, const int duree, const int tache1, const int tache2);

};

#endif