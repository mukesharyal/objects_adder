#include "Setup.h"

float size = -1.0f;

    GLfloat gridVertices3D[] = {
    // Horizontal lines
    -0.5f,  0.4f, 0.0f, 0.5f,  0.4f, 0.0f,
    -0.5f,  0.3f, 0.0f, 0.5f,  0.3f, 0.0f,
    -0.5f,  0.2f, 0.0f, 0.5f,  0.2f, 0.0f,
    -0.5f,  0.1f, 0.0f, 0.5f,  0.1f, 0.0f,
    -0.5f,  0.0f, 0.0f, 0.5f,  0.0f, 0.0f,
    -0.5f, -0.1f, 0.0f, 0.5f, -0.1f, 0.0f,
    -0.5f, -0.2f, 0.0f, 0.5f, -0.2f, 0.0f,
    -0.5f, -0.3f, 0.0f, 0.5f, -0.3f, 0.0f,
    -0.5f, -0.4f, 0.0f, 0.5f, -0.4f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,

    // Vertical lines
    -0.4f,  0.5f, 0.0f, -0.4f, -0.5f, 0.0f,
    -0.3f,  0.5f, 0.0f, -0.3f, -0.5f, 0.0f,
    -0.2f,  0.5f, 0.0f, -0.2f, -0.5f, 0.0f,
    -0.1f,  0.5f, 0.0f, -0.1f, -0.5f, 0.0f,
    0.0f,   0.5f, 0.0f,  0.0f, -0.5f, 0.0f,
    0.1f,   0.5f, 0.0f,  0.1f, -0.5f, 0.0f,
    0.2f,   0.5f, 0.0f,  0.2f, -0.5f, 0.0f,
    0.3f,   0.5f, 0.0f,  0.3f, -0.5f, 0.0f,
    0.4f,   0.5f, 0.0f,  0.4f, -0.5f, 0.0f,
    0.5f,   0.5f, 0.0f,  0.5f, -0.5f, 0.0f,

    // Border lines
    -0.5f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f,  // Left border
     0.5f,  0.5f, 0.0f,  0.5f, -0.5f, 0.0f,  // Right border
    -0.5f,  0.5f, 0.0f,  0.5f,  0.5f, 0.0f,  // Top border
    -0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f   // Bottom border
};

    GLuint gridIndices[] = {
        // Horizontal lines
        0, 1,
        2, 3,
        4, 5,
        6, 7,
        8, 9,
        10, 11,
        12, 13,
        14, 15,
        16, 17,
        // Vertical lines
        18, 19,
        20, 21,
        22, 23,
        24, 25,
        26, 27,
        28, 29,
        30, 31,
        32, 33,
        34, 35,
        36, 37,
        38, 39,
        // Border lines
        40, 41,
        42, 43,
        44, 45,
        46, 47,
        48, 49,
        50, 51,
        52, 53,
        54, 55
    };


// The variables xNorm and yNorm are the coordinates of the cursor in normalized coordinates. They were to be sent
// between the mouse_button_callback and the cursor_position_callback, so they are defined here
float xNorm, yNorm;

    
// These three functions help us to load the shader programs from the GLSL files into our program  
std::string readShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const GLchar* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint createShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::string vertexShaderSource = readShaderSource(vertexShaderPath);
    std::string fragmentShaderSource = readShaderSource(fragmentShaderPath);

    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cerr << "Failed to load shader sources" << std::endl;
        return 0;
    }

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


// Does all the necessary to start a window and get a OpenGL context up and running
int startWindow(GLFWwindow* &window)
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "3D Objects Adder - View Mode", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    return 0;
}


// The function to setup the grid
// Can be made into grid.setup()
void setupGrid(GLuint &gridVAO, GLuint &gridVBO, GLuint &gridEBO) {
    // Set up Grid VAO, VBO, and EBO
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glGenBuffers(1, &gridEBO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices3D), gridVertices3D, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gridIndices), gridIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // Position
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
 }


