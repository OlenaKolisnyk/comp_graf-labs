#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID = 0;

    Shader(const char* vsPath, const char* tcsPath, const char* tesPath, const char* fsPath);
    ~Shader();

    void use() const;

    void setMat4(const char* name, const glm::mat4& m) const;
    void setFloat(const char* name, float v) const;

private:
    static std::string loadText(const char* path);
    static unsigned int compile(unsigned int type, const std::string& src);
    static unsigned int link(unsigned int vs, unsigned int tcs, unsigned int tes, unsigned int fs);
};