#include "Game.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include <fstream>


	

 Game::Game()
{
m_isGameChrg = false;
m_mode=-1;
m_vitesse =32;
m_direction=Up;
m_window = new sf::RenderWindow();
m_window->create(sf::VideoMode(20*32, 20*32, 32), "Editeur " );


for(int i =0;i <20;i++)
{
	vector <sf::Sprite> lol(20);
	vector <int> lel(20);
	m_carteChge.push_back(lol);
	m_carte.push_back(lol);
    m_carteCol.push_back(lel);
	m_carteColEdit.push_back(lol);
    m_arPlan.push_back(lol);
	

}

m_palette = new sf::RenderWindow();
m_palette->create(sf::VideoMode(1036, 475, 32), "Palette " );
sf::RectangleShape rect;
	rect.setFillColor(sf::Color(50,0,0,150));
	rect.setSize(sf::Vector2f(16,16));
	rect.setPosition(0,0);
	m_window->draw(rect);

}
 void Game::SetEditMode()
 {
	/* sf::Vector2f posVue;
	posVue.x=0;
	posVue.y=0;
	sf::View vue;
	sf::RenderWindow window;
	sf::RenderWindow palette;
	m_window->create(sf::VideoMode(20*32, 20*32, 32), "Editeur " );//,sf::Style::Fullscreen);
	m_palette->create(sf::VideoMode(1036, 475, 32), "Palette " );*/
	sf::Sprite s_col;
	m_window->setPosition(sf::Vector2i(200,200));

	m_palette->setPosition(sf::Vector2i(m_window->getPosition().x+20*32+10,m_window->getPosition().y));
	

	int wheelX =0;
	int wheelY =0;
	int tileX =0;
	int tileY =0;
	
	
	ofstream monNiveau("level1.lvl");

	if(monNiveau)
	{
		
	}
	else{
		cout<<"ERREUR impossible d'ouvrir le fichier !"<<endl;
	}
	
	string tab[TAILLE_X_EDIT][TAILLE_Y_EDIT];
	string tabCol[TAILLE_X_EDIT][TAILLE_Y_EDIT];

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(50,0,0,150));
	rect.setSize(sf::Vector2f(16,16));
	rect.setPosition(0,0);

	sf::RectangleShape rect2;
	rect2.setFillColor(sf::Color(50,50,100,150));
	rect2.setSize(sf::Vector2f(16,16));
	rect2.setPosition(0,0);

	 sf::Texture environmt;
	 
	if (!environmt.loadFromFile("Sprites_Env.png"))
{
    cout<<"Erreur !";
}  
	sf::Texture t_col;
		if (!t_col.loadFromFile("Collisions.png"))
{
    cout<<"Erreur !";
}  
  sf::Sprite Map[71][28];
  s_col.setTexture(t_col);
  sf::Sprite mondePal;
  mondePal.setTexture(environmt);

 
