#include "shaderClass.h"



std::string readShaderFromFile(const char* filename)
{
    std::ifstream shaderFile(filename);
    if (!shaderFile.is_open())
    {
        std::cout << "Unable to open file: " << filename << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    std::string content = shaderStream.str();
    if (content.empty())
    {
        std::cout << "File content is empty: " << filename << std::endl;
        return "";
    }

    return content;
}

//Конструктор, який створює шейдерну програму з  шейдерів
Shader::Shader(const char* vertsFile, const char* fragmFile)
{
    ID = 0;
    isValid = false;
    //зчитування vertexFile і fragmFile і зберігання в рядки
    std::string vertCode = readShaderFromFile(vertsFile);
    std::string fragmCode = readShaderFromFile(fragmFile);

    if (vertCode.empty() || fragmCode.empty())
    {
        std::cout << "Failed to load shader files." << std::endl;
        return;
    }
    
    //Перетворення вихідних рядків шейдера на масиви символів
    //std::string у const char*
    const GLchar* vertexSource = vertCode.c_str();
    
    const GLchar* fragmentSource = fragmCode.c_str();

    // створення і компіляція вершинного шейдера
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Передача GLSL - коду у шейдер
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    // Компіляція шейдера
    glCompileShader(vertexShader);

    // Перевірка помилок компіляції вершинного шейдера
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

        std::cout << "Vertex shader compilation failed:\n"
            << infoLog << std::endl;

        glDeleteShader(vertexShader);
        return;

    }
    
    // створення і компіляція фрагментного шейдера
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Перевірка помилок компіляції фрагментного шейдера
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

        std::cout << "Fragment shader compilation failed:\n"
            << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return;
    }

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);

        std::cout << "Program linking failed:\n"
            << infoLog << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(ID);

        ID = 0;
        isValid = false;

        return;
    }

    // Якщо лінкування пройшло успішно,
    // shader object видаляємо
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Шейдерна програма успішно створена
    isValid = true;
}

// активація шейдерної програми
void Shader::Use() const
{
    if (isValid)
        glUseProgram(ID);
}


//  видалення шейдерної програми
void Shader::Delete() const
{
    if (ID != 0)
        glDeleteProgram(ID);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    else
        std::cout << "Uniform not found: " << name << std::endl;
}