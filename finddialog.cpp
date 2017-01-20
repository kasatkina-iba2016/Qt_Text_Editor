#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    label = new QLabel(tr("Найти:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);
    caseCheckBox=new QCheckBox(tr("У&читывать регистр"));
    backwardButton=new QPushButton(tr("Наза&д"));
    findButton=new QPushButton(tr("В&перед"));
    closeButton = new QPushButton(tr("&Закрыть"));

    text=lineEdit->text();

    connect(lineEdit, SIGNAL(textChanged(QString &)),this, SLOT(slotEnableFind(const QString &)));
    connect(findButton, SIGNAL(clicked()),this, SLOT(slotFindNext()));
    connect(backwardButton, SIGNAL(clicked()),this, SLOT(slotFindPrev()));
    connect(closeButton, SIGNAL(clicked()),this, SLOT(close()));

    QHBoxLayout *Lay1=new QHBoxLayout;
    Lay1->addWidget(label);
    Lay1->addWidget(lineEdit);
    QVBoxLayout *Lay2=new QVBoxLayout;
    Lay2->addLayout(Lay1);
    Lay2->addWidget(caseCheckBox);
    QVBoxLayout *Lay3=new QVBoxLayout;
    Lay3->addWidget(findButton);
    Lay3->addWidget(backwardButton);
    Lay3->addWidget(closeButton);
    Lay3->addStretch();
    QHBoxLayout *Lay4=new QHBoxLayout;
    Lay4->addLayout(Lay2);
    Lay4->addLayout(Lay3);
    setLayout(Lay4);

    setWindowTitle(tr("Поиск"));
    setFixedHeight(sizeHint().height());
}

void FindDialog::slotFindNext()
{
   // Qt::CaseSensitivity cs=caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    emit findNext(text);//,cs);
}

void FindDialog::slotFindPrev()
{
   // Qt::CaseSensitivity cs=caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    emit findPrevious(text);//, cs);
}

void FindDialog::slotEnableFind()
{
    findButton->setEnabled(!text.isEmpty());
}

