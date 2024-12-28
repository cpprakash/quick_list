#include "MainFrame.hpp"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Hello TODO Quick List") {
  CreateStatusBar();
  SetStatusText("Welcome to this quick todo list.");
}
