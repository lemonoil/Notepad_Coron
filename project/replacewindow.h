#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>

class Replacewindow:public QDialog{
    Q_OBJECT
public:
    Replacewindow(QWidget *parent = 0);
    ~Replacewindow();
signals:
    void replaceAll(QString , QString,bool);
    void replaceCurOne(QString,QString);
    void findReplace(QString,bool);
private slots:
    void chooseSlot();
    void findSlot();
    void replaceOneSlot();
    void replaceAllSlot();
private:
    QLineEdit       *find_str,*replace_str;
    QPushButton     *find_next,*replaced_one,*replaced_all,*cancle;
    QCheckBox       *ignore_flag;
    QLabel          *find_label,*replace_label;
};

#endif // REPLACEDIALOG_H
