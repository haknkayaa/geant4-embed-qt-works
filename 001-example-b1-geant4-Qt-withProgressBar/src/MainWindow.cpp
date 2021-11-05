
#include "MainWindow.h"
#include "./ui_mainwindow.h"


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


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

//    ui->label   = lAbs;
//    ui->label_2 = eGab;
//    ui->label_3 = eAbs;
//    ui->label_4 = lGap;
    eAbs = ui->label_3;
    eGab = ui->label_2;
    lAbs = ui->label;
    lGap = ui->label_4;
    myBar = ui->progressBar;

    connect(ui->runButton, &QPushButton::clicked, [this]{
        this->simulationRun();
    });

    connect(ui->chooseFile, &QPushButton::clicked, [this]{
        fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open File"), qApp->applicationDirPath(), tr("All Files (*.*)"));
        macro = fileName.toUtf8().constData();
    });


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::simulationRun() {


    G4String session;
#ifdef G4MULTITHREADED
    G4int nThreads = 0;
#endif


    // Detect interactive mode (if no macro provided) and define UI session
    //
//    G4UIExecutive* ui = nullptr;
//    if ( ! macro.size() ) {
//        ui = new G4UIExecutive(argc, argv, session);
//    }

    // Optionally: choose a different Random engine...
    //
    // G4Random::setTheEngine(new CLHEP::MTwistEngine);

    // Construct the default run manager
    //
#ifdef G4MULTITHREADED
    auto runManager = new G4MTRunManager;
    if (nThreads > 0) {
        runManager->SetNumberOfThreads(nThreads);
    }
#else
    auto runManager = new G4RunManager;
#endif

    // Set mandatory initialization classes
    //
    auto detConstruction = new B4DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);

    auto physicsList = new FTFP_BERT;
    runManager->SetUserInitialization(physicsList);

    auto actionInitialization = new B4aActionInitialization(detConstruction);
    runManager->SetUserInitialization(actionInitialization);

    // Initialize visualization
    //
    auto visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //

    // batch mode
    G4String command = "/control/execute ";
//    macro = "exampleB4.in";
    UImanager->ApplyCommand(command + macro);



    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !

    delete visManager;
    delete runManager;
}





