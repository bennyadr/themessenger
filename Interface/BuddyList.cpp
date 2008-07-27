#include <QApplication>
#include <QListWidget>
#include <QComboBox>

#include "BuddyList.h"


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
    Q_UNUSED(this);
};


