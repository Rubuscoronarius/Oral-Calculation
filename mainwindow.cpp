#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

bool game_status=0;

/* a static viriation,
 * ensure there will be only one instance,
 * get MainWindow in the program without the global variation
*/
MainWindow* MainWindow::m_instance = nullptr;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), gw(nullptr) {
    ui->setupUi(this);
    if (!m_instance) {
        m_instance = this;
    }
}

MainWindow::~MainWindow()
{
    if (m_instance == this) {  // check this
        m_instance = nullptr;  // clear m_instance
    }
    delete ui;
}


//start a new game
void MainWindow::on_Button_New_clicked()
{
    game_status = 1; // the game start
    if (!gw) { // new a GameWindow
        gw = new GameWindow;
    }
    gw->initGame(); // init the game
    gw->show(); // show GameWindow
    this->hide(); // hide MainWindow
}


//continue the game
void MainWindow::on_Button_Continue_clicked()
{
    if (game_status) {
        gw->show();
        this->hide();
    } else {
        QMessageBox::information(this, "Game Not Started", "Please start a new game first.");
    }
}


//exit the game
void MainWindow::on_Button_Exit_clicked()
{
    if (gw) {
        gw->close(); // close GameWindow
        gw = nullptr; // clear the pointer of gw
    }
    this->close();
    if (m_instance == this) {
        m_instance = nullptr; // clear the pointer of m_instance
    }
    exit(0);
}




