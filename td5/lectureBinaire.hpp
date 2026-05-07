/*
		Nom du fichier : lectureBinaire.hpp
		Crée le 19 mars 2026
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient des fonctions pour lire des données à partir de fichiers binaires.  
					  Les fonctions permettent de lire des entiers de 8 bits, des entiers de 16 bits, 
					  et des chaînes de caractères à partir d'un flux d'entrée.  
					  Ces fonctions sont utilisées pour lire les données des héros et vilains à partir des fichiers binaires dans le main.cpp.
*/

#pragma once
#include <fstream>
using namespace std;
// Entêtes copiées du main.cpp fourni (ou du fichier du TD3):

using UInt8  = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(istream& fichier);
UInt16 lireUint16(istream& fichier);
string lireString(istream& fichier);
