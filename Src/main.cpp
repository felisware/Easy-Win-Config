#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#include <wx/wx.h>
#include <main_window.h>
#include <firewall_dialog.h>
using namespace std;

class program : public wxApp
{
    public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(program);

//global declaration :)
string winupdate_status;
wxColour dark = wxColour(1, 22, 39);
wxColour red = wxColour(247, 23, 53);
wxColour green = wxColour(29, 215, 85);
wxColour blue = wxColour(0, 167, 225);
//GUI Variable
main_window *main_form;
firewall_dialog *dialog_form;

//overloading function
string winupadate_isrunning();
void ui_status_winupdate();

bool program :: OnInit()
{
    winupdate_status = winupadate_isrunning();

    //add handler to render PNG image
    wxImage::AddHandler(new wxPNGHandler);

    main_form = new main_window("Easy Win Config", wxDefaultPosition, wxSize(300,400));
    //set parent & TOP LEVEL WINDOW
    SetTopWindow(main_form);

    //binding function widgets event on main_form
    main_form->advanced->Bind(wxEVT_CHECKBOX, main_window :: show_hide_advanced, main_form);
    main_form->add_btn->Bind(wxEVT_BUTTON, main_window :: show_blocking_dialog, main_form);
    main_form->action->Bind(wxEVT_BUTTON, main_window :: action_Clicked, main_form);

    //show main form GUI
    main_form->Show();
    //change UI windows update by service status
    ui_status_winupdate();
    

    return 1;
}

//show or hide advanced panel on windows update page
void main_window :: show_hide_advanced(wxCommandEvent &e)
{
    if(e.IsChecked()){
        winupdate_vertical->Show(advanced_panel);
        winupdate_vertical->Layout();
    }else{
        winupdate_vertical->Hide(advanced_panel);
        winupdate_vertical->Layout();
    }
}

//create blocking dialog when press add button on block access page
void main_window :: show_blocking_dialog(wxCommandEvent &e)
{
    dialog_form = new firewall_dialog("Blocking Dialog", wxDefaultPosition, wxSize(320,325));

    //binding function widgets event on dialog_form
    dialog_form->cancel_btn->Bind(wxEVT_BUTTON, firewall_dialog :: close_dialog, dialog_form);

    dialog_form->SetParent(main_form);
    dialog_form->CenterOnParent();
    dialog_form->Raise();
    dialog_form->ShowModal();
    dialog_form->Destroy();
}

void main_window :: action_Clicked(wxCommandEvent &e)
{
    action->Disable();
    SC_HANDLE sch = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (sch == NULL){wxMessageBox("ERROR OpenSCManager failed", "Error Dialog", wxOK | wxICON_ERROR);}
    SC_HANDLE svc = OpenService(sch, _T("wuauserv"), SERVICE_START | SERVICE_STOP | SERVICE_CHANGE_CONFIG);
    if (svc == NULL){wxMessageBox("ERROR OpenService failed", "Error Dialog", wxOK | wxICON_ERROR);}

    //change service startup type
    if (startuptype->GetStringSelection() == "Disable")
    {
        ChangeServiceConfig(svc, SERVICE_NO_CHANGE, static_cast<DWORD>(SERVICE_DISABLED), SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }else if (startuptype->GetStringSelection() == "Manual")
    {
        ChangeServiceConfig(svc, SERVICE_NO_CHANGE, static_cast<DWORD>(SERVICE_DEMAND_START), SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }else if (startuptype->GetStringSelection() == "Automatic")
    {
        ChangeServiceConfig(svc, SERVICE_NO_CHANGE, static_cast<DWORD>(SERVICE_AUTO_START), SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }

    //change service status
    if(statustarget->IsChecked())
    {
        if (winupdate_status == "RUNNING"){
            auto ssp = SERVICE_STATUS_PROCESS{ 0 };
            ControlService(svc, SERVICE_CONTROL_STOP, reinterpret_cast<LPSERVICE_STATUS>(&ssp));
        }
        else if (winupdate_status == "STOPPED"){
            StartService(svc, 0, nullptr);
        }
    }
    
    wxBeginBusyCursor();
    Sleep(2000);
    CloseServiceHandle(svc);
    CloseServiceHandle(sch);
    wxEndBusyCursor();
    action->Enable();
    
    //update UI winupdate
    winupdate_status = winupadate_isrunning();
    ui_status_winupdate();
}

//close dialog form if press cancel button
void firewall_dialog :: close_dialog(wxCommandEvent &e)
{
    dialog_form->Close();
    dialog_form->Destroy();
}

//get windows update status
string winupadate_isrunning()
{
    SC_HANDLE sch = OpenSCManager(NULL, NULL, GENERIC_READ);
    if (sch == NULL){return "ERROR OpenSCManager failed";}
    
    SC_HANDLE svc = OpenService(sch, _T("wuauserv"), SERVICE_QUERY_STATUS);
    if (svc == NULL){return "ERROR OpenService failed";}
    
    SERVICE_STATUS_PROCESS stat;
    DWORD needed = 0;
    BOOL ret = QueryServiceStatusEx(svc, SC_STATUS_PROCESS_INFO, (BYTE*) &stat, sizeof stat, &needed);
    if (ret == 0){return "ERROR QueryServiceStatusEx failed";}

    if (stat.dwCurrentState == SERVICE_RUNNING){
        return "RUNNING";
    }else{
        return "STOPPED";
    }

  CloseServiceHandle(svc);
  CloseServiceHandle(sch);
}

void ui_status_winupdate()
{
    if (winupdate_status == "RUNNING"){
        main_form->statusupdate->SetLabel("windows update service is " + winupdate_status);
        main_form->statusupdate->SetForegroundColour(green);
        main_form->statustarget->SetLabel("Stop win-update service");

        main_form->startuptype->SetSelection(1);
        main_form->startuptype->Enable();

        main_form->action->SetLabel("Turn OFF");
        main_form->action->SetBitmap(wxBITMAP_PNG(turn-off));
        main_form->action->Enable();
    }else if (winupdate_status == "STOPPED"){
        main_form->statusupdate->SetLabel("windows update service is " + winupdate_status);
        main_form->statusupdate->SetForegroundColour(red);
        main_form->statustarget->SetLabel("Start win-update service");

        main_form->startuptype->SetSelection(3);
        main_form->startuptype->Enable();

        main_form->action->SetLabel("Turn ON");
        main_form->action->SetBitmap(wxBITMAP_PNG(turn-on));
        main_form->action->Enable();
    }else{
        main_form->statusupdate->SetLabel(winupdate_status);
        main_form->statusupdate->SetForegroundColour(red);
        main_form->statustarget->SetLabel("I don't know");
    }
    main_form->winupdate_vertical->Layout();
}