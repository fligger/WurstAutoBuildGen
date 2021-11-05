#include "pch.h"
#include "cMain.h"

#include <wx/wx.h>
#include <wx/tglbtn.h>
#include <wx/vscroll.h>
#include <wx/splitter.h>

#include "icon/icon.xpm"

enum Eventid {
	ID_LayerUp = wxID_LAST + 1,
	ID_LayerDown,
	ID_HeightPlus,
	ID_HeightMinus,
	ID_WidthPlus,
	ID_WidthMinus,
	ID_ButtonSlider,
	ID_PasteLayer,
	ID_SetLayer
};


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_NEW, cMain::OnNew)
EVT_MENU(wxID_OPEN, cMain::OnOpen)
EVT_MENU(wxID_SAVE, cMain::OnSave)
EVT_MENU(wxID_SAVEAS, cMain::OnSaveAs)
EVT_MENU(wxID_HELP, cMain::OnHelp)
EVT_MENU(wxID_ABOUT, cMain::OnAbout)
EVT_BUTTON(ID_LayerUp, cMain::OnLayerUp)
EVT_BUTTON(ID_LayerDown, cMain::OnLayerDown)
EVT_BUTTON(ID_HeightPlus, cMain::OnHeightPlus)
EVT_BUTTON(ID_HeightMinus, cMain::OnHeightMinus)
EVT_BUTTON(ID_WidthPlus, cMain::OnWidthPlus)
EVT_BUTTON(ID_WidthMinus, cMain::OnWidthMinus)
EVT_BUTTON(ID_PasteLayer, cMain::OnPasteLayer)
EVT_BUTTON(ID_SetLayer, cMain::OnSetLayer)
wxEND_EVENT_TABLE();

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Wurst Autobuild Generator", wxDefaultPosition, wxSize(1200, 800)) {

	wxIcon icon(icon_xpm);
	this->SetIcon(icon);

	wxMenu* menuFile = new wxMenu();
	menuFile->Append(wxID_NEW);
	menuFile->Append(wxID_OPEN);
	menuFile->Append(wxID_SAVE);
	menuFile->Append(wxID_SAVEAS);

	wxMenu* menuHelp = new wxMenu();
	menuHelp->Append(wxID_HELP);
	menuHelp->Append(wxID_ABOUT);

	menuBar = new wxMenuBar();
	menuBar->Append(menuFile, "File");
	menuBar->Append(menuHelp, "Help");
	this->SetMenuBar(menuBar);

	splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSB_FLAT);
	splitter->SetBackgroundColour(wxColor(255, 255, 255));
	mainScrollWindow = new wxScrolledWindow(splitter, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxHSCROLL | wxVSCROLL);
	mainScrollWindow->SetScrollRate(10, 10);
	//mainScrollWindow->SetBackgroundColour("#00ff00");

	mainPanel = new wxPanel(mainScrollWindow, wxID_ANY, wxPoint(0,0), wxSize(200, 200));
	//mainPanel->SetBackgroundColour("#ff0000");

	mainPanelSizer = new wxBoxSizer(wxVERTICAL);
	mainPanelSizer->Add(mainPanel);
	mainScrollWindow->SetSizerAndFit(mainPanelSizer);

	wxFont hugeFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont kindaHugeFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	controlPanel = new wxPanel(splitter, wxID_ANY, wxDefaultPosition, wxSize(140, 100));
	upButton = new wxButton(controlPanel, ID_LayerUp, "+", wxDefaultPosition, wxSize(80, 80));
	upButton->SetFont(hugeFont);
	layerText = new wxStaticText(controlPanel, wxID_ANY, "Layer: 0", wxDefaultPosition, wxDefaultSize);
	layerText->SetFont(kindaHugeFont);
	downButton = new wxButton(controlPanel, ID_LayerDown, "-", wxDefaultPosition, wxSize(80, 80));
	downButton->SetFont(hugeFont);
	blocksText = new wxStaticText(controlPanel, wxID_ANY, "Blocks: 0", wxDefaultPosition, wxDefaultSize);
	blocksText->SetFont(kindaHugeFont);

	sizeSliderText = new wxStaticText(controlPanel, wxID_ANY, "Set button size: ", wxDefaultPosition, wxDefaultSize);
	buttonSizeSlider = new wxSlider(controlPanel, ID_ButtonSlider, buttonSize.x, 40, 200);
	buttonSizeSlider->Bind(wxEVT_SCROLL_CHANGED, &cMain::OnButtonSlider, this); //Windows Only 

	widthPanel = new wxPanel(controlPanel);
	modifyWidthText = new wxStaticText(controlPanel, wxID_ANY, "Modify width: ");
	widthMinusButton = new wxButton(widthPanel, ID_HeightMinus, "-", wxDefaultPosition, wxSize(80, 40));
	widthPlusButton = new wxButton(widthPanel, ID_HeightPlus, "+", wxDefaultPosition, wxSize(80, 40));

	widthSizer = new wxBoxSizer(wxHORIZONTAL);
	widthSizer->Add(widthMinusButton, 1);
	widthSizer->Add(widthPlusButton, 1);
	widthPanel->SetSizerAndFit(widthSizer);

	heightPanel = new wxPanel(controlPanel);
	modifyHeightText = new wxStaticText(controlPanel, wxID_ANY, "Modify height: ");
	HeightMinusButton = new wxButton(heightPanel, ID_WidthMinus, "-", wxDefaultPosition, wxSize(80, 40));
	HeightPlusButton = new wxButton(heightPanel, ID_WidthPlus, "+", wxDefaultPosition, wxSize(80, 40));

	heightSizer = new wxBoxSizer(wxHORIZONTAL);
	heightSizer->Add(HeightMinusButton, 1);
	heightSizer->Add(HeightPlusButton, 1);
	heightPanel->SetSizerAndFit(heightSizer);

	copyPastePanel = new wxPanel(controlPanel);
	copyPasteText = new wxStaticText(controlPanel, wxID_ANY, "Duplicate layers: ");
	copyButton = new wxButton(copyPastePanel, ID_SetLayer, "Set", wxDefaultPosition, wxSize(80, 40));
	pasteButton = new wxButton(copyPastePanel, ID_PasteLayer, "Paste", wxDefaultPosition, wxSize(80, 40));
	currentCopyPasteText = new wxStaticText(controlPanel, wxID_ANY, "Position to duplicate: 0");

	copyPasteSizer = new wxBoxSizer(wxHORIZONTAL);
	copyPasteSizer->Add(copyButton, 1);
	copyPasteSizer->Add(pasteButton, 1);
	copyPastePanel->SetSizerAndFit(copyPasteSizer);

	controlPanelSizer = new wxBoxSizer(wxVERTICAL);
	controlPanelSizer->Add(upButton, 0, wxEXPAND | wxALL, 10);
	controlPanelSizer->Add(layerText, 0, wxEXPAND | wxLEFT, 10);
	controlPanelSizer->Add(downButton, 0, wxEXPAND | wxALL, 10);
	controlPanelSizer->AddSpacer(20);
	controlPanelSizer->Add(blocksText, 0, wxEXPAND | wxLEFT, 10);
	controlPanelSizer->AddStretchSpacer(2);

	controlPanelSizer->Add(copyPasteText, 0, wxEXPAND | wxLEFT, 10);
	controlPanelSizer->Add(copyPastePanel, 0, wxALL | wxEXPAND, 10);
	controlPanelSizer->Add(currentCopyPasteText, 0, wxEXPAND | wxLEFT, 10);
	controlPanelSizer->AddStretchSpacer(1);

	controlPanelSizer->Add(sizeSliderText, 0, wxEXPAND | wxLEFT | wxBOTTOM, 10);
	controlPanelSizer->Add(buttonSizeSlider, 0, wxEXPAND | wxLEFT | wxBOTTOM, 10);
	controlPanelSizer->Add(modifyWidthText, 0, wxEXPAND | wxLEFT, 10);
	controlPanelSizer->Add(widthPanel, 0, wxALL | wxEXPAND, 10);
	controlPanelSizer->Add(modifyHeightText, 0, wxEXPAND | wxLEFT, 10);
	controlPanelSizer->Add(heightPanel, 0, wxALL | wxEXPAND, 10);
	controlPanel->SetSizerAndFit(controlPanelSizer);

	splitter->SplitVertically(mainScrollWindow, controlPanel);
	splitter->SetSashGravity(1.f);
	splitter->SetSashPosition(800);
	splitter->SetMinimumPaneSize(100);

	createButtonGrid();
}

