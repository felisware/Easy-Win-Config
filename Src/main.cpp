#include <wx/wx.h>
#include <main_window.h>
#include <firewall_dialog.h>

class program : public wxApp{
    public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(program);

//global declaration :)
main_window *main_form;
firewall_dialog *dialog_form;

bool program :: OnInit(){
    //add handler to render PNG image
    wxImage::AddHandler(new wxPNGHandler);

    main_form = new main_window("Easy Win Config", wxDefaultPosition, wxSize(300,400));
    //set parent & TOP LEVEL WINDOW
    SetTopWindow(main_form);

    //binding function widgets event on main_form
    main_form->advanced->Bind(wxEVT_CHECKBOX, main_window :: show_hide_advanced, main_form);
    main_form->add_btn->Bind(wxEVT_BUTTON, main_window :: show_blocking_dialog, main_form);

    //show main form GUI
    main_form->Show();
    return 1;
}

//show or hide advanced panel on windows update page
void main_window :: show_hide_advanced(wxCommandEvent &e){
    if(e.IsChecked()){
        winupdate_vertical->Show(advanced_panel);
        winupdate_vertical->Layout();
    }else
    {
        winupdate_vertical->Hide(advanced_panel);
        winupdate_vertical->Layout();
    }
}

//create blocking dialog when press add button on block access page
void main_window :: show_blocking_dialog(wxCommandEvent &e){
    dialog_form = new firewall_dialog("Blocking Dialog", wxDefaultPosition, wxSize(320,325));

    //binding function widgets event on dialog_form
    dialog_form->cancel_btn->Bind(wxEVT_BUTTON, firewall_dialog :: close_dialog, dialog_form);

    dialog_form->SetParent(main_form);
    dialog_form->CenterOnParent();
    dialog_form->Raise();
    dialog_form->ShowModal();
    dialog_form->Destroy();
}

//close dialog form if press cancel button
void firewall_dialog :: close_dialog(wxCommandEvent &e){
    dialog_form->Close();
    dialog_form->Destroy();
}