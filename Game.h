#ifndef DEF_GAME
#define DEF_GAME
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include <fstream>

using namespace std;
class Game
{
	public:
		
		Game();
		void ChargerLvl(vector <vector<sf::Sprite>> &CarteChge,vector <vector<sf::Sprite>> &Map,vector <vector<int>> &CarteCol);
		void SvgderLvl();
		void EditerLvl();
		void Jouer();
		void SetEditMode();
		void ChargerLvlCol();
		~Game();

	private :
		 sf::RenderWindow* m_window;
		 sf::RenderWindow* m_palette;
		 static const int LARGEUR_NPC=32;
		 static const int HAUTEUR_NPC=32;
		 static const int LARGEUR_FEN=20*32;
		 static const int HAUTEUR_FEN=20*32;
		 static const int TAILLE_X_EDIT=20;
		 static const int TAILLE_Y_EDIT=20;
		 float m_vitesse;
		 int m_direction;
		 int m_mode;
		 bool m_isGameChrg;
		 sf::View m_vue;
		 vector <vector<sf::Sprite>> m_carteChge;
		 vector <vector<sf::Sprite>> m_carteColEdit;
		 vector <vector<sf::Sprite>> m_carte;
		 vector <vector<int>> m_carteCol;
		 vector <vector<sf::Sprite>> m_arPlan;
		 enum dir {Up,Down,Left,Right};
		
};

#endif DEF_GAME