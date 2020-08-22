#include "MainWindow.hpp"

#include "./ui_MainWindow.h"

#include <QDir>
#include <QGridLayout>
#include <QPushButton>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(QApplication::applicationName() + " " +
                         QApplication::applicationVersion());

    centralWidget()->setLayout(new QGridLayout);
    const auto l = qobject_cast<QGridLayout *>(centralWidget()->layout());
    m_button     = new QPushButton("&Scan Directory");
    connect(m_button, &QPushButton::clicked, this, &MainWindow::scanFolder);
    l->addWidget(m_button);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scanFolder()
{
    QDir directory("/home/");
    auto files = directory.entryList();
    for (auto f : files) {
        qDebug() << f;
    }
}
