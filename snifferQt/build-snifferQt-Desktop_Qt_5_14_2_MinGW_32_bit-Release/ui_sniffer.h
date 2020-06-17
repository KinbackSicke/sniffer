/********************************************************************************
** Form generated from reading UI file 'sniffer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNIFFER_H
#define UI_SNIFFER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sniffer
{
public:
    QWidget *centralwidget;
    QComboBox *adapters;
    QPushButton *selectBtn;
    QTableWidget *PCITable;
    QTableWidget *trafficTable;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *captimeText;
    QTextEdit *PCIText;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sniffer)
    {
        if (sniffer->objectName().isEmpty())
            sniffer->setObjectName(QString::fromUtf8("sniffer"));
        sniffer->resize(1057, 640);
        sniffer->setMinimumSize(QSize(1057, 640));
        centralwidget = new QWidget(sniffer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        adapters = new QComboBox(centralwidget);
        adapters->setObjectName(QString::fromUtf8("adapters"));
        adapters->setGeometry(QRect(10, 10, 901, 22));
        selectBtn = new QPushButton(centralwidget);
        selectBtn->setObjectName(QString::fromUtf8("selectBtn"));
        selectBtn->setGeometry(QRect(930, 10, 111, 23));
        PCITable = new QTableWidget(centralwidget);
        if (PCITable->columnCount() < 8)
            PCITable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        PCITable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        PCITable->setObjectName(QString::fromUtf8("PCITable"));
        PCITable->setGeometry(QRect(10, 50, 711, 321));
        trafficTable = new QTableWidget(centralwidget);
        if (trafficTable->columnCount() < 3)
            trafficTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        trafficTable->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        trafficTable->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        trafficTable->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        trafficTable->setObjectName(QString::fromUtf8("trafficTable"));
        trafficTable->setGeometry(QRect(730, 90, 311, 501));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(730, 50, 311, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        captimeText = new QLineEdit(horizontalLayoutWidget);
        captimeText->setObjectName(QString::fromUtf8("captimeText"));

        horizontalLayout->addWidget(captimeText);

        PCIText = new QTextEdit(centralwidget);
        PCIText->setObjectName(QString::fromUtf8("PCIText"));
        PCIText->setGeometry(QRect(10, 400, 711, 191));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 380, 72, 15));
        sniffer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sniffer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1057, 23));
        sniffer->setMenuBar(menubar);
        statusbar = new QStatusBar(sniffer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        sniffer->setStatusBar(statusbar);

        retranslateUi(sniffer);

        QMetaObject::connectSlotsByName(sniffer);
    } // setupUi

    void retranslateUi(QMainWindow *sniffer)
    {
        sniffer->setWindowTitle(QCoreApplication::translate("sniffer", "sniffer", nullptr));
        selectBtn->setText(QCoreApplication::translate("sniffer", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem = PCITable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("sniffer", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = PCITable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("sniffer", "\345\214\205\346\200\273\351\225\277\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = PCITable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("sniffer", "\346\272\220ip\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = PCITable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("sniffer", "\347\233\256\347\232\204ip\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = PCITable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("sniffer", "\345\215\217\350\256\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = PCITable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("sniffer", "\346\272\220\347\253\257\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = PCITable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("sniffer", "\347\233\256\347\232\204\347\253\257\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = PCITable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("sniffer", "\345\255\230\346\264\273\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = trafficTable->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("sniffer", "\346\272\220ip\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = trafficTable->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("sniffer", "\347\233\256\347\232\204ip\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = trafficTable->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("sniffer", "\346\265\201\351\207\217\357\274\210\345\214\205\347\232\204\346\225\260\351\207\217\357\274\211", nullptr));
        label->setText(QCoreApplication::translate("sniffer", "\347\233\221\345\220\254\346\254\241\346\225\260\357\274\232", nullptr));
        captimeText->setText(QCoreApplication::translate("sniffer", "10", nullptr));
        label_2->setText(QCoreApplication::translate("sniffer", "\350\257\246\347\273\206\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sniffer: public Ui_sniffer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNIFFER_H
