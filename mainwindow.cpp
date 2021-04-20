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
#include <QCompleter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbconnector = new DBConnector("QSQLITE","./addrbooks.db");

    QObject::connect(dbconnector, SIGNAL(callMessage(QString)), this, SLOT(callMessage(QString)));

    connectToDataBase();

    createCompleter();

}

void MainWindow::showEvent(QShowEvent* e) {

    updateComboBox();

}

void MainWindow::closeEvent(QCloseEvent * e)
{
    emit closeHandler();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToDataBase(){

    bool connected = dbconnector->isConnected();

    if (!connected)
        do {
            QMessageBox msgBox;

            msgBox.setText(QMessageBox::tr("Ошибка подключения к БД."));

            QPushButton* pButtonYes = msgBox.addButton(QMessageBox::tr("Повторить подключение"), QMessageBox::YesRole);
            msgBox.addButton(QMessageBox::tr("Выход"), QMessageBox::NoRole);

            msgBox.exec();

            if ((QPushButton*)(msgBox.clickedButton()) != pButtonYes)
                exit(0);

    } while(!connected);
}

void MainWindow::callMessage(QString text){

    QMessageBox msgBox;

    msgBox.setText(text);
    msgBox.exec();
}

void MainWindow::updateComboBox(){


    ui->comboBox->clear();
    QList<PrjGroupAnswer> list;
    try {

        list = dbconnector->getPrjGroup();

    }  catch (QSqlError e) {

        callMessage("Проверьте файл БД.\nПроизошла ошибка в запросе:\n" + e.text());

        exit(-1);
    }

    foreach (PrjGroupAnswer item, list){

        QVariant qv = QVariant();

        qv.setValue(item);

        ui->comboBox->addItem(item, qv);
    }
}

void MainWindow::updateListWidget(){

    int id = (ui->comboBox->currentData(Qt::UserRole).value<PrjGroupAnswer>()).prj_group_id;

    ui->listWidget->clear();

    QList<PrjGroupAddrbookAnswer> lWidItems;

    try {

        lWidItems = dbconnector->getPrjGroupAddrbook(id);

    }  catch (QSqlError e) {

       callMessage("Проверьте файл БД.\nПроизошла ошибка в запросе:\n" + e.text());

       exit(-1);
    }

    foreach (PrjGroupAddrbookAnswer item, lWidItems){

        QListWidgetItem *wlItem = new QListWidgetItem(item);

        QVariant qv = QVariant();

        qv.setValue(item);

        wlItem->setData(Qt::UserRole, qv);

        ui->listWidget->addItem(wlItem);
    }

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    updateListWidget();
}



void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    PrjGroupAddrbookAnswer listItem = item->data(Qt::UserRole).value<PrjGroupAddrbookAnswer>();

    PrjGroupAnswer combItem = ui->comboBox->currentData(Qt::UserRole).value<PrjGroupAnswer>();

    AddForm* f = prepareAddFormEditVer(listItem, combItem);

    f->show();


}

void MainWindow::addPrjGroupAddrbook(PrjGroupAddrbookAnswer item){

    QMessageBox msgBox;

    try {

       dbconnector->addchangePrjGroupAddrbook(item);
       updateListWidget();

    }  catch (QSqlError e) {

        callMessage("Невозможно выполнить действие.\nПроизошла ошибка в запросе:\n" + e.text());
    }

}


void MainWindow::on_pushButton_2_clicked()
{

    PrjGroupAnswer i = ui->comboBox->currentData(Qt::UserRole).value<PrjGroupAnswer>();

    AddForm *f = new AddForm();

    f->setTitle("Добавленеие новой записи в " + i.name);
    f->setPrjGroupId(i.prj_group_id);

    QObject::connect(f, SIGNAL(addPrjGroupAddrbook(PrjGroupAddrbookAnswer)), this, SLOT(addPrjGroupAddrbook(PrjGroupAddrbookAnswer)));
    QObject::connect(this, SIGNAL(closeHandler()), f, SLOT(mainFormCloseHandler()));

    f->show();

}

void MainWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();

    if(list.empty()){
        callMessage("Необходимо выделить записи перед удалением");
    }

    foreach (QListWidgetItem* i, list){
        dbconnector->deletePrjGroupAddrbook(i->data(Qt::UserRole).value<PrjGroupAddrbookAnswer>().prj_group_addrbook_id);
    }
}


void MainWindow::createCompleter()
{
    QCompleter* completer = new QCompleter(this);

    auto model = ui->listWidget->model();

    completer->setModel(model);

    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->lineEdit->setCompleter(completer);
    QObject::connect(completer, QOverload<const QModelIndex &>::of(&QCompleter::highlighted),
        [=](const QModelIndex &index) {
            completer->setCurrentRow(index.row());
        }
    );
}

void MainWindow::on_lineEdit_returnPressed()
{
        PrjGroupAddrbookAnswer listItem = ui->lineEdit->completer()->currentIndex().data(Qt::UserRole).value<PrjGroupAddrbookAnswer>();
        PrjGroupAnswer combItem = ui->comboBox->currentData(Qt::UserRole).value<PrjGroupAnswer>();

        AddForm *f = prepareAddFormEditVer(listItem, combItem);

        f->show();

}

AddForm* MainWindow::prepareAddFormEditVer(PrjGroupAddrbookAnswer listItem, PrjGroupAnswer combItem){

    AddForm *f = new AddForm();

    f->setTitle("Обновление записи с id " + QString::number(listItem.prj_group_addrbook_id));
    f->setPrjGroupId(combItem.prj_group_id);
    f->setPrjGroupAddrbookId(listItem.prj_group_addrbook_id);
    f->setFamily(listItem.family);
    f->setFirstName(listItem.first_name);
    f->setButtonText("Обновить запись");

    QObject::connect(f, SIGNAL(addPrjGroupAddrbook(PrjGroupAddrbookAnswer)), this, SLOT(addPrjGroupAddrbook(PrjGroupAddrbookAnswer)));
    QObject::connect(this, SIGNAL(closeHandler()), f, SLOT(mainFormCloseHandler()));

    return f;
}
