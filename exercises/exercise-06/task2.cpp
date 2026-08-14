// Exercise 6 task 2. Small web server on port 8080.
// Written straight against POSIX sockets instead of the course example, so it
// builds without extra libraries on Linux and macOS. Windows needs Winsock.
//
// It handles one request at a time, which is enough for the task.
//
// Test:
//   ./exercise06_task2
//   curl -i http://localhost:8080/
//   curl -i http://localhost:8080/en_side
//   curl -i http://localhost:8080/missing

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

using namespace std;

namespace {

const int port = 8080;

/// Content-Length has to be right, or the browser waits for data that never
/// arrives.
string make_response(const string &status, const string &body) {
  return "HTTP/1.1 " + status + "\r\n" +
         "Content-Type: text/plain; charset=utf-8\r\n" +
         "Content-Length: " + to_string(body.size()) + "\r\n" +
         "Connection: close\r\n" +
         "\r\n" + body;
}

/// Picks the path out of the first request line, so "/en_side" in
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
    return make_response("405 Method Not Allowed", "Only GET is supported");

  const string path = parse_path(request);
  if (path == "/")
    return make_response("200 OK", "This is the main page");
  if (path == "/en_side")
    return make_response("200 OK", "This is a page");
  return make_response("404 Not Found", "Page not found");
}

} // namespace

int main() {
  const int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    cerr << "could not create socket" << endl;
    return 1;
  }

  // Without SO_REUSEADDR, bind fails for a few minutes after a restart.
  int reuse = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_socket, reinterpret_cast<sockaddr *>(&address), sizeof(address)) < 0) {
    cerr << "could not bind to port " << port << endl;
    close(server_socket);
    return 1;
  }

  if (listen(server_socket, 10) < 0) {
    cerr << "listen failed" << endl;
    close(server_socket);
    return 1;
  }

  cout << "Server running on http://localhost:" << port << endl;

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
