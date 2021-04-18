#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDialog>
#include <QDir>
#include <QMap>
#include <QMessageBox>
#include <QList>


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

    bool connected = db.open();

    if (!connected)
        do {
            QMessageBox msgBox;

            msgBox.setText(tr("Ошибка подключения к БД."));

            QPushButton* pButtonYes = msgBox.addButton(tr("Повторить подключение"), QMessageBox::YesRole);
            msgBox.addButton(tr("Выход"), QMessageBox::NoRole);

            msgBox.exec();

            if ((QPushButton*)(msgBox.clickedButton()) != pButtonYes)
                exit(0);


    } while(!connected);
}

QMap<QString, int> MainWindow::loadComboBoxItems(){

    connectToDataBase();

    QMap<QString, int> map = QMap<QString, int>();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec("SELECT prj_group_id, name FROM prj_group")){

        QMessageBox msgBox;

        msgBox.setText("Произошла ошибка при выполнении запроса к БД: \n" + query.lastError().text());
        msgBox.exec();

        exit(0);
    }

    while(query.next()){
        map.insert(query.value(1).toString(),query.value(0).toInt());
}

    return map;

}

void MainWindow::updateComboBox(){

    cBoxItems = loadComboBoxItems();

    ui->comboBox->clear();

    QList<QString> keys = cBoxItems.keys();

    foreach (QString item, keys){
        ui->comboBox->addItem(item);
    }
}

QList<prj_group_addrbook_answer> MainWindow::loadListWidgetItems(int id){

    connectToDataBase();

    QList<prj_group_addrbook_answer> list = QList<prj_group_addrbook_answer>();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(("SELECT prj_group_addrbook_id, family, first_name FROM prj_group_addrbook WHERE prj_group_id = ") + QString::number(id))){

        QMessageBox msgBox;

        msgBox.setText("Произошла ошибка при выполнении запроса к БД: \n" + query.lastError().text());
        msgBox.exec();

        exit(0);
    }


    while(query.next()){
        list.append(prj_group_addrbook_answer(query.value(0).toString(),query.value(1).toString(),query.value(2).toString()));
}

    return list;

}



void MainWindow::updateListWidget(int id){

    ui->listWidget->clear();

    QList<prj_group_addrbook_answer> lWidItems = loadListWidgetItems(id);

    foreach (prj_group_addrbook_answer item, lWidItems){

        QListWidgetItem *wlItem = new QListWidgetItem(item);

        QVariant qv = QVariant();

        qv.setValue(item);

        wlItem->setData(Qt::UserRole, qv);

        ui->listWidget->addItem(wlItem);
    }

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->listWidget->clear();

    updateListWidget(cBoxItems.find(arg1).value());
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    prj_group_addrbook_answer i = item->data(Qt::UserRole).value<prj_group_addrbook_answer>();

    qDebug() << i.prj_group_addrbook_id;
}

MainWindow::~MainWindow()
{
    delete ui;
}

