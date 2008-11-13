#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QFrame>
#include <QDialog>
#include <QRadioButton>
#include <QApplication>

#include "Login.h"
#include "yinstance.h"

LoginDialog::LoginDialog(QWidget *parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("LoginDialog"));
    this->resize(288, 165);
    LoginGroupBox = new QGroupBox(this);
    LoginGroupBox->setObjectName(QString::fromUtf8("LoginGroupBox"));
    LoginGroupBox->setGeometry(QRect(20, 10, 251, 141));
    PasswordEdit = new QLineEdit(LoginGroupBox);
    PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
	PasswordEdit->setEchoMode(QLineEdit::Password);
    PasswordEdit->setGeometry(QRect(70, 50, 171, 20));
    UserEdit = new QLineEdit(LoginGroupBox);
    UserEdit->setObjectName(QString::fromUtf8("UserEdit"));
    UserEdit->setGeometry(QRect(70, 20, 171, 20));
    PasswordLabel = new QLabel(LoginGroupBox);
    PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));
    PasswordLabel->setGeometry(QRect(10, 50, 51, 20));
    VertLine = new QFrame(LoginGroupBox);
    VertLine->setObjectName(QString::fromUtf8("VertLine"));
    VertLine->setGeometry(QRect(10, 80, 221, 16));
    VertLine->setFrameShape(QFrame::HLine);
    VertLine->setFrameShadow(QFrame::Sunken);
    UserLabel = new QLabel(LoginGroupBox);
    UserLabel->setObjectName(QString::fromUtf8("UserLabel"));
    UserLabel->setGeometry(QRect(10, 20, 51, 16));
    LoginButton = new QPushButton(LoginGroupBox);
    LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
    LoginButton->setGeometry(QRect(150, 100, 75, 24));

	this->setModal(true);
	//setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowTitle(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
    LoginGroupBox->setTitle(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
    PasswordLabel->setText(QApplication::translate("LoginDialog", "Password:", 0, QApplication::UnicodeUTF8));
    UserLabel->setText(QApplication::translate("LoginDialog", "Username:", 0, QApplication::UnicodeUTF8));
    LoginButton->setText(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
	connect(LoginButton,SIGNAL(clicked()),this,SLOT(LoginSlot()));

	//setting the tab order 
	setTabOrder(UserEdit,PasswordEdit);	
	Q_UNUSED(parent);
};

void LoginDialog::LoginSlot()
{
	if(UserEdit->text().isEmpty() || PasswordEdit->text().isEmpty())
		return;
	c_YInstance* yinstance = c_YInstance::GetInstance();	
	yinstance->SetUserPass(UserEdit->text().toStdString(),PasswordEdit->text().toStdString());
	yinstance->start();
	UserEdit->clear();
	PasswordEdit->clear();
	close();
};




