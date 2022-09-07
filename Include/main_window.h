#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/hyperlink.h>

class main_window : public wxFrame
{
    public:
    //make widgets accessible on main.cpp
    
    wxNotebook *pagesystem;
    //page win update
    wxBoxSizer *winupdate_vertical;
    wxStaticText *statusupdate;
    wxCheckBox *advanced;
    wxPanel *advanced_panel;
    wxCheckBox *statustarget;
    wxChoice *startuptype;
    wxButton *action;
    //page blocking firewall
    wxListBox *list_blocked;
    wxButton *add_btn;
    wxButton *remove_btn;
    wxButton *refresh_btn;
    //custom DNS
    wxChoice *interfaces;
    wxRadioButton *defaultdns;
    wxRadioButton *customdnsserver;
    wxStaticBoxSizer *custombox;
    wxTextCtrl *prefereddnsinput;
    wxTextCtrl *alternatednsinput;
    wxButton *apply;
    wxButton *reset;

    main_window(const wxString &title, const wxPoint &pos, const wxSize &size);

    //create function for widgets event
    void change_page(wxBookCtrlEvent &e);//run spesific task every page selection is changed
    void show_hide_advanced(wxCommandEvent &e);//to show and hide advance panel
    void action_Clicked(wxCommandEvent &e);//confuguration windows update service action
    void show_blocking_dialog(wxCommandEvent &e);//to show blocking Dialog
    void get_data_selected(wxCommandEvent &e);//check if selected choice not default
    void is_auto(wxCommandEvent &e);//setting for automatic dns configuration
    void is_custom(wxCommandEvent &e);//setting for custom dns configuration
    void apply_dns_conf(wxCommandEvent &e);//update dns configuration on regedit
    void reset_dns_conf(wxCommandEvent &e);//reset dns configuration on regedit to automatic or withour nameserver
};

#endif