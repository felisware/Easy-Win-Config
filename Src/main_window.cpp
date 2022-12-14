#include <main_window.h>

main_window :: main_window(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame(NULL,wxID_ANY, title, pos, size, wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    //color
    wxColour dark = wxColour(1, 22, 39);
    wxColour red = wxColour(247, 23, 53);
    wxColour green = wxColour(29, 215, 85);
    wxColour blue = wxColour(0, 167, 225);
    wxColour yellow = wxColour(255,228,51);

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
    pagesystem = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    //create page winupdate
    wxPanel *winupdate = new wxPanel(pagesystem,wxID_ANY, wxDefaultPosition, wxDefaultSize);
    winupdate->SetBackgroundColour(dark);
    winupdate->SetForegroundColour(blue);
    winupdate->SetFont(default_font);
    pagesystem->AddPage(winupdate, "Windows Update", 1);
    winupdate_vertical = new wxBoxSizer(wxVERTICAL);
    wxStaticText *winupdate_title = new wxStaticText(winupdate, wxID_ANY, "Windows Update", wxDefaultPosition, wxDefaultSize);
    winupdate_title->SetFont(title_font);
    winupdate_vertical->Add(winupdate_title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL,20);
    statusupdate = new wxStaticText(winupdate, wxID_ANY, "Get windows update Status...", wxDefaultPosition, wxDefaultSize);
    statusupdate->SetFont(wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    winupdate_vertical->AddSpacer(10);
    winupdate_vertical->Add(statusupdate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    winupdate_vertical->AddSpacer(10);
    advanced = new wxCheckBox(winupdate, wxID_ANY, "Advanced Settings", wxDefaultPosition, wxDefaultSize);
    winupdate_vertical->Add(advanced, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    advanced_panel = new wxPanel(winupdate, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    advanced_panel->SetForegroundColour(blue);
    advanced_panel->SetFont(default_font);
    wxBoxSizer *adv_vert = new wxBoxSizer(wxVERTICAL);
    statustarget = new wxCheckBox(advanced_panel, wxID_ANY, "Wait winupdate status...", wxDefaultPosition, wxDefaultSize);
    statustarget->SetValue(true);
    adv_vert->Add(statustarget, 1, wxEXPAND|wxALL, 5);
    startuptype = new wxChoice(advanced_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    startuptype->Append("Select...");
    startuptype->Append("Disable");
    startuptype->Append("Manual");
    startuptype->Append("Automatic");
    startuptype->SetSelection(0);
    startuptype->Disable();
    adv_vert->Add(startuptype, 1, wxEXPAND|wxALL, 5);
    advanced_panel->SetSizer(adv_vert);
    winupdate_vertical->Add(advanced_panel, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 10);
    winupdate_vertical->Hide(advanced_panel);
    winupdate_vertical->Layout();
    action = new wxButton(winupdate, wxID_ANY, "Loading...", wxDefaultPosition, normal_btn);
    action->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    action->Disable();
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
    list_blocked = new wxListBox(blocking, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    blocking_vertical->Add(list_blocked, 1, wxEXPAND|wxRIGHT|wxLEFT,10);
    wxBoxSizer *blocking_horizontal = new wxBoxSizer(wxHORIZONTAL);
    add_btn = new wxButton(blocking, wxID_ANY, "Add", wxDefaultPosition, normal_btn);
    add_btn->SetBitmap(wxBITMAP_PNG(plus));
    add_btn->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));;
    blocking_horizontal->Add(add_btn, 0, wxALL, 5);
    remove_btn = new wxButton(blocking, wxID_ANY, "Remove", wxDefaultPosition, normal_btn);
    remove_btn->SetBitmap(wxBITMAP_PNG(remove));
    remove_btn->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    blocking_horizontal->Add(remove_btn, 0, wxALL, 5);
    refresh_btn = new wxButton(blocking, wxID_ANY, "Refresh", wxDefaultPosition, normal_btn);
    refresh_btn->SetBitmap(wxBITMAP_PNG(refresh));
    refresh_btn->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    blocking_horizontal->Add(refresh_btn, 0, wxALL, 5);
    blocking_vertical->Add(blocking_horizontal, 0, wxALIGN_RIGHT|wxALL, 5);
    blocking->SetSizer(blocking_vertical);

    //create page custom dns
    wxPanel *customdns = new wxPanel(pagesystem, wxID_ANY, wxDefaultPosition, wxDefaultSize);
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
    interfaces = new wxChoice(customdns, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    interfaces->Append("Select...");
    interfaces->SetSelection(0);
    interfaces->Disable();
    customdns_vertical->AddSpacer(5);
    customdns_vertical->Add(interfaces, 0, wxEXPAND|wxLEFT|wxRIGHT, 20);
    customdns_vertical->AddSpacer(5);
    defaultdns = new wxRadioButton(customdns, wxID_ANY, "Default DNS (DHCP/Automatic)", wxDefaultPosition, wxDefaultSize);
    customdns_vertical->Add(defaultdns, 0, wxALL, 5);
    customdnsserver = new wxRadioButton(customdns, wxID_ANY, "Custom DNS", wxDefaultPosition, wxDefaultSize);
    customdns_vertical->Add(customdnsserver, 0, wxALL, 5);
    custombox = new wxStaticBoxSizer( new wxStaticBox(customdns, wxID_ANY, "Customized DNS server", wxDefaultPosition, wxDefaultSize), wxVERTICAL);
    wxBoxSizer *custom_horizontal1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *preferedlabel =  new wxStaticText(customdns, wxID_ANY, "Prefered DNS  ", wxDefaultPosition, wxDefaultSize);
    custom_horizontal1->Add(preferedlabel, 0, wxALL, 5);
    prefereddnsinput = new wxTextCtrl(customdns, wxID_ANY, "example 8.8.8.8", wxDefaultPosition, wxDefaultSize);
    prefereddnsinput->Disable();
    custom_horizontal1->Add(prefereddnsinput, 0, wxALL, 1);
    custombox->Add(custom_horizontal1, 0, wxALL, 5);
    wxBoxSizer *custom_horizontal2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *alternatelabel =  new wxStaticText(customdns, wxID_ANY, "Alternate DNS ", wxDefaultPosition, wxDefaultSize);
    custom_horizontal2->Add(alternatelabel, 0, wxALL, 5);
    alternatednsinput = new wxTextCtrl(customdns, wxID_ANY, "example 1.1.1.1", wxDefaultPosition, wxDefaultSize);
    alternatednsinput->Disable();
    custom_horizontal2->Add(alternatednsinput, 0, wxALL, 1);
    custombox->Add(custom_horizontal2, 0, wxALL, 5);
    customdns_vertical->Add(custombox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2);
    wxBoxSizer *btn_actionlocation = new wxBoxSizer(wxHORIZONTAL);
    apply = new wxButton(customdns, wxID_ANY, "Apply", wxDefaultPosition, normal_btn);
    apply->SetBitmap(wxBITMAP_PNG(ok));
    apply->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    apply->Disable();
    btn_actionlocation->Add(apply, 0, wxALL, 5);
    reset = new wxButton(customdns, wxID_ANY, "Reset", wxDefaultPosition, normal_btn);
    reset->SetBitmap(wxBITMAP_PNG(not));
    reset->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    reset->Disable();
    btn_actionlocation->Add(reset, 0, wxALL, 5);
    customdns_vertical->Add(btn_actionlocation, 0, wxALIGN_RIGHT|wxALL, 5);
    customdns->SetSizer(customdns_vertical);

    //create page Checkdisk
    wxPanel *checkdisk = new wxPanel(pagesystem, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    checkdisk->SetBackgroundColour(dark);
    checkdisk->SetForegroundColour(yellow);
    checkdisk->SetFont(default_font);
    pagesystem->AddPage(checkdisk, "Boot Checkdisk");
    checkdisk_vertical = new wxBoxSizer(wxVERTICAL);
    wxStaticText *checkdisk_title = new wxStaticText(checkdisk, wxID_ANY, "Booting Checkdisk", wxDefaultPosition, wxDefaultSize);
    checkdisk_title->SetFont(title_font);
    checkdisk_vertical->Add(checkdisk_title, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 20);
    info = new wxStaticText(checkdisk, wxID_ANY, "Loading...", wxDefaultPosition, wxDefaultSize);
    info->SetForegroundColour(wxColour(255,255,255));
    checkdisk_vertical->Add(info, 0, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
    turn = new wxButton(checkdisk, wxID_ANY, "Loading", wxDefaultPosition, normal_btn);
    turn->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    turn->Disable();
    checkdisk_vertical->AddSpacer(10);
    checkdisk_vertical->Add(turn, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    checkdisk->SetSizer(checkdisk_vertical);

    //create page donation
    wxPanel *donate = new wxPanel(pagesystem, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    donate->SetBackgroundColour(dark);
    donate->SetForegroundColour(green);
    donate->SetFont(default_font);
    pagesystem->AddPage(donate, "Donate");
    wxBoxSizer *donate_vertical = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *paypal_horizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *paypal = new wxStaticText(donate, wxID_ANY, "Paypal ", wxDefaultPosition, wxDefaultSize);
    paypal->SetFont(title_font);
    paypal_horizontal->Add(paypal, 0, wxALL, 5);
    wxHyperlinkCtrl *paypal_link = new wxHyperlinkCtrl(donate, wxID_ANY, "Admin Hanif", "https://paypal.me/felisware?country.x=ID&locale.x=id_ID", wxDefaultPosition, wxDefaultSize);
    paypal_link->SetFont(title_font);
    paypal_horizontal->Add(paypal_link, 0, wxALL, 5);
    wxBoxSizer *eth_horizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *eth = new wxStaticText(donate, wxID_ANY, "Ethereum", wxDefaultPosition, wxDefaultSize);
    eth->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Segoe UI")));
    eth_horizontal->Add(eth, 0, wxALL, 5);
    wxTextCtrl *address = new wxTextCtrl(donate, wxID_ANY, "0x764822c3e7991a951ce06279D4088E7D1eB1E934", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    address->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Segoe UI")));
    eth_horizontal->Add(address, 1, wxALL, 5);
    donate_vertical->AddStretchSpacer();
    donate_vertical->Add(paypal_horizontal, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    donate_vertical->Add(eth_horizontal, 0, wxEXPAND|wxALL, 5);
    donate_vertical->AddStretchSpacer();
    donate->SetSizer(donate_vertical);

    //footer
    wxHyperlinkCtrl *myweb = new wxHyperlinkCtrl(this,wxID_ANY, "From Felisware.com", "www.felisware.com", wxDefaultPosition, wxDefaultSize);
    wxStaticText *city = new wxStaticText(this, wxID_ANY, "Tegal, Center Java, Indonesia", wxDefaultPosition, wxDefaultSize);
    wxBoxSizer *footers = new wxBoxSizer(wxHORIZONTAL);
    footers->Add(myweb, 0, wxALL, 5);
    footers->AddStretchSpacer();
    footers->Add(city, 0, wxALL, 5);

    mainsizer->Add(pagesystem, 1, wxEXPAND);
    mainsizer->Add(footers, 0, wxEXPAND|wxALL, 0);
    this->SetSizer(mainsizer);
}