#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <QMainWindow>

namespace Ui {
class Kalkulator;
}

class Kalkulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kalkulator(QWidget *parent = nullptr);
    ~Kalkulator();

private:
    Ui::Kalkulator *ui;
};

#endif // KALKULATOR_H
