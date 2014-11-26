#include "optionsview.h"
#include "ui_optionsview.h"
#include "labelslidereditwidget.h"

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>

OptionsView::OptionsView(Algorithm &algorithm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsView),
    _alg(algorithm),
    _currentParameter(algorithm.parameters())
{
    ui->setupUi(this);
    initialize();
}

OptionsView::~OptionsView()
{
    delete ui;
}

void OptionsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_O:
    case Qt::Key_Escape:
        this->hide();
        break;
    case Qt::Key_D:
        _alg.detect();
        break;
    default:
        break;
    }
}

void OptionsView::in(int value, ParameterType type)
{
    qDebug() << "OptionsView::in(int value, ParameterType type)" << value << ", " << type;
    foreach (DoubleParamter parameter, _currentParameter)
    {
        if (std::get<Type>(parameter) == type)
            std::get<Default>(parameter) = value;
    }
    _alg.setParameters(_currentParameter);
}

void OptionsView::initialize()
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    foreach (DoubleParamter parameter, _currentParameter)
    {
        LabelSliderEditWidget* widget = new LabelSliderEditWidget(this);
        widget->configure(parameter);
        layout->addWidget(widget);
        connect(widget, SIGNAL(valueChanged(int,ParameterType)), this, SLOT(in(int,ParameterType)));
    }
    setLayout(layout);

}
