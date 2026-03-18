
/*
		Nom du fichier : VilainHeros.cpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Implémentation de la classe VilainHeros combinant les comportements de Heros et Vilain.
					  Ce fichier définit les méthodes permettant de créer un personnage hybride à partir d’un héros
					  et d’un vilain, ainsi que d’afficher ses informations, incluant une mission spéciale générée.
*/

#pragma once
#include "VilainHeros.hpp"

const std::string RESET_COULEUR = "\33[0m";

VilainHeros::VilainHeros(const Heros& heros, const Vilain& vilain) : 
	Personnage((vilain.obtenirNom() + "-" + heros.obtenirNom()), (vilain.obtenirParution() + "-" + heros.obtenirParution())),
	Heros(heros),
	Vilain(vilain),
	missionSpeciale_(vilain.obtenirObjectif() + " dans le monde de " + heros.obtenirParution())
{}

void VilainHeros::afficherMissionSpeciale(std::ostream& os) const {
	os << Personnage::enString(Personnage::obtenirCouleur());
	os << "Mission spéciale : " << missionSpeciale_ + RESET_COULEUR << std::endl;
	os << RESET_COULEUR;
}

void VilainHeros::afficher(std::ostream& os) const {

	Personnage::afficher(os);

	Vilain::afficherObjectif(os);

	Heros::afficherListeEnnemiAllies(os);

	afficherMissionSpeciale(os);
}