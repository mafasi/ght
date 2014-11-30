#include "precomp.h"

#include "imageview.h"

int main(int argc, char *argv[])
{
    using namespace std;

    QApplication a(argc, argv);
    qDebug() << "working dir: " << QDir::currentPath();
    qDebug() << "executable dir: " << QCoreApplication::applicationDirPath();


    ImageView imageView;
    imageView.show();

    a.exec();

    std::vector<std::string> fileNames = {"Img_01.png", "Img_02.png", "Img_03.png"};
    foreach (std::string fileName, fileNames) {

    }

    //return a.exec();
}
