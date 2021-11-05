#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// User Libraries
#include "simulation/B4DetectorConstruction.hh"
#include "simulation/B4aActionInitialization.hh"

#ifdef G4MULTITHREADED

#include "G4MTRunManager.hh"

#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// OpenCASCADE Libraries
#include <V3d_View.hxx>

// Qt Libraries
#include <QMainWindow>
#include <QtWidgets>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void simulationRun();



public:
    inline static QLabel* eAbs;
    inline static QLabel* eGab;
    inline static QLabel* lAbs;
    inline static QLabel* lGap;
    inline static QProgressBar* myBar;


private:
    Ui::MainWindow *ui;

    QString fileName;
    G4String macro;
};

#endif // MAINWINDOW_H
