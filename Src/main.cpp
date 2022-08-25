#include <wx/wx.h>
#include <main_window.h>

class program : public wxApp{
    public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(program);

bool program :: OnInit(){
    wxImage::AddHandler(new wxPNGHandler);
    main_window *main_form = new main_window("Easy Win Config", wxDefaultPosition, wxSize(300,400));
    main_form->Show();
    return 1;
}