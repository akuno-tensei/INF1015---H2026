
/*
		Nom du fichier : Personnage.cpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Implémentation de la classe Heros, incluant la gestion et l'affichage des ennemis et alliés.
					  Ce fichier définit les méthodes permettant d'initialiser un personnage, de modifier sa couleur,
					  et d'afficher ses informations avec des codes ANSI selon la couleur sélectionnée.
*/

#pragma once
#include "Personnage.hpp"

const std::string RESET_COULEUR = "\33[0m";

Personnage::Personnage(const std::string& nom, const std::string& titreJeu)	: 
	nom_(nom), 
	parution_(titreJeu), 
	couleur_(Couleur::BLANC) 
{}

Personnage::Personnage(const Personnage& autre) : 
	nom_(autre.nom_), 
	parution_(autre.parution_), 
	couleur_(autre.couleur_) 
{}

void Personnage::changerCouleur(const Couleur& couleur) { 
	couleur_ = couleur;
}

void Personnage::afficher(std::ostream& os) const {
	os << enString(couleur_);
	os << "Nom : " << nom_ << std::endl
	   << "Parution : " << parution_ << std::endl;
	os << RESET_COULEUR;
}

std::string Personnage::enString(const Couleur& couleur) const {
	switch (couleur) {
	case Couleur::NOIR: return "\33[30m";
	case Couleur::ROUGE: return "\33[31m";
	case Couleur::VERT: return "\33[32m";
	case Couleur::JAUNE: return "\33[33m";
	case Couleur::BLEU: return "\33[34m";
	case Couleur::MAGENTA: return "\33[35m";
	case Couleur::CYAN: return "\33[36m";
	case Couleur::BLANC: return "\33[37m";
	case Couleur::NOIR_BRILLANT: return "\33[90m";
	case Couleur::ROUGE_VIF: return "\33[91m";
	case Couleur::VERT_VIF: return "\33[92m";
	case Couleur::JAUNE_VIF: return "\33[93m";
	case Couleur::BLEU_VIF: return "\33[94m";
	case Couleur::MAGENTA_VIF: return "\33[95m";
	case Couleur::CYAN_BRILLANT: return "\33[96m";
	case Couleur::BLANC_ECLATANT: return "\33[97m";
	default: return "inconnu";
	}
}
