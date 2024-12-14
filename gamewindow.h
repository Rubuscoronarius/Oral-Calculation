#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event) override;
    void updateScore(int points);
    void initGame();


private slots:
    void on_Button_Next_clicked();

    void generateNewQuestion();


private:
    Ui::GameWindow *ui;
    int correctAnswer;   // record the correct answer
    int currentScore;   // record the current score
};

#endif // GAMEWINDOW_H
