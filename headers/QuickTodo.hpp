#ifndef __HEADER_QUICKTODO__
#define __HEADER_QUICKTODO__

#include <string>
#include <vector>

class QuickTodo {
private:
  unsigned int m_id;
  unsigned int m_size;
  std::string m_title;
  std::string m_description;
  bool m_completed;

public:
  QuickTodo();
  QuickTodo(const unsigned int id, const std::string &title,
            const bool completed, const std::string &description);
  const std::string &get_title(void);
  const std::string &get_description(void);
  const bool get_completed(void);
  const unsigned int get_size(void);
  void write_todos_on_disk(const std::string &file_name,
                           const std::vector<QuickTodo> todo);
  void delete_a_todo(void);
  void delete_all_todos(const std::string &file_name);
  std::vector<QuickTodo> get_all_todos(const std::string &file_name);
  void update_task_completed_field(const unsigned int index, const bool value);

  void set_title(std::string title);
  void set_completed(bool completed);
  void set_description(std::string description);

private:
  void add_a_todo(const std::string &file_name, const QuickTodo &todo);
  std::vector<QuickTodo> read_binary_file(const std::string &file_name);
  std::vector<QuickTodo> read_text_file(const std::string &file_name);
};

#endif