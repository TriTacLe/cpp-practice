// Exercise 10. Replaces main.cpp in gitlab.com/ntnu-iini4003/game.
// The changes are in World and in Application::start().
// Not compiled here: sfml, glm and bullet are not installed on this machine.

#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>

#include <btBulletDynamicsCommon.h>

#include <chrono>

#include <iostream>

extern "C" {
// Implementation is in glut_shapes.c
void glutSolidCube(GLdouble size);
}

class Ground {
  btStaticPlaneShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Ground() : shape(btVector3(0.0, 1.0, 0.0), 0.0), body(0.0, &motion_state, &shape) {
    body.setRollingFriction(0.1);
    body.setRestitution(0.8);
  }

  void draw() {
    auto position = body.getCenterOfMassPosition();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(position.x() - 5.0, position.y(), position.z() - 5.0);
    glVertex3f(position.x() - 5.0, position.y(), position.z() + 5.0);
    glVertex3f(position.x() + 5.0, position.y(), position.z() - 5.0);
    glVertex3f(position.x() + 5.0, position.y(), position.z() + 5.0);
    glEnd();
  }
};

class Sphere {
  btSphereShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Sphere() : shape(btScalar(0.1)), body(1.0, &motion_state, &shape) {
    auto mass = 1.0 / body.getInvMass();

    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);

    body.setMassProps(mass, inertia);
    body.setRollingFriction(0.2);
    body.setRestitution(0.8);
  }

  void draw() {
    glPushMatrix();
    auto position = body.getCenterOfMassPosition();
    glTranslatef(position.x(), position.y(), position.z());
    glColor3f(0.0, 0.0, 1.0);
    auto quadric = gluNewQuadric();
    gluSphere(quadric, shape.getRadius(), 32, 32);
    gluDeleteQuadric(quadric);
    glPopMatrix();
  }
};

class Cube {
  btBoxShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Cube() : shape({0.1, 0.1, 0.1}), body(1.0, &motion_state, &shape) {
    auto mass = 1.0 / body.getInvMass();

    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);

    body.setMassProps(mass, inertia);
    body.setFriction(0.5);
    body.setRollingFriction(0.1);
    body.setRestitution(0.2);
  }

  void draw() {
    glPushMatrix();
    auto position = body.getCenterOfMassPosition();
    glTranslatef(position.x(), position.y(), position.z());
    auto orientation = body.getOrientation();
    auto axis = orientation.getAxis().normalize();
    glRotatef(orientation.getAngle() * 180.0 / M_PI, axis.x(), axis.y(), axis.z());
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(0.2);
    glPopMatrix();
  }
};

class World {
  btDefaultCollisionConfiguration collision_configuration;
  btCollisionDispatcher dispatcher;
  btDbvtBroadphase broadphase;
  btSequentialImpulseConstraintSolver solver;

  // The ball stays out of the physics until it is dropped.
  bool ball_in_world = false;
  btVector3 ball_position{0.9, 3.0, 0.0};

  static void place(btRigidBody &body, const btVector3 &position) {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(position);
    body.setCenterOfMassTransform(transform);
    body.setLinearVelocity(btVector3(0.0, 0.0, 0.0));
    body.setAngularVelocity(btVector3(0.0, 0.0, 0.0));
    body.clearForces();
    body.activate();
  }

public:
  btDiscreteDynamicsWorld dynamics;

  Ground ground;
  Sphere ground_sphere, falling_sphere;
  std::vector<Cube> cubes;

  World() : dispatcher(&collision_configuration),
            dynamics(&dispatcher, &broadphase, &solver, &collision_configuration),
            cubes(6) {
    dynamics.setGravity(btVector3(0, -10.0, 0));

    // Add objects to the physics engine
    dynamics.addRigidBody(&ground.body);
    dynamics.addRigidBody(&ground_sphere.body);
    for (auto &cube : cubes)
      dynamics.addRigidBody(&cube.body);

    restart();
  }

