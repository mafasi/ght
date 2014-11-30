#include "optionsview.h"
#include "ui_optionsview.h"

#include "labelslidereditwidget.h"

OptionsView::OptionsView(QObject *parent) :
    _parent(parent),
    _ui(new Ui::OptionsView)
{
    _ui->setupUi(this);
}

OptionsView::~OptionsView()
{
    delete _ui;
}

void OptionsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_O:
    case Qt::Key_Escape:
        this->hide();
        break;
    case Qt::Key_D:
        emit detect();
        break;
    default:
        break;
    }
}


void OptionsView::initialize(std::vector<DoubleParameter> parameters)
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    foreach (DoubleParameter parameter, parameters)
    {
        LabelSliderEditWidget* widget = new LabelSliderEditWidget(this);
        widget->configure(parameter);
        layout->addWidget(widget);
        connect(widget, SIGNAL(valueChanged(int,ParameterType)), _parent, SLOT(inParameter(int,ParameterType)));
    }
    setLayout(layout);
    connect(this, SIGNAL(detect()), _parent, SLOT(detect()));

}
