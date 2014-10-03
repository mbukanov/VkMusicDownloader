#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Window;

class AuthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AuthWidget(QWidget *parent = 0);
    friend class Window;

private:
    QHBoxLayout * layLogin = NULL;
    QHBoxLayout * layPassword = NULL;
    QHBoxLayout * layButtons = NULL;

    QLabel * lblLogin = NULL;
    QLabel * lblPassword = NULL;

    QLineEdit *leLogin = NULL;
    QLineEdit *lePassword = NULL;

    QPushButton *btnLogin = NULL;


signals:

public slots:

};

#endif // AUTHWIDGET_H
