#pragma once
#include <iostream>
#include <string>

class Concepteur {
public:
	// Un constructeur par défaut et un constructeur paramétré.
	Concepteur() {
		nom_ = "inconnu";	
		anneeNaissance_ = 0;
		pays_ = "inconnu";
	}

	Concepteur(const std::string& nom, int anneNaissance, const std::string& pays) {
		nom_ = nom;
		anneeNaissance_ = anneNaissance;
		pays_ = pays;
	}

	const std::string& getNom() const     { return nom_; }
	void setNom(std::string nom)          { nom_ = move(nom); }
	int getAnneeNaissance() const         { return anneeNaissance_; }
	void setAnneeNaissance(int annee)     { anneeNaissance_ = annee; }
	const std::string& getPays() const    { return pays_; }
	void setPays(std::string pays)        { pays_ = move(pays); }

private:
	std::string nom_;
	int anneeNaissance_;
	std::string pays_;
};
