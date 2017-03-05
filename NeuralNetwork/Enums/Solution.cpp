#include "stdafx.h"
#include "Solution.h"

std::string to_string(const Solution solution)
{
	switch (solution)
	{
	case Ostre_zapalenie_wyrostka_robaczkowego: return "Ostre zapalenie wyrostka robaczkowego";
	case Zapalenie_uchylkow_jelit: return "Zapalenie uchylkow jelit";
	case Niedroznosc_mechaniczna_jelit: return "Niedroznosc mechaniczna jelit";
	case Perforowany_wrzod_trawienny: return "Perforowany wrzod trawienny";
	case Zapalenie_woreczka_zolciowego: return "Zapalenie woreczka zolciowego";
	case Ostre_zapalenie_trzustki: return "Ostre zapalenie trzustki";
	case Niecharakterystyczny_bol_brzucha: return "Niecharakterystyczny bol brzucha";
	case Inne_przyczyny_ostrego_bolu_brzucha: return "Inne przyczyny ostrego bolu brzucha";			
	}
	return "Unknown";
}
