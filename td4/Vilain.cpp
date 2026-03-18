
/*
		Nom du fichier : Vilain.cpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Implémentation de la classe Vilain, incluant la gestion et l'affichage de son objectif.
					  Ce fichier définit les méthodes de la classe Vilain, permettant d'initialiser un vilain,
					  de gérer son objectif et d'afficher ses informations avec mise en couleur.
*/

#pragma once
#include "Vilain.hpp"

const std::string RESET_COULEUR = "\33[0m";

Vilain::Vilain(const std::string& nom, const std::string& parution, const std::string& objectif) : 
	Personnage::Personnage(nom, parution),
	objectif_(objectif) 
{}

Vilain::Vilain(const Vilain& autreVilain) : 
	Personnage::Personnage(autreVilain.obtenirNom(), autreVilain.obtenirParution()),
	objectif_(autreVilain.obtenirObjectif())
{}

void Vilain::afficherObjectif(std::ostream& os) const {
	os << Personnage::enString(Personnage::obtenirCouleur());
	os << "Objectif : " << objectif_ << std::endl;
	os << RESET_COULEUR;
}

void Vilain::afficher(std::ostream& os) const {
	Personnage::afficher(os);

	afficherObjectif(os);
}