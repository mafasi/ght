#include "ghtalgorithm.h"

GHTAlgorithm::GHTAlgorithm(QObject *parent) :
    QObject(parent)
{
    _ght = cv::createGeneralizedHoughBallard();
}

void GHTAlgorithm::setTemplate(cv::Mat mat, cv::Point center)
{
    _ght->setTemplate(_templateImage = mat, center);
}

void GHTAlgorithm::setImage(cv::Mat mat)
{
    _detectImage = mat;
}

void GHTAlgorithm::setParameters(const std::vector<DoubleParameter> &parameters)
{
    GHTAlgorithm::printParameters(parameters);
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



void GHTAlgorithm::detect()
{
    std::vector<cv::Vec4f> positions;
    try {
        //_ght->detect(_detectImage, positions);

        cv::Mat edges;
        cv::Mat dx; cv::Mat dy;
        calcEdges(_detectImage, edges, dx, dy);

        cv::imshow("edges", edges);
        cv::imshow("dx", dx);
        cv::imshow("dy", dy);
        cv::waitKey();
        cv::destroyAllWindows();

        cv::Mat votes;

        _ght->detect(edges, dx, dy, positions, votes);

        cv::imshow("votes", votes);
        cv::waitKey();
        cv::destroyAllWindows();

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

void GHTAlgorithm::printParameters(const std::vector<DoubleParameter> &parameters)
{
    qDebug() << "----------------";
    foreach (DoubleParameter parameter, parameters)
        qDebug() << QString::fromStdString(std::get<Description>(parameter)) << "=" << QString::number(std::get<Default>(parameter)) ;
    qDebug() << "----------------";

}

using namespace cv;
void GHTAlgorithm::calcEdges(cv::InputArray _src, cv::Mat& edges, cv::Mat& dx, cv::Mat& dy)
{

    int cannyLowThresh_ = 60;
    int cannyHighThresh_ = 90;
    Mat src = _src.getMat();

    CV_Assert( src.type() == CV_8UC1 );
    CV_Assert( cannyLowThresh_ > 0 && cannyLowThresh_ < cannyHighThresh_ );

    Canny(src, edges, cannyLowThresh_, cannyHighThresh_);
    Sobel(src, dx, CV_32F, 1, 0);
    Sobel(src, dy, CV_32F, 0, 1);
}

