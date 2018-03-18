#include "jeu.h"
#include <iostream>
#include <assert.h>
#include <istream>
#include <fstream>
#include <vector>

Fantome::Fantome()
{
    posX = 0; posY = 0;
    dir = BAS;
}

Fantome::Fantome(int x, int y)
{
    posX = x; posY = y;
    dir = (Direction) (rand()%4);
}

int Fantome::getPosX() const
{
    return posX;
}

int Fantome::getPosY() const
{
    return posY;
}

Jeu::Jeu()
{
    terrain = NULL;
    largeur = 0; hauteur = 0;
    posPacmanX = 0; posPacmanY = 0;
}

Jeu::~Jeu()
{
    if (terrain!=NULL)
        delete[] terrain;
}

bool Jeu::init()
{
	int x, y;
	list<Fantome>::iterator itFantome;

	/*const char terrain_defaut[15][21] = {
		"####################",
		"#........##........#",
		"#.#####..##...####.#",
		"#........##........#",
		"#..................#",
		"#......#....#......#",
		"#......#...##......#",
		"#####..#....#..#####",
		"#......##...#......#",
		"#......#....#......#",
		"#..................#",
		"#..................#",
		"#.....#......#.....#",
		"#.....#......#.....#",
        "####################" */

    ifstream fichier;
    string ligne;
    fichier.open("Terrain.txt");
    bool lg1 = true;
    if(!fichier.is_open())
    {
        cout<<"Impossible d'ouvrir le fichier"<<endl;
    }
    while(!fichier.eof())
    {
        getline(fichier, ligne);
        vector <string> champs;
        bool fin=false;
        unsigned int pos=0, posSuivante;
        while(!fin)
        {
            posSuivante=ligne.find(' ',pos);
            if(posSuivante!=string::npos)
            {
                champs.push_back(ligne.substr(pos, posSuivante-pos)); //WARNING
                pos=posSuivante++;
            }
            else
            {
                champs.push_back(ligne.substr(pos, string::npos));
                fin = true;
            }
            for(unsigned int i=0; i<champs.size(); i++)
            {
                if(lg1)
                {
                    largeur = stol(champs[0]);
                    hauteur = stol(champs[1]);
                    lg1 = false;
                    cout << largeur << " "<<hauteur<<endl;
                }
            }
        }
    }
    fichier.close();
    return true;

/*	largeur = 20;
	hauteur = 15;

	terrain = new Case[largeur*hauteur];

	for(y=0;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else
                terrain[y*largeur+x] = VIDE;

    fantomes.resize(10);

	for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

        itFantome->posX = x;
        itFantome->posY = y;
        itFantome->dir = (Direction)(rand()%4);
    }

    do {
        x = rand()%largeur;
        y = rand()%hauteur;
    } while (terrain[y*largeur+x]!=VIDE);

    posPacmanX = x,
    posPacmanY = y; */

    return true;
}

void Jeu::evolue()
{
    int testX, testY;
	list<Fantome>::iterator itFantome;

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        testX = itFantome->posX + depX[itFantome->dir];
        testY = itFantome->posY + depY[itFantome->dir];

        if (terrain[testY*largeur+testX]==VIDE)
        {
            itFantome->posX = testX;
            itFantome->posY = testY;
        }
        else
            // Changement de direction
            itFantome->dir = (Direction)(rand()%4);
    }
}

int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

int Jeu::getPacmanX() const
{
    return posPacmanX;
}

int Jeu::getPacmanY() const
{
    return posPacmanY;
}

Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<largeur && y>=0 && y<hauteur);
    return terrain[y*largeur+x];
}

bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && terrain[y*largeur+x]==VIDE);
}

bool Jeu::deplacePacman(Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    testX = posPacmanX + depX[dir];
    testY = posPacmanY + depY[dir];

    if (posValide(testX, testY))
    {
        posPacmanX = testX;
        posPacmanY = testY;
        return true;
    }
    else
        return false;
}
