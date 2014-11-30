#ifndef LABELSLIDEREDITWIDGET_H
#define LABELSLIDEREDITWIDGET_H

#include "precomp.h"

namespace Ui {
class LabelSliderEditWidget;
}

class LabelSliderEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LabelSliderEditWidget(QWidget *parent = 0);
    ~LabelSliderEditWidget();

signals:
    void valueChanged(int value, ParameterType type);

public slots:
    void configure(DoubleParameter paramter);
    void update(int value);

private:
    Ui::LabelSliderEditWidget* _ui;
    ParameterType _type;

};

#endif // LABELSLIDEREDITWIDGET_H
