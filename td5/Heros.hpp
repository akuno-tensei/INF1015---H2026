/*
		Nom du fichier : Heros.hpp
		Crée le 19 mars 2026
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient la définition de la classe Heros, 
					  qui représente un héros dans un jeu vidéo.  
					  La classe hérite de la classe Personnage 
					  et ajoute des attributs spécifiques tels que l'ennemi principal et les alliés du héros.  
					  Elle implémente également les méthodes d'affichage et 
					  de changement de couleur pour personnaliser l'apparence du héros lors de l'affichage.
*/

#pragma once
#include "Personnage.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "cppitertools/range.hpp"
using namespace std;
using namespace iter;

class Heros : public virtual Personnage
{
public:
	Heros() = default;
		
	Heros(const string& nom, const string& jeu, const string& ennemi)  // Non nécessaire si on construit toujour en lisant du istream.
		: Personnage(nom, jeu), ennemi_(ennemi) {}
	
	Heros(istream& fichier) : Personnage(fichier), ennemi_(lireString(fichier)) {
		for ([[maybe_unused]] int i : range(lireUint8(fichier)))
			ajouterAllie(lireString(fichier));
	}
	
	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		afficherSpecificites(os);
	}
	void afficherSpecificites(ostream& os) const {  // Pourrait être protected.
		os << "Ennemi : " << ennemi_ << "\n";
		os << "Alliés :\n";
		for (auto&& allie : allies_)
			os << "\t" << allie << "\n";
	}
	void changerCouleur(ostream& os, int couleur) const override {
		Personnage::changerCouleur(os, couleur^1);  // Pas demandé directement dans l'énoncé, mais c'est bon d'avoir des couleurs différentes pour les différentes classes, tant qu'à avoir une méthode vituelle pour ça...
	}
	
	void ajouterAllie(const string& allie) { allies_.push_back(allie); }

	// Les getters sont non nécessaires:
	const string& getEnnemi() { return ennemi_; }
	vector<string>& getAllies() { return allies_; }

private:
	string ennemi_;
	vector<string> allies_;
};
