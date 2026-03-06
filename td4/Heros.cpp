#pragma once
#include "Heros.hpp"

Heros::Heros(const std::string& nom, const std::string& parution) : 
	Personnage::Personnage(nom, parution),
	listeEnnemiAllies_(std::vector<std::string>(0))
{}

Heros::Heros(const Heros& autreHeros) :
	Personnage::Personnage(autreHeros.obtenirNom(), autreHeros.obtenirParution()),
	listeEnnemiAllies_(autreHeros.obtenirListe())
{}

void Heros::ajouterPersonnage(const std::string& nom) { listeEnnemiAllies_.push_back(nom); }

void Heros::changerCouleur(const Couleur& couleur) { Personnage::changerCouleur(couleur); };

void Heros::afficherListeEnnemiAllies(std::ostream& os) const {
	unsigned int enemi = 1;

	for (const std::string& nom : std::span(listeEnnemiAllies_)) {
		if (enemi == 1) {
			os << Personnage::enString(Personnage::obtenirCouleur()) + "Enemi : "
			   << nom + "\33[0m" << std::endl;
			enemi = 0;
		}
		else {
			os << Personnage::enString(Personnage::obtenirCouleur()) + "Alliés : "
			   << nom + "\33[0m" << std::endl;
		}
	}
}

void Heros::afficher(std::ostream& os) const {
	Personnage::afficher(os);
	afficherListeEnnemiAllies(os);
}