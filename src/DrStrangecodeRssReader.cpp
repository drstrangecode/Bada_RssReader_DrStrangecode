/**
 * Name        : DrStrangecodeRssReader
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "DrStrangecodeRssReader.h"
#include "MainForm.h"
#include "ItemForm.h"
#include "Settings.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

DrStrangecodeRssReader::DrStrangecodeRssReader()
{
}

DrStrangecodeRssReader::~DrStrangecodeRssReader()
{
}

Application*
DrStrangecodeRssReader::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new DrStrangecodeRssReader();
}

bool
DrStrangecodeRssReader::OnAppInitializing(AppRegistry& appRegistry)
{

	// Create a form
	MainForm *pMainForm = new MainForm();
	pMainForm->Initialize();
	pMainForm->SetName(kMainFormNameString);

	ItemForm * pItemForm = new ItemForm();
	pItemForm->Initialize();
	pItemForm->SetName(kItemFormNameString);

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();

	pFrame->AddControl(*pMainForm);
	pFrame->AddControl(*pItemForm);

	// Set the current form
	pFrame->SetCurrentForm(*pMainForm);

	// Draw and Show the form
	pMainForm->Draw();
	pMainForm->Show();

	return true;
}

bool
DrStrangecodeRssReader::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
DrStrangecodeRssReader::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
DrStrangecodeRssReader::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
DrStrangecodeRssReader::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
DrStrangecodeRssReader::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
DrStrangecodeRssReader::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
DrStrangecodeRssReader::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
