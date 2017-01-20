#ifndef WIDGET_H
#define WIDGET_H
#include <QtWidgets>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMessageBox>
#include <QDir>
#include <QAction>
#include <QTextCursor>
#include <QCloseEvent>
#include "finddialog.h"

class Widget : public QWidget
{
    Q_OBJECT

    QTextEdit *txt;
    QMenu *mnuFile1,*mnuFile2,*mnuFile3;
    QMenuBar *mnuBar;
    QToolBar *ptb1,*ptb2,*ptb3,*ptb4,*ptb5;
    QAction *boldAction,*itallicAction,*underAction,*leftAction,*rightAction,*centerAction,*justifyAction,*colorAction;
    QActionGroup *group;
    QFontComboBox *comFont;
    QComboBox *comSize;

public:
    QString fileName;
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    void formatSelection(const QTextCharFormat &format);
    void alignmentChanged(Qt::Alignment a);
    void findWord();

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    bool maybeSave();
    void textAlign(QAction *act);
    void textBold();
    void textColor();
    void textItallic();
    void textFamily(const QString &myFamily);
    void textSize(const QString &mySize);
    void textUnderLine();
    void cursorPositionChanged();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
