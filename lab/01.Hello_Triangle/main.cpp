#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

// Include model data
#include "models/cube_triangle_soup.hpp"
#include "models/avocado_triangle_soup.hpp"
#include "models/donut_triangle_soup.hpp"
#include "models/cube_vlist_triangles.hpp"
#include "models/avocado_vlist_triangles.hpp"
#include "models/donut_vlist_triangles.hpp"

// Shader and buffer variables
GLuint program;
GLint loc_a_position;
GLint loc_a_color;
GLuint position_buffer = 0;
GLuint color_buffer = 0;
GLuint index_buffer = 0;

// Model and render mode enums
enum MeshModel { kCube, kAvocado, kDonut };
enum MeshType { kTriangleSoup, kVlistTriangles };

MeshModel g_mesh_model = kCube;
MeshType g_mesh_type = kTriangleSoup;

// Read shader file
std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Compile shader from file
GLuint create_shader_from_file(const std::string& filename, GLenum shader_type) {
    std::string shader_source = read_file(filename);
    const char* source_cstr = shader_source.c_str();

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source_cstr, nullptr);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "Shader compilation error in " << filename << ":\n" << log << std::endl;
        exit(1);
    }

    return shader;
}

// Initialize shader program
void init_shader_program() {
    GLuint vertex_shader = create_shader_from_file("shader/vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragment_shader = create_shader_from_file("shader/fragment.glsl", GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cerr << "Shader linking error:\n" << log << std::endl;
        exit(1);
    }

    glUseProgram(program);

    loc_a_position = glGetAttribLocation(program, "a_position");
    loc_a_color = glGetAttribLocation(program, "a_color");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

// Upload data to GPU buffers
void update_buffer_objects() {
    if (position_buffer) glDeleteBuffers(1, &position_buffer);
    if (color_buffer) glDeleteBuffers(1, &color_buffer);
    if (index_buffer) glDeleteBuffers(1, &index_buffer);

    glGenBuffers(1, &position_buffer);
    glGenBuffers(1, &color_buffer);

    if (g_mesh_type == kTriangleSoup) {
        const float* positions = nullptr;
        const float* colors = nullptr;
        int vertex_count = 0;

        switch (g_mesh_model) {
            case kCube:
                positions = cube_triangle_soup::positions;
                colors = cube_triangle_soup::colors;
                vertex_count = cube_triangle_soup::num_vertices;
                break;
            case kAvocado:
                positions = avocado_triangle_soup::positions;
                colors = avocado_triangle_soup::colors;
                vertex_count = avocado_triangle_soup::num_vertices;
                break;
            case kDonut:
                positions = donut_triangle_soup::positions;
                colors = donut_triangle_soup::colors;
                vertex_count = donut_triangle_soup::num_vertices;
                break;
        }

        glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), positions, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), colors, GL_STATIC_DRAW);
    } else {
        const float* positions = nullptr;
        const float* colors = nullptr;
        const unsigned int* indices = nullptr;
        int vertex_count = 0;
        int index_count = 0;

        glGenBuffers(1, &index_buffer);

        switch (g_mesh_model) {
            case kCube:
                positions = cube_vlist::positions;
                colors = cube_vlist::colors;
                indices = cube_vlist::indices;
                vertex_count = cube_vlist::num_vertices;
                index_count = cube_vlist::num_indices;
                break;
            case kAvocado:
                positions = avocado_vlist::positions;
                colors = avocado_vlist::colors;
                indices = avocado_vlist::indices;
                vertex_count = avocado_vlist::num_vertices;
                index_count = avocado_vlist::num_indices;
                break;
            case kDonut:
                positions = donut_vlist::positions;
                colors = donut_vlist::colors;
                indices = donut_vlist::indices;
                vertex_count = donut_vlist::num_vertices;
                index_count = donut_vlist::num_indices;
                break;
        }

        glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), positions, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), colors, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }
}

// Render the selected object
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(loc_a_color);
    glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    if (g_mesh_type == kTriangleSoup) {
        int count = 0;
        switch (g_mesh_model) {
            case kCube: count = cube_triangle_soup::num_vertices; break;
            case kAvocado: count = avocado_triangle_soup::num_vertices; break;
            case kDonut: count = donut_triangle_soup::num_vertices; break;
        }
        glDrawArrays(GL_TRIANGLES, 0, count);
    } else {
        int count = 0;
        switch (g_mesh_model) {
            case kCube: count = cube_vlist::num_indices; break;
            case kAvocado: count = avocado_vlist::num_indices; break;
            case kDonut: count = donut_vlist::num_indices; break;
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_color);
}

// Handle key input for model/mode switching
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;

    switch (key) {
        case GLFW_KEY_1: g_mesh_model = kCube; g_mesh_type = kTriangleSoup; break;
        case GLFW_KEY_2: g_mesh_model = kAvocado; g_mesh_type = kTriangleSoup; break;
        case GLFW_KEY_3: g_mesh_model = kDonut; g_mesh_type = kTriangleSoup; break;
        case GLFW_KEY_4: g_mesh_model = kCube; g_mesh_type = kVlistTriangles; break;
        case GLFW_KEY_5: g_mesh_model = kAvocado; g_mesh_type = kVlistTriangles; break;
        case GLFW_KEY_6: g_mesh_model = kDonut; g_mesh_type = kVlistTriangles; break;
    }

    update_buffer_objects();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "TriangleMesh", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, key_callback);

    init_shader_program();
    update_buffer_objects();

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
