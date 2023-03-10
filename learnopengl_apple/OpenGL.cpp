//
//  OpenGL.cpp
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

#include "OpenGL.hpp"
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

OpenGL::OpenGL(const char* vertexPath,
               const char* fragmentPath) {
    shader = new Shader(vertexPath,fragmentPath);
}

OpenGL::~OpenGL() {
    delete shader;
    delete texture1;
    delete texture2;
}

// set up vertex data (and buffer(s)) and configure vertex attributes
void OpenGL::vertex(const float *vertices, int vertices_count,
                    const int *indices, int indices_count) {
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_count, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices_count, indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
}

void OpenGL::textureImage(const char* texturePath1,
                          const char* texturePath2) {
    texture1 = new TextureImage(texturePath1);
    texture2 = new TextureImage(texturePath2);
    
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader->use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
//    glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);
    // or set it via the texture class
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
}

void OpenGL::update() {
    texture1->active_bind(GL_TEXTURE0);
    texture2->active_bind(GL_TEXTURE1);
}

void OpenGL::render() {
    // render the triangle
    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void OpenGL::delete_vertex() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
                   const float *vertices,int vertices_count,
                   const int *indices, int indices_count) {
    OpenGLPtr(ptr, objc);
    ptr->vertex(vertices, vertices_count, indices,indices_count);
}

void OpenGL_texture_image(OpenGLClass objc,
                          const char* texturePath1, const char* texturePath2) {
    OpenGLPtr(ptr, objc);
    ptr->textureImage(texturePath1, texturePath2);
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
