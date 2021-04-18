#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "structures.h"

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

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlTableModel* model;

    QMap<QString, int> cBoxItems;
    QMap<QString, int> loadComboBoxItems();
    void updateComboBox();

    QList<prj_group_addrbook_answer> loadListWidgetItems(int id);
    void updateListWidget(int id);

    void showEvent(QShowEvent* e) override;
private slots:
    void connectToDataBase();
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

signals:
    void reconnect();

};
#endif // MAINWINDOW_H
