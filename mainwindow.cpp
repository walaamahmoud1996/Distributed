#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
=======
#include<QListWidgetItem>
#include<QPixmap>
#include <QVBoxLayout>
#include<QBoxLayout>
#include<QLabel>
#include<QPushButton>
#include <QGridLayout>
#include<vector>
#include<string>
#include<QObject>
#include<iostream>

using namespace std;
>>>>>>> f2aef850d327d338c595adff7842f1ace66f2fa5

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
=======

    QPixmap p1 ("/home/abdel-shahid/pic1.jpg");
    globalImg["3b4a_movie"] = p1;
    //this->globalImg.push_back(p1);

    QPixmap p2 ("/home/abdel-shahid/pic2.jpg");
    globalImg["3b4a_avatar"] = p2;
    //this->globalImg.push_back(p2);

    QPixmap p3 ("/home/abdel-shahid/pic3.jpg");
    globalImg["Walaa_dragon"] = p3;
    //this->globalImg.push_back(p3);


    QListWidgetItem *itm = new QListWidgetItem(tr("pic 1"));
    itm->setIcon(p3);
    //globalImg.pop_back();
    ui->listView_2->addItem(itm);

>>>>>>> f2aef850d327d338c595adff7842f1ace66f2fa5
}

MainWindow::~MainWindow()
{
    delete ui;
}
<<<<<<< HEAD
=======

//for the update button
void MainWindow::on_update_clicked()
{
    ui->listView->clearSelection();
    ui->listView->clearFocus();
    ui->listView->clearPropertyFlags();
    ui->listView->clear();

    //this is to update the list of the images shared with me
    map<string, QPixmap>::iterator it;
    for(it = globalImg.begin(); it != globalImg.end(); it++){
        QListWidgetItem *itm = new QListWidgetItem(tr(it->first.c_str()));
        itm->setIcon(it->second);
        //globalImg.pop_back();
        ui->listView->addItem(itm);
    }
}



//for the list in the home page
void MainWindow::on_listView_itemClicked(QListWidgetItem *item)
{
    QIcon p = item->icon();
    QPixmap p1 = p.pixmap(p.actualSize(QSize(250, 100)));
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(p1);
    ui->gv->setScene(scene);
}

//for the list in the home page
void MainWindow::on_listView_itemDoubleClicked(QListWidgetItem *item)
{
    //from the other part
    //request the photo under this username and image name
    //DO NOT USE THE IMAGE FROM THE ITEM AGAIN

    //create new window
    QGridLayout *grid = new QGridLayout;
    QWidget *mainwin = new QWidget;

    //set the image
    QLabel *piclab = new QLabel();

    //HERE---USE THE IMAGE REQUESTED FROM THE OWNER
    //Check whether you have an instance of it or not
    QIcon p = item->icon();

    QPixmap p1 = p.pixmap(p.actualSize(QSize(600, 600)));
    piclab->setPixmap(p1);

    grid->addWidget(piclab, 0, 0);
    mainwin->setLayout(grid);
    mainwin->show();
}


//for the list in the profile tab(images)
void MainWindow::on_listView_2_itemClicked(QListWidgetItem *item)
{
    QIcon p = item->icon();
    QPixmap p1 = p.pixmap(p.actualSize(QSize(300, 300)));
    ui->labelimg->setPixmap(p1);
}
>>>>>>> f2aef850d327d338c595adff7842f1ace66f2fa5
