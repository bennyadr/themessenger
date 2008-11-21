#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QFrame>
#include <QDialog>
#include <QRadioButton>
#include <QApplication>
#include <QGridLayout>

#include "Login.h"
#include "yinstance.h"

LoginDialog::LoginDialog(QWidget *parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("LoginDialog"));
    this->resize(288, 165);


	GLayout = new QGridLayout(this);
		
	UserLabel = new QLabel(this);
    UserLabel->setObjectName(QString::fromUtf8("UserLabel"));
	UserEdit = new QLineEdit(this);
    UserEdit->setObjectName(QString::fromUtf8("UserEdit"));
	GLayout->addWidget(UserLabel,0,0);
	GLayout->addWidget(UserEdit,0,1);

   	PasswordLabel = new QLabel(this);
    PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));
    PasswordEdit = new QLineEdit(this);
    PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
	PasswordEdit->setEchoMode(QLineEdit::Password);
	GLayout->addWidget(PasswordLabel,1,0);
	GLayout->addWidget(PasswordEdit,1,1);
	
    LoginButton = new QPushButton(this);
    LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
    LoginButton->setGeometry(QRect(150, 100, 75, 24));

	GLayout->addWidget(LoginButton,2,0);
	this->setLayout(GLayout);

	this->setModal(true);
	//setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowTitle(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
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




