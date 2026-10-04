#include "mainwindow.h"
#include "drawview.h"
#include "waveview.h"
#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QLineEdit>
//#include <QTreeView>
#include <QVBoxLayout>
#include <QCheckBox>
#include "ringbuffer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("QT Study"));
    
    // Allow main window to be resized freely in both directions
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumSize(400, 300);  // Set a reasonable minimum size
    
    // Create central wave view
    m_waveView = new WaveView(this);
    setCentralWidget(m_waveView);
    
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
    if (m_ringBuffer) {
        delete m_ringBuffer;
        m_ringBuffer = nullptr;
    }
}

void MainWindow::cut()
{
    QMessageBox::information(this, tr("Cut"), tr("Cut action triggered"));
}

void MainWindow::copy()
{
    QMessageBox::information(this, tr("Copy"), tr("Copy action triggered"));
}

void MainWindow::paste()
{
    QMessageBox::information(this, tr("Paste"), tr("Paste action triggered"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("QT Study Application\nA simple Qt application for learning purposes."));
}

void MainWindow::onCheckBoxStateChanged(int state)
{
    QMessageBox::information(this, tr("Checked"), tr("Checked action triggered"));
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
    m_toolBar->setMovable(false);

    QAction* newAct = m_toolBar->addAction(style()->standardIcon(QStyle::SP_FileIcon), tr("&New"));
    QAction* openAct = m_toolBar->addAction(style()->standardIcon(QStyle::SP_DialogOpenButton), tr("&Open"));
    m_toolBar->addSeparator();
    QAction* cutAct = m_toolBar->addAction(QIcon(":/icons/cut32.png"), tr("Cu&t"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);
    QAction* copyAct = m_toolBar->addAction(QIcon(":/icons/copy32.png"), tr("&Copy"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);
    QAction* pasteAct = m_toolBar->addAction(QIcon(":/icons/paste32.png"), tr("&Paste"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);
    m_toolBar->addSeparator();

    QAction* aboutAct = m_toolBar->addAction(QIcon(":/icons/about32.png"), tr("&About"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
    m_toolBar->addSeparator();
    
    // Add checkbox to toolbar
    QCheckBox *checkBox = new QCheckBox(tr("Checkbox"), m_toolBar);
    QWidgetAction *checkableAction = new QWidgetAction(m_toolBar);
    checkableAction->setDefaultWidget(checkBox);
    m_toolBar->addAction(checkableAction);
    connect(checkBox, &QCheckBox::checkStateChanged, this, &MainWindow::onCheckBoxStateChanged);

    m_toolBar->addSeparator();
    QAction* resetAct = m_toolBar->addAction(QIcon(":/icons/reset32.png"), tr("&Reset"));
    //connect(resetAct, &QAction::triggered, m_drawView, &DrawView::reset);

    QAction* stepForwardAct = m_toolBar->addAction(QIcon(":/icons/next32.png"), tr("Next"));
    //connect(stepForwardAct, &QAction::triggered, m_drawView, &DrawView::stepForward);
    connect(stepForwardAct, &QAction::triggered, this, &MainWindow::startCapture);
}

void MainWindow::createDockWindows()
{
    // Create dock widget
    m_treeDock = new QDockWidget(tr("Navigation"), this);
    m_treeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // Create a widget to hold both the line edit and tree view
    QWidget *contentWidget = new QWidget(m_treeDock);
    
    // Create layout for the content widget
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    layout->setContentsMargins(5, 5, 5, 5); // Small margins
    layout->setSpacing(5); // Small spacing between widgets
    
    // Create line edit (single line text input)
    QLineEdit *lineEdit = new QLineEdit(contentWidget);
    lineEdit->setPlaceholderText(tr("Enter notes here..."));
    
    // Create tree view
    m_treeView = new QTreeWidget(contentWidget);
    m_treeView->setHeaderLabel(tr("Items"));
    
    // Add widgets to layout (line edit above tree view)
    layout->addWidget(lineEdit);
    layout->addWidget(m_treeView);
    
    // Add some sample items to tree view
    QTreeWidgetItem *item1 = new QTreeWidgetItem(m_treeView);
    item1->setText(0, tr("Item 1"));
    
    QTreeWidgetItem *item2 = new QTreeWidgetItem(item1);
    item2->setText(0, tr("Sub-item 1"));
    
    QTreeWidgetItem *item3 = new QTreeWidgetItem(item1);
    item3->setText(0, tr("Sub-item 2"));
    
    QTreeWidgetItem *item4 = new QTreeWidgetItem(m_treeView);
    item4->setText(0, tr("Item 2"));
    
    m_treeView->expandAll();
    
    // Set the content widget in the dock
    m_treeDock->setWidget(contentWidget);
    addDockWidget(Qt::LeftDockWidgetArea, m_treeDock);
}

static double create_value() {
    return rand() % 100; // Random value between 0 and 99
}

void MainWindow::startCapture()
{
    if (!m_ringBuffer) {
        m_ringBuffer = new RingBuffer(1000); 
    }
    m_waveView->setModel(m_ringBuffer);

    m_timer.start(5); // Update every 10 ms
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        double newValue = create_value();
        m_ringBuffer->enqueue(newValue);
    });
    m_waveView->startAnimation();
}