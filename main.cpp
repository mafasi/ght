#include <QApplication>
#include <QDir>
#include <QDebug>

#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "optionsview.h"
#include "imageview.h"
#include "algorithm.h"

int main(int argc, char *argv[])
{
    using namespace std;

    QApplication a(argc, argv);
    qDebug() << "working dir: " << QDir::currentPath();
    qDebug() << "executable dir: " << QCoreApplication::applicationDirPath();

    Algorithm alg;

    ImageView imageView (alg);
    imageView.show();

    a.exec();

    std::vector<std::string> fileNames = {"Img_01.png", "Img_02.png", "Img_03.png"};
    foreach (std::string fileName, fileNames) {

    }

    //return a.exec();
}
