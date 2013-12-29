#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zudirogrid.h"
#include <QSignalMapper>
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sliderLevel->setMinimum(1);
    ui->sliderLevel->setMaximum(150);
    connect(ui->sliderLevel,SIGNAL(valueChanged(int)),this,SLOT(updateLevelLcd(int)));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(getValueAndUpdate()));
    doTheStuff(2,2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLevelLcd(int value)
{
    int level = value/10 + 1;
    int sublevel = value- (level-1)*10 + 1;
    ui->lcdLevel->display(QString::number(level));
    ui->lcdSubLevel->display(QString::number(sublevel));
}

void MainWindow::doTheStuff(int level, int sublevel){
    QSignalMapper *signalMapper = new QSignalMapper;
//    grille.ZudiroGridSecond("game.xml", 2, 7);
    grille.ZudiroGridSecond("game.xml", level, sublevel);
    ui->LabelCurrentLevel->setText(QString::number(level)+"-"+QString::number(sublevel));
    std::cout << grille.dim << std::endl;
    for (int i = 0; i < grille.dim; i++) {
        for (int j = 0; j < grille.dim; j++) {
            QPair<int, int> gridPair(i, j);
            QPushButton* button = new QPushButton();
            button->setFixedHeight(40);
            button->setFixedWidth(40);
            buttonHash.insert(button, gridPair);
            ui->gridLayout->addWidget(button, i+1, j+1);

            connect(button, SIGNAL(clicked()),
                    signalMapper, SLOT(map()));
            signalMapper->setMapping(button, qobject_cast<QWidget*>(button));
        }
    }

    for(int i=0;i<labelHorizontal.size();i++){
        labelHorizontal[i]->setText("");
        delete labelHorizontal[i];
    }
    labelHorizontal.clear();
    labelHorizontal.resize(0);
    for (int count=0; count<grille.dim; count++){
        QLabel *label = new QLabel();
        label->setText(QString::number(grille.atg[count]));
        label->setFixedHeight(40);
        label->setFixedWidth(40);
        label->setAlignment(Qt::AlignHCenter);
        label->setAlignment(Qt::AlignVCenter);
        labelHorizontal.push_back(label);
    }
    for (int count=0; count<grille.dim; count++){
        ui->gridLayout->addWidget(labelHorizontal[count],0,count+1);
    }

    for(int i=0;i<labelVertical.size();i++){
        labelVertical[i]->setText("");
        delete labelVertical[i];
    }
    labelVertical.clear();
    labelVertical.resize(0);
    for (int count=0; count<grille.dim; count++){
        QLabel *label = new QLabel();
        label->setText(QString::number(grille.lotg[count]));
        label->setFixedHeight(40);
        label->setFixedWidth(40);
        label->setAlignment(Qt::AlignVCenter);
        label->setAlignment(Qt::AlignHCenter);
        labelVertical.push_back(label);
    }
    for (int count=0; count<grille.dim; count++){
        ui->gridLayout->addWidget(labelVertical[count],count+1,0);
    }

    connect(signalMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(buttonClick(QWidget*)));
}

void MainWindow::buttonClick(QWidget* widget) {
   QPair<int, int> pair = buttonHash.value(qobject_cast<QPushButton*>(widget));
   int myRow = pair.first;
   int myColumn = pair.second;
   if (widget->styleSheet().isEmpty()){
       widget->setStyleSheet(
          "QPushButton {"
          "margin: 1px;"
          "border-color: #0c457e;"
          "border-style: outset;"
          "border-radius: 3px;"
          "border-width: 1px;"
          "color: black;"
          "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2198c0, stop: 1 #0d5ca6);"
          "}"
      );
   }
   else{
       widget->setStyleSheet("");
   }

   grille.grid[myRow][myColumn] = 1-grille.grid[myRow][myColumn];
   vector<int> test = grille.isDoneHere(myRow,myColumn);

   if (QString::number(test[0])==labelHorizontal[myColumn]->text())
       labelHorizontal[myColumn]->setStyleSheet("background-color : red");
   else
       labelHorizontal[myColumn]->setStyleSheet("background-color : light gray");

   if (QString::number(test[1])==labelVertical[myRow]->text())
       labelVertical[myRow]->setStyleSheet("background-color : red");
   else
       labelVertical[myRow]->setStyleSheet("background-color : light gray");

    // test all colors
   int ok=1;
    for(int i=0;i<grille.dim;i++){
        if (grille.Flotg[i] != grille.lotg[i])
            ok = 0 * ok;
        if (grille.Fatg[i] != grille.atg[i])
            ok = 0 * ok;
    }
    if (ok==1){
        int sublevel = grille.subLevel +1;
        int level = grille.level;
        if (sublevel>10) {
            sublevel--;
            level++;
        }
        doTheStuff(level, sublevel);
    }

}

void MainWindow::getValueAndUpdate(){
    updateIt();
    updateLevelLcd(ui->sliderLevel->value());
    int level = ui->lcdLevel->value();
    int sublevel = ui->lcdSubLevel->value();
    doTheStuff(level, sublevel);
}

void MainWindow::updateIt(){
    QLayoutItem *item;

    int i=1;
    while ((item = ui->gridLayout->takeAt(0))!=NULL)
    {
        delete item;
        i++;
    }
    qDeleteAll(buttonHash.keys());
    buttonHash.clear();
}
