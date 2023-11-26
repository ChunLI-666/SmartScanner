#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QLocale locale = QLocale::system();

    if( locale.language() == QLocale::Chinese )
    {
        //中文环境使用默认界面
    }
    else
    {
        //其他环境使用英文
        translator.load(QString(":/BasicDemoByGenTL_zh_EN.qm"));  //选择翻译文件
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
