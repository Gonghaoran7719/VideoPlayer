/********************************************************************************
** Form generated from reading UI file 'qmymovielabel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMYMOVIELABEL_H
#define UI_QMYMOVIELABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMyMovieLabel
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lb_movie;

    void setupUi(QWidget *QMyMovieLabel)
    {
        if (QMyMovieLabel->objectName().isEmpty())
            QMyMovieLabel->setObjectName(QStringLiteral("QMyMovieLabel"));
        QMyMovieLabel->resize(214, 160);
        verticalLayout = new QVBoxLayout(QMyMovieLabel);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        lb_movie = new QLabel(QMyMovieLabel);
        lb_movie->setObjectName(QStringLiteral("lb_movie"));
        lb_movie->setFrameShape(QFrame::Box);
        lb_movie->setScaledContents(false);
        lb_movie->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lb_movie);


        retranslateUi(QMyMovieLabel);

        QMetaObject::connectSlotsByName(QMyMovieLabel);
    } // setupUi

    void retranslateUi(QWidget *QMyMovieLabel)
    {
        QMyMovieLabel->setWindowTitle(QApplication::translate("QMyMovieLabel", "Form", Q_NULLPTR));
        lb_movie->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QMyMovieLabel: public Ui_QMyMovieLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMYMOVIELABEL_H
