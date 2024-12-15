#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <qevent.h>
#include <QMessageBox>

#include "mainwindow.h"


#include <cstdlib>
#include <ctime>

// a flag showing the initial random seed status
bool seedInitialized = false;



GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    currentScore(0),
    correctAnswer(0) // initialize the score and answer
{
    ui->setupUi(this);
    ui->label_score->setText(QString::number(currentScore)); // score init show
    std::srand(static_cast<unsigned int>(std::time(0)));  // score random seed

    connect(ui->Edit_Ans, SIGNAL(returnPressed()), this, SLOT(on_Button_Next_clicked()));


}


// generate randint
int get_randint() {
    return std::rand() % 50 + 1;
}


int get_randint_sum() {
    int a = std::rand() % 50 + 1;
    int b = std::rand() % 50 + 1;
    return a + b;
}



void GameWindow::initGame()
{
    currentScore = 0; // reset the score
    ui->label_score->setText(QString("Score: %1").arg(currentScore)); // show the score
    generateNewQuestion(); // show the first question
}



//when press "esc"
void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        this->hide();
        MainWindow *mainWin = MainWindow::instance();
        if (mainWin) {  // check the existance of MainWindow
            mainWin->show();
            mainWin->raise();
            mainWin->activateWindow();
        }
    }
    QMainWindow::keyPressEvent(event);  // deal keyPressEvent
}


//when press next
void GameWindow::on_Button_Next_clicked() {
    QString userAnswerStr = ui->Edit_Ans->text();
    bool ok;
    int userAnswer = userAnswerStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number.");
        ui->Edit_Ans->setFocus();
        return;
    }

    if (userAnswer == correctAnswer) {
        QMessageBox::information(this, "Correct", "Great! You got it right.");
        updateScore(1); // score plus
        generateNewQuestion();
    } else {
        QMessageBox::critical(this, "Incorrect", QString("Sorry, that's not correct.\nYour final score is %1.\nGame Over!").arg(currentScore));
        this->hide();
        MainWindow *mainWin = MainWindow::instance();
        if (mainWin) {
            mainWin->game_status = 0; // 更新游戏状态
        }
        mainWin->game_status=0;
        if (mainWin) {
            mainWin->show();
            mainWin->raise();
            mainWin->activateWindow();
        }
    }
}



void GameWindow::generateNewQuestion()
{
    int a = get_randint();
    int b = get_randint();
    correctAnswer = a + b;

    // show question
    QString question = QString::number(a) + " + " + QString::number(b) + " = ";
    ui->label_formular->setText(question);

    // reset Edit_Ans
    ui->Edit_Ans->clear();
}


void GameWindow::updateScore(int points) {
    currentScore += points; // update score
    ui->label_score->setText(QString("Score: %1").arg(currentScore)); // show new score
}


GameWindow::~GameWindow()
{
    delete ui;
}






