
/*
		Nom du fichier : Personnage.hpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
		
		Description : Classe représentant un personnage affichable avec un nom, une date de parution et une couleur.
					  Cette classe hérite de Affichable et permet de gérer l'affichage d'un personnage,
					  ainsi que la modification et l'obtention de ses attributs (nom, parution, couleur).
*/

#pragma once
#include "Affichable.hpp"

class Personnage : public Affichable {
	public:
		Personnage(const std::string& nom, const std::string& parution);
		~Personnage() override = default;

		void changerCouleur(const Couleur& couleur) override;
		void afficher(std::ostream& os) const override;

		std::string enString(const Couleur& couleur) const;
		const Couleur obtenirCouleur() const { return couleur_; }
		const std::string& obtenirNom() const { return nom_; }
		const std::string& obtenirParution() const { return parution_; }

	protected:
		Personnage(const Personnage& autre);

	private:
		std::string nom_;
		std::string parution_;
		Couleur couleur_;
};
