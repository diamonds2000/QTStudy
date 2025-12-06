#include "mainwindow.h"
#include "drawview.h"
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("QT Study"));
    
    // Create central draw view
    m_drawView = new DrawView(this);
    setCentralWidget(m_drawView);
    
    // Create menus
    createMenus();
    
    // Create toolbars
    createToolBars();
    
    // Create dock windows
    createDockWindows();
    
    // Set initial window size
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenus()
{
    m_menuBar = menuBar();
    
    // File menu
    QMenu *fileMenu = m_menuBar->addMenu(tr("&File"));
    QAction *newAct = fileMenu->addAction(tr("&New"));
    QAction *openAct = fileMenu->addAction(tr("&Open"));
    fileMenu->addSeparator();
    QAction *exitAct = fileMenu->addAction(tr("E&xit"));
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QApplication::quit);
    
    // Edit menu
    QMenu *editMenu = m_menuBar->addMenu(tr("&Edit"));
    QAction *cutAct = editMenu->addAction(tr("Cu&t"));
    QAction *copyAct = editMenu->addAction(tr("&Copy"));
    QAction *pasteAct = editMenu->addAction(tr("&Paste"));
    
    // View menu
    QMenu *viewMenu = m_menuBar->addMenu(tr("&View"));
    
    // Help menu
    QMenu *helpMenu = m_menuBar->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"));
}

void MainWindow::createToolBars()
{
    m_toolBar = addToolBar(tr("Main"));

    QAction* newAct = m_toolBar->addAction(style()->standardIcon(QStyle::SP_FileIcon), tr("&New"));
    QAction* openAct = m_toolBar->addAction(style()->standardIcon(QStyle::SP_DialogOpenButton), tr("&Open"));
    m_toolBar->addSeparator();
    QAction* cutAct = m_toolBar->addAction(QIcon(":/icons/cut32.png"), tr("Cu&t"));
    QAction* copyAct = m_toolBar->addAction(QIcon(":/icons/copy32.png"), tr("&Copy"));
    QAction* pasteAct = m_toolBar->addAction(QIcon(":/icons/paste32.png"), tr("&Paste"));
    m_toolBar->addSeparator();
    QAction* aboutAct = m_toolBar->addAction(QIcon(":/icons/about32.png"), tr("&About"));
}

void MainWindow::createDockWindows()
{
    // Create dock widget
    m_treeDock = new QDockWidget(tr("Navigation"), this);
    m_treeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Create tree view
    m_treeView = new QTreeWidget(m_treeDock);
    m_treeView->setHeaderLabel(tr("Items"));
    
    // Add some sample items
    QTreeWidgetItem *item1 = new QTreeWidgetItem(m_treeView);
    item1->setText(0, tr("Item 1"));
    
    QTreeWidgetItem *item2 = new QTreeWidgetItem(item1);
    item2->setText(0, tr("Sub-item 1"));
    
    QTreeWidgetItem *item3 = new QTreeWidgetItem(item1);
    item3->setText(0, tr("Sub-item 2"));
    
    QTreeWidgetItem *item4 = new QTreeWidgetItem(m_treeView);
    item4->setText(0, tr("Item 2"));
    
    m_treeView->expandAll();
    
    m_treeDock->setWidget(m_treeView);
    addDockWidget(Qt::LeftDockWidgetArea, m_treeDock);
}