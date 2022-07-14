#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {
    QVector<int> c = QVector<int>(3);
    board.push_back(c);
    board.push_back(c);
    board.push_back(c);
}

void MainWindow::playerMove(QString name) {
    QToolButton *btn = ui->gridWidget->findChild<QToolButton *>(name);
    if(btn->icon().isNull()) {
        btn->setIcon(QIcon(":/images/images/o.png"));
        btn->setIconSize(QSize(150,150));

        QChar c = name[name.size() - 1];
        if(c == QChar('n')) {
            c = '1';
        }
        int val  = c.digitValue() - 1;
        int col = val / 3;
        int lin = val % 3;
        board[col][lin] = 1;
        for(int i = 0; i < 3; i++) {
                qDebug() << board[i][0] << " " << board[i][1] << " " << board[i][2];
        }
    }else {
        return;
    }
}

void MainWindow::aiMove() {


}










void MainWindow::on_toolButton_clicked()
{
    playerMove("toolButton");
}

void MainWindow::on_toolButton_2_clicked()
{
    playerMove("toolButton_2");
}


void MainWindow::on_toolButton_3_clicked()
{
    playerMove("toolButton_3");
}


void MainWindow::on_toolButton_4_clicked()
{
    playerMove("toolButton_4");
}


void MainWindow::on_toolButton_5_clicked()
{
    playerMove("toolButton_5");
}

void MainWindow::on_toolButton_6_clicked()
{
    playerMove("toolButton_6");
}


void MainWindow::on_toolButton_7_clicked()
{
    playerMove("toolButton_7");
}


void MainWindow::on_toolButton_8_clicked()
{
    playerMove("toolButton_8");
}


void MainWindow::on_toolButton_9_clicked()
{
    playerMove("toolButton_9");
}

