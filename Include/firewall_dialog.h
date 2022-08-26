#ifndef FIREWALL_DIALOG_H
#define FIREWALL_DIALOG_H
#include <wx/wx.h>
#include <wx/filepicker.h>

class firewall_dialog : public wxDialog{
    public:
    //make widgets accessible on main.cpp
	wxTextCtrl *name_input;
	wxRadioButton *file_choose;
	wxFilePickerCtrl *fileselect;
	wxRadioButton *port_choose;
	wxTextCtrl *number_input;
	wxButton *apply_btn;
	wxButton *cancel_btn;

    firewall_dialog(const wxString &title, const wxPoint &pos, const wxSize &size);
};

#endif