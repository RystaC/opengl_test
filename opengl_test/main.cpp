#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

GLuint createProgram(std::string vertexShaderFile, std::string fragmentShaderFile, std::string geometryShaderFile, std::string TCShaderFile, std::string TEShaderFile) {

	const GLuint program = glCreateProgram();

	GLint status = GL_FALSE;
	GLsizei infoLogLength;

	// Vertex shader 
	std::ifstream vertexIfs(vertexShaderFile, std::ios::binary);
	if (vertexIfs.fail()) {
		std::cerr << "Error: Cannot open source file: " << vertexShaderFile << std::endl;
		return 0;
	}

	auto vertexShaderSource = std::string(std::istreambuf_iterator<char>(vertexIfs), std::istreambuf_iterator<char>());
	if (vertexIfs.fail()) {
		std::cerr << "Error: Cannot read source file: " << vertexShaderFile << std::endl;
		return 0;
	}

	const GLchar* vertexShaderSourcePointer = vertexShaderSource.c_str();

	const GLuint vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObj, 1, &vertexShaderSourcePointer, nullptr);
	glCompileShader(vertexShaderObj);
	glAttachShader(program, vertexShaderObj);

	glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Compile error in vertex shader." << std::endl;
	glGetShaderiv(vertexShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		std::vector<GLchar> vertexShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(vertexShaderObj, infoLogLength, nullptr, vertexShaderErrorMessage.data());
	}

	glDeleteShader(vertexShaderObj);

	// Vertex shader

	// Fragment shader

	std::ifstream fragmentIfs(fragmentShaderFile, std::ios::binary);
	if (fragmentIfs.fail()) {
		std::cerr << "Error: Cannot open source file: " << fragmentShaderFile
			<< std::endl;
		return 0;
	}
	auto fragmentShaderSource =
		std::string(std::istreambuf_iterator<char>(fragmentIfs),
			std::istreambuf_iterator<char>());
	if (fragmentIfs.fail()) {
		std::cerr << "Error: Cannot read source file: " << fragmentShaderFile
			<< std::endl;
		return 0;
	}
	const GLchar* fragmentShaderSourcePointer = fragmentShaderSource.c_str();

	const GLuint fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObj, 1, &fragmentShaderSourcePointer, nullptr);
	glCompileShader(fragmentShaderObj);
	glAttachShader(program, fragmentShaderObj);

	glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		std::cerr << "Compile error in fragment shader." << std::endl;
	glGetShaderiv(fragmentShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		std::vector<GLchar> fragmentShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(fragmentShaderObj, infoLogLength, nullptr,
			fragmentShaderErrorMessage.data());
		std::cerr << fragmentShaderErrorMessage.data() << std::endl;
	}

	glDeleteShader(fragmentShaderObj);

	// Fragment shader

	// Geometry shader

	if (!geometryShaderFile.empty()) {

		std::ifstream geometryIfs(geometryShaderFile, std::ios::binary);
		if (geometryIfs.fail()) {
			std::cerr << "Error: Cannot open source file: " << geometryShaderFile
				<< std::endl;
			return 0;
		}
		auto geometryShaderSource =
			std::string(std::istreambuf_iterator<char>(geometryIfs),
				std::istreambuf_iterator<char>());
		if (geometryIfs.fail()) {
			std::cerr << "Error: Cannot read source file: " << geometryShaderFile
				<< std::endl;
			return 0;
		}
		const GLchar* geometryShaderSourcePointer = geometryShaderSource.c_str();

		const GLuint geometryShaderObj = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShaderObj, 1, &geometryShaderSourcePointer, nullptr);
		glCompileShader(geometryShaderObj);
		glAttachShader(program, geometryShaderObj);

		glGetShaderiv(geometryShaderObj, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			std::cerr << "Compile error in geometry shader." << std::endl;
		glGetShaderiv(geometryShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 1) {
			std::vector<GLchar> geometryShaderErrorMessage(infoLogLength);
			glGetShaderInfoLog(geometryShaderObj, infoLogLength, nullptr,
				geometryShaderErrorMessage.data());
			std::cerr << geometryShaderErrorMessage.data() << std::endl;
		}

		glDeleteShader(geometryShaderObj);

	}

	// Geometry shader

	// Tessellation control shader (TCShader)

	if (!TCShaderFile.empty()) {
		std::ifstream TCIfs(TCShaderFile, std::ios::binary);
		if (TCIfs.fail()) {
			std::cerr << "Error: Cannot open source file: " << TCShaderFile
				<< std::endl;
			return 0;
		}
		auto TCShaderSource =
			std::string(std::istreambuf_iterator<char>(TCIfs),
				std::istreambuf_iterator<char>());
		if (TCIfs.fail()) {
			std::cerr << "Error: Cannot read source file: " << TCShaderFile
				<< std::endl;
			return 0;
		}
		const GLchar* TCShaderSourcePointer = TCShaderSource.c_str();

		const GLuint TCShaderObj = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(TCShaderObj, 1, &TCShaderSourcePointer, nullptr);
		glCompileShader(TCShaderObj);
		glAttachShader(program, TCShaderObj);

		glGetShaderiv(TCShaderObj, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			std::cerr << "Compile error in tessellation control shader." << std::endl;
		glGetShaderiv(TCShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 1) {
			std::vector<GLchar> TCShaderErrorMessage(infoLogLength);
			glGetShaderInfoLog(TCShaderObj, infoLogLength, nullptr,
				TCShaderErrorMessage.data());
			std::cerr << TCShaderErrorMessage.data() << std::endl;
		}

		glDeleteShader(TCShaderObj);
	}

	// Tessellation controll shader

	// Tessellation evaluation shader (TEShader)

	if (!TEShaderFile.empty()) {
		std::ifstream TEIfs(TEShaderFile, std::ios::binary);
		if (TEIfs.fail()) {
			std::cerr << "Error: Cannot open source file: " << TEShaderFile
				<< std::endl;
			return 0;
		}
		auto TEShaderSource =
			std::string(std::istreambuf_iterator<char>(TEIfs),
				std::istreambuf_iterator<char>());
		if (TEIfs.fail()) {
			std::cerr << "Error: Cannot read source file: " << TEShaderFile
				<< std::endl;
			return 0;
		}
		const GLchar* TEShaderSourcePointer = TEShaderSource.c_str();

		const GLuint TEShaderObj = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(TEShaderObj, 1, &TEShaderSourcePointer, nullptr);
		glCompileShader(TEShaderObj);
		glAttachShader(program, TEShaderObj);

		glGetShaderiv(TEShaderObj, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			std::cerr << "Compile error in tessellation evaluation shader." << std::endl;
		glGetShaderiv(TEShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 1) {
			std::vector<GLchar> TEShaderErrorMessage(infoLogLength);
			glGetShaderInfoLog(TEShaderObj, infoLogLength, nullptr,
				TEShaderErrorMessage.data());
			std::cerr << TEShaderErrorMessage.data() << std::endl;
		}

		glDeleteShader(TEShaderObj);
	}

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Link error." << std::endl;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		std::vector<GLchar> progrramLinkErrorMessage(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, nullptr, progrramLinkErrorMessage.data());
		std::cerr << progrramLinkErrorMessage.data() << std::endl;
	}

	return program;
}

