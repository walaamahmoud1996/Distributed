#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD

=======
#include<vector>
#include<string>
#include<QListWidgetItem>

using namespace std;
>>>>>>> f2aef850d327d338c595adff7842f1ace66f2fa5
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
=======
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_update_clicked();
    void on_listView_itemClicked(QListWidgetItem *item);



    //void on_listView_itemActivated(QListWidgetItem *item);

    void on_listView_itemDoubleClicked(QListWidgetItem *item);

    void on_listView_2_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    //vector<QPixmap> globalImg;
    //vector<QPixmap> personImg;
    map<string, QPixmap> globalImg;
    map<string, QPixmap> personImg;


>>>>>>> f2aef850d327d338c595adff7842f1ace66f2fa5
};

#endif // MAINWINDOW_H