// Just a helper function that does what it says
float roundToDecimalPlaces(float number, int decimalPlaces) {
    float scale = std::pow(10.0f, decimalPlaces);
    return std::round(number * scale) / scale;
}


// The calculations to do on moving the cursor
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

	ImGuiIO& io = ImGui::GetIO();
    io.MousePos.x = (float)xpos;
    io.MousePos.y = (float)ypos;


    // If we are not in the top view, then the editing stuffs cannot be done. So, we don't do anything
     if(topView == false)
    {
        return;
    }


    // Get the window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Convert GLFW coordinates to OpenGL coordinates
    xNorm = (2.0f * xpos / width) - 1.0f;
    yNorm = 1.0f - (2.0f * ypos / height);

    // Grid boundaries
    float minX = -0.5f, maxX = 0.5f, minY = -0.5f, maxY = 0.5f;
    if (xNorm < minX || xNorm > maxX || yNorm < minY || yNorm > maxY) {
        //std::cout << "Cursor is outside the grid boundaries" << std::endl;
        return;
    }

    // If no object is selected, we do nothing
    if(size == -1.0f)
    {
        return;
    }

    // Grid cell size
    float cellWidth = 0.1f, cellHeight = 0.1f;
    // We use the scale variable to change the size of the rectangle according to the object we are selecting
    float scale = size; // Scale factor to cover 2x2 original cells

    // Adjusted cell size with scaling (in terms of number of cells)
    float scaledCellWidth = cellWidth * scale;
    float scaledCellHeight = cellHeight * scale;

    // Determine the row and column of the cursor
    int col = (int)((xNorm - minX) / cellWidth);
    int row = (int)((yNorm - minY) / cellHeight);

    // Ensure col and row are within valid range
    int maxCols = (int)((maxX - minX) / cellWidth);
    int maxRows = (int)((maxY - minY) / cellHeight);

    if (col < 0) col = 0;
    if (col >= maxCols) col = maxCols - 1;
    if (row < 0) row = 0;
    if (row >= maxRows) row = maxRows - 1;

    // Calculate the top-left corner of the scaled cell
    xLeft = minX + col * cellWidth;
    yBottom = minY + row * cellHeight;

    // Clamp the top-left corner to ensure the square is within the grid
    if (xLeft + scaledCellWidth > maxX) {
        xLeft = maxX - scaledCellWidth;
    }
    if (yBottom + scaledCellHeight > maxY) {
        yBottom = maxY - scaledCellHeight;
    }

    // Calculate the coordinates of the scaled cell
    xRight = roundToDecimalPlaces(xLeft + scaledCellWidth, 1);
    yTop = roundToDecimalPlaces(yBottom + scaledCellHeight, 1);
    xLeft = roundToDecimalPlaces(xLeft, 1);
    yBottom = roundToDecimalPlaces(yBottom, 1);


    float rectangleVertices[] = {
        xLeft, yBottom,
        xRight, yBottom,
        xLeft, yTop,
        xRight, yTop
    };

    // Bind the vertex buffer and update its data
    glBindBuffer(GL_ARRAY_BUFFER, highlightedCellVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rectangleVertices), rectangleVertices);

    
}

// Another helper function
// Function to check if two rectangles overlap (touching allowed but not overlapping)
bool doRectanglesOverlap(float x1Left, float x1Right, float y1Bottom, float y1Top,
                         float x2Left, float x2Right, float y2Bottom, float y2Top) {
    // Check if one rectangle is strictly to the left, right, above, or below the other
    if (x1Right <= x2Left || x1Left >= x2Right || y1Top <= y2Bottom || y1Bottom >= y2Top) {
        return false;
    }
    // If none of the above, the rectangles overlap
    return true;
}

