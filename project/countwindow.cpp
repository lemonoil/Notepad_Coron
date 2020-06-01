#include "countwindow.h"
#include<iomanip>
using namespace std;


Countwindow::Countwindow(QWidget *parent):QDialog(parent){
    setWindowTitle(tr("词频统计"));
    this->setMaximumSize(17000,10000);
}

bool Countwindow::cmp_raw(const string &a,const string &b){return a<b;}

bool Countwindow::cmp_cnt(const word &a,const word &b){return a.cnt>b.cnt;}


bool Countwindow::skip(){ scanf("%*[^a-z||A-Z]"); return true;}
string formatLetter(string oldStr){
    string tempStr;
    for(int i = 0; i < (int)oldStr.length(); ++i){
        char pCh =oldStr[i];
        if(pCh>='A'&&pCh<='Z')tempStr += oldStr[i];
        if(pCh>='a'&&pCh<='z')tempStr += oldStr[i];
    }
    return tempStr;
}
void Countwindow::CountStrC(const char *filename){
   word w;

   string _word;
   vector<string> virtual_word;
   vector<string> raw_word;
   vector<word> word_statistics;
/*
   vector<string>::iterator it,last;
   vector<word>::iterator wit;

   重定向输入流至 virtual.txt 文件,读取 virtual.txt 文件所有英文单词
   freopen("virtual.ini","r",stdin);
   while(skip()&&scanf("%[a-zA-Z]",_word)!=EOF) virtual_word.push_back(_word);
    */

   /*对虚词表进行排序以便其后的搜索操作
   sort(virtual_word.begin(),virtual_word.end(),cmp_raw);
   */
   /*重定向输入流至 in.txt 文件,并读取 in.txt 文件中所有英文单词*/
   QFile fin(filename);
   fin.open(QIODevice::ReadOnly);
   QString s;
   QTextStream s1(&fin);
   s.append(s1.readAll());
   _word=s.toStdString();
   QStringList strList = s.split(" ");

   for(int i=0;i<strList.size();++i){
      string zt=formatLetter(strList[i].toStdString().data());
        if(zt.length()<2)continue;
        if(zt[1]!='\0'&&isupper(zt[0])&&islower(zt[1])) zt[0]|=1<<5;
        raw_word.push_back(zt);
   }
   fin.close();
   QFile fou("count_words.txt");
   fou.open(QIODevice::WriteOnly | QIODevice::Text);
   QTextStream out(&fou);
   out<<"-----------------COUNT WORDS-------------------\n";
   out<<"-----------------------------------------------\n";
   out<<(int)raw_word.size()<<" words be counted!Details are as follow:\n";
   out<<"no.              word       time      frequency\n";
   out<<"-----------------------------------------------\n";
   if(!raw_word.size()){
      out<<"There is no word in the *.txt inexistence!\n";
      out<<"-----------------------------------------------\n";
      return;
   }
   _word="";

   sort(raw_word.begin(),raw_word.end(),cmp_raw);
   for(int i=0;i<(int)raw_word.size();++i){
       if(i==0){
           _word=raw_word[i];
           w.str=_word;
           w.cnt=1;
       }else if(_word==raw_word[i]){
           w.cnt++;
       }else{
           word_statistics.push_back(w);
           _word=raw_word[i];
           w.str=_word;
           w.cnt=1;
       }
   }
   word_statistics.push_back(w);
   sort(word_statistics.begin(),word_statistics.end(),cmp_cnt);
   bool b=0;
   out.setRealNumberNotation(QTextStream::FixedNotation);
   for(int i=0;i<(int)word_statistics.size();++i){
          //if(word_statistics[i].cnt*1.0/num_words>=0.05||(word_statistics[i].cnt>=2&&word_statistics[i].cnt*100.0/num_words>=0.01)){
       out.setFieldWidth(5);
       out<<i+1;
       out.setFieldWidth(20);
       out<<(word_statistics[i].str).c_str();
       out.setFieldWidth(8);
       out<<(int)(word_statistics[i].cnt);
       out.setFieldWidth(12);
       out<<(double)(word_statistics[i].cnt*100.00/(double)raw_word.size());
       out.setFieldWidth(2);
       out<<"%\n";
     // }
   }
   //if(!b)printf("no appropriate word!\n");
   printf("-----------------------------------------------\n");
   fou.close();
}



