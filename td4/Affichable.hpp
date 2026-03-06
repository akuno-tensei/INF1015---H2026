#pragma once
#include <iostream>
#include <string>
#include "Couleur.h"

class Affichable {
	public:
		virtual ~Affichable() {}
		virtual void afficher(std::ostream& os) const = 0;
		virtual void changerCouleur(const Couleur& couleur) = 0;
};