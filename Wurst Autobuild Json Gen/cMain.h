#pragma once

struct GridPos { int x, z; wxToggleButton* button; };
struct BlockPos { int x, y, z; };

class cMain : public wxFrame
{
public:
	cMain();

private:
	wxMenuBar* menuBar = nullptr;

	wxScrolledWindow* mainScrollWindow = nullptr;
	wxPanel* mainPanel = nullptr;

	wxSplitterWindow* splitter = nullptr;

	wxPanel* controlPanel = nullptr;
	wxButton* upButton = nullptr;
	wxStaticText* layerText = nullptr;
	wxButton* downButton = nullptr;

	wxStaticText* blocksText = nullptr;

	wxStaticText* sizeSliderText = nullptr;
	wxSlider* buttonSizeSlider = nullptr;

	wxPanel* widthPanel = nullptr;
	wxStaticText* modifyWidthText = nullptr;
	wxButton* widthPlusButton = nullptr;
	wxButton* widthMinusButton = nullptr;

	wxPanel* heightPanel = nullptr;
	wxStaticText* modifyHeightText = nullptr;
	wxButton* HeightPlusButton = nullptr;
	wxButton* HeightMinusButton = nullptr;

	wxPanel* copyPastePanel = nullptr;
	wxStaticText* copyPasteText = nullptr;
	wxButton* copyButton = nullptr;
	wxButton* pasteButton = nullptr;
	wxStaticText* currentCopyPasteText = nullptr;

	wxBoxSizer* mainPanelSizer = nullptr;
	wxBoxSizer* controlPanelSizer = nullptr;

	wxBoxSizer* widthSizer = nullptr;
	wxBoxSizer* heightSizer = nullptr;
	wxBoxSizer* copyPasteSizer = nullptr;


	wxDialog* dimensionDialog = nullptr;
	wxPanel* dialogBasePanel = nullptr;

	int size[2] = { 7, 7 };
	int blocks = 0;

	wxStaticText* fromHeading = nullptr;
	wxButton* dialogOkBtn = nullptr;
	wxButton* dialogCancelBtn = nullptr;
	wxMessageDialog* clearBlocks = nullptr;

	int posFrom[2] = { -2, -3 };
	wxTextCtrl* textCtrlSize_X = nullptr;
	int posTo[2] = { 3, 3 };
	wxTextCtrl* textCtrlSize_Z = nullptr;

	void OnNew(wxCommandEvent& WXUNUSED(event));
	void OnOpen(wxCommandEvent& WXUNUSED(event));
	void OnSave(wxCommandEvent& WXUNUSED(event));
	void OnSaveAs(wxCommandEvent& WXUNUSED(event));
	void OnHelp(wxCommandEvent& WXUNUSED(event));
	void OnAbout(wxCommandEvent& WXUNUSED(event));

	void OnLayerUp(wxCommandEvent& WXUNUSED(event));
	void OnLayerDown(wxCommandEvent& WXUNUSED(event));
	void OnButtonSlider(wxCommandEvent& WXUNUSED(event));

	void OnHeightPlus(wxCommandEvent& WXUNUSED(event));
	void OnHeightMinus(wxCommandEvent& WXUNUSED(event));
	void OnWidthPlus(wxCommandEvent& WXUNUSED(event));
	void OnWidthMinus(wxCommandEvent& WXUNUSED(event));
	void OnSetLayer(wxCommandEvent& WXUNUSED(event));
	void OnPasteLayer(wxCommandEvent& WXUNUSED(event));

	void OnButtonHover(wxToggleButton* button, GridPos* pos);

	wxSize buttonSize = {100, 100};
	int spacer = 5;

	int layer = 0;
	int layerToDuplicate = 0;

	std::string filename = "";
	std::string filepath = "";

	std::vector< std::shared_ptr<BlockPos> > selectedBlocks;
	std::vector< std::shared_ptr<GridPos> > allocatedGridPos;

	void updateButtonGrid();
	void createButtonGrid();
	void resetLabels();
	void setBlockState(GridPos* block, bool state);

public:
	wxDECLARE_EVENT_TABLE();
};

