#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

	using Self = MainWindow;
	using Super = QMainWindow;
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void closeEvent(QCloseEvent* event) override;
	virtual void moveEvent(QMoveEvent* event) override;
private:
	void OnAboutQtTriggered();
	void OnNewFileTriggered();
	void OnSaveTriggered();
	void OnSaveAsTriggered();
	void OnToggleSnapping(bool checked);

	void SetupUi();
	void MakeConnections();
	void InitializeIcons();

public:
	static QWidget* s_mainUi;

private:
	Ui::MainWindowClass ui;

};
