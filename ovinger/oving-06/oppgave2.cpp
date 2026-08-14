// Øving 6, oppgave 2: enkel web-server på port 8080.
//
// Oppgaven sier "ta utgangspunkt i example6". Denne fila bruker ikke det
// eksempelet, den er skrevet rett mot POSIX-sockets, så den kompilerer uten
// eksterne bibliotek på Linux og macOS. Windows trenger Winsock i stedet.
// Struktur og API-kall vil derfor avvike fra kursets eksempel.
//
// Serveren tar én forespørsel om gangen. Det holder for oppgaven, men er ikke
// noe man ville satt i produksjon.
//
// Test:
//   ./oving06_oppgave2
//   curl -i http://localhost:8080/
//   curl -i http://localhost:8080/en_side
//   curl -i http://localhost:8080/finnes_ikke
//
// Avslutt med Ctrl+C.

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

using namespace std;

namespace {

const int port = 8080;

/// Bygger en komplett HTTP-respons. Content-Length må stemme, ellers venter
/// nettleseren på data som aldri kommer.
string make_response(const string &status, const string &body) {
  return "HTTP/1.1 " + status + "\r\n" +
         "Content-Type: text/plain; charset=utf-8\r\n" +
         "Content-Length: " + to_string(body.size()) + "\r\n" +
         "Connection: close\r\n" +
         "\r\n" + body;
}

/// Plukker ut stien fra første linje i forespørselen, altså "/en_side" i
/// "GET /en_side HTTP/1.1".
string parse_path(const string &request) {
  const size_t start = request.find(' ');
  if (start == string::npos)
    return "";
  const size_t end = request.find(' ', start + 1);
  if (end == string::npos)
    return "";
  return request.substr(start + 1, end - start - 1);
}

string handle_request(const string &request) {
  if (request.rfind("GET ", 0) != 0)
    return make_response("405 Method Not Allowed", "Bare GET er støttet");

  const string path = parse_path(request);
  if (path == "/")
    return make_response("200 OK", "Dette er hovedsiden");
  if (path == "/en_side")
    return make_response("200 OK", "Dette er en side");
  return make_response("404 Not Found", "Fant ikke siden");
}

} // namespace

int main() {
  const int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    cerr << "kunne ikke lage socket" << endl;
    return 1;
  }

  // Uten SO_REUSEADDR nekter bind i noen minutter etter at serveren er stoppet.
  int reuse = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_socket, reinterpret_cast<sockaddr *>(&address), sizeof(address)) < 0) {
    cerr << "kunne ikke binde til port " << port << endl;
    close(server_socket);
    return 1;
  }

  if (listen(server_socket, 10) < 0) {
    cerr << "listen feilet" << endl;
    close(server_socket);
    return 1;
  }

  cout << "Serveren kjører på http://localhost:" << port << endl;

  while (true) {
    const int client_socket = accept(server_socket, nullptr, nullptr);
    if (client_socket < 0)
      continue;

    char buffer[4096];
    const ssize_t read_bytes = read(client_socket, buffer, sizeof(buffer) - 1);
    if (read_bytes > 0) {
      buffer[read_bytes] = '\0';
      const string response = handle_request(string(buffer));
      ssize_t written = 0;
      while (written < static_cast<ssize_t>(response.size())) {
        const ssize_t n = write(client_socket, response.data() + written,
                                response.size() - static_cast<size_t>(written));
        if (n <= 0)
          break;
        written += n;
      }
    }

    close(client_socket);
  }
}
