#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolButton>
#include <QTime>
#include <QRandomGenerator>
#include <QMessageBox>

bool done = false;

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
    if(not done) {
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
        draw();

        if(end() != 0) {
            endMessage(end());
            return;
        }
        aiMove();

        draw();

        if(end() != 0) {
            endMessage(end());
            return;
        }

    }else {
        return;
    }
}
}

void MainWindow::aiMove() {

    int row{-1}, col{-1}, dia{-1};
    int i, j;

    if(winnable(board, row, col, dia)) {

        if(row >= 0) {
            if(board[row][empty_c(row)] != 1) {
                board[row][empty_c(row)] = 2;
            }
            return;
        }

        if(col >= 0) {

            if(board[empty_r(col)][col] != 1) {
                board[empty_r(col)][col] = 2;
            }
            return;
        }

        if(dia == 0) {

            if(board[0][0] != 1 and board[1][1] != 1 and board[2][2] != 1) {
                board[0][0] = 2;
                board[1][1] = 2;
                board[2][2] = 2;

            }
            return;

        }else if(dia == 1) {

            if(board[0][2] != 1 and board[1][1] != 1 and board[2][0] != 1) {
                board[0][2] = 2;
                board[1][1] = 2;
                board[2][0] = 2;

            }
            return;

        }

    }

    if(vulnerable(board, row, col, dia)) {
        if(col > 0) {

            if( board[empty_r(col)][col] != 1) {
                board[empty_r(col)][col] = 2;
            }
            return;
        }

        //qDebug() << "row test";
        if(row > 0) {

            if(board[row][empty_c(row)] != 1) {
                board[row][empty_c(row)] = 2;
            }
            return;
        }

        //qDebug() << "dia test";
        if(dia == 0) {

            if(board[0][0] != 1) {
                board[0][0] = 2;
                return;
            }

            if(board[1][1] != 1) {
                board[1][1] = 2;
                return;
            }

            if(board[2][2] != 1) {
                board[2][2] = 2;
                return;
            }
            return;
        }

        if(dia == 1) {

            if(board[0][2] != 1) {
                board[0][2] = 2;
                return;
            }

            if(board[1][1] != 1) {
                board[1][1] = 2;
                return;
            }

            if(board[2][0] != 1) {
                board[2][0] = 2;
                return;
            }
            return;
        }
    }


    while(true) {
        QRandomGenerator generator(QDateTime::currentMSecsSinceEpoch());
        i = generator.bounded(0,3);
        j = generator.bounded(0,3);
        if(board[i][j] == 1) {
            continue;
        }else {
            break;
        }
    }
    if(board[i][j] != 1) {
        board[i][j] = 2;
        return;
    }

}

bool vulnerable(QVector<QVector<int>> board, int &row, int &col, int &dia) {

    int a, b, c, d, e, f, g, h, i;
    a = board[0][0], b = board[0][1], c = board[0][2];
    d = board[1][0], e = board[1][1], f = board[1][2];
    g = board[2][0], h = board[2][1], i = board[2][2];

    //check row
    if( (a == 1 and b == 1 and c != 2) or (a == 1 and b != 2 and c == 1) or (a != 2 and b == 1 and c == 1) ) {
        row = 0;
        return true;
    }

    if( (d == 1 and e == 1 and f != 2) or (d == 1 and e != 2 and f == 1) or (d != 2 and e == 1 and f == 1)) {
        row = 1;
        return true;
    }

    if( (g == 1 and h == 1 and i != 2) or (g == 1 and h != 2 and i == 1) or (g != 2 and h == 1 and i == 1)) {
        row = 2;
        return true;
    }

    //check column
    if( (a == 1 and d == 1 and g != 2) or (a == 1 and d != 2 and g == 1) or (a != 2 and d == 1 and g == 1)) {
        col = 0;
        return true;
    }

    if( (b == 1 and e == 1 and h != 2) or (b == 1 and e != 2 and h == 1) or (b != 2 and e == 1 and h == 1)) {
        col = 1;
        return true;
    }

    if( (c == 1 and f == 1 and i != 2) or (c == 1 and f != 2 and i == 1) or (c != 2 and f == 1 and i == 1)) {
        col = 2;
        return true;
    }

    //check dia
    if( (a == 1 and e == 1 and i != 2) or (a == 1 and e != 2 and i == 1) or (a != 2 and e == 1 and i == 1)) {
        dia = 0;
        return true;
    }
    if( (c == 1 and e == 1 and g != 2) or (c == 1 and e != 2 and g == 1) or (c != 2 and e == 1 and g == 1)) {
        dia = 1;
        return true;
    }
    return false;

}

