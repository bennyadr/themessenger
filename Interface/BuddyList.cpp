#include <QApplication>
#include <QComboBox>

#include "BuddyList.h"
#include "yinstance.h"

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

    this->setWindowTitle(QApplication::translate("BuddyListWidget", "Form", 0, QApplication::UnicodeUTF8));
	c_YInstance* yinstance = c_YInstance::GetInstance();	
	connect(yinstance,SIGNAL(SetBuddyList(c_BuddyList *)),this,SLOT(ShowBuddies(c_BuddyList*)));
	connect(yinstance,SIGNAL(SetOnlineBuddies(c_BuddyList *)),this,SLOT(ShowOnline(c_BuddyList*)));
	connect(BuddyListLW,SIGNAL(itemDoubleClicked(QListWidgetItem*)),parent,SLOT(StartTalk(QListWidgetItem*)));
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
				BuddyListLW->item(iterator)->setBackgroundColor(color);
				BuddyListLW->item(iterator)->setFont(font);
			}
			BuddyListLW->addItem(QString::fromStdString(buddylist->GetBuddy(iterator)->GetName()));
		}
	}

};

void BuddyListWidget::ShowOnline(c_BuddyList* buddylist)
{
	QColor color(20,240,20,50);			//green
	for(unsigned int iterator = 0;iterator < buddylist->c_BuddyList::GetSize();iterator++)
	{
		if(buddylist->GetBuddy(iterator)->c_Buddy::isOnline())
		{
			BuddyListLW->item(iterator + buddylist->GetBuddy(iterator)->GetGroupNum())->setBackgroundColor(color);
		}
	}
};
