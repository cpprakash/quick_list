#ifndef __HEADER_MAINFRAME__
#define __HEADER_MAINFRAME__

#include <wx/wx.h>

#include "QuickTodo.hpp"
#include <vector>

class MainFrame : public wxFrame {
private:
  wxStaticText *header;
  wxTextCtrl *input_title;
  wxTextCtrl *input_description;
  wxButton *button_add;
  wxCheckListBox *display_todos;
  wxButton *button_clear_todos;

  wxStaticText *display_title;
  wxStaticText *display_description;

  wxBoxSizer *outer_box_sizer; // outer box sizer
  wxBoxSizer *display_box_sizer;
  wxBoxSizer *input_box_sizer;
  wxBoxSizer *display_list_box_sizer;
  wxBoxSizer *display_title_description_box_sizer;

  wxBoxSizer *edit_todo_sizer;

  wxTextCtrl *title_text;              // editable text title
  wxTextCtrl *title_desc;              // editable text desc
  wxButton *button_edit_todo;          // update the selected todo
  wxButton *button_edit_cancel;        // cancel the edit operation
  wxButton *button_delete_single_todo; // delete the selecte todo

  wxPanel *edit_panel;

  std::vector<QuickTodo> todos;
  unsigned int id = 0;

public:
  MainFrame();

private:
  void on_add_todo_button_click(wxCommandEvent &event);
  void on_clear_todos_button_click(wxCommandEvent &event);
  void on_main_window_close(wxCloseEvent &event);
  void create_gui_controls(void);
  void load_todos_from_file_at_program_start(void);
  void on_todo_checklistbox_checked(wxCommandEvent &event);
  void on_todo_checklist_mouse_selected(wxMouseEvent &event);
  void initialize_box_sizers(void);
  void create_box_sizers(void);
  void on_todo_checklist_double_click(wxMouseEvent &event);

  void hide_controls_for_edit(void);
  void restore_controls_after_edit(void);
  void on_button_edit_todo_click(wxCommandEvent &event);
  void on_button_edit_cancel_click(wxCommandEvent &event);
  void on_button_delete_single_todo_click(wxCommandEvent &event);
};

#endif