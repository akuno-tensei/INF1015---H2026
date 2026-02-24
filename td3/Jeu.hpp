#pragma once
#include <string>
#include "Concepteur.hpp"
#include "Liste.hpp"

using ListeConcepteurs = Liste<Concepteur>;

class Jeu {
public:
	//TODO: un constructeur par défaut et un constructeur paramétré.
	Jeu() {
		titre_ = "Inconnu";
		anneeSortie_ = 0;
		developpeur_ = "Inconnu";
	}

	Jeu(std::string titre, unsigned anneeSortie, std::string developpeur) {
		titre_ = titre;
		anneeSortie_ = anneeSortie;
		developpeur_ = developpeur;
	}

	Jeu(const Jeu& autre) {
		titre_ = autre.titre_;
		anneeSortie_ = autre.anneeSortie_;
		developpeur_ = autre.developpeur_;
		listeConcepteurs_ = autre.listeConcepteurs_;  // La classe Liste doit faire une copie profonde de ses éléments.
	}

	const std::string& getTitre() const     { return titre_; }
	void setTitre(std::string titre)        { titre_ = move(titre); }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(std::string developpeur) { developpeur_ = move(developpeur); }

	// surchage de l'opérateur = 
	Jeu& operator=(const Jeu& autre) {
		if (this != &autre) {
			titre_ = autre.titre_;
			anneeSortie_ = autre.anneeSortie_;
			developpeur_ = autre.developpeur_;
			listeConcepteurs_ = autre.listeConcepteurs_;  // La classe Liste doit faire une copie profonde de ses éléments.
		}
		return *this;
	}

	//TODO: Pouvoir accéder à la liste de concepteurs.
	ListeConcepteurs& accederListeConcepteurs() { return listeConcepteurs_; }

	// Méthode pour changer un concepteur de la liste en connaissant son indice
	void changerConcepteur(unsigned indice, std::shared_ptr<Concepteur> autreConcepteur) {
		listeConcepteurs_[indice] = autreConcepteur;
	}

	//TODO: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	std::shared_ptr<Concepteur> trouverConcepteur(const std::function<bool(std::shared_ptr<Concepteur>)>& critere) const {
		return listeConcepteurs_.trouverElement(critere);
	}

private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;

	//TODO: Attribut de la liste des concepteurs du jeu
	ListeConcepteurs listeConcepteurs_;
};

// struct ListeJeux{};  //TODO: Remplacer cette définition (qui est ici juste pour que le code fourni compile) pour que ListeJeux soit une Liste<Jeu> .