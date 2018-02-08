
#ifndef DAMEO_H
#define DAMEO_H
#include <iostream>
#include <vector>
#include <utility>

class Damier
{
	std::vector <std::vector <char> > Dam ; 
	friend class Joueur;
	int nbpion = 0;
	public:
		Damier();
		void Affiche();
		char Affiche_Couleur(int i, int j);
		void Remplir_plateau();
		std::vector <std::vector <char> > get_DamSize();
		int getP();
		~Damier();

};

class Joueur
{
	std::vector <std::pair <std::pair<int,int> ,bool> > Tion; 
	friend class Damier; 
	int pion;
	char *J;			//caractere de jeu
	public:
		Joueur(int s);
		void Affiche();
		void get_Pion(std::vector <std::vector <char> > Dam , char P);
		void Perpion(int x, int y);
		~Joueur();
};


#endif