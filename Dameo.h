
#ifndef DAMEO_H
#define DAMEO_H
#include <iostream>
#include <vector>
#include <utility>

class Joueur
{
	std::vector <std::pair <std::pair<int,int> ,bool> > Pion; 
	friend class Damier; 
	char inf;
	public:
		Joueur();
		void Affiche();
		void get_Pion(Joueur O);
};

class Damier
{
	std::vector <std::vector <char> > Dam ; 
	friend class Joueur;
	int nb_pion;
	public:
		Damier();
		void Affiche();
		char Affiche_Couleur(int i, int j);
		void Remplir_plateau();
		//virtual ~Damier();

};

#endif