  // Puts everything back to the start position.
  void restart() {
    place(ground.body, btVector3(0.0, 0.0, 0.0));
    place(ground_sphere.body, btVector3(1.0, 0.1, 0.0));

    place(cubes[0].body, btVector3(-1.0, 0.1, -0.2));
    place(cubes[1].body, btVector3(-1.0, 0.1, 0.0));
    place(cubes[2].body, btVector3(-1.0, 0.1, 0.2));
    place(cubes[3].body, btVector3(-1.0, 0.3, -0.1));
    place(cubes[4].body, btVector3(-1.0, 0.3, 0.1));
    place(cubes[5].body, btVector3(-1.0, 0.5, 0.0));

    hold_ball();
  }

  // Takes the ball out of the physics and holds it where the user put it.
  void hold_ball() {
    if (ball_in_world) {
      dynamics.removeRigidBody(&falling_sphere.body);
      ball_in_world = false;
    }
    place(falling_sphere.body, ball_position);
  }

  void drop_ball() {
    if (ball_in_world)
      return;
    place(falling_sphere.body, ball_position);
    dynamics.addRigidBody(&falling_sphere.body);
    ball_in_world = true;
  }

  bool ball_dropped() const {
    return ball_in_world;
  }

  // Moves the ball while it is held. Does nothing once it is dropped.
  void set_ball_position(float horizontal, float vertical) {
    ball_position = btVector3(horizontal, vertical, 0.0);
    if (!ball_in_world)
      place(falling_sphere.body, ball_position);
  }

  void draw() {
    ground.draw();
    ground_sphere.draw();
    falling_sphere.draw();
    for (auto &cube : cubes)
      cube.draw();
  }
};

class Application {
  sf::RenderWindow window;

  World world;

public:
  Application() : window(sf::VideoMode({800, 600}), "SFML Example", sf::State::Windowed, sf::ContextSettings{24, 8}) {
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    // Various settings
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {-3.0, 4.0, 0.0, 1.0};
    GLfloat spot_direction[] = {1.0, -1.0, -0.5};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    glEnable(GL_COLOR_MATERIAL);

    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    // ImGui settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    if (!ImGui::SFML::Init(window))
      throw "Failed to initialize Imgui::SFML";
  }

  void start() {
    glm::vec3 camera(0.0, 1.0, 6.0);

    sf::Clock delta_clock;

    // These have to live outside the loop. The original declared them inside
    // it without a value, so the slider lost its position every frame.
    float horizontal_position = 0.9;
    float vertical_position = 3.0;

    auto last_time = std::chrono::system_clock::now();
    bool running = true;
    while (running) {
      // Handle events
      while (auto event = window.pollEvent()) {
        ImGui::SFML::ProcessEvent(window, *event);
        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
            running = false;
          }
        } else if (event->is<sf::Event::Closed>()) {
          window.close();
          running = false;
        }
      }

      ImGui::SFML::Update(window, delta_clock.restart());

      ImGui::Begin("ImGui");
      if (ImGui::Button("Restart game")) {
        horizontal_position = 0.9;
        vertical_position = 3.0;
        world.set_ball_position(horizontal_position, vertical_position);
        world.restart();
      }
      if (ImGui::Button("Drop ball")) {
        world.drop_ball();
      }
      // Sliders are only active until the ball is dropped.
      ImGui::BeginDisabled(world.ball_dropped());
      if (ImGui::SliderFloat("Horizontal ball position", &horizontal_position, -3.0, 3.0)) {
        world.set_ball_position(horizontal_position, vertical_position);
      }
      if (ImGui::VSliderFloat("Vertical ball position", {20, 100}, &vertical_position, 0.2, 5.0)) {
        world.set_ball_position(horizontal_position, vertical_position);
      }
      ImGui::EndDisabled();
      ImGui::End();

      // Draw
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      gluLookAt(camera.x, camera.y, camera.z, // Camera position in World Space
                camera.x, camera.y, 0.0,      // Camera looks towards this position
                0.0, 1.0, 0.0);               // Up

      auto time = std::chrono::system_clock::now();
      world.dynamics.stepSimulation(std::chrono::duration<float>(time - last_time).count());
      last_time = time;

      world.draw();

      window.pushGLStates();
      ImGui::SFML::Render(window);
      window.popGLStates();

      // Swap buffer (show result)
      window.display();
    }
    ImGui::SFML::Shutdown();
  }
};

int main() {
  Application application;
  application.start();
}
