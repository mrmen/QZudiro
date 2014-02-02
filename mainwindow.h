#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHash>
#include <QLabel>
#include "zudirogrid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QHash<QPushButton*, QPair<int, int> > buttonHash;
    QVector<QLabel*> labelHorizontal;
    QVector<QLabel*> labelVertical;
    // add another int for value
    ZudiroGrid grille;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void updateLevelLcd(int);
    void buttonClick(QWidget*);
    void doTheStuff(int level, int sublevel);
    void getValueAndUpdate();
    void updateIt();
    // must be done with only one
 /*   void getSavedGames();
    void getMax();
    void getMin();
    // generate
    void generateGrid();
    void updateGrid();*/
};

#endif // MAINWINDOW_H
