# ifndef PROTO_PROJET_HPP
# define PROTO_PROJET_HPP

# include"projet.hpp"

class ProtoProjet : public Projet {
	public:
		ProtoProjet();
		bool ajoute (const string nom, const int duree);
		bool ajoute (const string nom, const int duree, const int tacheid);
		bool ajoute (const string nom, const int duree, const int tache1, const int tache2); //TODO
};

#endif