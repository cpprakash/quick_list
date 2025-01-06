#include "MainApp.hpp"
#include "MainFrame.hpp"
#include "QuickTodo.hpp"

#include <vector>

bool MainApp::OnInit() {
  MainFrame *mainFrame = new MainFrame();
  mainFrame->SetClientSize(800, 600);
  mainFrame->Center();

  mainFrame->Show();
  return true;
}