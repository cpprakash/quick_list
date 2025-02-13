#include "../headers/MainApp.hpp"
#include "../headers/MainFrame.hpp"
#include "../headers/QuickTodo.hpp"

#include <vector>

bool MainApp::OnInit() {
  MainFrame *mainFrame = new MainFrame();
  mainFrame->SetClientSize(1000, 800);
  mainFrame->Center();

  mainFrame->Show();
  return true;
}