// And another helper function. They work hand in hand, by the way.
// Function to check if the space is occupied
bool checkForOccupiedSpace(float xLeft, float xRight, float yBottom, float yTop, 
                           const std::vector<std::vector<float>>& objects, int numObjects) {
    for (int i = 0; i < numObjects; i++) {
        float objXLeft = objects[i][0];
        float objXRight = objects[i][1];
        float objYBottom = objects[i][3];
        float objYTop = objects[i][2];

        // Check if the clicked grid square overlaps with any existing object
        if (doRectanglesOverlap(xLeft, xRight, yBottom, yTop, objXLeft, objXRight, objYBottom, objYTop)) {

            // Ma yahasamma aaipugdaa maile click gareko xu, ani kunai object veteko xu

            // So, maile mode check garnu paryo

            if(mode == 0) // I intend to add an object, but the rectangles overlap
            {
                std::cout << "Space is occupied by object at index: " << i << std::endl;
            }

            if(mode == 1 || mode == 2) // I intend to move this object or remove this object, but the rectangles overlap.
                // That simply means that I have successfully selected an object
                // So, I retrieve the id of the object
            {
                selectedObject = i; // I stored the id of the selected object
            }


            return false;
        }
    }
    return true;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        // This function also does most of the things the previous function does, and thus can be made better and less redundant

        if(topView == false)
    {
        return;
    }


        // Grid boundaries
    float minX = -0.5f, maxX = 0.5f, minY = -0.5f, maxY = 0.5f;
    if (xNorm < minX || xNorm > maxX || yNorm < minY || yNorm > maxY) {
        //std::cout << "Cursor is outside the grid boundaries" << std::endl;
        return;
    }
    
    if(size == -1.0f)
    {
        return;
    }

    // Grid cell size
    float cellWidth = 0.1f, cellHeight = 0.1f;
    float scale = size; // Scale factor to cover 2x2 original cells

    // Adjusted cell size with scaling (in terms of number of cells)
    float scaledCellWidth = cellWidth * scale;
    float scaledCellHeight = cellHeight * scale;

    // Determine the row and column of the cursor
    int col = (int)((xNorm - minX) / cellWidth);
    int row = (int)((yNorm - minY) / cellHeight);

    // Ensure col and row are within valid range
    int maxCols = (int)((maxX - minX) / cellWidth);
    int maxRows = (int)((maxY - minY) / cellHeight);

    if (col < 0) col = 0;
    if (col >= maxCols) col = maxCols - 1;
    if (row < 0) row = 0;
    if (row >= maxRows) row = maxRows - 1;

    // Calculate the top-left corner of the scaled cell
    xLeft = minX + col * cellWidth;
    yBottom = minY + row * cellHeight;

    // Clamp the top-left corner to ensure the square is within the grid
    if (xLeft + scaledCellWidth > maxX) {
        xLeft = maxX - scaledCellWidth;
    }
    if (yBottom + scaledCellHeight > maxY) {
        yBottom = maxY - scaledCellHeight;
    }

    // Calculate the coordinates of the scaled cell
    xRight = roundToDecimalPlaces(xLeft + scaledCellWidth, 1);
    yTop = roundToDecimalPlaces(yBottom + scaledCellHeight, 1);
    xLeft = roundToDecimalPlaces(xLeft, 1);
    yBottom = roundToDecimalPlaces(yBottom, 1);



    if(checkForOccupiedSpace(xLeft, xRight, yBottom, yTop, objects, numObjects))
    {
        if(mode == 0) // If I intend to add an object, I add the object
        {
            std::vector<float> newObject = {xLeft, xRight, yTop, yBottom, size};
            objects.push_back(newObject); 
            numObjects++; // The number of objects is increased by 1
        }
        
    }else
    {
        if(objects.size() == 0) // If I don't intend to add the object, but have selected the object, and if there are no objects
            // This can break the program and thus we exit without doing anything
    {
        return;
    }

    if(mode == 1)  // I intend to move this object
    {
        // Moving the object just means first removing the object
        float sizeOfObject = objects[selectedObject][4];
        objects.erase(objects.begin() + selectedObject);

        numObjects--;

        // Then setting the mode to add the object, so that the same object will be added somewhere else
        mode = 0;
        size = sizeOfObject;
    }

    if(mode == 2) // I intend to remove this object
    {
        float sizeOfObject = objects[selectedObject][4];
        objects.erase(objects.begin() + selectedObject);

        numObjects--;
    }
    }



    }
}




