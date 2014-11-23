#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    using namespace std;
    QCoreApplication a(argc, argv);
    qDebug() << "working dir: " << QDir::currentPath();
    qDebug() << "executable dir: " << QCoreApplication::applicationDirPath();

    cv::Mat templateImage = cv::imread("contour_def2.bmp", cv::IMREAD_GRAYSCALE);

    cv::Ptr<cv::GeneralizedHoughBallard> ght = cv::createGeneralizedHoughBallard();

    ght->setMinDist(1.0);
    ght->setLevels(360);
    ght->setDp(1.0);
    ght->setMaxBufferSize(1000);
    ght->setVotesThreshold(30);
    ght->setTemplate(templateImage);

    std::vector<std::string> fileNames = {"Img_01.png", "Img_02.png", "Img_03.png"};
    foreach (std::string fileName, fileNames) {
        cv::Mat detectImage = cv::imread(fileName, cv::IMREAD_GRAYSCALE);

        std::vector<cv::Vec4f> positions;
        ght->detect(detectImage, positions);


        std::cout << fileName << "'s positions: " << positions.size() << std::endl;

        // back projection
        cv::Mat out;
        cv::cvtColor(detectImage, out, cv::COLOR_GRAY2BGR);
        for (size_t i = 0; i < positions.size(); ++i)
        {
           cv::Point2f pos(positions[i][0], positions[i][1]);
           float scale = positions[i][2];
           float angle = positions[i][3];
           cv::RotatedRect rect;
           rect.center = pos;
           rect.size = cv::Size2f(templateImage.cols * scale, templateImage.rows * scale);
           rect.angle = angle;
           cv::Point2f pts[4];
           rect.points(pts);
           line(out, pts[0], pts[1], cv::Scalar(0, 0, 255), 3);
           line(out, pts[1], pts[2], cv::Scalar(0, 0, 255), 3);
           line(out, pts[2], pts[3], cv::Scalar(0, 0, 255), 3);
           line(out, pts[3], pts[0], cv::Scalar(0, 0, 255), 3);
        }
        imshow("out", out);
        cv::waitKey();
    }

    //return a.exec();
}
