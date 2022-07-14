#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_9_clicked();

private:
    Ui::MainWindow *ui;

    //empty: 0, player:1, bot: 2
    QVector<QVector<int>> board;

    void init();



    void playerMove(QString name);

    void aiMove();
};
#endif // MAINWINDOW_H
