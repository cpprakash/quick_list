#include <iostream>
#include <string>
#include <vector>

#include "../headers/MainFrame.hpp"
#include "../headers/QuickTodo.hpp"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "TODO Quick List") {
  create_gui_controls();
  button_add->Bind(wxEVT_BUTTON, &MainFrame::on_add_todo_button_click, this);
  button_clear_todos->Bind(wxEVT_BUTTON,
                           &MainFrame::on_clear_todos_button_click, this);
  display_todos->Bind(wxEVT_CHECKLISTBOX,
                      &MainFrame::on_todo_checklistbox_checked, this);

  this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::on_main_window_close, this);
  CreateStatusBar();
  SetStatusText("Welcome to this quick todo list.");
}

void MainFrame::create_gui_controls(void) {
  panel = new wxPanel(this);
  header = new wxStaticText(panel, wxID_ANY, "TODO List", wxPoint(0, 22),
                            wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
  header->SetBackgroundColour(*wxBLACK);

  input_title =
      new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(600, 35));

  input_description =
      new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 125), wxSize(600, 35));
  button_add = new wxButton(panel, wxID_ANY, "Add TODO", wxPoint(100, 170),
                            wxSize(100, 40));
  display_todos =
      new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 220), wxSize(600, 350));
  load_todos_from_file_at_program_start();
  button_clear_todos = new wxButton(panel, wxID_ANY, "Clear TODOs",
                                    wxPoint(100, 580), wxSize(100, 40));
}

void MainFrame::load_todos_from_file_at_program_start(void) {
  QuickTodo todo;
  todos = todo.get_all_todos("tasks.txt");
  for (unsigned int i = 0; i < todos.size(); i++) { // auto todo : todos) {
    display_todos->Insert(todos[i].get_title(), display_todos->GetCount());
    std::cout << todos[i].get_completed() << std::endl;
    if (todos[i].get_completed() == true) {
      display_todos->Check(i, true);
    }
  }
}

void MainFrame::on_add_todo_button_click(wxCommandEvent &event) {
  wxString title = input_title->GetValue();
  wxString description = input_description->GetValue();
  if (title.IsEmpty() || description.IsEmpty()) {
    SetStatusText("Please enter the required fields.");
  } else {
    display_todos->Insert(title, display_todos->GetCount());
    QuickTodo todo{id, std::string(title.mb_str()), false,
                   std::string(description.mb_str())};
    id++;
    todos.push_back(todo);
    input_title->Clear();
    input_description->Clear();
  }
  input_title->SetFocus();
}

void MainFrame::on_clear_todos_button_click(wxCommandEvent &event) {

  if (display_todos->IsEmpty()) {
    return;
  }
  wxMessageDialog dialog(this, "Delete all tasks?", "Clear",
                         wxYES_NO | wxCANCEL);
  unsigned int result = dialog.ShowModal();
  if (result == wxID_YES) {
    display_todos->Clear();
    todos.clear();
  }
}

void MainFrame::on_main_window_close(wxCloseEvent &event) {
  QuickTodo to_do;
  to_do.write_todos_on_disk("tasks.txt", todos);
  event.Skip();
}

void MainFrame::on_todo_checklistbox_checked(wxCommandEvent &event) {
  std::cout << "Hola amigos" << std::endl;
  std::cout << event.GetInt() << std::endl;

  if (display_todos->IsChecked(event.GetInt())) {
    std::cout << "Item at index " << event.GetInt() << " is been checked."
              << std::endl;
    todos[event.GetInt()].update_task_completed_field(event.GetInt(), true);
  } else {
    std::cout << "Item at index " << event.GetInt() << " is been unchecked."
              << std::endl;
    todos[event.GetInt()].update_task_completed_field(event.GetInt(), false);
  }
}
