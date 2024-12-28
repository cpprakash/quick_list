#include "MainApp.hpp"
#include "MainFrame.hpp"

bool MainApp::OnInit() {
  MainFrame *mainFrame = new MainFrame();
  mainFrame->Show();
  return true;
}