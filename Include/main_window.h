#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/hyperlink.h>

class main_window : public wxFrame{
    public:
    main_window(const wxString &title, const wxPoint &pos, const wxSize &size);
};

#endif