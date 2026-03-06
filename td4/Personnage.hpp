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
