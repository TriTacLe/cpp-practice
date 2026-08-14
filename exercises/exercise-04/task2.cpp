// Exercise 4 task 2. gtkmm program that joins a first and last name.
// Written straight against gtkmm-3.0 instead of the course example repo, so
// the layout may differ, but the API is the same.
//
// The point is the signal handling: the button is only sensitive when both
// entries have text, so both signal_changed() signals recompute it.

#include <gtkmm.h>
#include <string>

class NameWindow : public Gtk::Window {
public:
  NameWindow() {
    set_title("Name");
    set_border_width(10);

    grid.set_row_spacing(6);
    grid.set_column_spacing(6);

    first_name_label.set_text("First name");
    last_name_label.set_text("Last name");

    // attach(child, column, row, width, height)
    grid.attach(first_name_label, 0, 0, 1, 1);
    grid.attach(first_name_entry, 1, 0, 1, 1);
    grid.attach(last_name_label, 0, 1, 1, 1);
    grid.attach(last_name_entry, 1, 1, 1, 1);
    grid.attach(button, 0, 2, 2, 1);
    grid.attach(result_label, 0, 3, 2, 1);

    button.set_label("Join");
    button.set_sensitive(false);

    first_name_entry.signal_changed().connect(
        sigc::mem_fun(*this, &NameWindow::update_sensitivity));
    last_name_entry.signal_changed().connect(
        sigc::mem_fun(*this, &NameWindow::update_sensitivity));

    button.signal_clicked().connect(sigc::mem_fun(*this, &NameWindow::on_button_clicked));

    add(grid);
    show_all_children();
  }

private:
  void update_sensitivity() {
    const bool both_filled =
        !first_name_entry.get_text().empty() && !last_name_entry.get_text().empty();
    button.set_sensitive(both_filled);
  }

  void on_button_clicked() {
    const std::string full_name = first_name_entry.get_text() + " " + last_name_entry.get_text();
    result_label.set_text(full_name);
  }

  Gtk::Grid grid;
  Gtk::Label first_name_label, last_name_label, result_label;
  Gtk::Entry first_name_entry, last_name_entry;
  Gtk::Button button;
};

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "no.ntnu.inft2503.exercise4");
  NameWindow window;
  return app->run(window);
}
