#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "precomp.h"

class GHTAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit GHTAlgorithm(QObject *parent = 0);

signals:
    void done(cv::Mat image);

public slots:
    void setTemplate(cv::Mat mat, cv::Point center);
    void setImage(cv::Mat mat);
    void setParameters(const std::vector<DoubleParameter> &parameters);
    void detect();

    static void printParameters(const std::vector<DoubleParameter>& parameters);

private:
    // taken from OpenCV's generalized_hough.cpp
    void calcEdges(cv::InputArray _src, cv::Mat& edges, cv::Mat& dx, cv::Mat& dy);


private:
    cv::Ptr<cv::GeneralizedHoughBallard>    _ght;
    cv::Mat                                 _templateImage;
    cv::Mat                                 _detectImage;

};

#endif // ALGORITHM_H
