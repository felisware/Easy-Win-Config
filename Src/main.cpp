#include <wx/wx.h>
#include <main_window.h>
#include <firewall_dialog.h>

class program : public wxApp{
    public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(program);

bool program :: OnInit(){
    wxImage::AddHandler(new wxPNGHandler);
    main_window *main_form = new main_window("Easy Win Config", wxDefaultPosition, wxSize(300,400));
    main_form->Show();
    firewall_dialog *dialog_form = new firewall_dialog("Blocking Dialog", wxDefaultPosition, wxSize(320,325));
    dialog_form->Raise();
    dialog_form->ShowModal();
	dialog_form->Destroy();
	dialog_form = 0;
    return 1;
}