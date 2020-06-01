#include "mainwindow.h"
using namespace std;
#define _GLIBCXX_USE_CXX11_ABI 1


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowTitle(tr("CORON -1.0v"));
    notepad_text = new QTextEdit;
    this->setCentralWidget(notepad_text);
    resize(900,500);
    cur_file_name = tr("");
    createActions();
    createMenus();
}

MainWindow::~MainWindow(){
   if(file_menu)delete file_menu;
   if(edit_menu)delete edit_menu;
   if(about_menu)delete about_menu;
   if(new_act)delete new_act;
   if(open_act)delete open_act;
   if(save_act)delete save_act;
   if(exit_act)delete exit_act;
   if(find_act)delete find_act;
   if(replace_act)delete replace_act;
   if(about_act)delete about_act;
   if(notepad_text)delete notepad_text;
   if(find_dialog)delete find_dialog;
   if(replace_dialog)delete replace_dialog;
   if(another_save_act)delete another_save_act;
}


void MainWindow::createMenus(){
    file_menu = menuBar()->addMenu(tr("&文件"));
    file_menu->setStyleSheet("color:black");
    file_menu->addAction(new_act);
    file_menu->addAction(open_act);
    file_menu->addAction(save_act);
    file_menu->addAction(another_save_act);
    file_menu->addSeparator();
    file_menu->addAction(exit_act);
    edit_menu = menuBar()->addMenu(tr("&编辑"));
    edit_menu->setStyleSheet("color:black");
    edit_menu->addAction(find_act);
    edit_menu->addAction(replace_act);
     edit_menu->addAction(count_act);
    about_menu = menuBar()->addMenu(tr("&关于"));
    about_menu->setStyleSheet("color:black");
    about_menu->addAction(about_act);
}

void MainWindow::createActions(){
    find = false;
    find_dialog = new Findwindow(this);
    replace_dialog = new Replacewindow(this);

    new_act = new QAction(tr("&新建"),this);
    new_act->setShortcut(QKeySequence::New);

    open_act = new QAction(tr("&打开"),this);
    open_act->setShortcut(QKeySequence::Open);

    save_act = new QAction(tr("&保存"),this);
    save_act->setShortcut(QKeySequence::Save);

    another_save_act = new QAction(tr("另存为"),this);
    another_save_act->setShortcut(QKeySequence::SaveAs);

    exit_act = new QAction(tr("&退出"),this);
    exit_act->setShortcut(QKeySequence::Quit);

    find_act = new QAction(tr("&查找"),this);
    find_act->setShortcut(QKeySequence::Find);

    replace_act = new QAction(tr("&替换"),this);
    replace_act->setShortcut(QKeySequence::Replace);

    count_act = new QAction(tr("&词频统计"),this);
    count_act->setShortcut(QKeySequence::Bold);

    about_act = new QAction(tr("关于"),this);

    connect(new_act,SIGNAL(triggered()),this,SLOT(newAct()));
    connect(open_act,SIGNAL(triggered()),this,SLOT(openAct()));
    connect(save_act,SIGNAL(triggered()),this,SLOT(saveAct()));
    connect(another_save_act,SIGNAL(triggered()),this,SLOT(anotherSaveAct()));
    connect(exit_act,SIGNAL(triggered()),this,SLOT(exitAct()));
    connect(find_act,SIGNAL(triggered()),this,SLOT(showFindDialog()));
    connect(replace_act,SIGNAL(triggered()),this,SLOT(showReplaceDialog()));

    connect(count_act,SIGNAL(triggered()),this,SLOT(cuntAct()));
    connect(about_act,SIGNAL(triggered()),this,SLOT(aboutAct()));

    connect(find_dialog,SIGNAL(findnext(QString,bool,bool)),this,SLOT(findAct(QString,bool,bool)));
    connect(replace_dialog,SIGNAL(findReplace(QString,bool)),this,SLOT(findReplace(QString,bool)));
    connect(replace_dialog,SIGNAL(replaceCurOne(QString,QString)),this,SLOT(replaceCur(QString,QString)));
    connect(replace_dialog,SIGNAL(replaceAll(QString,QString,bool)),this,SLOT(replaceAll(QString,QString,bool)));

}

void MainWindow::newAct(){
    if (notepad_text->document()->isModified()){
        QMessageBox::StandardButton button = QMessageBox::information(this,"尚未保存", "是否要保存?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch(button){
            case QMessageBox::Save:{
                saveAct();
                if (notepad_text->document()->isModified())return;
            }
            case QMessageBox::Cancel:return;
            case QMessageBox::Discard:break;
            default:break;
        }
    }
    notepad_text->clear();
}


void MainWindow::openAct(){
    QString file_name = QFileDialog::getOpenFileName(this,tr("打开文件"),QString(),tr("所有文件(*.*)"));
    cur_file_name = file_name;
    if(!file_name.isEmpty()){
       QFile file(file_name);
       if(!file.open(QIODevice::ReadOnly)){
          QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
          return;
       }
       QTextStream ins(&file);
       notepad_text->setText(ins.readAll());
       file.close();
    }
}

