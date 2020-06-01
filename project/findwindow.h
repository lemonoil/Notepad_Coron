#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>

class Findwindow:public QDialog{
    Q_OBJECT
public:
    Findwindow(QWidget *parent = 0);
    ~Findwindow();

signals:
    void findnext(QString,bool,bool);

private slots:
    void findButton();
    void findButtonClick();

private:
    QLineEdit       *find_edit;
    QLabel          *find_label,*ignore_label,*next_label,*back_label;
    QPushButton     *find_button;
    QRadioButton    *next_radio,*back_radio;
    QCheckBox       *ignore_flag;
};

#endif // FINDDIALOG_H
