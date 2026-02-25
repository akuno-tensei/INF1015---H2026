/*
	Fichier : lectureFichierJeux.hpp
	Auteur : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
	Crée le : 2026-02-10
	Modifié le : 2026-02-24

	Description: Ce fichier contient les fonctions pour lire le fichier binaire contenant les jeux et les concepteurs, 
	chercher un concepteur dans la liste de jeux selon un nom donné, créer des concepteurs et des jeux, et créer la liste de jeux à partir du fichier binaire.
*/


// Fonctions pour lire le fichier binaire.
#pragma once
#include "Jeu.hpp"
#include "Concepteur.hpp"
#include <iostream>

using ListeJeux = Liste<Jeu>;

std::shared_ptr<Concepteur> chercherConcepteur(ListeJeux& listeJeux, const std::string& nom);
std::shared_ptr<Concepteur> lireConcepteur(ListeJeux& lj, std::istream& f);
std::shared_ptr<Jeu> lireJeu(std::istream& f, ListeJeux& lj);
ListeJeux creerListeJeux(const std::string& nomFichier);
