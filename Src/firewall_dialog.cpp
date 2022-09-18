#include <firewall_dialog.h>

firewall_dialog :: firewall_dialog (const wxString &title, const wxPoint &pos, const wxSize &size)
: wxDialog(NULL, wxID_ANY, title, pos, size, wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    //color
    wxColour dark = wxColour(1, 22, 39);
    wxColour yellow = wxColour(255, 231, 76);

    //button size
    wxSize normal_btn = wxSize(75,-1);

    //font
    wxFont title_font = wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Segoe UI"));
    wxFont default_font = wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Segoe UI"));

    this->SetIcon(wxIcon("appicon"));
    this->SetBackgroundColour(wxColour(dark));
    this->SetForegroundColour(wxColour(yellow));
    this->SetFont(default_font);
    
    wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *dialog_title = new wxStaticText(this, wxID_ANY, "Blocked Target", wxDefaultPosition, wxDefaultSize);
    dialog_title->SetFont(title_font);
    mainsizer->Add(dialog_title, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 20);
    
    wxBoxSizer *box_name = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *name_label = new wxStaticText(this, wxID_ANY, "Name", wxDefaultPosition, wxDefaultSize);
    box_name->Add(name_label, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    name_input = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    box_name->Add(name_input, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    mainsizer->Add(box_name, 0, wxALL, 5);
    
    file_choose = new wxRadioButton(this, wxID_ANY, "File/Software", wxDefaultPosition, wxDefaultSize);
    file_choose->SetValue(true);
    mainsizer->Add(file_choose, 0, wxALL, 10);
    fileselect = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, "Select File or Software", "*", wxDefaultPosition, wxDefaultSize);
    fileselect->SetLabelMarkup("");
    mainsizer->Add(fileselect, 0, wxEXPAND|wxLEFT|wxRIGHT, 20);
    mainsizer->AddSpacer(10);

    port_choose = new wxRadioButton(this, wxID_ANY, "Port", wxDefaultPosition, wxDefaultSize);
    mainsizer->Add(port_choose, 0, wxALL, 5);
    
    wxBoxSizer *portbox = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *labelnumber = new wxStaticText(this, wxID_ANY, "Number Port", wxDefaultPosition, wxDefaultSize);
    portbox->Add(labelnumber, 0, wxALL, 5);
    number_input = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize);
    number_input->Disable();
    portbox->Add(number_input, 0, wxALL, 5);
    type_port = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    type_port->Append("TCP");
    type_port->Append("UDP");
    type_port->SetSelection(0);
    type_port->Disable();
    portbox->Add(type_port, 0, wxALL, 5);
    mainsizer->Add(portbox, 1, wxLEFT, 15);

    wxBoxSizer *action_btn = new wxBoxSizer(wxHORIZONTAL);
    apply_btn = new wxButton(this, wxID_ANY, "Apply", wxDefaultPosition, normal_btn);
    apply_btn->SetBitmap(wxBITMAP_PNG(ok));
    apply_btn->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    action_btn->Add(apply_btn, 0, wxALL, 5);
    cancel_btn = new wxButton(this, wxID_ANY, "Cancel", wxDefaultPosition, normal_btn);
    cancel_btn->SetBitmap(wxBITMAP_PNG(not));
    cancel_btn->SetBackgroundColour(wxSystemSettings :: GetColour( wxSYS_COLOUR_BTNFACE));
    action_btn->Add(cancel_btn, 0, wxALL, 5);
    mainsizer->Add(action_btn, 0, wxALIGN_RIGHT|wxALL, 5);

    this->SetSizer(mainsizer);
}