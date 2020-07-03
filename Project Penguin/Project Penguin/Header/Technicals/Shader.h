#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    const char* addCurrentDirectory(std::string fileName);
    void checkAndPrintErrors(unsigned int id, bool checkCompilation);

public:
    unsigned int ProgramId;

    Shader(const char* fragmentFileName);
    Shader(const char* vertexFileName, const char* fragmentFileName, const char* geometryFileName = nullptr);

    void changeStatus(bool activate);
    void deleteThisShader();

    void setMat4Uniform(const std::string& name, glm::mat4 value) const;
    void setVec3Uniform(const std::string& name, glm::vec3 value) const;
    void setVec4Uniform(const std::string& name, glm::vec4 value) const;

    void setFloatUniform(const std::string& name, float value) const;
    void setIntUniform(const std::string& name, int value) const;
    void setBoolUniform(const std::string& name, bool value) const;
};

#endif // SHADER_HEADER