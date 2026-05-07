/*
		Nom du fichier : VilainHeros.hpp
		Crée le 19 mars 2026
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient la définition de la classe VilainHeros, 
					  qui représente un personnage qui est à la fois un vilain et un héros dans un jeu vidéo.  
					  La classe hérite de la classe Vilain et de la classe Heros, 
					  et combine les attributs et les comportements des deux classes.  
					  Elle implémente les méthodes d'affichage et de changement de couleur pour personnaliser l'apparence du personnage lors de l'affichage.
*/

#pragma once
#include "Heros.hpp"
#include "Vilain.hpp"
#include <iostream>
using namespace std;

class VilainHeros : public Vilain, public Heros
{
public:
	VilainHeros(const Vilain& v, const Heros& h) :
		Personnage(v.getNom() + "-" + h.getNom(), v.getParutionJeu() + "-" + h.getParutionJeu()),
		Vilain(v),
		Heros(h),
		mission_(v.getObjectif() + " dans le monde de " + h.getParutionJeu())
	{}

	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		Vilain::afficherSpecificites(os);
		Heros::afficherSpecificites(os);
		os << "Mission spéciale: " << mission_ << endl;
	}

	void changerCouleur(ostream& os, int couleur) const override {
		Personnage::changerCouleur(os, couleur^3);
	}

private:
	string mission_;
};
