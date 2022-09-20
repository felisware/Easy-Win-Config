#include <iostream>
#include <sstream>
#include <winsock2.h>
#include <iphlpapi.h>
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
vector<string> GUID_adapter;
vector<string> ID_FwRule;
//Color Variable
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
void get_blocked_list();
void get_allinterface();

bool program :: OnInit()
{
    winupdate_status = winupadate_isrunning();

    //add handler to render PNG image
    wxImage::AddHandler(new wxPNGHandler);

    main_form = new main_window("Easy Win Config", wxDefaultPosition, wxSize(430,400));
    //set parent & TOP LEVEL WINDOW
    SetTopWindow(main_form);

    //binding function widgets event on main_form
    //winupdate page
    main_form->pagesystem->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, main_window :: change_page, main_form);
    main_form->advanced->Bind(wxEVT_CHECKBOX, main_window :: show_hide_advanced, main_form);
    main_form->action->Bind(wxEVT_BUTTON, main_window :: action_Clicked, main_form);
    //block page
    main_form->add_btn->Bind(wxEVT_BUTTON, main_window :: show_blocking_dialog, main_form);
    main_form->remove_btn->Bind(wxEVT_BUTTON, main_window :: delete_fwrule, main_form);
    main_form->refresh_btn->Bind(wxEVT_BUTTON, main_window :: refresh_list, main_form);
    //custom dns page
    main_form->interfaces->Bind(wxEVT_CHOICE, main_window :: get_data_selected, main_form);
    main_form->defaultdns->Bind(wxEVT_RADIOBUTTON, main_window :: is_auto, main_form);
    main_form->customdnsserver->Bind(wxEVT_RADIOBUTTON, main_window :: is_custom, main_form);
    main_form->apply->Bind(wxEVT_BUTTON, main_window :: apply_dns_conf, main_form);
    main_form->reset->Bind(wxEVT_BUTTON, main_window :: reset_dns_conf, main_form);

    //show main form GUI
    main_form->Show();
    //change UI windows update by service status
    ui_status_winupdate();
    
    return 1;
}

//update UI page every change page
void main_window :: change_page(wxBookCtrlEvent &e)
{
    if(e.GetSelection() == 0){//this winupdate page
        winupdate_status = winupadate_isrunning();
        ui_status_winupdate();
    }else if (e.GetSelection() == 1){//this block 
        ID_FwRule.clear();
        list_blocked->Clear();
        get_blocked_list();
    }else if (e.GetSelection() == 2){//this custom dns page
        interfaces->Clear();
        interfaces->Append("Select...");
        interfaces->SetSelection(0);
        defaultdns->SetValue(false);
        defaultdns->Disable();
        customdnsserver->SetValue(false);
        customdnsserver->Disable();
        prefereddnsinput->SetLabel("example 8.8.8.8");
        prefereddnsinput->Disable();
        alternatednsinput->SetLabel("example 1.1.1.1");
        alternatednsinput->Disable();
        apply->Disable();
        reset->Disable();
        get_allinterface();
    }
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
    dialog_form->file_choose->Bind(wxEVT_RADIOBUTTON, firewall_dialog :: use_file, dialog_form);
    dialog_form->port_choose->Bind(wxEVT_RADIOBUTTON, firewall_dialog :: use_port, dialog_form);
    dialog_form->apply_btn->Bind(wxEVT_BUTTON, firewall_dialog :: create_fwrule, dialog_form);
    dialog_form->cancel_btn->Bind(wxEVT_BUTTON, firewall_dialog :: close_dialog, dialog_form);

    dialog_form->SetParent(main_form);
    dialog_form->CenterOnParent();
    dialog_form->Raise();
    dialog_form->ShowModal();
    dialog_form->Destroy();
}

