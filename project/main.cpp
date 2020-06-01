#include "mainwindow.h"
#include "findwindow.h"
#include<QFontDatabase>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString pat =QDir::currentPath()+"/SourceCodePro-Regular.ttf";
    int fontId = QFontDatabase::addApplicationFont(pat);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    qDebug()<<fontId;
    QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
    QApplication::setFont(font);
    MainWindow w;
    w.show();
    return a.exec();
}
