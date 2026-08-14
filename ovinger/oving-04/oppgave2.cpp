// Øving 4, oppgave 2: gtkmm-program som slår sammen fornavn og etternavn.
//
// Oppgaven sier "ta utgangspunkt i gitlab.com/ntnu-iini4003/gtkmm-example".
// Denne fila bruker ikke det repoet, den er skrevet rett mot gtkmm-3.0. Layout
// og navn kan derfor avvike fra kursets eksempel, men API-et er det samme.
//
// Poenget i oppgaven er signal-håndteringen: knappen skal bare være sensitiv
// når begge feltene har innhold, så vi kobler oss på signal_changed() i begge
// Gtk::Entry og regner ut sensitiviteten på nytt hver gang.

#include <gtkmm.h>
#include <string>

class NameWindow : public Gtk::Window {
public:
  NameWindow() {
    set_title("Navn");
    set_border_width(10);

    grid.set_row_spacing(6);
    grid.set_column_spacing(6);

    first_name_label.set_text("Fornavn");
    last_name_label.set_text("Etternavn");

    // attach(child, kolonne, rad, bredde, høyde)
    grid.attach(first_name_label, 0, 0, 1, 1);
    grid.attach(first_name_entry, 1, 0, 1, 1);
    grid.attach(last_name_label, 0, 1, 1, 1);
    grid.attach(last_name_entry, 1, 1, 1, 1);
    grid.attach(button, 0, 2, 2, 1);
    grid.attach(result_label, 0, 3, 2, 1);

    button.set_label("Slå sammen");
    button.set_sensitive(false); // ingenting er skrevet inn ennå

    // Hver gang et felt endres, regner vi ut om knappen skal være aktiv.
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
  auto app = Gtk::Application::create(argc, argv, "no.ntnu.inft2503.oving4");
  NameWindow window;
  return app->run(window);
}
