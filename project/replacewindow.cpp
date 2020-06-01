#include "replacewindow.h"

Replacewindow::Replacewindow(QWidget *parent):QDialog(parent){
    find_label      = new QLabel(tr("查找内容"));
    replace_label   = new QLabel(tr("替换为"));
    find_str        = new QLineEdit();
    replace_str     = new QLineEdit();
    find_next       = new QPushButton(tr("查找下一个"));
    replaced_one    = new QPushButton(tr("替换"));
    replaced_all    = new QPushButton(tr("全部替换"));
    cancle          = new QPushButton(tr("取消"));
    ignore_flag     = new QCheckBox(tr("区分大小写"));

    QGridLayout *grdly  = new QGridLayout(this);
    QVBoxLayout *vboxly = new QVBoxLayout(this);

    vboxly->addWidget(replaced_all);
    vboxly->addWidget(cancle);
    grdly->addWidget(find_label,0,0);
    grdly->addWidget(find_str,0,1);
    grdly->addWidget(find_next,0,2);
    grdly->addWidget(replace_label,1,0);
    grdly->addWidget(replace_str,1,1);
    grdly->addWidget(replaced_one,1,2);
    grdly->addWidget(ignore_flag,2,1);
    grdly->addLayout(vboxly,2,2);

    find_str->setText(tr(""));
    replace_str->setText(tr(""));
    find_next->setEnabled(false);
    replaced_one->setEnabled(false);
    replaced_all->setEnabled(false);

    this->setMaximumSize(300,100);

    connect(find_str,SIGNAL(textChanged(QString)),this,SLOT(chooseSlot()));
    connect(cancle,SIGNAL(clicked()),this,SLOT(close()));
    connect(find_next,SIGNAL(clicked()),this,SLOT(findSlot()));
    connect(replaced_one,SIGNAL(clicked()),this,SLOT(replaceOneSlot()));
    connect(replaced_all,SIGNAL(clicked()),this,SLOT(replaceAllSlot()));
}

Replacewindow::~Replacewindow(){
    if(find_str)delete find_str;
    if(replace_str)delete replace_str;
    if(find_next)delete find_next;
    if(replaced_one)delete replaced_one;
    if(replaced_all)delete replaced_all;
    if(cancle)delete cancle;
    if(ignore_flag)delete ignore_flag;
    if(find_label)delete find_label;
    if(replace_label)delete replace_label;
}

void Replacewindow::chooseSlot(){
    if(!find_str->text().isEmpty()){
        find_next->setEnabled(true);
        replaced_one->setEnabled(true);
        replaced_all->setEnabled(true);
    }
    else{
        find_next->setEnabled(false);
        replaced_one->setEnabled(false);
        replaced_all->setEnabled(false);
    }
}

void Replacewindow::findSlot(){
    if(ignore_flag->isChecked())emit findReplace(find_str->text(),true);
    else emit findReplace(find_str->text(),false);
}

void Replacewindow::replaceOneSlot(){
    emit replaceCurOne(find_str->text(),replace_str->text());
}

void Replacewindow::replaceAllSlot(){
    if(ignore_flag->isChecked())emit replaceAll(find_str->text() , replace_str->text(),true);
    else emit replaceAll(find_str->text() , replace_str->text(),false);
}
