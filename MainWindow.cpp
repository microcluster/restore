#include "MainWindow.hpp"

#include "./ui_MainWindow.h"

#include <QDir>
#include <QFileDialog>
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
    m_button     = new QPushButton("&Select Directory");
    connect(m_button, &QPushButton::clicked, this, &MainWindow::selectDir);
    l->addWidget(m_button);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectDir()
{
    auto dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/home",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QDir d(dir);
    if (!d.isReadable()) {
        qWarning() << "directory " << dir << "is not readable";
        return;
    }

    scan(std::move(d));
}

void MainWindow::scan(QDir &&dir)
{
    auto files = dir.entryList();
    for (auto f : files) {
        qDebug() << f;
    }
}
