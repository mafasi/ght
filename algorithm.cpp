#include "algorithm.h"
#include <QDebug>

Algorithm::Algorithm(QObject *parent) :
    QObject(parent)
{
    _ght = cv::createGeneralizedHoughBallard();
}

void Algorithm::setTemplate(cv::Mat mat)
{
    _ght->setTemplate(_templateImage = mat);
}

void Algorithm::setImage(cv::Mat mat)
{
    _detectImage = mat;
}

void Algorithm::setParameters(const std::vector<DoubleParameter> &parameters)
{
    Algorithm::printParameters(parameters);
    foreach (DoubleParameter parameter, parameters) {
        switch (std::get<Type> (parameter))
        {
        case ParameterType::MinDist:
            _ght->setMinDist(std::get<Default> (parameter));
            break;
        case ParameterType::VotesThreshold:
            _ght->setVotesThreshold(std::get<Default>(parameter));
            break;
        case ParameterType::MaxBufferSize:
            _ght->setMaxBufferSize(std::get<Default>(parameter));
            break;
        case ParameterType::Dp:
            _ght->setDp(std::get<Default>(parameter));
            break;
        case ParameterType::Levels:
            _ght->setLevels(std::get<Default>(parameter));
            break;
        default:
            qDebug() << "Algorithm::setParamters(): unknown type: "  << std::get<Type> (parameter);
        }
    }
}



void Algorithm::detect()
{
    std::vector<cv::Vec4f> positions;
    try {
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
        emit done(out);
    } catch (cv::Exception ex) {
        qDebug() << "Algorithm::detect(): " << ex.what();
    }
}

void Algorithm::printParameters(const std::vector<DoubleParameter> &parameters)
{
    qDebug() << "----------------";
    foreach (DoubleParameter parameter, parameters)
        qDebug() << QString::fromStdString(std::get<Description>(parameter)) << "=" << QString::number(std::get<Default>(parameter)) ;
    qDebug() << "----------------";

}

