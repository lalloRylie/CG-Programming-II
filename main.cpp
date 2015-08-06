#include "Application.h"
#include "World.h"

#pragma once

GLFWwindow* window = NULL;


vec3 LinearInterpolate(vec3 p1, vec3 p2, float scalar = 0.001f) {
	//p3 = p1 + scalar * (p2 - p1)
	vec3 p3;
	p3.x = p1.x + scalar * (p2.x - p1.x);
	p3.y = p1.y + scalar * (p2.y - p1.y);
	p3.z = p1.z + scalar * (p2.z - p1.z);

	return p3;
}

void window_refresh_callback(GLFWwindow* window){
	//world.Render(camera);
	glfwSwapBuffers(window);
}

int InitWindowFailed(){
	if(glfwInit() == GLFW_FAIL){
		fprintf(stderr, "Failed to initialize GLFW\n");
		return EXIT_WITH_ERROR;
	}

	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Gets working on mac...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old open gl...

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);
	
	if(window == NULL){
		fprintf(stderr, "Failed to create/open GLFW window.\n");
		glfwTerminate();
		return EXIT_WITH_ERROR;
	}

	//Initialize GLEW.
    glfwMakeContextCurrent(window);
    
    //Ensure we can capture the escape key being pressed below.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	//glfwSetWindowFocusCallback(window, windowFocusCallback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);

	return EXIT_WITH_SUCCESS;
}

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path){
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read in shader code here...
	string vertexShaderCode = "";
	ifstream vertexShaderStream(vertex_file_path, ios::in);
	if(vertexShaderStream.is_open()){
		string line = "";
		while(getline(vertexShaderStream, line)){
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}

	string fragmentShaderCode = "";
	ifstream fragmentShaderStream(fragment_file_path, ios::in);
	if(fragmentShaderStream.is_open()){
		string line = "";
		while(getline(fragmentShaderStream, line)){
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength = 0;

	//Compile shaders here...
	printf("Compiling vertex shader: %s\n", vertex_file_path);
	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Check Vertex Shader...
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* vertexShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);

	//Compile Fragment Shader...
	printf("Compiling fragment shader: %s\n", fragment_file_path);
	char const *fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check Vertex Shader...
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* fragmentShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &fragmentShaderErrorMessage[0]);

	//Link Program...
	fprintf(stdout, "Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check the progam...
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char *programErrorMessage = new char[glm::max(infoLogLength, int(1))];
	glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
	fprintf(stdout, "%s\n", &programErrorMessage[0]);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	
	delete(programErrorMessage);
	programErrorMessage = NULL;

	delete(vertexShaderErrorMessage);
	vertexShaderErrorMessage = NULL;

	delete(fragmentShaderErrorMessage);
	fragmentShaderErrorMessage = NULL;

	return programID;
}

int InitGlewFailed(){
	glewExperimental = true; //Has to do with core profile.
	if(glewInit() != GLEW_OK){
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_WITH_ERROR;
	}

	return EXIT_WITH_SUCCESS;
}

double getDeltaTime(){
	static double lastTime = glfwGetTime();

	double now = glfwGetTime();
	double deltaTime = now - lastTime;

	lastTime = now;

	return deltaTime;
}

int main(){
	if(InitWindowFailed() | InitGlewFailed()){
		return EXIT_WITH_ERROR;
	}

	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Create and compile glsl program from shaders...
	GLuint programID = LoadShaders("TexturedVertexShader.vertexshader", "TexturedFragmentShader.fragmentshader");
	glUseProgram(programID);

	Camera camera;
	float aspectRatio = SCREEN_WIDTH/(float)SCREEN_HEIGHT;
	camera.MVPMatrixID = glGetUniformLocation(programID, "MVP");
	camera.projectionMatrix = perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);

	World world;

	#if 0
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	#endif

	// Camera matrix info
	camera.position = vec3(4,0,0); // Camera is at (4,3,3), in World Space
	camera.looking = vec3(0,0,0); // and looks at the origin
	camera.headsUp  = vec3(0,1,0);  // Head is up (set to 0,-1,0 to look upside-down)

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Getting delta time...
		float deltaTime = (float)getDeltaTime();

		// Camera matrix
		camera.viewMatrix = lookAt(
			camera.position,
			camera.looking, 
			camera.headsUp  
		);



		// CAMERA INSTRUCTIONS
		// Up, Down, Left and Right Arrows control where the camera looks
		// "W" will lineally interpolate between the camera's current position and its starting position
		// i.e., "W" will return you to the starting position
		// "Spacebar" and "X" control vertical movement
		// "A" and "D" control control horizontal movement
		// "S" Let's you pull the camera back, essentially zooming out.
		// The camera more or less behaves like it's on a rail, only going horizontally and vertically.

		float highSpeed = 3.0f;
		float lowSpeed = 3.0f;

		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			camera.looking.y += highSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			camera.looking.y -= highSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			camera.looking.z += highSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			camera.looking.z -= highSpeed * deltaTime;
		}

		////////////

		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			//camera.position.x -= 0.001f;
			camera.position = LinearInterpolate(camera.position, vec3(4,0,0), 0.04f);
			camera.looking = LinearInterpolate(camera.looking, vec3(0,0,0)), 5.0f;
		}

		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
			camera.position.x += highSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			camera.position.z += highSpeed * deltaTime;
			camera.looking.z += lowSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			camera.position.z -= highSpeed * deltaTime;
			camera.looking.z -= lowSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
			camera.position.y += highSpeed * deltaTime;
			camera.looking.y += lowSpeed * deltaTime;
		}

		if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
			camera.position.y -= highSpeed * deltaTime;
			camera.looking.y -= lowSpeed * deltaTime;
		}

		world.Update(deltaTime);
		world.Render(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return EXIT_WITH_SUCCESS;
}