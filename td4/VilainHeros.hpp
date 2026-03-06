#pragma once

#include "Heros.hpp"
#include "Vilain.hpp"

class VilainHeros : public Heros, public Vilain {
	public:
		VilainHeros(const Heros& heros, const Vilain& vilain);
		~VilainHeros() override = default;
		void changerCouleur(const Couleur& couleur) override;
		void afficher(std::ostream& os) const override;

		void afficherMissionSpeciale(std::ostream& os) const;
		const std::string& obtenirMissionSpeciale() const { return missionSpeciale_; }

	private:
		std::string missionSpeciale_;
};

