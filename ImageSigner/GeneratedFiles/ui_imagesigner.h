/********************************************************************************
** Form generated from reading UI file 'imagesigner.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESIGNER_H
#define UI_IMAGESIGNER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageSignerClass
{
public:
    QAction *actionOpen_Source_Image;
    QAction *actionOpen_Sign_Image;
    QAction *actionExit;
    QAction *actionAbout_ImageSigner;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_13;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_Res;
    QLabel *label;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_Sign;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_11;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_R;
    QCheckBox *checkBox_G;
    QCheckBox *checkBox_B;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_Enlarge;
    QRadioButton *radioButton_Reduce;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_15;
    QSlider *horizontalSlider_Power;
    QPushButton *pushButton_DoSign;
    QPushButton *pushButton_SaveTo;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_RColor;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_RSpec;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_RAmp;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_GColor;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_GSpec;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_GAmp;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_8;
    QWidget *widget_BColor;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_9;
    QWidget *widget_BSpec;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_BAmp;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_18;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_17;
    QWidget *widget_SignedImage;
    QLabel *label_12;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageSignerClass)
    {
        if (ImageSignerClass->objectName().isEmpty())
            ImageSignerClass->setObjectName(QString::fromUtf8("ImageSignerClass"));
        ImageSignerClass->resize(1340, 911);
        actionOpen_Source_Image = new QAction(ImageSignerClass);
        actionOpen_Source_Image->setObjectName(QString::fromUtf8("actionOpen_Source_Image"));
        actionOpen_Sign_Image = new QAction(ImageSignerClass);
        actionOpen_Sign_Image->setObjectName(QString::fromUtf8("actionOpen_Sign_Image"));
        actionExit = new QAction(ImageSignerClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout_ImageSigner = new QAction(ImageSignerClass);
        actionAbout_ImageSigner->setObjectName(QString::fromUtf8("actionAbout_ImageSigner"));
        centralWidget = new QWidget(ImageSignerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_7 = new QHBoxLayout(centralWidget);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_Res = new QWidget(centralWidget);
        widget_Res->setObjectName(QString::fromUtf8("widget_Res"));
        widget_Res->setMinimumSize(QSize(256, 256));
        widget_Res->setMaximumSize(QSize(256, 256));
        widget_Res->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout->addWidget(widget_Res);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        verticalLayout_13->addLayout(verticalLayout);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        widget_Sign = new QWidget(centralWidget);
        widget_Sign->setObjectName(QString::fromUtf8("widget_Sign"));
        widget_Sign->setMinimumSize(QSize(128, 128));
        widget_Sign->setMaximumSize(QSize(128, 128));
        widget_Sign->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        horizontalLayout_4->addWidget(widget_Sign);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_11->addLayout(horizontalLayout_4);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_11);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_16 = new QVBoxLayout(groupBox);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_14 = new QVBoxLayout(groupBox_2);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_R = new QCheckBox(groupBox_2);
        checkBox_R->setObjectName(QString::fromUtf8("checkBox_R"));
        checkBox_R->setChecked(true);

        horizontalLayout_5->addWidget(checkBox_R);

        checkBox_G = new QCheckBox(groupBox_2);
        checkBox_G->setObjectName(QString::fromUtf8("checkBox_G"));
        checkBox_G->setChecked(true);

        horizontalLayout_5->addWidget(checkBox_G);

        checkBox_B = new QCheckBox(groupBox_2);
        checkBox_B->setObjectName(QString::fromUtf8("checkBox_B"));
        checkBox_B->setChecked(true);

        horizontalLayout_5->addWidget(checkBox_B);


        verticalLayout_14->addLayout(horizontalLayout_5);


        verticalLayout_16->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        radioButton_Enlarge = new QRadioButton(groupBox_3);
        radioButton_Enlarge->setObjectName(QString::fromUtf8("radioButton_Enlarge"));

        horizontalLayout_6->addWidget(radioButton_Enlarge);

        radioButton_Reduce = new QRadioButton(groupBox_3);
        radioButton_Reduce->setObjectName(QString::fromUtf8("radioButton_Reduce"));
        radioButton_Reduce->setChecked(true);

        horizontalLayout_6->addWidget(radioButton_Reduce);


        verticalLayout_16->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_15 = new QVBoxLayout(groupBox_4);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalSlider_Power = new QSlider(groupBox_4);
        horizontalSlider_Power->setObjectName(QString::fromUtf8("horizontalSlider_Power"));
        horizontalSlider_Power->setMinimum(1);
        horizontalSlider_Power->setMaximum(100);
        horizontalSlider_Power->setValue(10);
        horizontalSlider_Power->setOrientation(Qt::Horizontal);

        verticalLayout_15->addWidget(horizontalSlider_Power);


        verticalLayout_16->addWidget(groupBox_4);

        pushButton_DoSign = new QPushButton(groupBox);
        pushButton_DoSign->setObjectName(QString::fromUtf8("pushButton_DoSign"));

        verticalLayout_16->addWidget(pushButton_DoSign);

        pushButton_SaveTo = new QPushButton(groupBox);
        pushButton_SaveTo->setObjectName(QString::fromUtf8("pushButton_SaveTo"));

        verticalLayout_16->addWidget(pushButton_SaveTo);


        verticalLayout_11->addWidget(groupBox);


        verticalLayout_13->addLayout(verticalLayout_11);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer);


        horizontalLayout_7->addLayout(verticalLayout_13);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_RColor = new QWidget(centralWidget);
        widget_RColor->setObjectName(QString::fromUtf8("widget_RColor"));
        widget_RColor->setMinimumSize(QSize(256, 256));
        widget_RColor->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_4->addWidget(widget_RColor);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_RSpec = new QWidget(centralWidget);
        widget_RSpec->setObjectName(QString::fromUtf8("widget_RSpec"));
        widget_RSpec->setMinimumSize(QSize(256, 256));
        widget_RSpec->setMaximumSize(QSize(256, 16777215));
        widget_RSpec->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_2->addWidget(widget_RSpec);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_RAmp = new QWidget(centralWidget);
        widget_RAmp->setObjectName(QString::fromUtf8("widget_RAmp"));
        widget_RAmp->setMinimumSize(QSize(256, 256));
        widget_RAmp->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_3->addWidget(widget_RAmp);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_12->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widget_GColor = new QWidget(centralWidget);
        widget_GColor->setObjectName(QString::fromUtf8("widget_GColor"));
        widget_GColor->setMinimumSize(QSize(256, 256));
        widget_GColor->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_5->addWidget(widget_GColor);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_5);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widget_GSpec = new QWidget(centralWidget);
        widget_GSpec->setObjectName(QString::fromUtf8("widget_GSpec"));
        widget_GSpec->setMinimumSize(QSize(256, 256));
        widget_GSpec->setMaximumSize(QSize(256, 16777215));
        widget_GSpec->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_6->addWidget(widget_GSpec);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_6);


        horizontalLayout_2->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        widget_GAmp = new QWidget(centralWidget);
        widget_GAmp->setObjectName(QString::fromUtf8("widget_GAmp"));
        widget_GAmp->setMinimumSize(QSize(256, 256));
        widget_GAmp->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_7->addWidget(widget_GAmp);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_7);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout_12->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        widget_BColor = new QWidget(centralWidget);
        widget_BColor->setObjectName(QString::fromUtf8("widget_BColor"));
        widget_BColor->setMinimumSize(QSize(256, 256));
        widget_BColor->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_8->addWidget(widget_BColor);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_8);


        horizontalLayout_3->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        widget_BSpec = new QWidget(centralWidget);
        widget_BSpec->setObjectName(QString::fromUtf8("widget_BSpec"));
        widget_BSpec->setMinimumSize(QSize(256, 256));
        widget_BSpec->setMaximumSize(QSize(256, 16777215));
        widget_BSpec->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_9->addWidget(widget_BSpec);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_9);


        horizontalLayout_3->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        widget_BAmp = new QWidget(centralWidget);
        widget_BAmp->setObjectName(QString::fromUtf8("widget_BAmp"));
        widget_BAmp->setMinimumSize(QSize(256, 256));
        widget_BAmp->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_10->addWidget(widget_BAmp);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_10);


        horizontalLayout_3->addLayout(verticalLayout_10);


        verticalLayout_12->addLayout(horizontalLayout_3);


        horizontalLayout_7->addLayout(verticalLayout_12);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_3);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        widget_SignedImage = new QWidget(centralWidget);
        widget_SignedImage->setObjectName(QString::fromUtf8("widget_SignedImage"));
        widget_SignedImage->setMinimumSize(QSize(256, 256));
        widget_SignedImage->setMaximumSize(QSize(256, 256));
        widget_SignedImage->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        verticalLayout_17->addWidget(widget_SignedImage);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_12);


        verticalLayout_18->addLayout(verticalLayout_17);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_4);


        horizontalLayout_7->addLayout(verticalLayout_18);

        ImageSignerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageSignerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1340, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        ImageSignerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ImageSignerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ImageSignerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen_Source_Image);
        menuFile->addAction(actionOpen_Sign_Image);
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAbout_ImageSigner);

        retranslateUi(ImageSignerClass);

        QMetaObject::connectSlotsByName(ImageSignerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageSignerClass)
    {
        ImageSignerClass->setWindowTitle(QApplication::translate("ImageSignerClass", "ImageSigner", 0, QApplication::UnicodeUTF8));
        actionOpen_Source_Image->setText(QApplication::translate("ImageSignerClass", "Open Source Image", 0, QApplication::UnicodeUTF8));
        actionOpen_Sign_Image->setText(QApplication::translate("ImageSignerClass", "Open Sign Image", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("ImageSignerClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionAbout_ImageSigner->setText(QApplication::translate("ImageSignerClass", "About ImageSigner", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImageSignerClass", "Source Image", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ImageSignerClass", "Sign Image", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ImageSignerClass", "Sign Infomations", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ImageSignerClass", "Sign to color channel", 0, QApplication::UnicodeUTF8));
        checkBox_R->setText(QApplication::translate("ImageSignerClass", "R", 0, QApplication::UnicodeUTF8));
        checkBox_G->setText(QApplication::translate("ImageSignerClass", "G", 0, QApplication::UnicodeUTF8));
        checkBox_B->setText(QApplication::translate("ImageSignerClass", "B", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ImageSignerClass", "Sign mode", 0, QApplication::UnicodeUTF8));
        radioButton_Enlarge->setText(QApplication::translate("ImageSignerClass", "enlarge", 0, QApplication::UnicodeUTF8));
        radioButton_Reduce->setText(QApplication::translate("ImageSignerClass", "Reduce", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ImageSignerClass", "Power", 0, QApplication::UnicodeUTF8));
        pushButton_DoSign->setText(QApplication::translate("ImageSignerClass", "Do Sign", 0, QApplication::UnicodeUTF8));
        pushButton_SaveTo->setText(QApplication::translate("ImageSignerClass", "Save to file", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ImageSignerClass", "R", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ImageSignerClass", "Spectrum", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ImageSignerClass", "Amplitude", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ImageSignerClass", "G", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ImageSignerClass", "Spectrum", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ImageSignerClass", "Amplitude", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ImageSignerClass", "B", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ImageSignerClass", "Spectrum", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ImageSignerClass", "Amplitude", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ImageSignerClass", "Signed Image", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("ImageSignerClass", "File", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("ImageSignerClass", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageSignerClass: public Ui_ImageSignerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESIGNER_H
