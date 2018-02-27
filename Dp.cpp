#include <string>
#include <utility>
#include <iostream>

#include <fstream>
#include <sstream>


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
int H = 8;
 char P1= 'x';
 char P2= 'o'; // ou < et > pour le mode hard
int ecart_it = 0; /// c'est lécart parametrable entre les deux jopueur
string coul1 = BOLDYELLOW;
string coul2 = BOLDMAGENTA;
string coul3 = RED;

string border1 = BOLDCYAN;
string border2 = BOLDWHITE;

int SaisieEntier();
void ViderBuffer();
bool verif_p(string p);
bool verif_p(string p,string p1);
string choixColor();



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
	for(int h = 0; h<=Dam.size()-1; h++)	cout<<"  "<<h<<"  ";
	cout<<endl;
	for(int i = 0 ; i<=Dam.size()-1 ; i++)
	{
		
		for(int deco=0; deco<= Dam.size()-1; deco++)
		{
			
			if(i % 2 == 0 && deco % 2 == 0 || i % 2 != 0 && deco % 2 != 0) {
				cout<< border1 <<"+---+"<<RESET;
				}
			else{
					cout<< border2 <<"+---+"<<RESET;
				}
		}	
		cout<<endl;

		for(int j = 0; j<=Dam.size()-1 ;j++)
		{
			if(i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0) {
			cout<< border1 <<"| " <<RESET;
			Affiche_Couleur(i,j);
			cout << border1 <<" |"<< RESET;
			}
			else {
     		cout << border2 <<"| "<<RESET ;
     		Affiche_Couleur(i,j) ;
     		cout<< border2 <<" |" << RESET;
     		}
		}
		cout<<"	|"<<i;
		cout<<endl;
	}
		for(int deco2=0; deco2<= Dam.size()-1; deco2++)
		{
			if(deco2 % 2 != 0 ) {

				cout<< border1 <<"+---+"<<RESET;
				}
			else{
				cout<< border2 <<"+---+"<<RESET;
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

void Damier::Suppression(int x, int y)
{
	if(Dam[x][y] != '0'){
		Dam[x][y] = '0';
		cout <<"lol";
		}
	else cout<<endl<<"Erreur de traitement !"<<endl;

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
				this->Tion[pions].first.first = i;
				this->Tion[pions].first.second = j;
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
			cout<<"		Le pion ("<<x<<","<<y<<")"<<endl;
				Tion[i].first.first = Tion[pion-1].first.first ;
				Tion[i].first.second = Tion[pion-1].first.second ;
			Tion[i].second = Tion[pion-1].second ;
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

void estDame(int)
{


}

void Miam(Joueur& j,Damier &D, int a, int b)
{
	j.Suppression(a,b);
	D.Suppression(a,b);

}

void Deplacement(Joueur& J, Damier& D, int a , int b, int x, int y)
{
	if(Dam[x][y]==J->c && Dam[a][b] ==)
	{
	/*	

bool Plateau_jeu::Verify_mange(int a, int b, bool J1)
{
  string p1 = mesJoueurs[0]->get_Pion() ;
  string p2 = mesJoueurs[1]->get_Pion() ;

  for(int i = a ; i < H ; i++)
  {
    for(int j = b ; j < H ; j++)
    {
      if(J1 == true)
      {
        if(Dameo[i][j] == p1)
        {
          int x = i+1 ;

          if(Dameo[x][j] == p2)
          {
            int y = x+1 ;

            if(Dameo[y][j] == ".")
            {
                Mange_pion(i, j, true) ;
                Verify_mange(i, j, true) ;
                return true ;
            }
          }
        }
      }
      else
      {
        if(Dameo[i][j] == p2)
        {
          int x = i-1 ;

          if(Dameo[x][j] == p1)
          {
            int y = x-1 ;
            if(Dameo[y][j] == ".")
            {
              Mange_pion(i, j, false) ;
              Verify_mange(i, j, false) ;
              return true ;
            }
          }
        }
      }
    }
  }

}




void Plateau_jeu::Mange_pion(int x, int y, bool J1)
{
  cout << "------------eavrabevhrfbrbbefhrebv" << endl ;
  if(J1 == true)
  {
    if(x > N) return ;
    else
    {
      int i = x+2 ;
      Dameo[x][y] = "." ;
      Dameo[x+1][y] = "." ;
      Dameo[i][y] = mesJoueurs[0]->get_Pion() ;
      mesJoueurs[1]->Perd_pion() ;
    }
  }
  else
  {
    int i = x-2 ;
    int j = x-1 ;
    if(i < 0 || j < 0) return ;
    else
    {
      Dameo[x][y] = "." ;
      Dameo[x-1][y] = "." ;
      Dameo[i][y] = mesJoueurs[1]->get_Pion() ;
      mesJoueurs[0]->Perd_pion() ;
    }
  }
}*/
int main()
{    
		Damier Dameo;
		Dameo.Affiche();
		Dameo.Remplir_plateau();
		system("clear");
		Dameo.Affiche();

		vector <vector<char> > Size = Dameo.get_DamSize();
		int serv = Dameo.getP();
		cout <<serv<<endl;

 		Joueur J1(serv);
 		Joueur J2(serv);
 		J1->c=P1;
 		J2->c=P2;
 		J1.get_Pion(Size, P1);
 		J2.get_Pion(Size, P2);
 		system("clear");
 		Miam(J1,Dameo,5,5);		//manger

 		J1.Affiche();
 		Dameo.Affiche();

		cout << endl;


    return 0;
}



string choixColor()
{
	int choix;
	cout<<BOLDYELLOW<<"1: couleur jaune"<<RESET<<endl;
	cout<<BOLDRED<<"2: couleur rouge"<<RESET<<endl;
	cout<<BOLDGREEN<<"3: couleur vert"<<RESET<<endl;
	cout<<BOLDBLUE<<"4: couleur bleu"<<RESET<<endl;
	cout<<BOLDMAGENTA<<"5: couleur Magenta??"<<RESET<<endl;
	do{
			cout<<"Votre couleur : " ; // Et aussi rajouté l'écart inter pion changeable;
			cin>> choix;
	}while(choix > 5 || choix < 1);
	switch(choix){
			case 1 : return BOLDYELLOW;
			case 2 : return BOLDRED;
			case 3 : return BOLDGREEN;
			case 4 : return BOLDBLUE;
			case 5 : return BOLDMAGENTA;
			default : return BOLDYELLOW;
			}
} 

bool verif_p(string p)
{
	if(p.size() > 1)	return false;
	else{
		if(p[0] == 's' || p[0] == 'u'|| p[0] == 'a'|| p[0] == 'y'|| p[0] == 'w'|| p[0] == 'x'|| p[0] == 'o'|| p[0] == 'i'|| p[0] == 'm'|| p[0] == 'k'|| p[0] == 'h'|| p[0] == 'g'|| p[0] == 'v'|| p[0] == 'z'){
			return true;
		}
		else return false;
	}
}

bool verif_p(string p, string p1)
{
	if(p.size() > 1)	return false;
	else{
	if(p == p1)	return false;
	else {
				if(p[0] == 's' || p[0] == 'u'|| p[0] == 'a'|| p[0] == 'y'|| p[0] == 'w'|| p[0] == 'x'|| p[0] == 'o'|| p[0] == 'i'|| p[0] == 'm'|| p[0] == 'k'|| p[0] == 'h'|| p[0] == 'g'|| p[0] == 'v'|| p[0] == 'z'){
				return true;
			}
		else return false;
		}
	}
}

void ViderBuffer()
{
	
    cin.clear();
   // cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int SaisieEntier()
{
    int nombre;
    while(true)
    {

        cin >> nombre;
 
        if(cin.eof() || cin.bad())                      //Vérifie si la saisie s'est faite correctement
        {
            cerr << "Une erreur interne est survenue." << endl;
            if(cin.eof())
                break;
            ViderBuffer();
            continue;
        }
        else if(cin.fail())                             //Vérifie si le type de la saisie correspond à celui attendu
        {
            cerr << "Erreur, saisie incorrecte!" << endl;
            ViderBuffer();
            continue;
        }
        else if(nombre<0 || nombre>H-1)             //Vérifie si la variable est dans le bon interval
        {
            cerr << "Erreur : entrer une valeur entre 0 et " << H-1 << " !" << endl;
            ViderBuffer();
            continue;
        }
        break;
    }
    return nombre;
}
