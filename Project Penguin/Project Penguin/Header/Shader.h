#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    void checkAndPrintErrors(unsigned int id, bool checkCompilation);
    const char* addCurrentDirectory(std::string fileName);

public:
    unsigned int ProgramId;

    // constructor to read and build the shader
    Shader(const char* vertexFileName, const char* fragmentFileName, const char* geometryFileName = nullptr);

    // (de-)activate the shader
    void changeStatus(bool activate);

    // utility uniform functions
    void setBoolUniform(const std::string& name, bool value) const;
    void setIntUniform(const std::string& name, int value) const;
    void setFloatUniform(const std::string& name, float value) const;
    void setMat4Uniform(const std::string& name, glm::mat4 value) const;
};

#endif // SHADER_HEADER