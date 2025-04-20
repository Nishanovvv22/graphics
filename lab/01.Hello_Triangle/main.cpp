///// main.cpp
///// OpenGL 3+, GLSL 1.20, GLEW, GLFW3

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
/// Shader-related variables and functions
////////////////////////////////////////////////////////////////////////////////
GLuint  program;
GLint   loc_a_position;
GLint   loc_a_color;

GLuint  position_buffer;
GLuint  color_buffer;

GLuint create_shader_from_file(const std::string& filename, GLuint shader_type);
void init_shader_program();
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Rendering-related variables and functions
////////////////////////////////////////////////////////////////////////////////
GLfloat g_position[] = {
  0.5f,  0.5f,  0.0f,
 -0.5f, -0.5f,  0.0f,
  0.5f, -0.5f,  0.0f,
};

GLfloat g_color[] = {
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
};

void init_buffer_objects();
void render_object();
////////////////////////////////////////////////////////////////////////////////

GLuint create_shader_from_file(const std::string& filename, GLuint shader_type)
{
  GLuint shader = glCreateShader(shader_type);

  std::ifstream shader_file(filename.c_str());
  std::string shader_string;
  shader_string.assign(
    (std::istreambuf_iterator<char>(shader_file)),
    std::istreambuf_iterator<char>());

  if (shader_string.compare(0, 3, "\xEF\xBB\xBF") == 0)
  {
    std::cout << "Shader code (" << filename << ") is written in UTF-8 with BOM" << std::endl;
    std::cout << "  Temporarily removing BOM before compiling." << std::endl;
    shader_string.erase(0, 3);
  }

  const GLchar* shader_src = shader_string.c_str();
  glShaderSource(shader, 1, &shader_src, NULL);
  glCompileShader(shader);

  GLint is_compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled != GL_TRUE)
  {
    std::cout << "Shader COMPILE error: " << std::endl;

    GLint buf_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_len);

    std::string log_string(1 + buf_len, '\0');
    glGetShaderInfoLog(shader, buf_len, 0, (GLchar *)log_string.c_str());

    std::cout << "error_log: " << log_string << std::endl;

    glDeleteShader(shader);
    shader = 0;
  }

  return shader;
}

void init_shader_program()
{
  GLuint vertex_shader = create_shader_from_file("./shader/vertex.glsl", GL_VERTEX_SHADER);
  std::cout << "vertex_shader id: " << vertex_shader << std::endl;
  assert(vertex_shader != 0);

  GLuint fragment_shader = create_shader_from_file("./shader/fragment.glsl", GL_FRAGMENT_SHADER);
  std::cout << "fragment_shader id: " << fragment_shader << std::endl;
  assert(fragment_shader != 0);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint is_linked;
  glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
  if (is_linked != GL_TRUE)
  {
    std::cout << "Shader LINK error: " << std::endl;

    GLint buf_len;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buf_len);

    std::string log_string(1 + buf_len, '\0');
    glGetProgramInfoLog(program, buf_len, 0, (GLchar *)log_string.c_str());

    std::cout << "error_log: " << log_string << std::endl;

    glDeleteProgram(program);
    program = 0;
  }

  std::cout << "program id: " << program << std::endl;
  assert(program != 0);

  loc_a_position = glGetAttribLocation(program, "a_position");
  loc_a_color = glGetAttribLocation(program, "a_color");
}

void init_buffer_objects()
{
  glGenBuffers(1, &position_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_position), g_position, GL_STATIC_DRAW);

  glGenBuffers(1, &color_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color), g_color, GL_STATIC_DRAW);
}

void render_object()
{
  glUseProgram(program);

  glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
  glEnableVertexAttribArray(loc_a_position);
  glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glEnableVertexAttribArray(loc_a_color);
  glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(loc_a_position);
  glDisableVertexAttribArray(loc_a_color);

  glUseProgram(0);
}

int main(void)
{
  GLFWwindow* window;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(500, 500, "Hello Triangle", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    std::cout << "GLEW Init Error!" << std::endl;

  std::cout << glGetString(GL_VERSION) << std::endl;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  init_shader_program();
  init_buffer_objects();

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_object();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