void cMain::createButtonGrid() {

	mainPanel->DestroyChildren(); // clear panel
	allocatedGridPos.clear(); // monitored and cleared here to avoid memory leaks

	posTo[0] = size[0];
	posFrom[0] = size[0] / -2;
	posTo[0] += posFrom[0];


	posTo[1] = size[1];
	posFrom[1] = size[1] / -2;
	posTo[1] += posFrom[1];

	wxPoint point = { spacer, spacer };

	for (int iz = posFrom[1]; iz <= posTo[1]; iz++) {
		for (int ix = posFrom[0]; ix <= posTo[0]; ix++) {
			std::stringstream text;
			text << "( " << ix << ", " << iz << " )";

			wxToggleButton* button = new wxToggleButton(mainPanel, wxID_ANY, text.str(), point, buttonSize);

			GridPos* pos = new GridPos({ ix, iz, button });

			allocatedGridPos.push_back(std::shared_ptr<GridPos>(pos)); //keepig track of memory

			//button->Bind(wxEVT_TOGGLEBUTTON, [this, pos](wxCommandEvent& e) { // toggle module if clicked on module button
			//	setBlockState(pos, e.IsChecked());
			//	});
			button->Bind(wxEVT_ENTER_WINDOW, [this, pos, button](wxMouseEvent& e) { // dragging
				OnButtonHover(button, pos);
				});
			button->Bind(wxEVT_LEFT_DOWN, [this, pos, button](wxMouseEvent& e) { //Not the best method but works
				OnButtonHover(button, pos);
				});

			point.x += buttonSize.x + spacer;
		}
		point.x = spacer;
		point.y += buttonSize.y + spacer;
	}

	wxSize size;
	size.x = (buttonSize.x + spacer) * (abs(posFrom[0]) + abs(posTo[0])); //abs = absolute value (removes minus)

	size.y = (buttonSize.y + spacer) * (abs(posFrom[1]) + abs(posTo[1]));
	mainPanel->SetMinSize(size);
	mainPanel->SetSize(size);
	mainScrollWindow->SetVirtualSize(size); // to set the scroller to size

	updateButtonGrid();
}
void cMain::OnButtonHover(wxToggleButton* button, GridPos* pos) {
	if (!!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) { //wxMouseState didnt work
		bool state = !button->GetValue();
		setBlockState(pos, state);
		button->SetValue(state);
	}
}

