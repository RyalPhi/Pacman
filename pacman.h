#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

class PacmanWindow : public QFrame
{
  protected:
    Jeu jeu;
    QPixmap pixmapPacman, pixmapFantome, pixmapMur;

  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void handleTimer();


  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void clickBoutonAjout();
    void clickBoutonRetire();
};

class PacmanButton : public QPushButton
{
    protected:

    public:
        void keyPressEvent(QKeyEvent *);
        PacmanButton(QWidget* parent):QPushButton(parent){};
};

#endif
