#ifndef GUI_H
#define GUI_H

#include <QWidget>

#include "algorithm.h"

namespace Ui {
class OptionsView;
class LabelSliderEditWidget;
}

class QKeyEvent;

class OptionsView : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsView(Algorithm& algorithm, QWidget *parent = 0);
    ~OptionsView();

    void keyPressEvent(QKeyEvent *event);

private slots:
    void in(int value, ParameterType type);

private:
    void initialize();

private:
    Ui::OptionsView *ui;
    Algorithm& _alg;
    const std::vector<DoubleParamter>& _currentParameter;
};

#endif // GUI_H
