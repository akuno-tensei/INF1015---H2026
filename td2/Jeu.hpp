/*
	Fichier : Jeu.hpp
	Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)
	Date : 11 février 2026
	Crée le 23 janvier 2026
*/

#pragma once
#include <string>
#include "ListeDesigners.hpp"

struct Jeu
{
	std::string titre;
	unsigned int anneeSortie;
	std::string developpeur;
	ListeDesigners designers;
};
