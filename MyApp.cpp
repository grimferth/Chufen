/*************************************************************************************************************************************
 * Name:        MyApp.cpp
 * Purpose:     entry point into the project
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * -----------------------------------------------------------------------------------------------------------------------------------
 * Copyright (C) 2014, Stephen Wunschel
 *************************************************************************************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MyApp.h"
#include "MainFrame.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame* frame = new MainFrame(0L, _("Chufen Project"));
    frame->SetIcon(wxICON(aaaa));
    frame->Show();
    return true;
}