//function to get service information
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
    if(statustarget->IsChecked()){
        if (winupdate_status == "RUNNING"){
            auto ssp = SERVICE_STATUS_PROCESS{ 0 };
            ControlService(svc, SERVICE_CONTROL_STOP, reinterpret_cast<LPSERVICE_STATUS>(&ssp));
        }
        else if (winupdate_status == "STOPPED"){
            StartService(svc, 0, nullptr);
        }
    }
    
    wxBeginBusyCursor();
    Sleep(5000);
    CloseServiceHandle(svc);
    CloseServiceHandle(sch);
    wxEndBusyCursor();
    action->Enable();
    
    //update UI winupdate
    winupdate_status = winupadate_isrunning();
    ui_status_winupdate();
}

void firewall_dialog :: use_file(wxCommandEvent &e)
{
    if (e.IsChecked()){
        fileselect->Enable();
        number_input->SetValue("0");
        number_input->Disable();
        type_port->Disable();
    }  
}

void firewall_dialog :: use_port(wxCommandEvent &e)
{
    if (e.IsChecked()){
        number_input->Enable();
        type_port->Enable();
        fileselect->SetPath("");
        fileselect->Disable();   
    }
}

void firewall_dialog :: create_fwrule(wxCommandEvent &e)
{
    if (fileselect->GetPath() != "" || number_input->GetValue() != "0"){
        string protocol;
        if (type_port->GetStringSelection() == "TCP"){
            protocol = "6";
        }else if (type_port->GetStringSelection() == "UDP"){
            protocol = "17";
        }
        
        string value;
        string type_input;
        if (fileselect->GetPath() != ""){
            value = "v2.31|Action=Block|Active=TRUE|Dir=Out|App=";
            value += fileselect->GetPath();
            value += "|Name=";
            value += name_input->GetValue();
            value += "|";
        }else if (number_input->GetValue() != "0"){
            value = "v2.31|Action=Block|Active=TRUE|Dir=Out|Protocol=";
            value += protocol; value += "|RPort=";
            value += number_input->GetValue();
            value += "|Name=";
            value += name_input->GetValue();
            value += "|";
        }
        
        HKEY registry;
        if (name_input->GetValue() != "" && RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\FirewallRules\\", 0, KEY_SET_VALUE, &registry) == ERROR_SUCCESS){
            RegSetValueExA(registry, name_input->GetValue().c_str(), 0, REG_SZ, (const BYTE*)(value.c_str()), value.size()+1);
            this->Hide();
            wxMessageBox("Successfully create block rule", "Success add new rule", wxOK | wxICON_INFORMATION);
            ID_FwRule.clear();
            main_form->list_blocked->Clear();
            get_blocked_list();   
            RegCloseKey(registry);
            this->Close();
            this->Destroy();
        }
    }
}

//close dialog form if press cancel button
void firewall_dialog :: close_dialog(wxCommandEvent &e)
{
    dialog_form->Close();
    dialog_form->Destroy();
}

void main_window :: delete_fwrule(wxCommandEvent &e)
{
    HKEY registry;
    if (e.GetSelection() != -1){
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\FirewallRules\\", 0, KEY_ALL_ACCESS, &registry) == ERROR_SUCCESS){
            if (RegDeleteValueA(registry, ID_FwRule.at(list_blocked->GetSelection()).c_str()) == ERROR_SUCCESS){
                wxMessageBox("Successfully delete block rule", "Success deleted", wxOK | wxICON_INFORMATION);   
            }
            RegCloseKey(registry);
        }
    }

    ID_FwRule.clear();
    list_blocked->Clear();
    get_blocked_list();
}

void main_window :: refresh_list(wxCommandEvent &e)
{
    ID_FwRule.clear();
    list_blocked->Clear();
    get_blocked_list();
}