void cMain::updateButtonGrid() {
	layerText->SetLabelText("Layer: " + std::to_string(layer));

	//Set button state
	for (std::shared_ptr<GridPos> gridpos : allocatedGridPos) {
		for (std::shared_ptr<BlockPos> Blockpos : selectedBlocks) {
			if (Blockpos.get()->x == gridpos.get()->x && Blockpos.get()->y == layer && Blockpos.get()->z == gridpos.get()->z) {
				gridpos.get()->button->SetValue(true);
				break;
			}
			else {
				gridpos.get()->button->SetValue(false);
			}
		}
	}
}

void cMain::resetLabels() {
	blocksText->SetLabelText("Blocks: " + std::to_string(selectedBlocks.size()));
	layer = 0;
	layerText->SetLabelText("Layer: " + std::to_string(layer));
	layerToDuplicate = 0;
	currentCopyPasteText->SetLabelText("Position to duplicate: " + std::to_string(layerToDuplicate));
}

void cMain::setBlockState(GridPos* pos, bool state) {
	
	if (state) {
		selectedBlocks.push_back(std::shared_ptr<BlockPos>(new BlockPos({ pos->x, layer, pos->z })));
	}
	else {
		for (int i = 0; i < selectedBlocks.size(); i++) {
			if (selectedBlocks.at(i).get()->x == pos->x && selectedBlocks.at(i).get()->y == layer && selectedBlocks.at(i).get()->z == pos->z) {
				selectedBlocks.erase(selectedBlocks.begin()+i);
				break;
			}
		}
	}
	blocksText->SetLabelText("Blocks: " + std::to_string(selectedBlocks.size()));
}


