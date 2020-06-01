#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProcess>
#include <QAction>
#include <QTextEdit>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QToolBar>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPageSetupDialog>
#include <findwindow.h>
#include <replacewindow.h>
#include <windows.h>
#include <countwindow.h>
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
private slots:
    void createMenus();
    void createActions();
    void newAct();
    void openAct();
    void saveAct();
    void exitAct();
    void findAct(QString,bool,bool);
    void cuntAct();
    void aboutAct();
    void showFindDialog();
    void showReplaceDialog();
    void showCountDialog();
    void anotherSaveAct();
    void findReplace(QString,bool);
    void replaceCur(QString,QString);
    void replaceAll(QString,QString,bool);

private:
    bool            find;
    QMenu           *file_menu,*edit_menu,*about_menu;
    QAction         *new_act,*open_act,*save_act,*another_save_act,*exit_act,*find_act,*replace_act,*count_act,*about_act;
    QTextEdit       *notepad_text;
    Findwindow      *find_dialog;
    Replacewindow   *replace_dialog;
    Countwindow     *count_dialog;
    QString         cur_file_name;
};

#endif // MAINWINDOW_H
