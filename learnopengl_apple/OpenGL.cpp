//
//  OpenGL.cpp
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

#include "OpenGL.hpp"
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

OpenGL::OpenGL(const char* vertexPath, const char* fragmentPath) {
    shader = new Shader(vertexPath,fragmentPath);
}

OpenGL::~OpenGL() {
    delete shader;
}

void OpenGL::vertex(const float *vertices, int vertices_count) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_count, vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//         glBindVertexArray(0);
    
}

void OpenGL::update() {
    
}

void OpenGL::render() {
    // render the triangle
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OpenGL::delete_vertex() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

#include "OpenGLClass.h"

#define OpenGLPtr(x,y) OpenGL* x = (OpenGL*)y

OpenGLClass OpenGL_init(const char* vertexPath, const char* fragmentPath) {
    return new OpenGL(vertexPath, fragmentPath);
}

void OpenGL_deinit(OpenGLClass objc) {
    delete objc;
}

void OpenGL_vertex(OpenGLClass objc,
                   const float *vertices,int vertices_count) {
    OpenGLPtr(ptr, objc);
    ptr->vertex(vertices, vertices_count);
}

void OpenGL_update(OpenGLClass objc) {
    OpenGLPtr(ptr, objc);
    ptr->update();
}
void OpenGL_render(OpenGLClass objc) {
    OpenGLPtr(ptr, objc);
    ptr->render();
}

void OpenGL_delete_vertex(OpenGLClass objc) {
    OpenGLPtr(ptr, objc);
    ptr->delete_vertex();
}

void OpenGL_clear_color(){
    glClearColor(0.2f, 0.3f, 1.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
