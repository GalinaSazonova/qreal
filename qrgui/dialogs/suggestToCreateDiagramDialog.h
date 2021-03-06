#pragma once

#include "dialogs/managedClosableDialog.h"
#include "mainwindow/startWidget/suggestToCreateDiagramWidget.h"

namespace qReal {

class MainWindow;

/// @brief Dialog for create a diagram
/// This dialog prompts the user to create one of the available diagrams
class SuggestToCreateDiagramDialog : public ManagedClosableDialog
{
	Q_OBJECT

public:
	explicit SuggestToCreateDiagramDialog(MainWindow *mainWindow, bool isClosable = true);
};

}
