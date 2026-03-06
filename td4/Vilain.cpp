#pragma once
#include "Vilain.hpp"

Vilain::Vilain(const std::string& nom, const std::string& parution, const std::string& objectif) : 
	Personnage::Personnage(nom, parution),
	objectif_(objectif) 
{}

Vilain::Vilain(const Vilain& autreVilain) : 
	Personnage::Personnage(autreVilain.obtenirNom(), autreVilain.obtenirParution()),
	objectif_(autreVilain.obtenirObjectif())
{}

void Vilain::changerCouleur(const Couleur& couleur) { Personnage::changerCouleur(couleur); }

void Vilain::afficherObjectif(std::ostream& os) const {
	os << "Objectif : "
		<< Personnage::enString(Personnage::obtenirCouleur()) + objectif_ + "\33[0m" << std::endl;
}

void Vilain::afficher(std::ostream& os) const {
	Personnage::afficher(os);

	afficherObjectif(os);
}