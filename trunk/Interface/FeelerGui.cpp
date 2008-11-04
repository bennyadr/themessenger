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


FeelerGui::FeelerGui(QWidget *parent)
	:QDialog(parent),
	 isShowBuddies(0)
{

	if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("FeelerGui"));
    this->resize(432, 377);
    SettingsButtton = new QPushButton(this);
    SettingsButtton->setObjectName(QString::fromUtf8("SettingsButtton"));
    SettingsButtton->setGeometry(QRect(350, 30, 75, 24));
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
    QWidget::setTabOrder(SettingsButtton, BuddyListButton);
    QWidget::setTabOrder(BuddyListButton, Exit);
    QWidget::setTabOrder(Exit, TextEdit);
    QWidget::setTabOrder(TextEdit, TextBrowser);
    QWidget::setTabOrder(TextBrowser, TalkWidget);

    TalkWidget->setCurrentIndex(0);

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
    setToolTip(QApplication::translate("FeelerGui", "Feeler", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    SettingsButtton->setText(QApplication::translate("FeelerGui", "Settings", 0, QApplication::UnicodeUTF8));
    Exit->setText(QApplication::translate("FeelerGui", "Exit", 0, QApplication::UnicodeUTF8));
    BuddyListButton->setText(QApplication::translate("FeelerGui", "BuddyList", 0, QApplication::UnicodeUTF8));
    TalkWidget->setTabText(TalkWidget->indexOf(tab), QApplication::translate("FeelerGui", "Stats", 0, QApplication::UnicodeUTF8));

	c_YInstance* yinstance = c_YInstance::GetInstance();
	connect(yinstance,SIGNAL(SendText(QString ,QString )),this,SLOT(SendMessage(QString ,QString )));

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
	if(Item != NULL )
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
		QPushButton *closebutton = new QPushButton("X",tab);
		closebutton->setGeometry(QRect(313,1,13,13));
		connect(closebutton,SIGNAL(clicked()),this,SLOT(CloseTalk()));
  		QTextBrowser *TextBrowser = new QTextBrowser(tab);
   		TextBrowser->setObjectName(QString::fromUtf8("TextBrowser"));
   		TextBrowser->setGeometry(QRect(10, 10, 301, 271));
   		QLineEdit *TextEdit = new QLineEdit(tab);
   		TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
   		TextEdit->setGeometry(QRect(10, 290, 301, 21));
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

void FeelerGui::SendMessage(QString from,QString text)
{
	if(from == "Error")
	{
		//Login modal window
		LoginD->show();
	}
	QString send_text = from + ":" + text + "\n";
	emit PrintText(send_text);
};

