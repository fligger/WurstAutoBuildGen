#pragma once

#include "cMain.h"
class cApp : public wxApp
{
public:
	bool OnInit();

private:
	cMain* m_frame1 = nullptr;
};

