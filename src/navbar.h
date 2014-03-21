#ifndef NAVBAR_H
#define NAVBAR_H

#include <QLabel>
#include <QStackedWidget>
#include <QToolBar>
#include <QList>
#include <QActionGroup>
#include <QMenu>
#include "navbarsplitter.h"
#include "navbarpagelist.h"

class NavBarHeader: public QLabel
{
    Q_OBJECT

public:
    explicit NavBarHeader(QWidget *parent = 0, Qt::WindowFlags f = 0);
    explicit NavBarHeader(const QString & text, QWidget *parent = 0, Qt::WindowFlags f = 0);
};

class NavBarToolBar: public QToolBar
{
    Q_OBJECT

public:
    explicit NavBarToolBar(QWidget *parent = 0);
};

class NavBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int   count         READ count)
    Q_PROPERTY(int   currentIndex  READ currentIndex  WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int   rowHeight     READ rowHeight     WRITE setRowHeight)
    Q_PROPERTY(bool  showHeader    READ showHeader    WRITE setShowHeader)
    Q_PROPERTY(bool  showOptionsMenu READ showOptionsMenu WRITE setShowOptionsMenu)
    Q_PROPERTY(int   visibleRows   READ visibleRows   WRITE setVisibleRows  NOTIFY visibleRowsChanged)
    Q_PROPERTY(QSize smallIconSize READ smallIconSize WRITE setSmallIconSize)
    Q_PROPERTY(QSize largeIconSize READ largeIconSize WRITE setLargeIconSize)

public:
    explicit NavBar(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~NavBar();

    int      addPage(QWidget *page);
    int      addPage(QWidget *page, const QString &title);
    int      addPage(QWidget *page, const QString &title, const QIcon &icon);
    QWidget *currentWidget() const;
    int      indexOf(QWidget *widget) const;
    int      insertPage(int index, QWidget *page);
    int      insertPage(int index, QWidget *page, const QString &title);
    int      insertPage(int index, QWidget *page, const QString &title, const QIcon &icon);
    bool     isPageEnabled(int index);
    QIcon    pageIcon(int index) const;
    QString  pageTitle(int index) const;
    void     setPageEnabled(int index, bool enabled);
    void     setPageIcon(int index, const QIcon &icon);
    void     setPageTitle(int index, const QString &title);
    void     removePage(int index);
    QWidget *widget(int index) const;

    int      count() const;
    int      currentIndex() const;
    int      rowHeight() const;
    bool     showHeader() const;
    bool     showOptionsMenu() const;
    int      visibleRows() const;
    QSize    smallIconSize() const;
    QSize    largeIconSize() const;
    void     setSmallIconSize(const QSize &size);
    void     setLargeIconSize(const QSize &size);

    QSize    sizeHint() const;

    static QString loadStyle(const QString &filename);

signals:
    void currentChanged(int index);
    void visibleRowsChanged(int rows);

public slots:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);
    void setRowHeight(int height);
    void setShowHeader(bool show);
    void setShowOptionsMenu(bool show);
    void setVisibleRows(int rows);

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void onClickPageButton(QAction *action);
    void onButtonVisibilityChanged(int visCount);

private:
    int  createPage(int index, QWidget *page, const QString &title, const QIcon &icon);
    void resizeContent(const QSize &size, int rowheight);
    void refillToolBar(int visCount);
    void refillPagesMenu();

    NavBarHeader    *header;
    QStackedWidget  *stackedWidget;
    NavBarSplitter  *splitter;
    NavBarPageList  *pageList;
    NavBarToolBar   *pageToolBar;
    QList<QAction *> pageActions;
    QActionGroup    *actionGroup;
    QMenu           *pagesMenu;

    bool optMenuVisible;
    bool headerVisible;
    int  headerHeight;
};

#endif // NAVBAR_H
