#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addform.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QListWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent * e) override;

private:
    Ui::MainWindow *ui;

    DBConnector* dbconnector;
    QSqlTableModel* model;

    bool ascSort = true;

    void updateComboBox();
    void updateListWidget();

    void connectToDataBase();
    void createCompleter();

    AddForm* prepareAddFormEditVer(PrjGroupAddrbookAnswer listItem, PrjGroupAnswer combItem);

    void showEvent(QShowEvent * e) override;
private slots:
    void addPrjGroupAddrbook(PrjGroupAddrbookAnswer item);
    void callMessage(QString text);

    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_3_clicked();

signals:
    void closeHandler();

};
#endif // MAINWINDOW_H