void MainWindow::cuntAct(){
    if(cur_file_name.isEmpty()){
        QMessageBox::critical(this,tr("警告"),tr("请先保存文件"));
        return ;
    }else{
        count_dialog->CountStrC(cur_file_name.toStdString().data());
        QFile file("count_words.txt");
        string str;
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           str="Can't open the file!";
        }else{
           int num_cnt=13;
           QByteArray line;
           while(num_cnt--){
               line = file.readLine();
               str=str+line.toStdString();
           }
        }
        QMessageBox message(QMessageBox::NoIcon,tr("词频统计"), tr(str.c_str()));
        str="notepad \""+QDir::currentPath().toStdString()+"/count_words.txt\"";
        message.setButtonText (QMessageBox::Ok,QString("确 定"));
        message.addButton(tr("详 细"), QMessageBox::AcceptRole);
        int ret = message.exec();
        if(ret ==  QMessageBox::AcceptRole){
            qDebug()<<str.c_str();
            WinExec(str.c_str(),SW_SHOW);
        }
        return ;
    }
}

void MainWindow::saveAct(){
    if(cur_file_name.isEmpty()){
        QString file_name = QFileDialog::getSaveFileName(this,tr("保存文件"),QString(),tr("所有文件(*.*)"));
        cur_file_name = file_name;
        if(!file_name.isEmpty()){
            QFile file(file_name);
            if(!file.open(QIODevice::WriteOnly)){
                QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
                return;
            }
            QTextStream outs(&file);
            outs<<notepad_text->toPlainText();
            outs.flush();
            file.close();
        }
    }else{
        QFile file(cur_file_name);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
            return;
        }
        QTextStream outs(&file);
        outs<<notepad_text->toPlainText();
        outs.flush();
        file.close();
    }
}

void MainWindow::anotherSaveAct(){
    QString file_name = QFileDialog::getSaveFileName(this,tr("另存为文件"),QString(),tr("所有文件(*.*)"));
    cur_file_name = file_name;
    if(!file_name.isEmpty()){
        QFile file(file_name);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
            return;
        }
        QTextStream outs(&file);
        outs<<notepad_text->toPlainText();
        outs.flush();
        file.close();
    }

}

void MainWindow::findReplace(QString find_str, bool op){
    bool find_flag;
    if(op)find_flag = notepad_text->find(find_str,QTextDocument::FindCaseSensitively);
    else find_flag = notepad_text->find(find_str);
    if(!find_flag)QMessageBox::information(this,tr("结果"),tr("没有找到查找内容"),QMessageBox::Yes);
    else find = true;
}

void MainWindow::replaceCur(QString find_str, QString replace_str){
    if(find){
        QTextCursor text_cursor = notepad_text->textCursor();
        text_cursor.insertText(replace_str);
    }else QMessageBox::information(this,tr("结果"),tr("没有内容不能替换")+find_str,QMessageBox::Yes);
    find = false;
}

void MainWindow::replaceAll(QString find_str, QString replace_str,bool flg){
    if(!flg){
        bool haf = notepad_text->find(find_str);
        if(haf){
            QTextCursor text_cursor = notepad_text->textCursor();
            text_cursor.insertText(replace_str);
            while(notepad_text->find(find_str)){
                text_cursor = notepad_text->textCursor();
                text_cursor.insertText(replace_str);
            }
            while(notepad_text->find(find_str,QTextDocument::FindBackward)){
                text_cursor = notepad_text->textCursor();
                text_cursor.insertText(replace_str);
            }
        }else QMessageBox::information(this,tr("结果"),tr("没有内容不能替换 ")+find_str,QMessageBox::Yes);
    }else{
        bool haf = notepad_text->find(find_str,QTextDocument::FindCaseSensitively);
        if(haf){
            QTextCursor text_cursor = notepad_text->textCursor();
            text_cursor.insertText(replace_str);
            while(notepad_text->find(find_str,QTextDocument::FindCaseSensitively)){
                text_cursor = notepad_text->textCursor();
                text_cursor.insertText(replace_str);
            }
            while(notepad_text->find(find_str,QTextDocument::FindCaseSensitively|QTextDocument::FindBackward)){
                text_cursor = notepad_text->textCursor();
                text_cursor.insertText(replace_str);
            }
        }else QMessageBox::information(this,tr("结果"),tr("没有内容不能替换")+find_str,QMessageBox::Yes);
    }

}

void MainWindow::findAct(QString str,bool ignore,bool choose){
    QString text = str;
    bool find_flag;
    if(!text.isEmpty()){
        if(choose){
            if(ignore)find_flag = notepad_text->find(text,QTextDocument::FindCaseSensitively);
            else find_flag = notepad_text->find(text);
        }
        else{
            if(ignore)find_flag = notepad_text->find(text,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively);
            else find_flag = notepad_text->find(text,QTextDocument::FindBackward);
        }
        if(!find_flag)QMessageBox::information(this,tr("结果"),tr("没有找到查找内容"),QMessageBox::Yes);
    }
}

void MainWindow::aboutAct(){
    QMessageBox message(QMessageBox::NoIcon,tr("关于"), tr("<h4>东南大学c++大作业<br>by JS319111李明洋<br><a href=\"https://github.com/lemonoil/Notepad_Coron\">Github</a></h4>"));
    message.setButtonText (QMessageBox::Ok,QString("确 定"));
    message.exec();
}

void MainWindow::exitAct(){
    this->close();
}
void MainWindow::showFindDialog(){
    find_dialog->show();
}
void MainWindow::showReplaceDialog(){
    replace_dialog->show();
}

void MainWindow::showCountDialog(){
    replace_dialog->show();
}
