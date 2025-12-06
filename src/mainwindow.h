#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QTreeWidget>

class DrawView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cut();
    void copy();
    void paste();
    void about();
    void onCheckBoxStateChanged(int state);

private:
    void createMenus();
    void createToolBars();
    void createDockWindows();
    
    DrawView *m_drawView;
    QMenuBar *m_menuBar;
    QToolBar *m_toolBar;
    QDockWidget *m_treeDock;
    QTreeWidget *m_treeView;
};
#endif // MAINWINDOW_H