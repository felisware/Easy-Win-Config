#include <main_window.h>

main_window :: main_window(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame(NULL,wxID_ANY, title, pos, size, wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    //color
    wxColour dark = wxColour(1, 22, 39);
    wxColour red = wxColour(247, 23, 53);
    wxColour green = wxColour(29, 215, 85);
    wxColour blue = wxColour(0, 167, 225);

    //button size
    wxSize normal_btn = wxSize(75,-1);

    //font
    wxFont title_font = wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Segoe UI"));
    wxFont default_font = wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Segoe UI"));

    this->SetIcon(wxIcon("appicon"));
    this->CenterOnScreen();
    this->SetBackgroundColour(wxColour(255, 255, 255));
    this->SetFont(default_font);
    wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
    wxNotebook *pagesystem = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    //create page winupdate
    wxPanel *winupdate = new wxPanel(pagesystem,wxID_ANY, wxDefaultPosition, wxDefaultSize);
    winupdate->SetBackgroundColour(dark);
    winupdate->SetForegroundColour(blue);
    winupdate->SetFont(default_font);
    pagesystem->AddPage(winupdate, "Windows Update", 1);
    wxBoxSizer *winupdate_vertical = new wxBoxSizer(wxVERTICAL);
    wxStaticText *winupdate_title = new wxStaticText(winupdate, wxID_ANY, "Windows Update", wxDefaultPosition, wxDefaultSize);
    winupdate_title->SetFont(title_font);
    winupdate_vertical->Add(winupdate_title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL,20);
    wxStaticText *statusupdate = new wxStaticText(winupdate, wxID_ANY, "Windows update status is", wxDefaultPosition, wxDefaultSize);
    winupdate_vertical->AddSpacer(10);
    winupdate_vertical->Add(statusupdate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    winupdate_vertical->AddSpacer(10);
    wxCheckBox *advanced = new wxCheckBox(winupdate, wxID_ANY, "Advanced Settings", wxDefaultPosition, wxDefaultSize);
    winupdate_vertical->Add(advanced, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    wxPanel *advanced_panel = new wxPanel(winupdate, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    advanced_panel->SetForegroundColour(blue);
    advanced_panel->SetFont(default_font);
    wxBoxSizer *adv_vert = new wxBoxSizer(wxVERTICAL);
    wxCheckBox *statustarget = new wxCheckBox(advanced_panel, wxID_ANY, "Stop/Start windows update", wxDefaultPosition, wxDefaultSize);
    wxChoice *startuptype = new wxChoice(advanced_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    startuptype->Append("Disable");
    startuptype->Append("Manual");
    startuptype->Append("Automatic");
    adv_vert->Add(statustarget, 1, wxEXPAND|wxALL, 5);
    adv_vert->Add(startuptype, 1, wxEXPAND|wxALL, 5);
    advanced_panel->SetSizer(adv_vert);
    winupdate_vertical->Add(advanced_panel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 10);
    wxButton *action = new wxButton(winupdate, wxID_ANY, "Turn On", wxDefaultPosition, normal_btn);
    action->SetBitmap(wxBITMAP_PNG(turn-on));
    winupdate_vertical->Add(action, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    winupdate->SetSizer(winupdate_vertical);

    //create page blocking firewall
    wxPanel *blocking = new wxPanel(pagesystem,wxID_ANY, wxDefaultPosition, wxDefaultSize);
    blocking->SetBackgroundColour(dark);
    blocking->SetForegroundColour(red);
    blocking->SetFont(default_font);
    pagesystem->AddPage(blocking, "Block Access");
    wxBoxSizer *blocking_vertical = new wxBoxSizer(wxVERTICAL);
    wxStaticText *blocking_title = new wxStaticText(blocking, wxID_ANY, "Blocked List", wxDefaultPosition, wxDefaultSize);
    blocking_title->SetFont(title_font);
    blocking_vertical->Add(blocking_title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL,20);
    wxListBox *list_blocked = new wxListBox(blocking, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    blocking_vertical->Add(list_blocked, 1, wxEXPAND|wxRIGHT|wxLEFT,10);
    wxBoxSizer *blocking_horizontal = new wxBoxSizer(wxHORIZONTAL);
    wxButton *add_btn = new wxButton(blocking, wxID_ANY, "Add", wxDefaultPosition, normal_btn);
    add_btn->SetBitmap(wxBITMAP_PNG(plus));
    wxButton *remove_btn = new wxButton(blocking, wxID_ANY, "Remove", wxDefaultPosition, normal_btn);
    remove_btn->SetBitmap(wxBITMAP_PNG(remove));
    wxButton *refresh_btn = new wxButton(blocking, wxID_ANY, "Refresh", wxDefaultPosition, normal_btn);
    refresh_btn->SetBitmap(wxBITMAP_PNG(refresh));
    blocking_horizontal->Add(add_btn, 0, wxALL, 5);
    blocking_horizontal->Add(remove_btn, 0, wxALL, 5);
    blocking_horizontal->Add(refresh_btn, 0, wxALL, 5);
    blocking_vertical->Add(blocking_horizontal, 0, wxALIGN_RIGHT|wxALL, 5);
    blocking->SetSizer(blocking_vertical);

    //create page custom dns
    wxPanel *customdns = new wxPanel(pagesystem,wxID_ANY, wxDefaultPosition, wxDefaultSize);
    customdns->SetBackgroundColour(dark);
    customdns->SetForegroundColour(green);
    customdns->SetFont(default_font);
    pagesystem->AddPage(customdns, "Custom DNS");
    wxBoxSizer *customdns_vertical = new wxBoxSizer(wxVERTICAL);
    wxStaticText *customdns_title = new wxStaticText(customdns, wxID_ANY, "Custom DNS", wxDefaultPosition, wxDefaultSize);
    customdns_title->SetFont(title_font);
    customdns_vertical->Add(customdns_title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL,20);
    wxStaticText *select_text = new wxStaticText(customdns, wxID_ANY, "Select network interface", wxDefaultPosition, wxDefaultSize);
    select_text->SetFont(default_font);
    customdns_vertical->Add(select_text, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    wxChoice *interfaces = new wxChoice(customdns, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    customdns_vertical->AddSpacer(5);
    customdns_vertical->Add(interfaces, 0, wxEXPAND|wxLEFT|wxRIGHT, 20);
    customdns_vertical->AddSpacer(5);
    wxRadioButton *defaultdns = new wxRadioButton(customdns, wxID_ANY, "Default DNS (DHCP/Automatic)", wxDefaultPosition, wxDefaultSize);
    customdns_vertical->Add(defaultdns, 0, wxALL, 5);
    wxRadioButton *customdnsserver = new wxRadioButton(customdns, wxID_ANY, "Custom DNS", wxDefaultPosition, wxDefaultSize);
    customdns_vertical->Add(customdnsserver, 0, wxALL, 5);
    wxStaticBoxSizer *custombox = new wxStaticBoxSizer( new wxStaticBox(customdns, wxID_ANY, "Customized DNS server", wxDefaultPosition, wxDefaultSize), wxVERTICAL);
    wxBoxSizer *custom_horizontal1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *preferedlabel =  new wxStaticText(customdns, wxID_ANY, "Prefered DNS  ", wxDefaultPosition, wxDefaultSize);
    custom_horizontal1->Add(preferedlabel, 0, wxALL, 5);
    wxTextCtrl *prefereddnsinput = new wxTextCtrl(customdns, wxID_ANY, "8.8.8.8", wxDefaultPosition, wxDefaultSize);
    custom_horizontal1->Add(prefereddnsinput, 0, wxALL, 1);
    custombox->Add(custom_horizontal1, 0, wxALL, 5);
    wxBoxSizer *custom_horizontal2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *alternatelabel =  new wxStaticText(customdns, wxID_ANY, "Alternate DNS ", wxDefaultPosition, wxDefaultSize);
    custom_horizontal2->Add(alternatelabel, 0, wxALL, 5);
    wxTextCtrl *alternatednsinput = new wxTextCtrl(customdns, wxID_ANY, "1.1.1.1", wxDefaultPosition, wxDefaultSize);
    custom_horizontal2->Add(alternatednsinput, 0, wxALL, 1);
    custombox->Add(custom_horizontal2, 0, wxALL, 5);
    customdns_vertical->Add(custombox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2);

    wxBoxSizer *btn_actionlocation = new wxBoxSizer(wxHORIZONTAL);
    wxButton *apply = new wxButton(customdns, wxID_ANY, "Apply", wxDefaultPosition, normal_btn);
    apply->SetBitmap(wxBITMAP_PNG(ok));
    btn_actionlocation->Add(apply, 0, wxALL, 5);
    wxButton *reset = new wxButton(customdns, wxID_ANY, "Reset", wxDefaultPosition, normal_btn);
    reset->SetBitmap(wxBITMAP_PNG(not));
    btn_actionlocation->Add(reset, 0, wxALL, 5);

    customdns_vertical->Add(btn_actionlocation, 0, wxALIGN_RIGHT|wxALL, 5);
    customdns->SetSizer(customdns_vertical);

    //this my website link :)
    wxHyperlinkCtrl *myweb = new wxHyperlinkCtrl(this,wxID_ANY, "From Felisware.com", "https://felisware.com", wxDefaultPosition, wxDefaultSize);
    mainsizer->Add(pagesystem, 1, wxEXPAND);
    mainsizer->Add(myweb, 0, wxALIGN_BOTTOM|wxALL, 5);
    this->SetSizer(mainsizer);
}