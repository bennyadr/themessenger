/********************************************************************************
** Form generated from reading ui file 'untitled.ui'
**
** Created: Tue Jul 1 23:03:11 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

class QGroupBox;
class QLineEdit;
class QLabel;
class QFrame;
class QPushButton;
class QRadioButton;
class QDialog;
class QGridLayout;

class LoginDialog : public QDialog
{
	Q_OBJECT

private:

	QGridLayout *GLayout;
    QLineEdit *PasswordEdit;
    QLineEdit *UserEdit;
    QLabel *PasswordLabel;
    QLabel *UserLabel;
    QPushButton *LoginButton;

private slots:
	void LoginSlot();

public:
	LoginDialog(QWidget *parent = 0);


};

#endif // LOGIN_H
