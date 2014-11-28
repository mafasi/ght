#include "labelslidereditwidget.h"
#include "ui_labelslidereditwidget.h"

LabelSliderEditWidget::LabelSliderEditWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::LabelSliderEditWidget)
{
    _ui->setupUi(this);
    connect(_ui->slider, SIGNAL(valueChanged(int)), this, SLOT(update(int)));
}

LabelSliderEditWidget::~LabelSliderEditWidget()
{
    delete _ui;
}

void LabelSliderEditWidget::configure(DoubleParameter paramter)
{
    _ui->slider->setMinimum(std::get<Minimum>(paramter));
    _ui->slider->setMaximum(std::get<Maximum>(paramter));
    _ui->slider->setValue(std::get<Default>(paramter));
    _ui->edit->setPlainText(QString::number(std::get<Default>(paramter)));
    _ui->label->setText(QString::fromStdString(std::get<Description>(paramter)));
    _type = std::get<Type>(paramter);
}

void LabelSliderEditWidget::update(int value)
{
    _ui->edit->setPlainText(QString::number(value));
    emit valueChanged(value, _type);
}
