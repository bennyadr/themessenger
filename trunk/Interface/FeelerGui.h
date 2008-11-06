/********************************************************************************
** Form generated from reading ui file 'FeelerGui.ui'
**
** Created: Mon Jun 30 23:08:35 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef FEELERGUI_H
#define FEELERGUI_H

#include <QDialog>
#include <QListWidgetItem>
#include <QObjectCleanupHandler>

//forword declarations
class QPushButton;
class QCommandLinkButton;
class QTextBrowser;
class QTabWidget;
class QLineEdit;
class BuddyListWidget;
class LoginDialog;

class FeelerGui : public QDialog
{
	Q_OBJECT

public:
	FeelerGui(QWidget *parent = 0);
	virtual bool close(); 

private slots:
	void showBudies();
	void CloseTalk();	
	void SendMessage();

public slots:
	void StartTalk(QListWidgetItem *Item);
	void SendMessage(QString from,QString text);
	void RecvMessage(QString from,QString text);

signals:
	void PrintText(const QString&);

private:
    QPushButton *SettingsButtton;
    QPushButton *Exit;
    QCommandLinkButton *BuddyListButton;
    QTabWidget *TalkWidget;
    QWidget *tab;
    QTextBrowser *TextBrowser;
    QLineEdit *TextEdit;


	//extension widget : buddy list
	BuddyListWidget *BuddyListWid;
	int isShowBuddies;


	//Login modal window
	LoginDialog *LoginD;

};


#endif // FEELERGUI_H
