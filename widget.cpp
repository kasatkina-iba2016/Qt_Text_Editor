#include "widget.h"
#include "finddialog.h"

#include <QIcon>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    txt=new QTextEdit;
    mnuBar=new QMenuBar;

    connect(txt,SIGNAL(currentCharFormatChanged(QTextCharFormat)),this, SLOT(currentCharFormatChanged(QTextCharFormat)));
    connect(txt,SIGNAL(cursorPositionChanged()),this, SLOT(cursorPositionChanged()));
    txt->setFocus();

    mnuFile1=new QMenu("&Файл");
    mnuFile2=new QMenu("&Правка");
    mnuFile3=new QMenu("&Формат");

    this->setWindowIcon(QIcon(":/new/Gimp.png"));
    setWindowTitle("Новый-WordRed");

    QAction *newAction=new QAction(tr("&Создать"), this);
    mnuFile1->addAction(QIcon(":/new/New.png"),"&Создать",this,SLOT(fileNew()),Qt::CTRL + Qt::Key_N);
    newAction->setIcon(QIcon(":/new/New.png"));
    newAction->setIconVisibleInMenu(true);
    connect(newAction, SIGNAL(triggered()), txt, SLOT(fileNew()));
    mnuFile1->addSeparator();

    QAction *openAction=new QAction(tr("&Открыть..."), this);
    mnuFile1->addAction(QIcon(":/new/Open.png"),"&Открыть...",this,SLOT(fileOpen()),Qt::CTRL + Qt::Key_O);
    openAction->setIcon(QIcon(":/new/Open.png"));
    openAction->setIconVisibleInMenu(true);
    connect(openAction, SIGNAL(triggered()), txt, SLOT(fileOpen()));
    mnuFile1->addSeparator();

    QAction *saveAction=new QAction(tr("&Сохранить"), this);
    mnuFile1->addAction(QIcon(":/new/Save.png"),"Со&хранить",this,SLOT(fileSave()),Qt::CTRL + Qt::Key_S);
    saveAction->setIcon(QIcon(":/new/Save.png"));
    saveAction->setIconVisibleInMenu(true);
    connect(saveAction, SIGNAL(triggered()), txt, SLOT(fileSave()));
    mnuFile1->addSeparator();

    QAction *saveAsAction=new QAction(tr("&Сохранить как..."), this);
    mnuFile1->addAction(QIcon(":/new/SaveAs.png"),"&Сохранить как...",this,SLOT(fileSaveAs()),Qt::CTRL+Qt::SHIFT+Qt::Key_S);
    saveAsAction->setIcon(QIcon(":/new/SaveAs.png"));
    saveAsAction->setIconVisibleInMenu(true);
    connect(saveAsAction, SIGNAL(triggered()), txt, SLOT(fileSaveAs()));
    mnuFile1->addSeparator();

    QAction *exitAction=new QAction(tr("&Выход..."), this);
    mnuFile1->addAction(QIcon(":/new/Exit.png"),"&Выход...",this,SLOT(close()),Qt::ALT + Qt::Key_F4);
    exitAction->setIcon(QIcon(":/new/Exit.png"));
    exitAction->setIconVisibleInMenu(true);
    connect(exitAction, SIGNAL(triggered()), txt, SLOT(close()));

    QAction *undoAction=new QAction(tr("Отменить"), this);
    mnuFile2->addAction(undoAction);
    undoAction->setIcon(QIcon(":/new/undo.png"));
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setIconVisibleInMenu(true);
    connect(undoAction, SIGNAL(triggered()), txt, SLOT(undo()));

    QAction *redoAction=new QAction(tr("Повторить"), this);
    mnuFile2->addAction(redoAction);
    redoAction->setIcon(QIcon(":/new/redo.png"));
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setIconVisibleInMenu(true);
    connect(redoAction, SIGNAL(triggered()), txt, SLOT(redo()));

    connect(txt->document(),SIGNAL(modificationChanged(bool)),saveAction, SLOT(setEnabled(bool)));
    connect(txt->document(),SIGNAL(modificationChanged(bool)),this, SLOT(setWindowModified(bool)));
    connect(txt->document(), SIGNAL(undoAvailable(bool)),undoAction, SLOT(setEnabled(bool)));
    connect(txt->document(), SIGNAL(redoAvailable(bool)),redoAction, SLOT(setEnabled(bool)));

    setWindowModified(txt->document()->isModified());
    saveAction->setEnabled(txt->document()->isModified());
    undoAction->setEnabled(txt->document()->isUndoAvailable());
    redoAction->setEnabled(txt->document()->isRedoAvailable());

    connect(undoAction, SIGNAL(triggered()), txt, SLOT(undo()));
    connect(redoAction, SIGNAL(triggered()), txt, SLOT(redo()));

    mnuFile2->addSeparator();
    mnuFile2->addAction(QIcon(":/new/selectAll.png"),"&Выделить все",txt, SLOT(selectAll()),Qt::CTRL + Qt::Key_A);
    mnuFile2->addSeparator();
    mnuFile2->addAction(QIcon(":/new/Copy.png"),"&Копировать",txt, SLOT(copy()),Qt::CTRL + Qt::Key_C);
    mnuFile2->addSeparator();
    mnuFile2->addAction(QIcon(":/new/Paste.png"),"&Вставить",txt, SLOT(paste()), Qt::CTRL + Qt::Key_V);
    mnuFile2->addSeparator();
    mnuFile2->addAction(QIcon(":/new/Cut.png"),"&Вырезать",txt,SLOT(cut()),Qt::CTRL + Qt::Key_X);

    ptb1=new QToolBar;
    ptb1->addAction(QIcon(":/new/New.png"),"&Создать",this, SLOT(fileNew()));
    ptb1->addAction(QIcon(":/new/Open.png"),"&Открыть...",this,SLOT(fileOpen()));
    ptb1->addAction(QIcon(":/new/Save.png"),"Со&хранить",this,SLOT(fileSave()));
    ptb1->addSeparator();
    ptb1->addSeparator();
    ptb1->addAction(undoAction);
    ptb1->addAction(redoAction);

    ptb2=new QToolBar;
    ptb2->addAction(QIcon(":/new/selectAll.png"),"Выделить все",txt, SLOT(selectAll()));
    ptb2->addAction(QIcon(":/new/Copy.png"),"Копировать",txt, SLOT(copy()));
    ptb2->addAction(QIcon(":/new/Paste.png"),"Вставить",txt, SLOT(paste()));
    ptb2->addAction(QIcon(":/new/Cut.png"), "Вырезать", txt, SLOT(cut()));

    ptb4=new QToolBar;

    boldAction=new QAction(tr("Жирный"), this);
    mnuFile3->addAction(boldAction);
    boldAction->setIcon(QIcon(":/new/Formatting (Bold) - Red_32x32.png"));
    boldAction->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    boldAction->setFont(bold);
    connect(boldAction, SIGNAL(triggered()),this, SLOT(textBold()));
    boldAction->setCheckable(true);
    boldAction->setIconVisibleInMenu(true);

    itallicAction=new QAction(tr("Курсив"), this);
    mnuFile3->addAction(itallicAction);
    itallicAction->setIcon(QIcon(":/new/Formatting (Italic) - Orange_32x32.png"));
    itallicAction->setPriority(QAction::LowPriority);
    QFont ital;
    ital.setItalic(true);
    itallicAction->setFont(ital);
    connect(itallicAction, SIGNAL(triggered()),this, SLOT(textItallic()));
    itallicAction->setCheckable(true);
    itallicAction->setIconVisibleInMenu(true);

    underAction=new QAction(tr("Подчеркнутый"), this);
    mnuFile3->addAction(underAction);
    underAction->setIcon(QIcon(":/new/Formatting (Underline) - Green_32x32.png"));
    QFont under;
    under.setUnderline(true);
    underAction->setFont(under);
    connect(underAction, SIGNAL(triggered()),this, SLOT(textUnderLine()));
    underAction->setCheckable(true);
    underAction->setIconVisibleInMenu(true);

    mnuFile3->addSeparator();

    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction*)), this, SLOT(textAlign(QAction*)));

    if (QApplication::isLeftToRight()) {
        leftAction = new QAction(QIcon(":/new/Text Align (Left) - White_32x32.png"),
                                      tr("&По левому краю"), grp);
        centerAction = new QAction(QIcon(":/new/Text Align (Center) - White_32x32.png"), tr("По &центру"), grp);
        rightAction = new QAction(QIcon(":/new/Text Align (Right) - White_32x32.png"), tr("По п&равому краю"), grp);
    } else {
        rightAction = new QAction(QIcon(":/new/Text Align (Right) - White_32x32.png"), tr("По п&равому краю"), grp);
        centerAction = new QAction(QIcon(":/new/Text Align (Center) - White_32x32.png"), tr("По &центру"), grp);
        leftAction = new QAction(QIcon(":/new/Text Align (Left) - White_32x32.png"), tr("&По левому краю"), grp);
    }

    leftAction->setShortcut(Qt::CTRL + Qt::Key_L);
    leftAction->setCheckable(true);
    leftAction->setPriority(QAction::LowPriority);
    leftAction->setIconVisibleInMenu(true);
    centerAction->setShortcut(Qt::CTRL + Qt::Key_E);
    centerAction->setCheckable(true);
    centerAction->setPriority(QAction::LowPriority);
    centerAction->setIconVisibleInMenu(true);
    rightAction->setShortcut(Qt::CTRL + Qt::Key_R);
    rightAction->setCheckable(true);
    rightAction->setPriority(QAction::LowPriority);
    rightAction->setIconVisibleInMenu(true);

    mnuFile3->addAction(leftAction);
    mnuFile3->addAction(centerAction);
    mnuFile3->addAction(rightAction);
    mnuFile3->addSeparator();

    colorAction=new QAction(tr("Цвет текста..."), this);
    mnuFile3->addAction(colorAction);
    colorAction->setIcon(QIcon(":/new/Text Colour (Foreground) - Black_32x32.png"));
    colorAction->setPriority(QAction::LowPriority);
    colorAction->setIconVisibleInMenu(true);
    connect(colorAction, SIGNAL(triggered()),this, SLOT(textColor()));

    comFont=new QFontComboBox(ptb2);
    ptb2->addWidget(comFont);
    connect(comFont,SIGNAL(activated(QString)),this,SLOT(textFamily(QString)));

    comSize=new QComboBox(ptb2);
    ptb2->addWidget(comSize);
    comSize->setVisible(true);

    QFontDatabase db;
    foreach(int size, db.standardSizes())
       comSize->addItem(QString::number(size));

    comSize->setCurrentIndex(comSize->findText(QString::number(QApplication::font().pointSize())));
    connect(comSize,SIGNAL(activated(QString)),this,SLOT(textSize(QString)));

    ptb4->addAction(boldAction);
    ptb4->addAction(itallicAction);
    ptb4->addAction(underAction);
    ptb4->addSeparator();
    ptb4->addAction(leftAction);
    ptb4->addAction(centerAction);
    ptb4->addAction(rightAction);
    ptb4->addAction(colorAction);

    mnuBar->addMenu(mnuFile1);
    mnuBar->addMenu(mnuFile2);
    mnuBar->addMenu(mnuFile3);
    mnuBar->show();

    txt->setStyleSheet("background:white; border:orange; color: black");

   qApp->setStyleSheet("QWidget { background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0.1 #193838, stop: 0.2 #142121, stop:0.5 darckgrey);"
                                                 "color: white;}");
    QVBoxLayout *Lay1=new QVBoxLayout;
    QHBoxLayout *Lay2=new QHBoxLayout;
    Lay1->addWidget(mnuBar);
    Lay2->addWidget(ptb1);
    Lay2->addWidget(ptb2);
    Lay2->addWidget(ptb4);
    Lay1->addLayout(Lay2);
    Lay1->addWidget(txt);
    setLayout(Lay1);
    resize(900,600);
  }

