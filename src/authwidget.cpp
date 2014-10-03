#include "authwidget.h"

AuthWidget::AuthWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(new QVBoxLayout);
    layLogin = new QHBoxLayout(this);
    layPassword = new QHBoxLayout(this);
    layButtons = new QHBoxLayout(this);

    lblLogin = new QLabel("Login: ", this);     // Label "Login"
    lblPassword = new QLabel("Password: ", this);   // Label "Password"

    leLogin = new QLineEdit(this);      // Line Edit for Login
    lePassword = new QLineEdit(this);   // Line Edit for Password
    lePassword->setEchoMode(QLineEdit::Password); // for "Password: **********"

    btnLogin = new QPushButton("Login", this);

    layLogin->addWidget(lblLogin);
    layLogin->addWidget(leLogin);

    layPassword->addWidget(lblPassword);
    layPassword->addWidget(lePassword);

    layButtons->addWidget(btnLogin);

    this->layout()->addItem(layLogin);
    this->layout()->addItem(layPassword);
    this->layout()->addItem(layButtons);
}