for (int i=0;i<71;i++)
{
	for (int j=0;j<28;j++)
{
	
	Map[i][j].setTexture(environmt);
	Map[i][j].setTextureRect(sf::IntRect(i*16+i,j*16+j,16,16));
}
}
/*
vector <vector<sf::Sprite>> Carte(TAILLE_X_EDIT,vector<sf::Sprite>(TAILLE_Y_EDIT));
vector <vector<sf::Sprite>> CarteCol(TAILLE_X_EDIT,vector<sf::Sprite>(TAILLE_Y_EDIT));
vector <vector<sf::Sprite>> CarteChge(TAILLE_X_EDIT,vector<sf::Sprite>(TAILLE_Y_EDIT));
vector <vector<sf::Sprite>> ArPlan(TAILLE_X_EDIT,vector<sf::Sprite>(TAILLE_Y_EDIT));*/

  m_carte[0][0]=Map[0][0];

	while (m_window->isOpen())
	{
		sf::Event event;

		while (m_window->pollEvent(event))
        {
			
			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::S )
				wheelY++;
			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::Z )
				wheelY--;
			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::Q )
				wheelX--;
			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::D )
				wheelX++;
				
		if(wheelX >60)
			wheelX=0;
		if(wheelX < 0)
			wheelX=60;
		if(wheelY >27)
			wheelY=0;
		if(wheelY <0)
			wheelY=27;

		
			if(wheelX==0 && wheelY==0)
				rect.setPosition(0,0);
			else
			rect.setPosition(wheelX*16+wheelX*1,wheelY*16+wheelY*1);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				m_palette->close();

			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::Tab )
			{
				m_mode = m_mode * (-1);
				cout<<"mode : "<<m_mode<<endl;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				sf::Vector2i globalPosition = sf::Mouse::getPosition(*m_window);
				if(globalPosition.x >0 && globalPosition.x < LARGEUR_FEN && globalPosition.y >0 && globalPosition.y < HAUTEUR_FEN && m_mode == -1)
				{
				 tileX = int(globalPosition.x/LARGEUR_NPC);
				 tileY = int(globalPosition.y/HAUTEUR_NPC);
		    	 cout<<" Pos Soruis X : "<<tileX<<" Y : "<<tileY<<endl;
				m_carte[tileX][tileY] = Map[wheelX][wheelY];
			
				m_carte[tileX][tileY].setPosition(tileX*LARGEUR_NPC,tileY*HAUTEUR_NPC);
				m_carte[tileX][tileY].setScale(2,2);
				tab[tileX][tileY]="";
				
				if(to_string(static_cast<long long>(wheelX+wheelY*61)).length()==1)
				{
					
					tab[tileX][tileY] += "000";
					tab[tileX][tileY] += to_string(static_cast<long long>(wheelX+wheelY*61));
					tab[tileX][tileY] += " ";
				//	cout<<" le 00 ete ajoutee "<<"le mote : " <<"00"<< to_string(static_cast<long long>(wheelX+wheelY*61))<<" "<<endl;
				}

				else if(to_string(static_cast<long long>(wheelX+wheelY*61)).length()==2)	
				{
					
				tab[tileX][tileY] += "00";
				tab[tileX][tileY] += to_string(static_cast<long long>(wheelX+wheelY*61));
				tab[tileX][tileY] += " ";
			//	cout<<" le 0 ete ajoutee "<<"le mote : " <<"0"<< to_string(static_cast<long long>(wheelX+wheelY*61))<<" "<<endl;
				}
				else if(to_string(static_cast<long long>(wheelX+wheelY*61)).length()==3)	
				{
					
				tab[tileX][tileY] += "0";
				tab[tileX][tileY] += to_string(static_cast<long long>(wheelX+wheelY*61));
				tab[tileX][tileY] += " ";
			//	cout<<"le mote : " <<"0"<< to_string(static_cast<long long>(wheelX+wheelY*61))<<" "<<endl;
				}
				else if(to_string(static_cast<long long>(wheelX+wheelY*61)).length()>=4)	
				{
					
				
				tab[tileX][tileY] += to_string(static_cast<long long>(wheelX+wheelY*61));
				tab[tileX][tileY] += " ";
			//	cout<<"le mote : " <<"0"<< to_string(static_cast<long long>(wheelX+wheelY*61))<<" "<<endl;
				}

				
				//cout<<" X: "<<tileX<<" wheelX : "<<wheelX<<" Y: "<<tileY<<" wheelY : "<<wheelY<<endl;
				cout<< " Tableau ("<<tileX<<","<<tileY<<") : "<<tab[tileX][tileY]<<" de taille : "<<tab[tileX][tileY].length()<<endl;
			}
				else if (globalPosition.x >0 && globalPosition.x < LARGEUR_FEN && globalPosition.y >0 && globalPosition.y < HAUTEUR_FEN && m_mode == 1)
				{
					tileX = int(globalPosition.x/LARGEUR_NPC);
				 tileY = int(globalPosition.y/HAUTEUR_NPC);
		    	tabCol[tileX][tileY] = "";
					switch(wheelY)
					{
					case 0:
						{
		switch(wheelX)
					{
					case 0:
						{
						 tabCol[tileX][tileY] += "000";////////
						 tabCol[tileX][tileY] += "1";
						 cout<<" case 0 "<<endl;
						 m_carteColEdit[tileX][tileY] = s_col;
						 m_carteColEdit[tileX][tileY].setTextureRect(sf::IntRect(0,0,16,16));
						 m_carteColEdit[tileX][tileY].setPosition(tileX*LARGEUR_NPC,tileY*HAUTEUR_NPC);
						 m_carteColEdit[tileX][tileY].setScale(2,2);
						  tabCol[tileX][tileY] += " ";
						}
						break;
						
					case 1:
						{
						tabCol[tileX][tileY] += "000";////////
						tabCol[tileX][tileY] += "2";
						cout<<" case 1 "<<endl;
						m_carteColEdit[tileX][tileY] = s_col;
						m_carteColEdit[tileX][tileY].setTextureRect(sf::IntRect(16+1,0,16,16));
						m_carteColEdit[tileX][tileY].setPosition(tileX*LARGEUR_NPC,tileY*HAUTEUR_NPC);
						m_carteColEdit[tileX][tileY].setScale(2,2);
						tabCol[tileX][tileY] += " ";
						}
						break;
						
					case 2:
						{
						tabCol[tileX][tileY] += "000";////////
						tabCol[tileX][tileY] += "3";
						cout<<" case 2 "<<endl;
						m_carteColEdit[tileX][tileY] = s_col;
						m_carteColEdit[tileX][tileY].setTextureRect(sf::IntRect(32+2,0,16,16));
						m_carteColEdit[tileX][tileY].setPosition(tileX*LARGEUR_NPC,tileY*HAUTEUR_NPC);
						m_carteColEdit[tileX][tileY].setScale(2,2);
						tabCol[tileX][tileY] += " ";
						}
						break;
					
					default:
						break;
					}
						}
						break;
						
					case 1:
						{
							switch(wheelX)
					{
					case 0:
						{
							tabCol[tileX][tileY] += "000";////////
						tabCol[tileX][tileY] += "0";
						cout<<" case 3 "<<endl;
						m_carteColEdit[tileX][tileY] = s_col;
						m_carteColEdit[tileX][tileY].setTextureRect(sf::IntRect(0,16+1,16,16));
						m_carteColEdit[tileX][tileY].setPosition(tileX*LARGEUR_NPC,tileY*HAUTEUR_NPC);
						m_carteColEdit[tileX][tileY].setScale(2,2);
						tabCol[tileX][tileY] += " ";
						}
						break;
						
					case 1:
						{
							/////
						}
						break;
						
					case 2:
						{
							/////
						}
						break;
					
					default:
						break;
					}
						}
						break;
						
					case 2:
						{
			switch(wheelX)
					{
					case 0:
						{
							/////
						}
						break;
						
					case 1:
						{
							/////
						}
						break;
						
					case 2:
						{
								///////
						}
						break;
					
					default:
						break;
					}
						}
						break;
					
					default:
						break;
					}
				}
			}
			if (event.type == sf::Event::Closed)
			{
             
				m_window->close();
				
			}
	

			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::A )
			{
				if(m_mode == -1)
				{
				cout<<"svgder"<<endl;
				for (int i =0; i <TAILLE_Y_EDIT;i++)
				{
					for (int j =0; j <TAILLE_X_EDIT;j++)
				{
					monNiveau<<tab[j][i];
				//	cout<<" x : "<<j<<" y : "<<i<<"Tableau o : "<<tab[j][i]<<endl; 
				}
				}
				}
				else if(m_mode == 1)
				{
				cout<<"svgder"<<endl;
				for (int i =0; i <TAILLE_Y_EDIT;i++)
				{
					for (int j =0; j <TAILLE_X_EDIT;j++)
				{
					monNiveau<<tabCol[j][i];
				//	cout<<" x : "<<j<<" y : "<<i<<"Tableau o : "<<tab[j][i]<<endl; 
				}
				}
				}
			}
			
	if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::E )
			{
			
					m_isGameChrg=true;
			cout<<"chargement"<<endl;
				ifstream leLvl("monNiv.lvl");
			//	if(leLvl)
			//	cout<<"gg wp";
				string tout;
				
				if (leLvl.good())
	{
		while(getline(leLvl,tout))
		{
			cout<<"mot"<<endl;
			cout<<tout<<endl;
			
		}
	
		leLvl.close();
	}
				int chgX=0;
				int chgY=0;
				int y=0;
				int mapY=0;
				for(int x =0;x<2000;x=x+5)
				{
					
					mapY=int(atoi(tout.substr(x,4).c_str())/61);
				m_carteChge[chgX][chgY] =	Map[atoi(tout.substr(x,4).c_str())-(mapY*61)][mapY];
				cout<<" le x : "<<x<<endl;
				
					chgX++;

					if(chgX >=TAILLE_X_EDIT)
					{
						chgX=0;
						chgY++;
						if(chgY >= TAILLE_Y_EDIT)
							chgY=0;
					}

					y=0;
				}
			

			
			
	}

        }


	/*	vue.reset(sf::FloatRect(posVue.x,posVue.y,40*32,40*32));
		
		m_window->setView(vue);*/
		
	 // m_window->clear(); 
	   /*for(int i =0;i<20;i++)
			{
				for(int j =0;j<20;j++)
			{
				m_arPlan[i][j] = Map[29][20];
				m_arPlan[i][j].setScale(2,2);
				m_arPlan[i][j].setPosition(i*32,j*32);
				m_window->draw(m_arPlan[i][j]);
			}
			}*/
	
		if(m_isGameChrg)
		{
			for(int i =0;i<TAILLE_Y_EDIT;i++)
			{
				for(int j =0;j<TAILLE_X_EDIT;j++)
			{
				m_carteChge[i][j].setScale(2,2);
				m_carteChge[i][j].setPosition(i*32,j*32);
				m_carteChge[i][j].setColor(sf::Color(100,100,100,255));
				m_window->draw(m_carteChge[i][j]);
			}
			}
			
		}

	 //  m_window->draw(rect2);
	//   cout<<" Pos REct 2 X : "<<rect2.getPosition().x<<" Y : "<<rect2.getPosition().y<<endl;
	   
	// cout<< "Pos tile en x : "<< m_carteChge[0][0].getPosition().x<<"Pos tile en y : "<<m_carteChge[0][0].getPosition().y<<endl;
	   //cout<<" Posee aux valuers X : "<<tileX<<" Y : "<<tileY<<endl;
       
	   
	   m_palette->clear(); 
	   if(m_mode == -1){
		 m_palette->draw(mondePal);
	   m_window->draw(m_carte[tileX][tileY]);
	   }
	   else if ( m_mode == 1)
	   {
		   m_palette->draw(s_col);
		   m_window->draw(m_carteColEdit[tileX][tileY]);
		
	   }
	   m_palette->draw(rect);
	
	   m_window->display();
       m_palette->display();
		
	}	
 }
 
 void Game::ChargerLvl(vector <vector<sf::Sprite>> &m_carteChge,vector <vector<sf::Sprite>> &Map,vector <vector<int>> &m_carteColEdit)//,vector <vector<sf::Sprite>> &Map,vector <vector<int>> &m_carteColEdit)
 {

	
				m_isGameChrg=true;
				cout<<"chargement"<<endl;
				ifstream leLvl("monNiv.lvl");
				ifstream leLvlCol("monNiv_col.lvl");
				string tout1;
				string tout2;
				if (leLvl.good())
	{
		while(getline(leLvl,tout1))
		{
		
			cout<<"on est la"<<endl;
		}
	
		leLvl.close();
	}
						if (leLvlCol.good())
	{
		while(getline(leLvlCol,tout2))
		{
	
		}
	
		leLvlCol.close();
	}
				int chgX=0;
				int chgY=0;
				int y=0;
				int mapY=0;
				int chgX2=0;
				int chgY2=0;
				int y2=0;
				int mapY2=0;
				for(int x =0;x<2000;x=x+5)
				{
					
					mapY=int(atoi(tout1.substr(x,4).c_str())/61);
				m_carteChge[chgX][chgY] =	Map[atoi(tout1.substr(x,4).c_str())-(mapY*61)][mapY];
		
					chgX++;

					if(chgX >=TAILLE_X_EDIT)
					{
						chgX=0;
						chgY++;
						if(chgY >= TAILLE_Y_EDIT)
							chgY=0;
					}

					y=0;
				}

				for(int z =0;z<2000;z=z+5)
				{
					
					switch(atoi(tout2.substr(z,4).c_str()))
					{
					case 0:
						{
							m_carteColEdit[chgX2][chgY2] =	0;
							
						}
						break;
						case 1:
						{
							m_carteColEdit[chgX2][chgY2] =	1;
							
						}
						break;
						case 2:
						{
							m_carteColEdit[chgX2][chgY2] =	2;
						}

						break;
						case 3:
						{
							m_carteColEdit[chgX2][chgY2] =	3;
						}
						break;
						default:
						{
							
						}
						break;
					}
				
	
			
					chgX2++;
					
					if(chgX2 >=TAILLE_X_EDIT)
					{
						chgX2=0;
						chgY2++;
						if(chgY2 >= TAILLE_Y_EDIT)
							{
								chgY2=0;
								cout<<endl;
						}
						}

					y2=0;
					
				}

			
		
}


