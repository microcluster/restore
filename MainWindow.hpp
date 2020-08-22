#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void scanFolder();

  private:
    Ui::MainWindow *ui;

    QPushButton *m_button;
};
