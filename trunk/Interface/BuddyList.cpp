#include <QApplication>
#include <QComboBox>

#include "BuddyList.h"
#include "yinstance.h"
#include "../setStatus.h"
#include "../scanBuddies.h"

BuddyListWidget::BuddyListWidget(QWidget *parent)
	:QWidget(parent)
{
	if (this->objectName().isEmpty())
      	this->setObjectName(QString::fromUtf8("BuddyListWidget"));
    this->resize(251, 362);
    BuddyListLW = new QListWidget(this);
    BuddyListLW->setObjectName(QString::fromUtf8("BuddyListLW"));
    BuddyListLW->setGeometry(QRect(10, 50, 231, 312));
   	StatusCB = new QComboBox(this);
    StatusCB->setObjectName(QString::fromUtf8("StatusCB"));
    StatusCB->setGeometry(QRect(10, 10, 231, 22));
	StatusCB->addItem("Available");
	StatusCB->addItem("BeRightBack");
	StatusCB->addItem("Busy");
	StatusCB->addItem("NotAtHome");
	StatusCB->addItem("NotAtDesk");
	StatusCB->addItem("NotInOffice");
	StatusCB->addItem("OnThePhone");
	StatusCB->addItem("OnVacation");
	StatusCB->addItem("OutToLunch");
	StatusCB->addItem("SteppedOut");
	StatusCB->addItem("Invisible");
	StatusCB->addItem("Away");
	StatusCB->addItem("Offline");
	StatusCB->addItem("Custom...");
	connect(StatusCB,SIGNAL(activated(int)),this,SLOT(ChangeStatus(int)));


    this->setWindowTitle(QApplication::translate("BuddyListWidget", "Form", 0, QApplication::UnicodeUTF8));
	c_YInstance* yinstance = c_YInstance::GetInstance();	
	connect(yinstance,SIGNAL(SetBuddyList(c_BuddyList *)),this,SLOT(ShowBuddies(c_BuddyList*)));
	connect(yinstance,SIGNAL(SetOnlineBuddies(c_BuddyList *)),this,SLOT(ShowOnline(c_BuddyList*)));
	connect(BuddyListLW,SIGNAL(itemDoubleClicked(QListWidgetItem*)),parent,SLOT(StartTalk(QListWidgetItem*)));
	hidden = false;
    Q_UNUSED(this);
};

void BuddyListWidget::ShowBuddies(c_BuddyList* buddylist)
{
	QString group ="";
	QColor color(20,100,200,50);				//blue 
	QFont font( "Newyork", 14 );
	for(unsigned int iterator = 0;iterator < buddylist->GetSize();iterator++)
	{
		if(buddylist->GetBuddy(iterator))
		{
			if(group != QString::fromStdString(buddylist->GetBuddy(iterator)->GetGroup()))
			{
				group = QString::fromStdString(buddylist->GetBuddy(iterator)->GetGroup());
				BuddyListLW->addItem(group);
				BuddyListLW->item(BuddyListLW->count()-1)->setBackgroundColor(color);
				BuddyListLW->item(BuddyListLW->count()-1)->setFont(font);
			}
			BuddyListLW->addItem(QString::fromStdString(buddylist->GetBuddy(iterator)->GetName()));
		}
	}

};

void BuddyListWidget::ShowOnline(c_BuddyList* buddylist)
{
	QColor green(20,240,20,50);			//green
	QColor white(255,255,255,0);
	QColor gray(80,80,80,80);
	for(unsigned int iterator = 0;iterator < buddylist->c_BuddyList::GetSize();iterator++)
	{
		if(buddylist->GetBuddy(iterator)->c_Buddy::isOnline())
		{
			if(buddylist->GetBuddy(iterator)->GetYahooStatus() == YAHOO_STATUS_INVISIBLE)
				BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setBackgroundColor(gray);
			else
				BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setBackgroundColor(green);
			BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setToolTip(QString::fromStdString(buddylist->GetBuddy(iterator)->GetStatus()));
			if(hidden)
				BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setHidden(false);
		}
		else
		{	
			BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setBackgroundColor(white);
			BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setToolTip("Offline");
			if(hidden)
				BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setHidden(true);
		}
	}
};

void BuddyListWidget::HideOffline()
{
	if(hidden == true)
	{
		c_YInstance *yinstance = c_YInstance::GetInstance();
		c_BuddyList *buddylist = yinstance->GetBuddyList();
		if(buddylist == NULL)
			return;
		for(unsigned int iterator = 0;iterator < buddylist->c_BuddyList::GetSize();iterator++)
		{
			if(!buddylist->GetBuddy(iterator)->c_Buddy::isOnline())
			{
				BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setHidden(false);
			}
		}
		hidden = false;
	}
	else
	{
		c_YInstance *yinstance = c_YInstance::GetInstance();
		c_BuddyList *buddylist = yinstance->GetBuddyList();
		if(buddylist == NULL)
			return;
		for(unsigned int iterator = 0;iterator < buddylist->c_BuddyList::GetSize();iterator++)
		{
			if(!buddylist->GetBuddy(iterator)->c_Buddy::isOnline())
			{
				BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setHidden(true);
			}
		}
		hidden = true;
	}

};

void BuddyListWidget::Clear()
{
	BuddyListLW->clear();
};

bool BuddyListWidget::Contains(QString name)const
{
	for(int iterator = 0;iterator < BuddyListLW->count();iterator++)
	{
		if(BuddyListLW->item(iterator)->text() == name)
			return true;
	}
	return false;
};


void BuddyListWidget::ChangeStatus(int status)
{
	c_YInstance *yinstance = c_YInstance::GetInstance();
	if(status >= YAHOO_STATUS_AVAILABLE && status < YAHOO_STATUS_STEPPEDOUT)
	{
		c_SetStatus *set_status = new c_SetStatus(yinstance->GetSocket(),"",yahoo_status(status),yinstance->GetId());
		yinstance->AddAction(set_status);
		StatusCB->setEditable(false);
	}
	else
		if(status >= 13) //custom
		{
			if(StatusCB->isEditable())
			{
				c_SetStatus *set_status = new c_SetStatus(yinstance->GetSocket(),this->StatusCB->currentText().toLatin1().data(),YAHOO_STATUS_CUSTOM,yinstance->GetId());
				yinstance->AddAction(set_status);
				StatusCB->setEditable(false);
			}
			else
			{
				StatusCB->setEditable(true);
			}
		}
		else
			if(status == 10)  //invisible
			{
				c_SetStatus *set_status = new c_SetStatus(yinstance->GetSocket(),"",YAHOO_STATUS_INVISIBLE,yinstance->GetId());
				yinstance->AddAction(set_status);
				StatusCB->setEditable(false);
			}
};

void BuddyListWidget::ScanListI()
{
	c_YInstance *yinstance = c_YInstance::GetInstance();
	c_BuddyList *buddylist = yinstance->GetBuddyList();
	if(buddylist == NULL)
		return;
	for(unsigned int iterator = 0;iterator < buddylist->c_BuddyList::GetSize();iterator++)
	{
		if(!buddylist->GetBuddy(iterator)->c_Buddy::isOnline())
		{
			c_ScanBuddies *scanbud = new c_ScanBuddies(yinstance->GetSocket(),yinstance->GetId(),buddylist->GetBuddy(iterator)->GetName(),yinstance->GetUserNameSTL());
			yinstance->AddAction(scanbud);
			sleep(5);
		}
	}

};
