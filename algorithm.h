#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>
#include <tuple>

#include <QObject>
#include <opencv2/opencv.hpp>

enum ParameterType
{
    MinDist,
    Levels,
    VotesThreshold,
    Dp,
    MaxBufferSize
};


enum {
    Type = 0,
    Description = 1,
    Minimum = 2,
    Maximum = 3,
    Default = 4
};


typedef std::tuple<ParameterType, std::string, double, double, double> DoubleParameter;

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm(QObject *parent = 0);

signals:
    void done(cv::Mat image);

public slots:
    void setTemplate(cv::Mat mat);
    void setImage(cv::Mat mat);
    void setParameters(const std::vector<DoubleParameter> &parameters);
    void detect();

    static void printParameters(const std::vector<DoubleParameter>& parameters);

private:
    cv::Ptr<cv::GeneralizedHoughBallard>    _ght;
    cv::Mat                                 _templateImage;
    cv::Mat                                 _detectImage;

};

#endif // ALGORITHM_H
