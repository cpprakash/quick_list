#ifndef __HEADER_MAINFRAME__
#define __HEADER_MAINFRAME__

#include <wx/wx.h>

#include "QuickTodo.hpp"
#include <vector>

class MainFrame : public wxFrame {
private:
  wxPanel *panel;
  wxStaticText *header;
  wxTextCtrl *input_title;
  wxTextCtrl *input_description;
  wxButton *button_add;
  wxCheckListBox *display_todos;
  wxButton *button_clear_todos;

  std::vector<QuickTodo> todos;
  unsigned int id = 0;

public:
  MainFrame();

private:
  void OnHello(wxCommandEvent &event);
  void on_add_todo_button_click(wxCommandEvent &event);
  void on_clear_todos_button_click(wxCommandEvent &event);
  void on_main_window_close(wxCloseEvent &event);
  void create_gui_controls(void);
  void load_todos_from_file_at_program_start(void);
  void on_todo_checklistbox_checked(wxCommandEvent &event);
};

#endif