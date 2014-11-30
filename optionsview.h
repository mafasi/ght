#ifndef GUI_H
#define GUI_H

#include "precomp.h"

namespace Ui {
class OptionsView;
class LabelSliderEditWidget;
}

class QKeyEvent;

class OptionsView : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsView(QObject *parent = 0);
    ~OptionsView();

    void initialize(std::vector<DoubleParameter> parameters);

    void keyPressEvent(QKeyEvent *event);

signals:
    //void out(std::vector<DoubleParameter> parameter);
    void detect();


private:
    QObject*            _parent;
    Ui::OptionsView*    _ui;
};

#endif // GUI_H
