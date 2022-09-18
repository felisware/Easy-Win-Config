#ifndef FIREWALL_DIALOG_H
#define FIREWALL_DIALOG_H
#include <wx/wx.h>
#include <wx/filepicker.h>

class firewall_dialog : public wxDialog
{
    public:
    //make widgets accessible on main.cpp
	wxTextCtrl *name_input;
	wxRadioButton *file_choose;
	wxFilePickerCtrl *fileselect;
	wxRadioButton *port_choose;
	wxTextCtrl *number_input;
	wxChoice *type_port;
	wxButton *apply_btn;
	wxButton *cancel_btn;

    firewall_dialog(const wxString &title, const wxPoint &pos, const wxSize &size);

	//create function for widgets event
	void create_fwrule(wxCommandEvent &e);//create new block firewall rule
    void close_dialog(wxCommandEvent &e);//to close blocking Dialog
	void use_file(wxCommandEvent &e);//set config for use file or program
	void use_port(wxCommandEvent &e);//set config for use port
};

#endif