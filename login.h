#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "createaccount.h"
#include "kalkulator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::login *ui;
    CreateAccount *createacc;
    Kalkulator *calc;
};
#endif // LOGIN_H
