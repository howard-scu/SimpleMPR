/********************************************************************************
** Form generated from reading UI file 'qtmprdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMPRDEMO_H
#define UI_QTMPRDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtMprDemoClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnA;
    QPushButton *btnC;
    QPushButton *btnS;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSlider *x;
    QSlider *y;
    QSlider *z;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QSlider *ax;
    QSlider *ay;
    QSlider *az;
    QSlider *slice;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtMprDemoClass)
    {
        if (QtMprDemoClass->objectName().isEmpty())
            QtMprDemoClass->setObjectName(QStringLiteral("QtMprDemoClass"));
        QtMprDemoClass->resize(757, 420);
        centralWidget = new QWidget(QtMprDemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 21, 691, 151));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        btnA = new QPushButton(layoutWidget);
        btnA->setObjectName(QStringLiteral("btnA"));

        verticalLayout_3->addWidget(btnA);

        btnC = new QPushButton(layoutWidget);
        btnC->setObjectName(QStringLiteral("btnC"));

        verticalLayout_3->addWidget(btnC);

        btnS = new QPushButton(layoutWidget);
        btnS->setObjectName(QStringLiteral("btnS"));

        verticalLayout_3->addWidget(btnS);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        x = new QSlider(layoutWidget);
        x->setObjectName(QStringLiteral("x"));
        x->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(x);

        y = new QSlider(layoutWidget);
        y->setObjectName(QStringLiteral("y"));
        y->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(y);

        z = new QSlider(layoutWidget);
        z->setObjectName(QStringLiteral("z"));
        z->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(z);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        ax = new QSlider(layoutWidget);
        ax->setObjectName(QStringLiteral("ax"));
        ax->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(ax);

        ay = new QSlider(layoutWidget);
        ay->setObjectName(QStringLiteral("ay"));
        ay->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(ay);

        az = new QSlider(layoutWidget);
        az->setObjectName(QStringLiteral("az"));
        az->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(az);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);
        horizontalLayout->setStretch(2, 3);
        slice = new QSlider(centralWidget);
        slice->setObjectName(QStringLiteral("slice"));
        slice->setGeometry(QRect(60, 190, 531, 91));
        slice->setOrientation(Qt::Horizontal);
        QtMprDemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtMprDemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 757, 23));
        QtMprDemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtMprDemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtMprDemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtMprDemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtMprDemoClass->setStatusBar(statusBar);

        retranslateUi(QtMprDemoClass);

        QMetaObject::connectSlotsByName(QtMprDemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtMprDemoClass)
    {
        QtMprDemoClass->setWindowTitle(QApplication::translate("QtMprDemoClass", "QtMprDemo", Q_NULLPTR));
        btnA->setText(QApplication::translate("QtMprDemoClass", "A", Q_NULLPTR));
        btnC->setText(QApplication::translate("QtMprDemoClass", "C", Q_NULLPTR));
        btnS->setText(QApplication::translate("QtMprDemoClass", "S", Q_NULLPTR));
        label->setText(QApplication::translate("QtMprDemoClass", "\345\210\207\347\211\207", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtMprDemoClass", "\350\247\222\345\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtMprDemoClass: public Ui_QtMprDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMPRDEMO_H