//get adapter DNS setiings automatic or custom
void main_window :: get_data_selected(wxCommandEvent &e)
{
    if(e.GetSelection() != 0){
        string paths = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
        paths += GUID_adapter.at(e.GetSelection());
        CHAR lpData[1024]={0};
        DWORD buffersize = sizeof(lpData);
        HKEY hKey;
        string DNS;

        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, paths.c_str() , 0, KEY_READ, &hKey) == ERROR_SUCCESS)
        {

		    if (RegQueryValueExA(hKey, "NameServer", NULL, 0, (LPBYTE) lpData, &buffersize) == ERROR_SUCCESS){
                DNS = lpData;
			    if (DNS.empty())
                {
                    defaultdns->SetValue(true);
                    prefereddnsinput->SetLabel("example 8.8.8.8");
                    prefereddnsinput->Disable();
                    alternatednsinput->SetLabel("example 1.1.1.1");
                    alternatednsinput->Disable();
                }else{
                    customdnsserver->SetValue(true);
                    string ip_DNS = "";
                    if (DNS.find(',') != string::npos){
                        for (auto x : DNS){
                            if (x == ','){
                                prefereddnsinput->SetLabel(ip_DNS);
                                ip_DNS = "";
                            }else{ip_DNS = ip_DNS + x;}
                                alternatednsinput->SetLabel(ip_DNS);
                        }
                    }else{
                        prefereddnsinput->SetLabel(DNS);
                        alternatednsinput->SetLabel("");
                    }
                    
                    prefereddnsinput->Enable();
                    alternatednsinput->Enable();
                }
		    }

            RegCloseKey(hKey);
        }else{
            defaultdns->SetValue(false);
            customdnsserver->SetValue(false);
            prefereddnsinput->SetLabel("example 8.8.8.8");
            prefereddnsinput->Disable();
            alternatednsinput->SetLabel("example 1.1.1.1");
            alternatednsinput->Disable();
            apply->Disable();
            reset->Disable();
        }
        defaultdns->Enable();
        customdnsserver->Enable();
        apply->Enable();
        reset->Enable();
    }else{
        defaultdns->SetValue(false);
        defaultdns->Disable();
        customdnsserver->SetValue(false);
        customdnsserver->Disable();
        prefereddnsinput->SetLabel("example 8.8.8.8");
        prefereddnsinput->Disable();
        alternatednsinput->SetLabel("example 1.1.1.1");
        alternatednsinput->Disable();
        apply->Disable();
        reset->Disable();
    }
}

//setting for automatic dns configuration
void main_window :: is_auto(wxCommandEvent &e){
    prefereddnsinput->SetLabel("example 8.8.8.8");
    prefereddnsinput->Disable();
    alternatednsinput->SetLabel("example 1.1.1.1");
    alternatednsinput->Disable();
}

//setting for custom dns configuration
void main_window :: is_custom(wxCommandEvent &e){
    prefereddnsinput->SetLabel("");
    prefereddnsinput->Enable();
    alternatednsinput->SetLabel("");
    alternatednsinput->Enable();
    prefereddnsinput->SetFocus();
}

void main_window :: apply_dns_conf(wxCommandEvent &e){
    string paths = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
    paths += GUID_adapter.at(interfaces->GetSelection());
    string  DNS_list = "";
    HKEY hKey;
    
    if (prefereddnsinput->GetValue() != "example 8.8.8.8"){
        DNS_list = prefereddnsinput->GetValue().ToStdString();
        if (alternatednsinput->GetValue() != "example 1.1.1.1" and alternatednsinput->GetValue() != "")
        {
            DNS_list += ",";
            DNS_list += alternatednsinput->GetValue().ToStdString();
        }
    }

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, paths.c_str() , 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS){
        apply->Disable();
        RegSetValueExA(hKey, "NameServer", 0, REG_SZ, (LPBYTE)(DNS_list.c_str()), sizeof(DNS_list));
        RegCloseKey (hKey);
        wxBeginBusyCursor();
        Sleep(2000);
        wxEndBusyCursor();
        wxMessageBox("Successfully configured DNS for this interface :)", "Success configuration", wxOK | wxICON_INFORMATION);
        apply->Enable();
    }
}

