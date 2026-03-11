#pragma once
#include "Heros.hpp"

const std::string RESET_COULEUR = "\33[0m";

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

	os << Personnage::enString(Personnage::obtenirCouleur());

	for (const std::string& nom : std::span(listeEnnemiAllies_)) {
		if (enemi == 1) {
			os << "Enemi : " << nom << std::endl;
			enemi = 0;
		}
		else {
			os << "Alliés : " << nom  << std::endl;
		}
	}

	os << RESET_COULEUR;
}

void Heros::afficher(std::ostream& os) const {
	Personnage::afficher(os);

	afficherListeEnnemiAllies(os);
}