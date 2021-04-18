#ifndef ADDFORM_H
#define ADDFORM_H

#include <QWidget>

namespace Ui {
class AddForm;
}

class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = nullptr);
    ~AddForm();

private:
    Ui::AddForm *ui;
};

#endif // ADDFORM_H