int MainWindow::end() {
    bool tie = true;
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] and board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    for(int i = 0; i < 3; i++) {
        if(board[0][i] == board[1][i] and board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == 0) {
                tie = false;
            }
        }
    }

    if(board[0][0] == board[1][1] and board[0][0] == board[2][2]) {
        return board[0][0];
    }

    if(board[0][2] == board[1][1] and board[0][0] == board[2][0]) {
        return board[0][2];
    }
    if(tie) {
        return 3;
    }
    return 0;
}

void MainWindow::endMessage(int p) {
    QMessageBox msgBox;
    if(p == 1) {
        msgBox.setText("You have won!!");
    }else if(p == 2) {
        msgBox.setText("The ai dabbed on you!");
    }else {
        msgBox.setText("The game is a tie");
    }

    msgBox.setInformativeText("Do you want to start a new game?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes) {
        for(int i = 0; i < 3; i++) {
            for(int j =0; j < 3; j++) {
                board[i][j] = 0;
            }
        }
        draw();
        done = false;
 }else if(ret == QMessageBox::No) {
        done = true;
    }
}

bool winnable(QVector<QVector<int>> board,int &row, int &col, int &dia) {

    int a, b, c, d, e, f, g, h, i;
    a = board[0][0], b = board[0][1], c = board[0][2];
    d = board[1][0], e = board[1][1], f = board[1][2];
    g = board[2][0], h = board[2][1], i = board[2][2];

    //check row
    if( (a == 2 and b == 2 and c != 1) or (a == 2 and b != 1 and c == 2) or (a != 1 and b == 2 and c == 2) ) {
        row = 0;
        return true;
    }

    if( (d == 2 and e == 2 and f != 1) or (d == 2 and e != 1 and f == 2) or (d != 1 and e == 2 and f == 2)) {
        row = 1;
        return true;
    }

    if( (g == 2 and h == 2 and i != 1) or (g == 2 and h != 1 and i == 2) or (g != 1 and h == 2 and i == 2)) {
        row = 2;
        return true;
    }

    //check column
    if( (a == 2 and d == 2 and g != 1) or (a == 2 and d != 1 and g == 2) or (a != 1 and d == 2 and g == 2)) {
        col = 0;
        return true;
    }

    if( (b == 2 and e == 2 and h != 1) or (b == 2 and e != 1 and h == 2) or (b != 1 and e == 2 and h == 2)) {
        col = 1;
        return true;
    }

    if( (c == 2 and f == 2 and i != 1) or (c == 2 and f != 1 and i == 2) or (c != 1 and f == 2 and i == 2)) {
        col = 2;
        return true;
    }

    //check dia
    if( (a == 2 and e == 2 and i != 1) or (a == 2 and e != 1 and i == 2) or (a != 1 and e == 2 and i == 2)) {
        dia = 0;
        return true;
    }
    if( (c == 2 and e == 2 and g != 1) or (c == 2 and e != 1 and g == 2) or (c != 1 and e == 2 and g == 2)) {
        dia = 1;
        return true;
    }
    return false;
}

int MainWindow::empty_c(int r) {
    for(int i = 0; i < 3; i++) {
        if(board[r][i] == 0){
            return i;
        }
    }
}

int MainWindow::empty_r(int c)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][c] == 0)
            return i;
    }
}

void MainWindow::draw() {

    for(int i = 0; i < 3; i++) {

        for(int j = 0; j  < 3; j++) {

            QString name = "toolButton_";
            if (i == 0 and j == 0) {

                name = "toolButton";

            }else {

                int helper = 3 * i + j + 1;
                name += QString::number(helper);
            }

            QToolButton *btn = ui->gridWidget->findChild<QToolButton *>(name);

            if(board[i][j] == 0) {
                btn->setIcon(QIcon());
            }

            if(board[i][j] == 1) {
                btn->setIcon(QIcon(":/images/images/o.png"));
            }
            if(board[i][j] == 2) {
                btn->setIcon(QIcon(":/images/images/x.png"));
            }

            btn->setIconSize(QSize(150,150));
        }
    }
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


void MainWindow::on_toolButton_11_clicked()
{
    for(int i = 0; i < 3; i++) {
        for(int j =0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
    done = false;
    draw();
}


void MainWindow::on_BtnBack_clicked()
{
    close();
}

