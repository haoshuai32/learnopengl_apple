//
//  Shader.hpp
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>

struct Shader {
    
private:
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader(){}
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

};

#endif /* Shader_hpp */
