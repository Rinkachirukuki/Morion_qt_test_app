#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDialog>
#include <QDir>
#include <QMap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./addrbooks.db");
    connectToDataBase();

}

void MainWindow::showEvent(QShowEvent* e) {
    updateComboBox();
}


void MainWindow::connectToDataBase(){
    if (!db.open()){
        QMessageBox msgBox;

        msgBox.setText(tr("Ошибка подключения к БД. Повторить подключение?"));

        QPushButton* pButtonYes = msgBox.addButton(tr("Да"), QMessageBox::YesRole);
        msgBox.addButton(tr("Нет"), QMessageBox::NoRole);

       msgBox.exec();

       if ((QPushButton*)(msgBox.clickedButton()) == pButtonYes) {
           emit reconnect();
       }
       else{
           exit(0);
       }
    }
}


QMap<int, QString> MainWindow::loadComboBoxItems(){

    connectToDataBase();

    QMap<int, QString> map = QMap<int, QString>();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec("SELECT prj_group_id, name FROM prj_group")){

        QMessageBox msgBox;

        msgBox.setText("Произошла ошибка при выполнении запроса к БД: \n" + query.lastError().text());
        msgBox.exec();

        exit(0);
    }

    while(query.next()){
        map.insert(query.value(0).toInt(),query.value(1).toString());
    }

    return map;
}

void MainWindow::updateComboBox(){

    cBoxItems = loadComboBoxItems();

    ui->comboBox->clear();

    foreach (QString item, cBoxItems){
        ui->comboBox->addItem(item);
    }
}

void


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

}
