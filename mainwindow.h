#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

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

    QMap<int, QString> cBoxItems;
    QMap<int, QString> loadComboBoxItems();
    void updateComboBox();

    void showEvent(QShowEvent* e) override;
private slots:
    void connectToDataBase();
    void on_comboBox_currentIndexChanged(const QString &arg1);

signals:
    void reconnect();

};
#endif // MAINWINDOW_H
