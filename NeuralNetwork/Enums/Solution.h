#pragma once

#include <string>

enum Solution
{
	Ostre_zapalenie_wyrostka_robaczkowego = 0,
	Zapalenie_uchylkow_jelit,
	Niedroznosc_mechaniczna_jelit,
	Perforowany_wrzod_trawienny,
	Zapalenie_woreczka_zolciowego,
	Ostre_zapalenie_trzustki,
	Niecharakterystyczny_bol_brzucha,
	Inne_przyczyny_ostrego_bolu_brzucha
};

std::string to_string(const Solution solution);
