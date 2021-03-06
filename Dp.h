﻿
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
		void Suppression(int x, int y);
		~Damier();

};

class Joueur
{
	std::vector <std::pair <std::pair<int,int> ,bool> > Tion; 
	friend class Damier; 
	int pion;
	char *c;			//caractere de jeu
	public:
		Joueur(int s);
		void Affiche();
		void get_Pion(std::vector <std::vector <char> > Dam , char P);
		void Suppression(int x, int y);
		~Joueur();
};


#endif