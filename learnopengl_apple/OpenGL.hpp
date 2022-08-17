//
//  OpenGL.hpp
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

#ifndef OpenGL_hpp
#define OpenGL_hpp

#include <stdio.h>
#include "Shader.hpp"
#include "TextureImage.hpp"

class OpenGL {
private:
    Shader *shader;
    TextureImage *texture1;
    TextureImage *texture2;
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int EBO = 0;
public:
    OpenGL(const char* vertexPath, const char* fragmentPath);
    ~OpenGL();
    void vertex(const float *vertices, int vertices_count,
                const int *indices, int indices_count);
    void textureImage(const char* texturePath1,
                      const char* texturePath2);
    void update();
    void render();
    void delete_vertex();
};

#endif /* OpenGL_hpp */
