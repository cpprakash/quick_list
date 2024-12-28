#ifndef __HEADER_MAINFRAME__
#define __HEADER_MAINFRAME__

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
  MainFrame();

private:
  void OnHello(wxCommandEvent &event);
};

#endif