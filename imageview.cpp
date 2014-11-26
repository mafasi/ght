#include "imageview.h"
#include "ui_imageview.h"

#include <QKeyEvent>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include "optionsview.h"
#include <QDebug>


ImageView::ImageView(Algorithm& alg, QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ImageView),
    _options(new OptionsView(alg)),
    _alg(alg)
{
    _ui->setupUi(this);
    connect(&_alg, SIGNAL(done(cv::Mat)), this, SLOT(viewImageB(cv::Mat)));
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
    {
        cv::Mat mat = loadFileFromFileOpenDialog();
        _alg.setTemplate(mat);
        viewImage(Panel::A, mat);
    }
        break;
    case Qt::Key_L:  // Load Image
    {
        cv::Mat mat = loadFileFromFileOpenDialog();
        _alg.setImage(mat);
        viewImage(Panel::B, mat);
    }
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


