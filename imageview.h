#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

#include <opencv2/opencv.hpp>
#include "algorithm.h"

namespace Ui {
class ImageView;
}

class QKeyEvent;
class Algorithm;
class OptionsView;

enum Panel {
    A,
    B
};

class ImageView : public QWidget
{
    Q_OBJECT

public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void viewImageB(const cv::Mat &image);
    void inParameter(int value, ParameterType type);


private slots:
    void detect();

private:
    void viewImage(Panel panel, const cv::Mat &mat);
    cv::Mat loadFileFromFileOpenDialog();

private:
    Ui::ImageView*                  _ui;
    OptionsView*                    _options;
    cv::Mat                         _template;
    cv::Mat                         _image;
    std::vector<DoubleParameter>   _parameters;

};

#endif // IMAGEVIEW_H