void cMain::OnSetLayer(wxCommandEvent& WXUNUSED(event)) {
	layerToDuplicate = layer;

	currentCopyPasteText->SetLabelText("Position to duplicate: " + std::to_string(layerToDuplicate));
}
void cMain::OnPasteLayer(wxCommandEvent& WXUNUSED(event)) {

	if (layer == layerToDuplicate) {
		wxMessageBox("Move to another layer first", "Warning", wxICON_WARNING);
	}

	for (int i = 0; i < selectedBlocks.size(); i++) { //clear current layer
		if (selectedBlocks.at(i).get()->y == layer) {
			selectedBlocks.erase(selectedBlocks.begin() + i);
			break;
		}
	}

	for (std::shared_ptr<GridPos> gridpos : allocatedGridPos) {
		for (int i = 0; i < selectedBlocks.size(); i++) { //clear current layer
			if (selectedBlocks.at(i)->x == gridpos->x && selectedBlocks.at(i)->y == layerToDuplicate && selectedBlocks.at(i)->z == gridpos->z) {
				BlockPos* block = new BlockPos({ selectedBlocks.at(i)->x, layer, selectedBlocks.at(i)->z });
				selectedBlocks.push_back(std::shared_ptr<BlockPos>(block));
			}
		}
	}
	blocksText->SetLabelText("Blocks: " + std::to_string(selectedBlocks.size()));
	updateButtonGrid();
}

void cMain::OnLayerUp(wxCommandEvent& WXUNUSED(event)) {
	layer++;
	updateButtonGrid();
}
void cMain::OnLayerDown(wxCommandEvent& WXUNUSED(event)) {
	layer--;
	updateButtonGrid();
}

void cMain::OnHeightPlus(wxCommandEvent& WXUNUSED(event)) {
	size[0]++;
	createButtonGrid();

}
void cMain::OnHeightMinus(wxCommandEvent& WXUNUSED(event)) {
	size[0]--;
	createButtonGrid();
}

void cMain::OnWidthPlus(wxCommandEvent& WXUNUSED(event)) {
	size[1]++;
	createButtonGrid();
}
void cMain::OnWidthMinus(wxCommandEvent& WXUNUSED(event)) {
	size[1]--;
	createButtonGrid();
}

void cMain::OnNew(wxCommandEvent& WXUNUSED(event)) {

	dimensionDialog = new wxDialog(this, wxID_ANY, "Set Grid Size", wxDefaultPosition, wxSize(305, 150), wxDEFAULT_DIALOG_STYLE);
	dialogBasePanel = new wxPanel(dimensionDialog, wxID_ANY, wxDefaultPosition, wxSize(40, 40));

	fromHeading = new wxStaticText(dialogBasePanel, wxID_ANY, "Create a grid with size X and Z: ", wxPoint(10, 10));

	textCtrlSize_X = new wxTextCtrl(dialogBasePanel, wxID_ANY, std::to_string(size[0]), wxPoint(10, 35), wxSize(130, 20), wxTE_CENTRE, wxTextValidator(wxFILTER_NUMERIC));

	textCtrlSize_Z = new wxTextCtrl(dialogBasePanel, wxID_ANY, std::to_string(size[1]), wxPoint(150, 35), wxSize(130, 20), wxTE_CENTRE, wxTextValidator(wxFILTER_NUMERIC));

	dialogOkBtn = new wxButton(dialogBasePanel, wxID_OK, "Ok", wxPoint(125, 75), wxSize(75, 25));
	dialogCancelBtn = new wxButton(dialogBasePanel, wxID_CANCEL, "Cancel", wxPoint(205, 75), wxSize(75, 25));


	if (dimensionDialog->ShowModal() == wxID_OK) {
			size[0] = atoi(textCtrlSize_X->GetValue());
			size[1] = atoi(textCtrlSize_Z->GetValue());
			clearBlocks = new wxMessageDialog(this, "Do you want to unselect all selected blocks", "Grid Size", wxYES | wxNO);
			if (clearBlocks->ShowModal() == wxID_YES) {
				selectedBlocks.clear();
			}
			clearBlocks->Destroy(); // anti memory leaks
			resetLabels();
			createButtonGrid();
	}
}

