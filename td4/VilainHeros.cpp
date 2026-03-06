#pragma once
#include "VilainHeros.hpp"

VilainHeros::VilainHeros(const Heros& heros, const Vilain& vilain) : 
	Personnage((heros.obtenirNom() + "-" + vilain.obtenirNom()), (heros.obtenirParution() + "-" + vilain.obtenirParution())),
	Heros(heros),
	Vilain(vilain),
	missionSpeciale_(vilain.obtenirObjectif() + " dans le monde de " + heros.obtenirParution())
{}

void VilainHeros::changerCouleur(const Couleur& couleur) { Personnage::changerCouleur(couleur); }

void VilainHeros::afficherMissionSpeciale(std::ostream& os) const {
	os << "Mission spéciale : "
	   << Personnage::enString(Personnage::obtenirCouleur()) + missionSpeciale_ + "\33[0m" << std::endl;
}

void VilainHeros::afficher(std::ostream& os) const {
	Personnage::afficher(os);

	Vilain::afficherObjectif(os);

	Heros::afficherListeEnnemiAllies(os);

	afficherMissionSpeciale(os);
}