void Widget::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) event->accept();
    else event->ignore();
}

void Widget::fileNew()
{
    if (maybeSave()) {
            txt->clear();}
}

void Widget::fileOpen()
{
    fileName=QFileDialog::getOpenFileName
    (this,"Открыть...",QDir::homePath(),"Text files(*.txt )");
    QFileInfo fi(fileName);
    QString base=fi.baseName();
    QFile Myfile(fileName);
      if ( Myfile.open ( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            txt->setPlainText(Myfile.readAll());
            Myfile.close();
            setWindowTitle(base+"-WordRed");
            setWindowModified(false);
        }
}

void Widget::fileSave()
{
    if (!windowTitle().startsWith("Новый"))
     {
      QString str = txt->toPlainText();
      QFile file(fileName);
      file.open(QIODevice::WriteOnly | QIODevice::Text);
      file.write(str.toStdString().c_str());
      file.close();
      setWindowModified(false);
     }
    else fileSaveAs();
}

void Widget::fileSaveAs()
{
    fileName=QFileDialog::getSaveFileName
   (this,"Сохранить как...",QDir::homePath(),"Text files( *.txt )");

        QFile Myfile(fileName);
        if (Myfile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString str = txt->toPlainText();
            Myfile.write(str.toStdString().c_str());
            Myfile.close();
            setWindowModified(false);
        }
}

bool Widget::maybeSave()
{
    if (txt->document()->isModified())
    {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("WordRed"),
       tr("The file has been modified.\nDo you want to save your changes?"),
       QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
       if (ret == QMessageBox::Save)
        {
           fileSaveAs();
        }
       else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

void Widget::textBold()
{
    QTextCharFormat form;
    if (boldAction->isChecked())
        form.setFontWeight(QFont::Bold);
    else
        form.setFontWeight(QFont::Normal);

    formatSelection(form);
}

void Widget::textColor()
{
  QColor myColor=QColorDialog::getColor(txt->textColor(),this);
  if (!myColor.isValid()) return;
  QTextCharFormat myFormat;
  myFormat.setForeground(myColor);
  formatSelection(myFormat);
}

void Widget::textItallic()
{
    QTextCharFormat form;
    form.setFontItalic(itallicAction->isChecked());
    formatSelection(form);
}

void Widget::textFamily(const QString &myFamily)
{
    QTextCharFormat form;
    form.setFontFamily(myFamily);
    formatSelection(form);
}

void Widget::textSize(const QString &mySize)
{
    qreal pointSize = mySize.toFloat();
    if (mySize.toFloat() > 0)
    {
       QTextCharFormat myFormat;
       myFormat.setFontPointSize(pointSize);
       formatSelection(myFormat);
     }
}

void Widget::textUnderLine()
{
    QTextCharFormat form;
    form.setFontUnderline(underAction->isChecked());
    formatSelection(form);
}

Widget::~Widget()
{

}

void Widget::formatSelection(const QTextCharFormat &form)
{
    QTextCursor cursor = txt->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    cursor.mergeCharFormat(form);
    txt->mergeCurrentCharFormat(form);
}

void Widget::cursorPositionChanged()
{
  alignmentChanged(txt->alignment());
}

void Widget::textAlign(QAction *act)
{
    if (act==leftAction)
        txt->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (act==centerAction)
        txt->setAlignment(Qt::AlignHCenter);
    else if (act==rightAction)
        txt->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}

void Widget::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft) {
        leftAction->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        centerAction->setChecked(true);
    } else if (a & Qt::AlignRight) {
        rightAction->setChecked(true);
    }
}

void Widget::findWord()
{

}

