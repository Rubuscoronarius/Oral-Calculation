#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamewindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* instance() { return m_instance; }  // get m_instance
    bool game_status;

private slots:
    void on_Button_New_clicked();

    void on_Button_Exit_clicked();

    void on_Button_Continue_clicked();

private:
    Ui::MainWindow *ui;
    GameWindow *gw;
    static MainWindow* m_instance;  // def m_instance

};
#endif // MAINWINDOW_H
