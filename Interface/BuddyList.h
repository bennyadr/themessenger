/********************************************************************************
** Form generated from reading ui file 'untitled.ui'
**
** Created: Tue Jul 1 00:22:42 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef BUDDYLIST_H
#define BUDDYLIST_H


#include <QObject>
#include <QListWidget>
#include "../buddy_list.h"

class QComboBox;


class BuddyListWidget : public QWidget
{
	Q_OBJECT

public:
    BuddyListWidget(QWidget *parent = 0);
	void Clear();
	bool Contains(QString name)const;
private:
    QListWidget *BuddyListLW;
    QComboBox *StatusCB;
	bool hidden;

private slots:
	void ShowBuddies(c_BuddyList *buddylist);
	void ShowOnline(c_BuddyList *buddylist);
	void ChangeStatus(int status);

public slots:
	void ScanList();
	void HideOffline();

};


#endif // BUDDYLIST_H
