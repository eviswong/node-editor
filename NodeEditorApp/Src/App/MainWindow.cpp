#include "stdafx.h"
#include "MainWindow.h"
#include "LoggerWindow.h"
#include "ListWidget.h"
#include "Base/Config.h"
#include "Editor/DmGraphicsScene.h"
#include "Editor/DmGraphicsView.h"
#include "App/MainWindow.h"

QWidget* MainWindow::s_mainUi = nullptr;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Self::SetupUi();

	Self::MakeConnections();

	const QSize windowSize = Config::GetInstance().windowSize;
	const QPoint windowPos = Config::GetInstance().windowPos;

	Super::setGeometry(windowPos.x(), windowPos.y(), windowSize.width(), windowSize.height());

	s_mainUi = this;
}

void MainWindow::SetupUi()
{
	/* Windows */
	ui.loggerWidget->setWidget(new LoggerWindow(this));
	ui.libraryWidget->setWidget(new ListWidget(this));

	/* Docking window visiability */
	ui.menuWindow->addAction(ui.propertyWidget->toggleViewAction());
	ui.menuWindow->addAction(ui.libraryWidget->toggleViewAction());
	ui.menuWindow->addAction(ui.loggerWidget->toggleViewAction());

	/* Graphics scene and view */
	DmGraphicsScene* graphicsScene = new DmGraphicsScene(this);
	DmGraphicsView* graphicsView = new DmGraphicsView(graphicsScene, this);
	Super::setCentralWidget(graphicsView);

	/* State initialization */
	bool toggleSnapping = Config::GetInstance().itemSnapping;
	if (toggleSnapping)
	{
		ui.actionToggleSnapping->setChecked(true);
	}
}


void MainWindow::MakeConnections()
{
	connect(ui.actionAboutQt, &QAction::triggered, this, &Self::OnAboutQtTriggered);
	connect(ui.actionNew, &QAction::triggered, this, &Self::OnNewFileTriggered);
	connect(ui.actionSave, &QAction::triggered, this, &Self::OnSaveTriggered);
	connect(ui.actionSaveAs, &QAction::triggered, this, &Self::OnSaveAsTriggered);
	connect(ui.actionToggleSnapping, &QAction::triggered, this, &Self::OnToggleSnapping);
}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	const QSize windowSize = event->size();

	Config::GetInstance().windowSize = windowSize;
}

void MainWindow::moveEvent(QMoveEvent* event)
{
	const QPoint pos = event->pos();

	Config::GetInstance().windowPos = pos;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	auto result = QMessageBox::information(nullptr, qApp->applicationName(), "Are you sure to quit?", QMessageBox::Ok | QMessageBox::No);
	if (result == QMessageBox::No)
	{
		event->ignore();
		return;
	}

	Config::GetInstance().SaveConfigurations();
}

void MainWindow::OnAboutQtTriggered()
{
	QApplication::aboutQt();
}

void MainWindow::OnNewFileTriggered()
{
	qDebug() << "Into new" ;
}

void MainWindow::OnSaveTriggered()
{
	qDebug() << "Into Save";
}

void MainWindow::OnSaveAsTriggered()
{
	qDebug() << "Into Save As";
}

void MainWindow::OnToggleSnapping(bool checked)
{
	Config::GetInstance().itemSnapping = checked;
}