void cMain::OnOpen(wxCommandEvent& WXUNUSED(event)) {


	wxFileDialog openFileDialog(this, _("Open"), "", filename, "JSON files (*.json)|*.json; All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...
	
	filename = openFileDialog.GetFilename();
	filepath = openFileDialog.GetPath();
	json j;

	std::ifstream loadedConfig(filepath);

	if (loadedConfig.is_open()) {
		try {
			loadedConfig >> j;
		}
		catch (...) {
			wxLogError("LOAD: Config file is messed up and cannot be loaded");
		}
	}

	selectedBlocks.clear(); // clear array
	for (int i = 0; i < j["blocks"].size(); i++) {
	BlockPos* block = new BlockPos({ j["blocks"].at(i)[0], j["blocks"].at(i)[1], j["blocks"].at(i)[2] });
	selectedBlocks.push_back(std::shared_ptr<BlockPos>(block));
	}

	resetLabels();
	updateButtonGrid();
}

void cMain::OnSave(wxCommandEvent& event) {

	if (filepath == "") {
		OnSaveAs(event);
		return;
	}

	std::ofstream file(filepath);

	json j;

	for (std::shared_ptr<BlockPos> Blockpos : selectedBlocks) {
		j["blocks"].push_back({ Blockpos->x, Blockpos->y, Blockpos->z });
	}
	if (file.is_open()) {
		try {
			file << j;
		}
		catch (...) {
			wxLogError("LOAD: Config file is messed up and cannot be loaded");
		}
	}
}

void cMain::OnSaveAs(wxCommandEvent& WXUNUSED(event)) {
	wxFileDialog saveFileDialog(this, _("Save"), "", filename, "JSON files (*.json)|*.json; All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	filename = saveFileDialog.GetFilename();
	filepath = saveFileDialog.GetPath();
	std::ofstream file(filepath);

	json j;

	for (std::shared_ptr<BlockPos> Blockpos : selectedBlocks) {
		j["blocks"].push_back({ Blockpos->x, Blockpos->y, Blockpos->z });
	}
	if (file.is_open()) {
		try {
			file << j;
		}
		catch (...) {
			wxLogError("LOAD: Config file is messed up and cannot be loaded");
		}
	}
}

void cMain::OnButtonSlider(wxCommandEvent& WXUNUSED(event)) {
	int temp = buttonSizeSlider->GetValue();
	buttonSize = { temp , temp };
	createButtonGrid();
}

void cMain::OnHelp(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox("Controls\n\nLeft click: toggle block state\nHold down left click to toggle blocks by hovering\n\n\"+\" and \"-\": go up or down a layer");
}

void cMain::OnAbout(wxCommandEvent& WXUNUSED(event)) {
	wxAboutDialogInfo info;

	info.SetName(_("Wurst Autobuild Json Generator"));
	info.SetVersion(_("1.0"));
	info.SetDescription(_("A simple GUI application to generate Wurst compatible autobuild json files."));
	info.SetLicence("GNU General Public License v3.0");
	info.SetWebSite("https://github.com/fligger"); //don't skid pls
	wxAboutBox(info);
}