int main() {
	glfwSetErrorCallback(
		[](auto id, auto description) { std::cerr << description << std::endl; }
	);

	constexpr GLuint width = 640;
	constexpr GLuint height = 480;

	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Test", nullptr, nullptr);
	if (!window) {
		std::cerr << "Cannot create window." << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Cannot initialize GLEW." << std::endl;
		return -1;
	}

	glfwSwapInterval(1);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(
		[](auto source, auto type, auto id, auto severity, auto length, const auto* message, const void* userParam) {
			auto t = type == GL_DEBUG_TYPE_ERROR ? "** GL_ERROR **" : "";
			std::cerr << "GL CALLBACK: " << t << "type = " << type << ", severity = " << severity << ", message = " << message << std::endl;
		},
		0
			);

	GLint maxTessellation{};
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxTessellation);
	std::cerr << "Max tessellation vertices: " << maxTessellation << std::endl;

	const GLuint program = createProgram("shader.vs", "shader.fs", "tessellation.gs", "tessellation.tcs", "tessellation.tes");

	const std::vector<glm::vec3> vertices = {
		glm::vec3(-0.5, -0.5, 0.0),
		glm::vec3(0.5, -0.5, 0.0),
		glm::vec3(0.5, 0.5, 0.0),
		glm::vec3(-0.5, 0.5, 0.0),
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint verticesVbo;
	glGenBuffers(1, &verticesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));

	auto view = glm::lookAt(glm::vec3(0.f, -0.8f, 0.6f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	auto projection = glm::perspective(glm::radians(90.f), 4.f / 3.f, 0.5f, 10.f);

	GLuint viewId = glGetUniformLocation(program, "view");
	GLuint projectionId = glGetUniformLocation(program, "projection");

	GLuint timeId = glGetUniformLocation(program, "time");

	float time = 0;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		glPatchParameteri(GL_PATCH_VERTICES, 4);

		glUniformMatrix4fv(viewId, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionId, 1, GL_FALSE, &projection[0][0]);
		glUniform1f(timeId, time);

		glBindVertexArray(vao);
		glDrawArrays(GL_PATCHES, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();

		time += 0.05;
	}

	glfwTerminate();

	return 0;
}