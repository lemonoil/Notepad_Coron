#include "findwindow.h"

Findwindow::Findwindow(QWidget *parent):QDialog(parent){
    setWindowTitle(tr("查找"));
    find_label = new QLabel(tr("查找"));
    ignore_label = new QLabel(tr("区分大小写"));
    next_label = new QLabel(tr("向后"));
    back_label = new QLabel(tr("向前"));
    find_edit = new QLineEdit;
    find_button = new QPushButton(tr("查找下一个"));
    next_radio = new QRadioButton;
    back_radio = new QRadioButton;
    ignore_flag = new QCheckBox;
    find_edit->setText(tr(""));
    QGridLayout *grid_layout = new QGridLayout(this);
    grid_layout->addWidget(find_label,0,0);
    grid_layout->addWidget(find_edit,0,1);
    grid_layout->addWidget(find_button,0,3);
    QHBoxLayout *ignore_layout = new QHBoxLayout;
    ignore_layout->setSpacing(10);
    ignore_layout->addWidget(ignore_label);
    ignore_layout->addWidget(ignore_flag);
    QHBoxLayout *radio_layout = new QHBoxLayout;
    radio_layout->addWidget(next_label);
    radio_layout->addWidget(next_radio);

    radio_layout->addWidget(back_label);
    radio_layout->addWidget(back_radio);

    QGroupBox *group_radio = new QGroupBox(tr("方向"),this);
    group_radio->setLayout(radio_layout);

    QHBoxLayout *do_radio = new QHBoxLayout;
    do_radio->addWidget(group_radio);

    grid_layout->addLayout(ignore_layout,1,0);
    grid_layout->addLayout(do_radio,1,1);

    this->setMaximumSize(300,100);
    next_radio->setChecked(true);
    find_button->setEnabled(false);
    connect(find_edit,SIGNAL(textChanged(QString)),this,SLOT(findButton()));
    connect(find_button,SIGNAL(clicked(bool)),this,SLOT(findButtonClick()));
}

Findwindow::~Findwindow(){
    if(find_edit)delete find_edit;
    if(find_label)delete find_label;
    if(ignore_label)delete ignore_label;
    if(next_label)delete next_label;
    if(back_label)delete back_label;
    if(find_button)delete find_button;
    if(next_radio)delete next_radio;
    if(back_radio)delete back_radio;
    if(ignore_flag)delete ignore_flag;
}

void Findwindow::findButton(){
    if(find_edit->text().isEmpty())find_button->setEnabled(false);
    else find_button->setEnabled(true);
}

void Findwindow::findButtonClick(){
    if(find_edit->text().isEmpty())return;
    QString str = find_edit->text();
    if(next_radio->isChecked()){
        if(ignore_flag->isChecked())emit findnext(str,true,true);
        else emit findnext(str,false,true);
    }
    if(back_radio->isChecked()){
        if(ignore_flag->isChecked())emit findnext(str,true,false);
        else emit findnext(str,false,false);
    }
}
