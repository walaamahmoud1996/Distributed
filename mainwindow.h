#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include<string>
#include<QListWidgetItem>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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


};

#endif // MAINWINDOW_H
