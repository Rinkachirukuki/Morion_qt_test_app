#include "addform.h"
#include "ui_addform.h"

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
}

void AddForm::setTitle(QString title){
    this->setWindowTitle(title);
}

void AddForm::setPrjGroupId(int  prj_group_id){
    this->prj_group_id =  prj_group_id;
}

void AddForm::setPrjGroupAddrbookId(int prj_group_addrbook_id){
    this->prj_group_addrbook_id = prj_group_addrbook_id;
}

void AddForm::setFamily(QString family){
    ui->lineEdit->setText(family);
}

void AddForm::setFirstName(QString fname){
    ui->lineEdit_2->setText(fname);
}

void AddForm::setButtonText(QString text){
    ui->pushButton->setText(text);
}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::on_pushButton_clicked()
{
    ui->lineEdit->text();
    ui->lineEdit_2->text();
    emit addPrjGroupAddrbook(PrjGroupAddrbookAnswer(prj_group_addrbook_id,ui->lineEdit->text(),ui->lineEdit_2->text(), prj_group_id));
    this->close();
}

void AddForm::mainFormCloseHandler(){

    this->close();
}
