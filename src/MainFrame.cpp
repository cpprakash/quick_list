#include <iostream>
#include <string>
#include <vector>

#include "../headers/MainFrame.hpp"
#include "../headers/QuickTodo.hpp"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "TODO Quick List", wxPoint(0, 0)) {
  create_gui_controls();
  button_add->Bind(wxEVT_BUTTON, &MainFrame::on_add_todo_button_click, this);
  button_clear_todos->Bind(wxEVT_BUTTON,
                           &MainFrame::on_clear_todos_button_click, this);
  display_todos->Bind(wxEVT_LEFT_UP,
                      &MainFrame::on_todo_checklist_mouse_selected, this);
  display_todos->Bind(wxEVT_CHECKLISTBOX,
                      &MainFrame::on_todo_checklistbox_checked, this);

  this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::on_main_window_close, this);
  CreateStatusBar();
  SetStatusText("Welcome to this quick todo list.");
  this->SetMinClientSize(wxSize(800, 600));
}

void MainFrame::initialize_box_sizers(void) {
  outer_box_sizer = new wxBoxSizer(wxVERTICAL);
  display_box_sizer = new wxBoxSizer(
      wxVERTICAL); // box sizer for 2 things, first row for listbox and title,
                   // desc, second for the delete all todos button
  input_box_sizer = new wxBoxSizer(wxVERTICAL);
  display_list_box_sizer = new wxBoxSizer(wxHORIZONTAL);
  display_title_description_box_sizer =
      new wxBoxSizer(wxVERTICAL); // for title and description
}

void MainFrame::create_box_sizers(void) {

  // add input controls to the input box sizer
  input_box_sizer->Add(input_title, 0, wxEXPAND | wxALL, 10);
  input_box_sizer->Add(input_description, 0, wxEXPAND | wxALL, 10);
  input_box_sizer->Add(button_add, 0, wxALL, 10);

  // add input controls to the input box sizer
  display_title_description_box_sizer->Add(display_title, 0, wxEXPAND | wxALL,
                                           10);
  display_title_description_box_sizer->Add(display_description, 0,
                                           wxEXPAND | wxALL, 10);

  // add list box controls and title, descirption sizer to the this box sizer
  display_list_box_sizer->Add(display_todos, 0, wxALL, 10);
  display_list_box_sizer->Add(display_title_description_box_sizer, 0,
                              wxEXPAND | wxALL, 10);
  // Add display related controls to its sizer
  display_box_sizer->Add(display_list_box_sizer, 0, wxALL, 10);
  display_box_sizer->Add(button_clear_todos, 0, wxALL, 10);

  outer_box_sizer->Add(input_box_sizer, 1, wxEXPAND | wxALL, FromDIP(10));
  outer_box_sizer->Add(display_box_sizer, 2, wxEXPAND | wxALL, FromDIP(10));
}

void MainFrame::create_gui_controls(void) {

  initialize_box_sizers(); // initalize all box sizers

  // input field for title
  input_title =
      new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(600, 35));
  // input field for description
  input_description =
      new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 125), wxSize(600, 35),
                     wxTE_READONLY || wxTE_MULTILINE || wxTE_RICH || wxHSCROLL);
  // button to add a new todo from above fields
  button_add = new wxButton(this, wxID_ANY, "Add TODO", wxPoint(10, 170),
                            wxSize(100, 40));

  // displaying a saved todo
  display_todos =
      new wxCheckListBox(this, wxID_ANY, wxPoint(10, 10), wxSize(200, 350));

  /** adding two static texts to display the info about selected todo */
  display_title = new wxStaticText(this, wxID_ANY, "Title: ", wxPoint(200, 10),
                                   wxSize(500, 40));
  display_description = new wxStaticText(
      this, wxID_ANY, "Description: ", wxPoint(220, 60), wxSize(500, 300),
      wxTE_READONLY || wxTE_MULTILINE || wxTE_RICH || wxHSCROLL);

  button_clear_todos = new wxButton(this, wxID_ANY, "Clear TODOs",
                                    wxPoint(10, 10), wxSize(100, 40));

  this->create_box_sizers(); // create all box sizers
  this->SetSizerAndFit(outer_box_sizer);
  load_todos_from_file_at_program_start(); // load all todos at the program
                                           // start
}

/***
 * function to load all todos from a text file tasks.txt
 */
void MainFrame::load_todos_from_file_at_program_start(void) {
  QuickTodo todo;
  todos = todo.get_all_todos("tasks.txt");
  for (unsigned int i = 0; i < todos.size(); i++) {
    display_todos->Insert(todos[i].get_title(), display_todos->GetCount());
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

/***
 * Event gets fired when the window is closing
 * this is where we write the tasks to the disk in the file
 */
void MainFrame::on_main_window_close(wxCloseEvent &event) {
  QuickTodo to_do;
  to_do.write_todos_on_disk("tasks.txt", todos);
  event.Skip();
}

/***
 * function to handle the checkbox checked event in the listbox
 */
void MainFrame::on_todo_checklistbox_checked(wxCommandEvent &event) {
  if (display_todos->IsChecked(event.GetInt())) {
    todos[event.GetInt()].update_task_completed_field(event.GetInt(), true);
  } else {
    todos[event.GetInt()].update_task_completed_field(event.GetInt(), false);
  }
}

/***
 * Function to set the text for the title and description
 * based on the selected item from the list
 */
void MainFrame::on_todo_checklist_mouse_selected(wxMouseEvent &event) {
  const unsigned int index = display_todos->GetSelection();
  display_title->SetLabel("Title: " + todos[index].get_title());
  display_description->SetLabel("Description: " +
                                todos[index].get_description());
  // display_description->Wrap(20);
  event.Skip();
}
