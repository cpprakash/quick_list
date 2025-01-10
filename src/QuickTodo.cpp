#include "../headers/QuickTodo.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ********************** Constructor ******************************
QuickTodo::QuickTodo() : m_size{0}, m_title{""}, m_completed{false} {}

QuickTodo::QuickTodo(const unsigned int id, const std::string &title,
                     const bool completed, const std::string &description)
    : m_id{id}, m_size{0}, m_title{title}, m_description{description},
      m_completed{completed} {}
// ********************** Constructor ******************************

// ********************** Public Methods ******************************

const std::string &QuickTodo::get_title(void) { return this->m_title; }
const bool QuickTodo::get_completed(void) { return this->m_completed; }
const unsigned int QuickTodo::get_size(void) { return this->m_size; }

void QuickTodo::write_todos_on_disk(const std::string &file_name,
                                    const std::vector<QuickTodo> todo) {
  std::ofstream todo_file;
  todo_file.open(file_name, std::ios::out);
  if (!todo_file) {
    std::cout << "File could not be opened. Please try later." << std::endl;
    return;
  } else {
    todo_file << todo.size() << std::endl;
    todo_file.close();
    for (std::size_t i = 0; i < todo.size(); i++) {
      this->add_a_todo(file_name, todo[i]);
    }
  }
}

void QuickTodo::delete_a_todo(void) {}

void QuickTodo::delete_all_todos(const std::string &file_name) {}

std::vector<QuickTodo> QuickTodo::get_all_todos(const std::string &file_name) {
  return this->read_text_file(file_name);
}

// ********************** Private Methods ******************************

void QuickTodo::add_a_todo(const std::string &file_name,
                           const QuickTodo &todo) {
  std::ofstream todo_file;
  todo_file.open(file_name, std::ios::out | std::ios::app);
  if (!todo_file) {
    std::cout << "File could not be opened. Please try later." << std::endl;
    return;
  } else {
    todo_file << todo.m_id << std::endl;
    todo_file << todo.m_completed << std::endl;
    std::string title = todo.m_title;
    std::replace(title.begin(), title.end(), ' ', '_');
    todo_file << title << std::endl;
    std::string description = todo.m_description;
    std::replace(description.begin(), description.end(), ' ', '_');
    todo_file << description << std::endl;
  }
  todo_file.close();
}

/**
 * Read the binary file
 */
std::vector<QuickTodo> read_binary_file(const std::string &file_name) {
  if (std::filesystem::exists(file_name)) {
    std::ifstream todo_file;
    todo_file.open(file_name, std::ios::binary | std::ios::in);
    if (!todo_file) {
      std::cout << "File could not be opened. Please try later." << std::endl;
      // return;
    } else {
      unsigned char todo_size[1];
      todo_file.read(reinterpret_cast<char *>(todo_size), sizeof(todo_size));
      std::cout << "total number of todos are " << todo_size << std::endl;
      if (todo_size[0] == 0) {
        std::cout << "No todos at the moment. Please add one." << std::endl;
        // return;
      } else { // there is atleast one todo
      }
    }
  } else {
    std::cout << "File doesnt exists!" << std::endl;
  }
  // TODO remove it
  return std::vector<QuickTodo>();
}
/**
 * Read the text file
 */
std::vector<QuickTodo> QuickTodo::read_text_file(const std::string &file_name) {
  if (std::filesystem::exists(file_name)) {
    std::ifstream istream(file_name);

    std::vector<QuickTodo> todos;
    unsigned int total_todos;
    istream >> total_todos;

    if (total_todos > 0) {
      for (unsigned int i = 0; i < total_todos; i++) {
        unsigned int id;
        bool completed;
        std::string title;
        std::string description;
        istream >> id;
        istream >> completed;
        istream >> title;
        std::replace(title.begin(), title.end(), '_', ' ');
        istream >> description;
        std::replace(description.begin(), description.end(), '_', ' ');
        todos.push_back(QuickTodo{id, title, completed, description});
      }
    }
    return todos;

  } else {
    std::cout << "File doesnt exists!" << std::endl;
    return std::vector<QuickTodo>();
  }
}
