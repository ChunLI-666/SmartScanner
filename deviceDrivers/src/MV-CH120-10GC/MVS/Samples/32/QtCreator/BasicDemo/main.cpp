#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QLocale locale = QLocale::system();

    if( locale.language() == QLocale::Chinese )
    {
            //���Ļ���ʹ��Ĭ�Ͻ���
    }
    else
    {
        //��������ʹ��Ӣ��
        translator.load(QString(":/BasicDemo_zh_EN.qm"));  //ѡ�����ļ�
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.setWindowFlags(w.windowFlags() &~ Qt::WindowMaximizeButtonHint);//��ֹ���
    w.show();
    return a.exec();
}
