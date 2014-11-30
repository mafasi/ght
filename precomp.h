#ifndef PRECOMP_H
#define PRECOMP_H

#include <string>
#include <vector>
#include <tuple>
#include <vector>
#include <iostream>

#include <QWidget>
#include <QObject>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QVBoxLayout>
#include <QPushButton>

#include <opencv2/opencv.hpp>

enum ParameterType
{
    MinDist,
    Levels,
    VotesThreshold,
    Dp,
    MaxBufferSize
};

enum Panel {
    A,
    B
};

enum {
    Type = 0,
    Description = 1,
    Minimum = 2,
    Maximum = 3,
    Default = 4
};

typedef std::tuple<ParameterType, std::string, double, double, double> DoubleParameter;

class ImageView;
class GHTAlgorithm;
class OptionsView;

#endif // PRECOMP_H
