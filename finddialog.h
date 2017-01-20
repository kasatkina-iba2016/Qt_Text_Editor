#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <qdialog.h>
#include <QDialog>
#include <QtWidgets>
#include <Qt>

class FindDialog : public QDialog
{
    Q_OBJECT

    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
    QPushButton *backwardButton;
    QString text;
public:
    explicit FindDialog(QWidget *parent = 0);

signals:

    void findNext(const QString &str);//, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str);//, Qt::CaseSensitivity cs);
private slots:
    void slotFindNext();
    void slotFindPrev();
    void slotEnableFind();
};

#endif // FINDDIALOG_H
