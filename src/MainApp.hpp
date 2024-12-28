#ifndef __HEADER_MAINAPP__
#define __HEADER_MAINAPP_

#include <wx/wx.h>

class MainApp : public wxApp {
public:
  bool OnInit() override;
};
wxIMPLEMENT_APP(MainApp);
#endif
