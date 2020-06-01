#ifndef COUNTWINDOW_H
#define COUNTWINDOW_H
#include <QDialog>
#include <QDebug>
#include <iostream>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QCheckBox>
#include <QTextStream>
#include <QString>
#include <vector>
#include <algorithm>
#include <findwindow.h>
#include <replacewindow.h>
using namespace std;

typedef class{
public:
   string str;
   int cnt;
}word;

class Countwindow:public QDialog{
    Q_OBJECT
public:
    Countwindow(QWidget *parent = 0);
    ~Countwindow(){}
    void CountStrC(const char *);


    bool skip();
    static bool cmp_raw(const string &,const string &);
    static bool cmp_cnt(const word &,const word &);

};


#endif // COUNTWINDOW_H

