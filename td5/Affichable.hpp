/*
		Nom du fichier : Affichable.hpp
		Crée le 19 mars 2026
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient la définition de la classe Affichable, 
					  qui est une classe abstraite servant de base pour les classes qui peuvent être affichées.  
					  Elle définit des méthodes virtuelles pures pour l'affichage et le changement de couleur, 
					  que les classes dérivées doivent implémenter.
*/

#pragma once
#include <iostream>
using namespace std;

class Affichable
{
public:
	virtual ~Affichable() = default;  // Important!  Toute classe polymorphe doit avoir un destructeur virtuel, sinon la destruction par la classe de base est "undefined behavior".
	virtual void afficher(ostream&) const = 0;
	virtual void changerCouleur(ostream&, int laCouleur) const = 0;
};
