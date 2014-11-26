#include "algorithm.h"
#include <QDebug>

Algorithm::Algorithm(QObject *parent) :
    QObject(parent),
    _parameters({
        DoubleParamter(ParameterType::MinDist, "Minimal Distance", 1.0, 100.0, 10.0),
        DoubleParamter(ParameterType::Levels, "levels", 36.0, 360.0, 3600.0),
        DoubleParamter(ParameterType::MaxBufferSize, "Max Buffer Size", 100.0, 1000.0, 10000.0),
        DoubleParamter(ParameterType::Dp, "Dp", 1.0, 100.0, 10.0),
        DoubleParamter(ParameterType::VotesThreshold, "Votes Threshold", 1.0, 255.0, 30.0)
    })
{
    _ght = cv::createGeneralizedHoughBallard();

}

const std::vector<DoubleParamter>& Algorithm::parameters() const
{
    return _parameters;
}

void Algorithm::setTemplate(cv::Mat mat)
{
    _ght->setTemplate(_templateImage = mat);
}

void Algorithm::setImage(cv::Mat mat)
{
    _detectImage = mat;
}

void Algorithm::setParameters(std::vector<DoubleParamter> parameters)
{
    foreach (DoubleParamter parameter, parameters) {
        switch (std::get<Type> (parameter))
        {
        case ParameterType::MinDist:
            _ght->setMinDist(std::get<Default> (parameter));
            break;
        default:
            qDebug() << "Algorithm::setParamters(): unknown type";
        }
    }
}

void Algorithm::detect()
{
    std::vector<cv::Vec4f> positions;
    _ght->detect(_detectImage, positions);


    std::cout << "Detected positions: " << positions.size() << std::endl;

    // back projection
    cv::Mat out;
    cv::cvtColor(_detectImage, out, cv::COLOR_GRAY2BGR);
    for (size_t i = 0; i < positions.size(); ++i)
    {
       cv::Point2f pos(positions[i][0], positions[i][1]);
       float scale = positions[i][2];
       float angle = positions[i][3];
       cv::RotatedRect rect;
       rect.center = pos;
       rect.size = cv::Size2f(_templateImage.cols * scale, _templateImage.rows * scale);
       rect.angle = angle;
       cv::Point2f pts[4];
       rect.points(pts);
       line(out, pts[0], pts[1], cv::Scalar(0, 0, 255), 3);
       line(out, pts[1], pts[2], cv::Scalar(0, 0, 255), 3);
       line(out, pts[2], pts[3], cv::Scalar(0, 0, 255), 3);
       line(out, pts[3], pts[0], cv::Scalar(0, 0, 255), 3);
    }
    imshow("out", out);
    emit done(out);
    cv::waitKey();

}

