#ifndef SECONDPRACTICE_H
#define SECONDPRACTICE_H

#include <QWidget>

namespace Ui {
class SecondPractice;
}

class SecondPractice : public QWidget
{
    Q_OBJECT

public:
    explicit SecondPractice(QWidget *parent = nullptr);
    ~SecondPractice();

private:
    Ui::SecondPractice *ui;

private slots:
    void slot_btnCompile();
};

#endif // SECONDPRACTICE_H
