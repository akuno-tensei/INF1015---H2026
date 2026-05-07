/*
		Nom du fichier : Vilain.hpp
		Crée le 19 mars 2026
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient la définition de la classe Vilain, 
					  qui représente un vilain dans un jeu vidéo.  
					  La classe hérite de la classe Personnage et ajoute un attribut spécifique, 
					  l'objectif du vilain.  
					  Elle implémente les méthodes d'affichage et de changement de couleur pour personnaliser l'apparence du vilain lors de l'affichage.
*/

#pragma once
#include "Personnage.hpp"
#include <string>
#include <iostream>
using namespace std;

class Vilain : public virtual Personnage
{
public:
	// Vilain() = default;  // Non nécessaire.
	
	//Vilain(const string& nom, const string& jeu, const string& objectif)  // Non nécessaire si on construit toujour en lisant du istream.
	//	: Personnage(nom, jeu), objectif_(objectif) {}

	Vilain(istream& fichier) : Personnage(fichier), objectif_(lireString(fichier)) {}

	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		afficherSpecificites(os);
	}
	void afficherSpecificites(ostream& os) const {  // Pourrait être protected.
		os << "Objectif : " << objectif_ << "\n";
	}
	void changerCouleur(ostream& os, int couleur) const override {
		Personnage::changerCouleur(os, couleur^2);
	}

	// Getter nécessaire pour la construction du VilainHero (puisque généralement les attributs sont private et non protected):
	const string& getObjectif() const { return objectif_; }

private:
	string objectif_;
};
