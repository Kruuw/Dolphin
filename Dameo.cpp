#include <string>
#include <iostream>



#include "Dameo.h"

using namespace std;
 
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
 
#define CLEAR "\033[2J"  // clear screen escape code 
const int H = 8;
 char P1= 'x';
 char P2= 'o';
const int ecart_it = 0; /// c'est lécart parametrable entre les deux jopueur
string coul1 = BOLDYELLOW;
string coul2 = BOLDMAGENTA;
string coul3 = RED;
/*--------------------------------------------------------------||||||----------La MAP-------*/
Damier::Damier()
{
	Dam.resize( H , vector<char>( H , '0' ) );
}
Damier::~Damier()
{
	Dam.clear();
}
void Damier::Remplir_plateau()
{
	nbpion = 0;
	int t = Dam.size()-1; 	//Taille tableau
	int T = Dam.size();
	int med, row, xow;
	if(T%2==0){				//paire 
		 med=T/2;
		 row = med-1-ecart_it;			//Parametre de safezone P2
		 xow = t-row;					//Parametre de safezone P1
	}
		else{ 
		med = (T/2)+1;
		row = med-2 - ecart_it;
		xow = t-row;
	}

	 for(int i = 0 ; i <= t ; i++)
	  {
  		while(i > row && i < xow ) i++;
  	  for(int j = 0 ; j <= t ; j++)
  	  {	  
     	if(i == 0){
     		Dam[i][j] = P2; 
  	  		//nbpion++;
   		  } 
    	 if(i == t){
    	 	Dam[i][j] = P1 ;
    	 	//nbpion++;
    	 	}
    	 if(i != 0 || i != t) 
    	 {
     	     if(i < row)
          {
     	       if(j >= i && j <= t-i)
            {
        	     Dam[i][j] = P2 ;
        	    // nbpion++;
            }
          }
        	  if(i > xow)
          {
            if(j > t-(i+1) && j < t-(t-(i+1)))
            {
              Dam[i][j] = P1 ;
              //nbpion++;
            }
          }
      }

    }
  }
}


void Damier::Affiche()
{
	for(int i = 0 ; i<=Dam.size()-1 ; i++)
	{
		for(int deco=0; deco<= Dam.size()-1; deco++)
		{
			
			if(i % 2 == 0 && deco % 2 == 0 || i % 2 != 0 && deco % 2 != 0) {
				cout<< BOLDCYAN <<"+---+"<<RESET;
				}
			else{
					cout<< BOLDWHITE <<"+---+"<<RESET;
				}
		}	
		cout<<endl;
		for(int j = 0; j<=Dam.size()-1 ;j++)
		{
			if(i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0) {
			cout<< BOLDCYAN <<"| " <<RESET;
			Affiche_Couleur(i,j);
			cout << BOLDCYAN <<" |"<< RESET;
			}
			else {
     		cout << BOLDWHITE<<"| "<<RESET ;
     		Affiche_Couleur(i,j) ;
     		cout<<BOLDWHITE<<" |" << RESET;
     		}
		}
		cout<<endl;
	}
		for(int deco2=0; deco2<= Dam.size()-1; deco2++)
		{
			if(deco2 % 2 != 0 ) {

				cout<< BOLDCYAN<<"+---+"<<RESET;
				}
			else{
				cout<< BOLDWHITE <<"+---+"<<RESET;
				}
		}
			cout<<endl;
		
}
int Damier::getP()
{
	int pions =0;
	for(int i = 0 ; i<= Dam.size()-1; i++)
	{
		for(int j=0; j<= Dam.size()-1 ; j++)
		{
			if(Dam[i][j] == P1)	pions++;
		}
	}
	cout <<"Il y a tant pion : "<<pions<<endl;
	return pions;
}


vector <vector <char> > Damier::get_DamSize()
{
	return Dam;
}

char Damier::Affiche_Couleur(int i, int j)
{
	if(Dam[i][j] != '0')									//Peut transmettre la couleur d'une fonction a une autre  en oubliant le RESET !!GAFFE au mélange de couleurs
	{
		if(Dam[i][j] == P2)	cout<<coul2<<Dam[i][j]<<RESET;		
		if(Dam[i][j] == P1)	cout<<coul1<<Dam[i][j]<<RESET;
	}
	else	cout<< ' ';
}
//---------------------------------------------------------|||||||||||------------Le joueur-------------------------
//---------------------------------------------------------|||||||||||||-----------------------------------------------------------
Joueur::Joueur(int serv) //: nb_pion(H*2)
{
//	pair < pair<int,int>,bool>  P( pair < pair <int,int>, bool> (pair <int,int> (0,0) ,false) ); 
//	pair<int,int> P(0,0);
	this->pion = serv ;
	Tion.resize( this->pion , pair< pair <int ,int  > , bool >( pair<int,int> (0,0) , false) );

}
Joueur::~Joueur()
{
	Tion.clear();
}

void Joueur::Affiche()
{
	for(int i = 0 ; i<=Tion.size()-1 ; i++)
	{
		cout<<i<<" ";

		cout<<Tion[i].first.first<<",";
		cout<<Tion[i].first.second;
	//	cout<<Tion[i].second;
		cout<<endl;
	}
}

void Joueur::get_Pion(vector <vector<char> > S, char P)
{
	int pions =0;
	for(int i = 0 ; i<= S.size()-1; i++)
	{
		for(int j=0; j<= S.size()-1 ; j++)
		{
			if(S[i][j] == P){
				Tion[pions].first.first = i;
				Tion[pions].first.second = j;
				pions++;
				}
		}
	}
	this->pion = pions;
}


void Joueur::Suppression(int x, int y)
{
	for(int i = 0 ; i<=Tion.size()-1 ; i++)
	{
		if(Tion[i].first.first == x && Tion[i].first.second == y)
		{
			Tion[i].first.first = Tion[this->pion-1].first.first ;
			Tion[i].first.second = Tion[this->pion-1].first.second ;
			Tion[i].second = Tion[this->pion-1].second ;
			Tion.pop_back();
		}
	}
}
/*
void Joueur::save(int x , int y , char P)
{
	if(
	int = 
}
*/






int main()
{    	
		Damier Dameo;
	//	Dameo.Affiche();
		Dameo.Remplir_plateau();
		Dameo.Affiche();

		vector <vector<char> > Size = Dameo.get_DamSize();
		int serv = Dameo.getP();
		cout <<serv<<endl;

 		Joueur J1(serv);
 	//	Joueur J2(serv);
 		
 		J1.get_Pion(Size, P1);
 	//	J2.get_Pion(Size, P2);
 		J1.Affiche();
 		J1.Suppression(6,5);
 		J1.Affiche();
		cout << endl;

    return 0;
 }
