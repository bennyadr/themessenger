#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QTextBrowser>
#include <QLineEdit>
#include <QCommandLinkButton>
#include "FeelerGui.h"
#include "BuddyList.h"
#include "Login.h"

#include "yinstance.h"
#include "../sendMessage.h"


FeelerGui::FeelerGui(QWidget *parent)
	:QDialog(parent),
	 isShowBuddies(0)
{

	if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("FeelerGui"));
    this->resize(432, 377);

	ScanInvisible = new QPushButton(this);
	ScanInvisible->setObjectName(QString::fromUtf8("ScanBuddies"));
	ScanInvisible->setGeometry(QRect(350, 35, 75, 24));


	HideShowB = new QPushButton(this);
    HideShowB->setObjectName(QString::fromUtf8("HideOfflineButton"));
    HideShowB->setGeometry(QRect(350, 95, 75, 24));
	
	LogoutButton = new QPushButton(this);
   	LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));
    LogoutButton->setGeometry(QRect(350, 240, 75, 24));


    Exit = new QPushButton(this);
    Exit->setObjectName(QString::fromUtf8("Exit"));
    Exit->setGeometry(QRect(350, 340, 75, 24));

    BuddyListButton = new QCommandLinkButton(this);
    BuddyListButton->setObjectName(QString::fromUtf8("BuddyListButton"));
    BuddyListButton->setGeometry(QRect(340, 160, 91, 41));

    TalkWidget = new QTabWidget(this);
    TalkWidget->setObjectName(QString::fromUtf8("TalkWidget"));
    TalkWidget->setGeometry(QRect(10, 10, 331, 351));

    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    tab->setGeometry(QRect(0, 0, 327, 327));

    TextBrowser = new QTextBrowser(tab);
    TextBrowser->setObjectName(QString::fromUtf8("TextBrowser"));
    TextBrowser->setGeometry(QRect(10, 10, 301, 271));

	connect(this,SIGNAL(PrintText(const QString&)),TextBrowser,SLOT(append(const QString&)));

    TextEdit = new QLineEdit(tab);
    TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
    TextEdit->setGeometry(QRect(10, 290, 301, 21));
    TalkWidget->addTab(tab, QString());
    TalkWidget->setCurrentIndex(0);

	QWidget::setTabOrder(ScanInvisible,HideShowB);
	QWidget::setTabOrder(HideShowB,BuddyListButton);
    QWidget::setTabOrder(BuddyListButton, LogoutButton);
    QWidget::setTabOrder(Exit, TextEdit);
    QWidget::setTabOrder(TextEdit, TextBrowser);
    QWidget::setTabOrder(TextBrowser, TalkWidget);


	//buddylist extension initialization
	BuddyListWid = new BuddyListWidget(this);
	BuddyListWid->setGeometry(QRect(430,0,241,362));
	connect(BuddyListButton, SIGNAL(clicked()), this, SLOT(showBudies()));
	BuddyListWid->hide();


	//Login modal window
	LoginD = new LoginDialog(this);
	LoginD->show();


	//TODO settings and exit

	//set titles and text
	setWindowTitle(QApplication::translate("FeelerGui", "Feeler", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    //setToolTip(QApplication::translate("FeelerGui", "Feeler", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP


	ScanInvisible->setText(QApplication::translate("FeelerGui", "ScanBuddies", 0, QApplication::UnicodeUTF8));
	HideShowB->setText(QApplication::translate("FeelerGui", "HideOffline", 0, QApplication::UnicodeUTF8));
	LogoutButton->setText(QApplication::translate("FeelerGui", "Logout", 0, QApplication::UnicodeUTF8));
    Exit->setText(QApplication::translate("FeelerGui", "Exit", 0, QApplication::UnicodeUTF8));
    BuddyListButton->setText(QApplication::translate("FeelerGui", "BuddyList", 0, QApplication::UnicodeUTF8));
    TalkWidget->setTabText(TalkWidget->indexOf(tab), QApplication::translate("FeelerGui", "Stats", 0, QApplication::UnicodeUTF8));

	c_YInstance* yinstance = c_YInstance::GetInstance();
	connect(yinstance,SIGNAL(SendText(QString ,QString )),this,SLOT(SendMessages(QString ,QString )));
	connect(yinstance,SIGNAL(RecvText(QString ,QString )),this,SLOT(RecvMessage(QString ,QString )));
	connect(Exit,SIGNAL(clicked()),this,SLOT(close()));
	connect(HideShowB,SIGNAL(clicked()),BuddyListWid,SLOT(HideOffline()));
	connect(ScanInvisible,SIGNAL(clicked()),BuddyListWid,SLOT(ScanList()));
	connect(LogoutButton,SIGNAL(clicked()),this,SLOT(Logout()));

};

void FeelerGui::showBudies()
{
	if (0 == isShowBuddies)
	{	
		BuddyListWid->show();
		isShowBuddies = 1;
		this->resize(675,377);
		
	}
	else
	{
		BuddyListWid->hide();
		isShowBuddies = 0;
		this->resize(432,377);
	}
};

bool FeelerGui::close()
{
	c_YInstance* yinstance = c_YInstance::GetInstance();
	yinstance->stop();
	yinstance->wait();
	QWidget::close();	
	return true;
};

void FeelerGui::StartTalk(QListWidgetItem *Item)
{
	QFont font( "Newyork", 14 );
	if(Item != NULL && Item->font() != font)
	{
		for(int iterator = 0;iterator<TalkWidget->count();iterator++)
		{
			if(Item->text() == TalkWidget->tabText(iterator))
			{
				TalkWidget->setCurrentIndex(iterator);
				return;
			}
		}
		QWidget *tab = new QWidget();
   		tab->setObjectName(QString::fromUtf8("tab"));
 		tab->setGeometry(QRect(0, 0, 327, 327));
		QLineEdit *TextEdit = new QLineEdit(tab);
		connect(TextEdit,(SIGNAL(returnPressed())),this,SLOT(SendMessages()));
		connect(TextEdit,SIGNAL(textChanged(QString)),this,SLOT(SendNotify(QString)));
   		TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
   		TextEdit->setGeometry(QRect(10, 290, 301, 21));
		QPushButton *closebutton = new QPushButton("X",tab);
		closebutton->setGeometry(QRect(313,1,13,13));
		connect(closebutton,SIGNAL(clicked()),this,SLOT(CloseTalk()));
  		QTextBrowser *TextBrowser = new QTextBrowser(tab);
   		TextBrowser->setObjectName(QString::fromUtf8("TextBrowser"));
   		TextBrowser->setGeometry(QRect(10, 10, 301, 271));
   		TalkWidget->addTab(tab, Item->text());
		TalkWidget->setCurrentWidget(tab);
	}
};

void FeelerGui::CloseTalk()
{
	QWidget *currentwidget = TalkWidget->currentWidget();
	TalkWidget->removeTab(TalkWidget->indexOf(currentwidget));
	currentwidget->deleteLater();
};

void FeelerGui::SendMessages(QString from,QString text)
{
	QString send_text = from + " : " + text;
	if(from == "Error" || from == "Log")
	{
		//Login modal window
		LoginD->show();
		emit PrintText(send_text);
	}
	else
	{
		QWidget *currentwid = TalkWidget->currentWidget();
		QTextBrowser *cur_txt_brows = dynamic_cast<QTextBrowser*>(currentwid->children().last());
		cur_txt_brows->setTextColor(QColor(0,0,0));
		cur_txt_brows->append(send_text);
	}
};

void FeelerGui::RecvMessage(QString from,QString text)
{
	QString send_text;
	if(text == "Notify")
		send_text = from + " " + "is typing ...";
	else
		if(text == "Notify_end")
			send_text = from + " " + "finished typing ...";
		else	
			send_text = from + " : " + text;

	for(int iterator = 0;iterator<TalkWidget->count();iterator++)
	{
		if(from == TalkWidget->tabText(iterator))
		{
			QWidget *wid = TalkWidget->widget(iterator);
			QTextBrowser *txt_brows = dynamic_cast<QTextBrowser*>(wid->children().last());
			if(text == "Notify" || text == "Notify_end")
				txt_brows->setTextColor(QColor(20,40,200,90));
			else
				txt_brows->setTextColor(QColor(20,40,255));
			txt_brows->append(send_text);
			return;
		}
	}
	if(!BuddyListWid->Contains(from))
		return;
	QWidget *tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab"));
	tab->setGeometry(QRect(0, 0, 327, 327));
	QLineEdit *TextEdit = new QLineEdit(tab);
	connect(TextEdit,(SIGNAL(returnPressed())),this,SLOT(SendMessages()));
	connect(TextEdit,SIGNAL(textChanged(QString)),this,SLOT(SendNotify(QString)));
	TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
	TextEdit->setGeometry(QRect(10, 290, 301, 21));
	QPushButton *closebutton = new QPushButton("X",tab);
	closebutton->setGeometry(QRect(313,1,13,13));
	connect(closebutton,SIGNAL(clicked()),this,SLOT(CloseTalk()));
	QTextBrowser *TextBrowser = new QTextBrowser(tab);
	if(text == "Notify" || text == "Notify_end")
		TextBrowser->setTextColor(QColor(20,40,200,90));
	else
		TextBrowser->setTextColor(QColor(20,40,255));
	TextBrowser->append(send_text);
	TextBrowser->setObjectName(QString::fromUtf8("TextBrowser"));
	TextBrowser->setGeometry(QRect(10, 10, 301, 271));
	TalkWidget->addTab(tab, from);

};

void FeelerGui::SendMessages()
{
	QWidget *currentwid = TalkWidget->currentWidget();
	c_YInstance* yinstance = c_YInstance::GetInstance();	
	QString from = yinstance->GetUserName();
	QString to = TalkWidget->tabText(TalkWidget->currentIndex()); 
	QLineEdit *cur_line_edit = dynamic_cast<QLineEdit*>(currentwid->children().first());
	QString text;
	if(cur_line_edit)
	{
		text = cur_line_edit->text();
		cur_line_edit->clear();
	}
	SendMessages(from,text);
	c_SendMessage *sendmess = new c_SendMessage(yinstance->GetSocket(),from.toStdString(),to.toStdString(),text.toStdString(),YAHOO_STATUS_OFFLINE,yinstance->GetId());
	yinstance->AddAction(sendmess);
};

void FeelerGui::SendNotify(QString mes)
{
	if(mes.length() > 1)
		return;
	c_YInstance* yinstance = c_YInstance::GetInstance();	
	QString from = yinstance->GetUserName();
	QString to = TalkWidget->tabText(TalkWidget->currentIndex()); 
	if(mes.length() == 0)
	{
		c_SendNotify *sendnotif = new c_SendNotify(yinstance->GetSocket(),from.toStdString(),to.toStdString(),YAHOO_STATUS_OFFLINE,false,yinstance->GetId());
		yinstance->AddAction(sendnotif);
	}
	else
	{
		c_SendNotify *sendnotif = new c_SendNotify(yinstance->GetSocket(),from.toStdString(),to.toStdString(),YAHOO_STATUS_OFFLINE,true,yinstance->GetId());
		yinstance->AddAction(sendnotif);
	}

};

void FeelerGui::Logout()
{
	BuddyListWid->Clear();
	TalkWidget->clear();
	tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    tab->setGeometry(QRect(0, 0, 327, 327));

    TextBrowser = new QTextBrowser(tab);
    TextBrowser->setObjectName(QString::fromUtf8("TextBrowser"));
    TextBrowser->setGeometry(QRect(10, 10, 301, 271));

	connect(this,SIGNAL(PrintText(const QString&)),TextBrowser,SLOT(append(const QString&)));

    TextEdit = new QLineEdit(tab);
    TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
    TextEdit->setGeometry(QRect(10, 290, 301, 21));
    TalkWidget->addTab(tab, QString());
    TalkWidget->setCurrentIndex(0);
    TalkWidget->setTabText(TalkWidget->indexOf(tab), QApplication::translate("FeelerGui", "Stats", 0, QApplication::UnicodeUTF8));
	c_YInstance* yinstance = c_YInstance::GetInstance();		
	yinstance->stop();
	yinstance->wait();
	try
	{
		yinstance->GetSocket()->Disconnect();
	}
	catch(c_Error_Socket &error)
	{
		QString error_message1 = QString::fromStdString(error.GetErrorMessage());	
		QString error1 = "Error";
		SendMessages(error1,error_message1);
	}
	LoginD->show();
};