//reset adapter dns setting to DHCP or automatic
void main_window :: reset_dns_conf(wxCommandEvent &e){
    string paths = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
    paths += GUID_adapter.at(interfaces->GetSelection());
    string  DNS_list = "";
    HKEY hKey;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, paths.c_str() , 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS){
        reset->Disable();
        RegSetValueExA(hKey, "NameServer", 0, REG_SZ, (LPBYTE)(DNS_list.c_str()), sizeof(DNS_list));
        RegCloseKey (hKey);
        wxBeginBusyCursor();
        Sleep(2000);
        wxEndBusyCursor();
        wxMessageBox("Successfully reset DNS to automatic(DHCP) for this interface", "Reset to Automatic", wxOK | wxICON_INFORMATION);
        defaultdns->SetValue(true);
        prefereddnsinput->SetLabel("example 8.8.8.8");
        prefereddnsinput->Disable();
        alternatednsinput->SetLabel("example 1.1.1.1");
        alternatednsinput->Disable();
        reset->Enable();
    }
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

void get_blocked_list(){
    TCHAR achValue[5000];  
    CHAR lpData[1024]={0};
    string value_data;
    string remove = "Name=";

    DWORD cValues; 
    DWORD i, retCode;
    DWORD cchValue = 5000;
    DWORD buffersize = sizeof(lpData);

    size_t size_data;
    HKEY registry;
    if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\FirewallRules"), 0, KEY_READ, &registry) == ERROR_SUCCESS){
        retCode = RegQueryInfoKey(registry, NULL, NULL, NULL, NULL, NULL, NULL, &cValues, NULL, NULL, NULL, NULL);

        if (cValues){
            for (i=0, retCode==ERROR_SUCCESS; i<cValues; i++){ 
                cchValue = 5000; 
                achValue[0] = '\0'; 
                if (RegEnumValue(registry, i, achValue, &cchValue, NULL, NULL,NULL,NULL) == ERROR_SUCCESS){
                    if (RegQueryValueExA(registry, (LPSTR) achValue, 0, NULL, (LPBYTE) lpData, &buffersize) == ERROR_SUCCESS){
                        buffersize = sizeof(lpData)+1;
                        value_data = lpData;
                        if (value_data.find("Action=Block") != string::npos && value_data.find("Dir=Out") != string::npos){
                            stringstream s_stream(value_data);
                            while(s_stream) {
                                string rule_name;
                                getline(s_stream, rule_name, '|');
                                if (rule_name.find(remove) != string::npos){
                                    size_data = rule_name.find(remove);
                                    rule_name.erase(size_data, remove.length());

                                    main_form->list_blocked->Append(rule_name);
                                    ID_FwRule.push_back((LPSTR)achValue);
                                }
                                wxYield();
                            }     
                        }
                    }
                    wxYield();
                } 
            }
        }
        RegCloseKey(registry);
    }
}

void get_allinterface()
{
    PIP_ADAPTER_INFO pAdapterInfo;
    pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
    ULONG buflen = sizeof(IP_ADAPTER_INFO);

    if(GetAdaptersInfo(pAdapterInfo, &buflen) == ERROR_BUFFER_OVERFLOW) {
      free(pAdapterInfo);
      pAdapterInfo = (IP_ADAPTER_INFO *) malloc(buflen);
    }

    if(GetAdaptersInfo(pAdapterInfo, &buflen) == NO_ERROR) {
        GUID_adapter.clear();
        GUID_adapter.push_back("NONE");
        PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
        while (pAdapter) {
            main_form->interfaces->Append(pAdapter->Description);
            GUID_adapter.push_back(pAdapter->AdapterName);
            wxYield();
            pAdapter = pAdapter->Next;
        }
        free(pAdapter);
        main_form->interfaces->Enable();
    }
}