#pragma once
#include "Personnage.hpp"
#include <vector>
#include <span>

class Heros : virtual public Personnage {
	public:
		Heros(const std::string& nom, const std::string& parution);
		Heros(const Heros& autre);
		~Heros() override = default;

		// void redimensionnerListe(unsigned int nouvelleTaille);
		void ajouterPersonnage(const std::string& nom);
		void changerCouleur(const Couleur& couleur) override;
		void afficher(std::ostream& os) const override;

		const std::vector<std::string>& obtenirListe() const { return listeEnnemiAllies_; }
		void afficherListeEnnemiAllies(std::ostream& os) const;

	private:
		std::vector<std::string> listeEnnemiAllies_;
};