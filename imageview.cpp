#include "imageview.h"
#include "ui_imageview.h"

#include <QKeyEvent>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include "optionsview.h"
#include <QDebug>
#include <vector>


ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ImageView),
    _options(new OptionsView(this)),
    _parameters{
        DoubleParameter(ParameterType::MinDist, "Minimal Distance", 1.0, 100.0, 10.0),
        DoubleParameter(ParameterType::Levels, "levels", 36.0, 3600.0, 360.0),
        DoubleParameter(ParameterType::MaxBufferSize, "Max Buffer Size", 100.0, 10000.0, 1000.0),
        DoubleParameter(ParameterType::Dp, "Dp", 1.0, 100.0, 10.0),
        DoubleParameter(ParameterType::VotesThreshold, "Votes Threshold", 1.0, 255.0, 30.0)
    }
{
    _ui->setupUi(this);
    //connect(&_alg, SIGNAL(done(cv::Mat)), this, SLOT(viewImageB(cv::Mat)));
    connect(_ui->pushButton, SIGNAL(clicked()), this, SLOT(detect()));
    _options->initialize(_parameters);
}

ImageView::~ImageView()
{
    delete _ui;
    delete _options;
}

void ImageView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_T:  // load template
        _template = loadFileFromFileOpenDialog();
        viewImage(Panel::A, _template);
        break;
    case Qt::Key_L:  // Load Image
        _image = loadFileFromFileOpenDialog();
        viewImage(Panel::B, _image);
        break;
    case Qt::Key_D:
        detect();
        break;
    case Qt::Key_O: //options
        if (_options->isHidden())
            _options->show();
        else
            _options->hide();
        break;
    case Qt::Key_Escape:
        QApplication::exit();
    default:
        break;
    }
}

void ImageView::viewImageB(const cv::Mat& image)
{
    viewImage(Panel::B, image);
}

void ImageView::detect()
{
    Algorithm ght;
    connect(&ght, SIGNAL(done(cv::Mat)), this, SLOT(viewImageB(cv::Mat)));
    ght.setTemplate(_template);
    ght.setParameters(_parameters);
    ght.setImage(_image);
    ght.detect();
}

void ImageView::inParameter(int value, ParameterType type)
{
    std::for_each (_parameters.begin(), _parameters.end(), [type, value](DoubleParameter& parameter)
    {
        if (std::get<Type>(parameter) == type)
            std::get<Default>(parameter) = value;
    });

}

void ImageView::viewImage(Panel panel, const cv::Mat& mat)
{
    qDebug() << "ImageView::viewImage(): dims: " << mat.dims << "cannels:" << mat.channels();
    const uchar *qImageBuffer = (const uchar*)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img;
    if (mat.channels() == 1)
        img = QImage (qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    else if (mat.channels() == 3)
    {
        img = QImage (qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        img = img.rgbSwapped();
    }
    switch (panel)
    {
    case A:
        _ui->imageA->setPixmap(QPixmap::fromImage(img));
        break;
    case B:
        _ui->imageB->setPixmap(QPixmap::fromImage(img));
        break;
    default:
        qDebug() << "ImageView::viewImage(): unexpected panel.";
        abort();
        break;
    }
}

cv::Mat ImageView::loadFileFromFileOpenDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    cv::Mat mat = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
    return mat;
}


