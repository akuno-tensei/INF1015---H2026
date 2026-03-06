#pragma once
#include "Personnage.hpp"

class Vilain : virtual public Personnage {
	public:
		Vilain(const std::string& nom, const std::string& parution, const std::string& objectif);
		Vilain(const Vilain& autreVilain);
		~Vilain() override = default;

		void changerCouleur(const Couleur& couleur) override;
		void afficher(std::ostream& os) const override;

		void afficherObjectif(std::ostream& os) const;
		const std::string& obtenirObjectif() const { return objectif_; }

	private:
		std::string objectif_;
};