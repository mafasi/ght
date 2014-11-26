#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

#include <opencv2/opencv.hpp>

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
    explicit ImageView(Algorithm& alg, QWidget *parent = 0);
    ~ImageView();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void viewImageB(const cv::Mat &image);

private:
    void viewImage(Panel panel, const cv::Mat &mat);
    cv::Mat loadFileFromFileOpenDialog();
private:
    Ui::ImageView*  _ui;
    OptionsView*    _options;
    Algorithm&      _alg;
};

#endif // IMAGEVIEW_H
