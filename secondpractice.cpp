#include "secondpractice.h"
#include "ui_secondpractice.h"

SecondPractice::SecondPractice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondPractice)
{
    ui->setupUi(this);
}

SecondPractice::~SecondPractice()
{
    delete ui;
}

void SecondPractice::slot_btnCompile()
{

}