void Game::Jouer()
 {
	 	
	
	
	
    sf::ConvexShape carre;
	sf::Texture texture;
	sf::Texture environmt;
	sf::Clock clock;
	bool updateFps=true;
	float fpsCount=0,
	switchFps=50,
	fpsSpeed=350;
	sf::Time timedelta;
	float movement;
	
if (!environmt.loadFromFile("Sprites_Env.png"))
{
    cout<<"Erreur !";
}  
vector <vector<sf::Sprite>> Map(71,vector<sf::Sprite>(28));
// sf::Sprite Map[71][28];
// SetMap(environmt,Map,window);

 
for (int i=0;i<61;i++)
{
	for (int j=0;j<28;j++)
{
	
	Map[i][j].setTexture(environmt);
	Map[i][j].setTextureRect(sf::IntRect(i*16+i,j*16+j,16,16));
}
}

if (!texture.loadFromFile("Perso1.png"))
{
    cout<<"Erreur !";
}

	
	 sf::Sprite sprite;
	 sf::Sprite herbe;
	 herbe.setTexture(environmt);
	 herbe.setScale(2,2);
	 herbe.setPosition(0,0);
	 sprite.setTexture(texture);
	 sprite.setTextureRect(sf::IntRect(0, 0, LARGEUR_NPC, HAUTEUR_NPC));
	 m_window->setFramerateLimit(60);
	 sprite.setPosition(0,0);
	//  mapT[0][0] = sprite;
//	 texture.setSmooth(true);

	 int aH =1,aB =1,aD =1,aG =1;
	 int bH = 1,bB = 1,bD = 1,bG = 1;



    while (m_window->isOpen())
    {
		timedelta = clock.getElapsedTime();
		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window); 
        sf::Event event;





if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(updateFps)
			{
			fpsCount += fpsSpeed *clock.restart().asSeconds();
				
			}
	     	else 
			fpsCount=0;

			if(fpsCount>=switchFps)
			{
				
		fpsCount=0;
		fpsSpeed-=10;
		cout<<"La Vitesse a ete diminue : "<<fpsSpeed<<endl;
		   }
	
				m_direction= Up;
		}
			












		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if(m_carteCol[int(sprite.getPosition().x/32)][int(sprite.getPosition().y/32)-1]==0)
			{
			if(updateFps)
			{
			fpsCount += fpsSpeed *clock.restart().asSeconds();
				
			}
	     	else 
			fpsCount=0;

			if(fpsCount>=switchFps)
			{
				if (aH==1 && bH==1)
				{	
					sprite.setTextureRect(sf::IntRect(0*LARGEUR_NPC,3*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aH=0;
					
					
				}
				else if ( aH==0 && bH==0)
				{
					 
					sprite.setTextureRect(sf::IntRect(2*LARGEUR_NPC,3*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aH=1;
					bH=2;
				
					
				}
				
				if(bH!=2)
				{
				bH=0;
				sprite.move(0,-m_vitesse);
				}
				if(bH==2)
				{
					bH=1;
					
					sprite.move(0,-m_vitesse);
				}
		fpsCount=0;

		   }
		}
				m_direction= Up;
		}
			























		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
				if(m_carteCol[int(sprite.getPosition().x/32)-1][int(sprite.getPosition().y/32)]==0)
			{
				if(updateFps)
		        {
			     fpsCount += fpsSpeed *clock.restart().asSeconds();
				
		        }
		        else 
		      	fpsCount=0;

		    if(fpsCount>=switchFps)
		    {
				if (aG==1 && bG==1)
				{	
					sprite.setTextureRect(sf::IntRect(0*LARGEUR_NPC,1*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aG=0;
					
					
				}
				else if ( aG==0 && bG==0) 
				{
					 
					sprite.setTextureRect(sf::IntRect(2*LARGEUR_NPC,1*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aG=1;
					bG=2;
					
					
				}
				
				if(bG!=2)
				{
				bG=0;
				sprite.move(-m_vitesse,0);
				}
				if(bG==2)
				{
					bG=1;
					
					sprite.move(-m_vitesse,0);
				}
		fpsCount=0;
				
				
		    }
			}
			m_direction= Left;
     	}
















	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
			if(m_carteCol[int(sprite.getPosition().x/32)+1][int(sprite.getPosition().y/32)]==0)
			{
				if(updateFps)
				{
			    	fpsCount += fpsSpeed *clock.restart().asSeconds();
				
			    }
				else 
				fpsCount=0;

			if(fpsCount>=switchFps)
			{
				if (aD==1 && bD==1)
				{	
					sprite.setTextureRect(sf::IntRect(0*LARGEUR_NPC,2*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aD=0;
					
					
				}
				else if ( aD==0 && bD==0)
				{
					 
					sprite.setTextureRect(sf::IntRect(2*LARGEUR_NPC,2*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aD=1;
					bD=2;
				
					
				}
				
				if(bD!=2)
				{
				bD=0;
				sprite.move(m_vitesse,0);
				}
				if(bD==2)
				{
					bD=1;
					
					sprite.move(m_vitesse,0);
				}
		fpsCount=0;

		  }
			}
			m_direction= Right;	
	}


















	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
			if(m_carteCol[int(sprite.getPosition().x/32)][int(sprite.getPosition().y/32)+1]==0)
			{
				if(updateFps)
				{
					fpsCount += fpsSpeed *clock.restart().asSeconds();

					
				}
				else 
				fpsCount=0;

			if(fpsCount>=switchFps)
			{
				if (aB==1 && bB==1)
				{	
					sprite.setTextureRect(sf::IntRect(0*LARGEUR_NPC,0*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aB=0;
					
					
				}
				else if ( aB==0 && bB==0) 
				{
					 
					sprite.setTextureRect(sf::IntRect(2*LARGEUR_NPC,0*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
					aB=1;
					bB=2;
					
					
				}
				
				if(bB!=2)
				{
				bB=0;
				sprite.move(0,m_vitesse);
				}
				if(bB==2)
				{
					bB=1;
					
					sprite.move(0,m_vitesse);
					cout<<"draaaa"<<endl;
				}
		fpsCount=0;

		   }
			}
				m_direction= Down;
    }






		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
	{
		switch(m_direction){
		case Up:
			{
				sprite.setTextureRect(sf::IntRect(1*LARGEUR_NPC,3*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
			}
			break;
		case Down:
			{
				sprite.setTextureRect(sf::IntRect(1*LARGEUR_NPC,0*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
			}
			break;
		case Left:
			{
				sprite.setTextureRect(sf::IntRect(1*LARGEUR_NPC,1*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
			}
			break;
		case Right:
			{
				sprite.setTextureRect(sf::IntRect(1*LARGEUR_NPC,2*HAUTEUR_NPC,LARGEUR_NPC,HAUTEUR_NPC));
			}
			break;
		}
	}






        while (m_window->pollEvent(event))
        {
		
			if (event.type == sf::Event::Closed)
			{
             
				m_window->close();
				
			}
			if(event.type == sf::Event::KeyReleased && event.key.code ==sf::Keyboard::E )
			ChargerLvl(m_carteChge,Map,m_carteCol);  
        }

		
		
	
	m_vue.setCenter(sprite.getPosition().x+LARGEUR_NPC,sprite.getPosition().y-HAUTEUR_NPC);
	m_vue.zoom(1.25);
	m_window->setView(m_vue);
		//sprite.setTextureRect(sf::IntRect(anim.x*29.5,anim.y*30.75,29.5,30.75));
        m_window->clear();
		 for(int i =0;i<20;i++)
			{
				for(int j =0;j<20;j++)
			{
				m_arPlan[i][j] = Map[29][20];
				m_arPlan[i][j].setScale(2,2);
				m_arPlan[i][j].setPosition(i*32,j*32);
				m_window->draw(m_arPlan[i][j]);
			}
			}
	
       // m_window->draw(carre);
		if(m_isGameChrg)
		{
			for(int i =0;i<20;i++)
			{
				for(int j =0;j<20;j++)
			{
				m_carteChge[i][j].setScale(2,2);
				m_carteChge[i][j].setPosition(i*LARGEUR_NPC,j*HAUTEUR_NPC);
				m_window->draw(m_carteChge[i][j]);
				//cout<<"bvababababa"<<endl;
				/*switch(m_carteCol[i][j])
				{
				case 0:
					{

						Map[3][3].setPosition(i*LARGEUR_NPC/2,j*HAUTEUR_NPC/2);
					//	Map[3][3].scale(2,2);
				m_window->draw(Map[3][3]);
					}
					break;
					case 1:
					{

					Map[2][2].setPosition(i*LARGEUR_NPC/2,j*HAUTEUR_NPC/2);
				//	Map[2][2].scale(2,2);
				m_window->draw(Map[2][2]);
					}
					break;
					case 2:
					{

					}
					break;
					case 3:
					{

					}
					break;
					default :
					{
					}
					break;
				}*/
				//cout<<" c fait !"<<endl;
		}
			}
			
		}
		
	
		m_window->draw(sprite);
        m_window->display();
		
    }

 }
 
 Game::~Game()
{


m_window = NULL;
m_palette = NULL;


}