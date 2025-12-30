#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

static void checkCompile(GLuint sh, const char* tag)
{
    GLint ok = 0;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetShaderInfoLog(sh, 2048, nullptr, log);
        std::cerr << tag << " compile error:\n" << log << "\n";
    }
}

static void checkLink(GLuint p)
{
    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetProgramInfoLog(p, 2048, nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
    }
}

std::string Shader::loadText(const char* path)
{
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

unsigned int Shader::compile(unsigned int type, const std::string& src)
{
    GLuint sh = glCreateShader(type);
    const char* c = src.c_str();
    glShaderSource(sh, 1, &c, nullptr);
    glCompileShader(sh);
    return sh;
}

unsigned int Shader::link(unsigned int vs, unsigned int tcs, unsigned int tes, unsigned int fs)
{
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, tcs);
    glAttachShader(p, tes);
    glAttachShader(p, fs);
    glLinkProgram(p);
    checkLink(p);
    return p;
}

Shader::Shader(const char* vsPath, const char* tcsPath, const char* tesPath, const char* fsPath)
{
    auto vsSrc = loadText(vsPath);
    auto tcsSrc = loadText(tcsPath);
    auto tesSrc = loadText(tesPath);
    auto fsSrc = loadText(fsPath);

    GLuint vs = compile(GL_VERTEX_SHADER, vsSrc);  checkCompile(vs, "VS");
    GLuint tcs = compile(GL_TESS_CONTROL_SHADER, tcsSrc); checkCompile(tcs, "TCS");
    GLuint tes = compile(GL_TESS_EVALUATION_SHADER, tesSrc); checkCompile(tes, "TES");
    GLuint fs = compile(GL_FRAGMENT_SHADER, fsSrc);  checkCompile(fs, "FS");

    ID = link(vs, tcs, tes, fs);

    glDeleteShader(vs);
    glDeleteShader(tcs);
    glDeleteShader(tes);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    if (ID) glDeleteProgram(ID);
}

void Shader::use() const { glUseProgram(ID); }

void Shader::setMat4(const char* name, const glm::mat4& m) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &m[0][0]);
}

void Shader::setFloat(const char* name, float v) const
{
    glUniform1f(glGetUniformLocation(ID, name), v);
}