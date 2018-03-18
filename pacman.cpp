#include <iostream>
#include "pacmanwindow.h"
#define T_BANDEAU 100
#define LARG_BTN 50
#define LONG_BTN 100

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    if (pixmapPacman.load("./data/pacman.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman.png"<<endl;
        exit(-1);
    }

    if (pixmapFantome.load("./data/fantome.bmp")==false)
    {
        cout<<"Impossible d'ouvrir fantome.bmp"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(100);

    QSize *t_btn = new QSize;
    *t_btn = QSize(LONG_BTN, LARG_BTN);

    //Ajout des boutons
    PacmanButton *btn_ajout = new PacmanButton(this); //Attention
    PacmanButton *btn_retire = new PacmanButton(this);//Attention
    btn_ajout->setText("Ajout d'un fantome");
    btn_retire->setText("Retirer un fantome");
    btn_ajout->setGeometry(LONG_BTN/2, LARG_BTN/2, LONG_BTN, LARG_BTN);
    btn_retire->setGeometry(LONG_BTN+3*LONG_BTN/2,LARG_BTN/2, LONG_BTN, LARG_BTN);
    connect(btn_ajout, QPushButton::clicked, this, PacmanWindow::clickBoutonAjout);
    connect(btn_retire, QPushButton::clicked, this, PacmanWindow::clickBoutonRetire);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase + T_BANDEAU);
}
void PacmanWindow::clickBoutonAjout()
{
    int x, y;

    int largeur = 20;
	int hauteur = 15;

    do {
            x = rand()%(largeur);
            y = rand()%(hauteur);
        } while (!jeu.posValide(x, y));

    jeu.fantomes.push_back(Fantome(x, y));
}

void PacmanWindow::clickBoutonRetire()
{
    jeu.fantomes.pop_back();
}
void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les cases
    for (y=0;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR)
                painter.drawPixmap(x*largeurCase, y*hauteurCase + T_BANDEAU, pixmapMur);

    //Dessine les boutons


    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase + T_BANDEAU, pixmapFantome);

	// Dessine Pacman
	painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase + T_BANDEAU, pixmapPacman);
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
        jeu.deplacePacman(GAUCHE);
    else if (event->key()==Qt::Key_Right)
        jeu.deplacePacman(DROITE);
    else if (event->key()==Qt::Key_Up)
        jeu.deplacePacman(HAUT);
    else if (event->key()==Qt::Key_Down)
        jeu.deplacePacman(BAS);
    update();
}

void PacmanButton::keyPressEvent(QKeyEvent *e)
{
 if (parent()!=NULL)
 QCoreApplication::sendEvent(parent(), e);
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    update();
}
