#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///TODO porting DB to PostgreSQL
QVector<QString> MainWindow::loadDBuser(){

    QVector<QString> credentials;
    QFile db_file(QCoreApplication::applicationDirPath() + "/input.txt");

    if (!db_file.open(QFile::ReadOnly | QFile::Text) || !db_file.exists()){
        qDebug() << "Couldn't open the file.";
        qDebug() << QCoreApplication::applicationDirPath();
        qDebug() << "Error: " << db_file.errorString();
        exit(EXIT_FAILURE);
      }

    QTextStream in(&db_file);
    QString usernameDB = in.readLine();
    QString passwordDB = in.readLine();
    db_file.close();

    credentials.append(usernameDB);
    credentials.append(passwordDB);

    return credentials;

};

void MainWindow::validate(){

    QVector<QString> credentials = loadDBuser();

    QString usernameInput = ui->userInput->text();
    QString passwordInput = ui->pwInput->text();

    QString res = credentials.at(0) == usernameInput && credentials.at(1) == passwordInput ? "Logged in!" : "Login in failed";

    ui->textEdit->setPlainText(res);

}

void MainWindow::on_loginButton_clicked()
{
    validate();
}



