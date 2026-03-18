
/*
		Nom du fichier : Affichable.hpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Classe abstraite définissant une interface pour les objets affichables.
					  Cette interface impose l'implémentation des méthodes d'affichage et de gestion
					  de la couleur pour toute classe dérivée.
*/

#pragma once
#include <iostream>
#include <string>
#include "Couleur.hpp"

class Affichable {
	public:
		virtual ~Affichable() {}
		virtual void afficher(std::ostream& os) const = 0;
		virtual void changerCouleur(const Couleur& couleur) = 0;
};