#include <Shader.h>

/// <summary>
/// Takes the given id and checks for shader compilation problems when checkCompilation = true,
/// or checks for problems with the linking if checkCompilation = false
/// </summary>
/// <param name="id">id of shader to check</param>
/// <param name="checkCompilation">true to check compilation, false to check linking</param>
void Shader::checkAndPrintErrors(unsigned int id, bool checkCompilation) {
	char infoLog[512];
	int success;

	if (checkCompilation) {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	}
	else {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
	}

	if (!success) {
		if (checkCompilation) {
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			std::cout << "Error: Shader Compilation failed. Id: " << id << std::endl;
		}
		else {
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "Error: Shader Program Linking failed. Id: " << id << std::endl;
		}
	}
}

/// <summary>
/// Returns the current directory appended by the given filename.
/// Since the std::ifstream::open-Method in the constructor can not open the files from this directory,
/// this method is currently not used. Instead, the shader files are copied in the main directory.
/// </summary>
/// <param name="fileName">filename to append to the current directory</param>
/// <returns>directory as a path string</returns>
const char* Shader::addCurrentDirectory(std::string fileName) {
	char buff[FILENAME_MAX];
	GetCurrentDirectoryA(FILENAME_MAX, buff);
	std::string directory = buff;

	std::string toReplace = "\\";
	std::string replace = "/";

	size_t pos = directory.find(toReplace);
	while (pos != std::string::npos)
	{
		directory.replace(pos, toReplace.size(), replace);
		pos = directory.find(toReplace, pos + replace.size());
	}

	directory.append("/Shaders/" + fileName);
	return directory.c_str();
}

/// <summary>
/// Opens, compiles and links the given shader files.
/// </summary>
/// <param name="vertexFileName">Name of the vertex shader file</param>
/// <param name="fragmentFileName">Name of the fragment shader file</param>
/// <param name="geometryFileName">Name of the geometry shader file (optional)</param>
Shader::Shader(const char* vertexFileName, const char* fragmentFileName, const char* geometryFileName) {
	bool hasGeometry = (geometryFileName != nullptr);

	std::string vertexCodeString, fragmentCodeString, geometryCodeString;
	std::ifstream vertexFile, fragmentFile, geometryFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// read Shaders from files
	try {
		/*vertexFile.open(addCurrentDirectory(vertexFileName));
		fragmentFile.open(addCurrentDirectory(fragmentFileName));*/
		vertexFile.open(vertexFileName);
		fragmentFile.open(fragmentFileName);
		std::stringstream vertexStream, fragmentStream, geometryStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCodeString = vertexStream.str();
		fragmentCodeString = fragmentStream.str();

		if (hasGeometry) {
			geometryFile.open(geometryFileName);
			geometryStream << geometryFile.rdbuf();
			geometryFile.close();
			geometryCodeString = geometryStream.str();
		}
	} catch (std::ifstream::failure ex) {
		std::cout << "Error: Shader file could not be read - " << ex.what() << std::endl;
	}

	const char* vertexCodeChar = vertexCodeString.c_str();
	const char* fragmentCodeChar = fragmentCodeString.c_str();
	unsigned int vertexId, fragmentId, geometryId;

	// vertex Shader
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexCodeChar, NULL);
	glCompileShader(vertexId);
	checkAndPrintErrors(vertexId, true);

	// fragment Shader
	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fragmentCodeChar, NULL);
	glCompileShader(fragmentId);
	checkAndPrintErrors(fragmentId, true);

	// geometry shader (if defined)
	if (hasGeometry) {
		const char* geometryCodeChar = geometryCodeString.c_str();
		geometryId = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryId, 1, &geometryCodeChar, NULL);
		glCompileShader(geometryId);
		checkAndPrintErrors(geometryId, true);
	}

	// create Shader Program
	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, vertexId);
	glAttachShader(ProgramId, fragmentId);
	if (hasGeometry) {
		glAttachShader(ProgramId, geometryId);
	}
	glLinkProgram(ProgramId);
	checkAndPrintErrors(ProgramId, false);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
	if (hasGeometry) {
		glDeleteShader(geometryId);
	}
}

/// <summary>
/// Either activates or deactivates (= deletes) this shader program
/// </summary>
/// <param name="activate">true to activate</param>
void Shader::changeStatus(bool activate) {
	if (activate) {
		glUseProgram(ProgramId);
	} else {
		glDeleteProgram(ProgramId);
	}	
}

/// <summary>
/// Sets a mat4 uniform value for the shaders of this object to the given value
/// </summary>
/// <param name="name">Name of the uniform parameter</param>
/// <param name="value">value to set</param>
void Shader::setMat4Uniform(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}