#include "Setup.h"

GLFWwindow* window;

GLint shaderProgram;

GLuint highlightedCellVBO, highlightedCellVAO; // The memory for the cell to be highlighted when we hover over it in the ADD mode

GLfloat xLeft, xRight, yTop, yBottom;

std::vector<std::vector<float>> objects; // The vector of arrays that holds the number of objects we have added onto the plane

int mode = -1; // View mode

int numObjects = 0; // Initially, there are no objects in the space

int selectedObject; // The ID of the selected object to be used for manipulation. The ID is just the index of the object in our vector

bool topView = false;  // Initially show the view in the 3D view, and not the top view

int main() {
    startWindow(window);

    // Set the cursor position callback for handling the cursor
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Set the mouse button callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);

	// The memory to hold the vertices of the grid
	// This is the initialisation for the Grid object
    GLuint gridVAO, gridVBO, gridEBO;
    
    // We could run this as grid.render() to render the grid
    setupGrid(gridVAO, gridVBO, gridEBO);


	// Initialize VBO and VAO for the highlighted cell
	// This is the initialisation portion for the Highlight object
	glGenVertexArrays(1, &highlightedCellVAO);
	glGenBuffers(1, &highlightedCellVBO);

	glBindVertexArray(highlightedCellVAO);
	glBindBuffer(GL_ARRAY_BUFFER, highlightedCellVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, nullptr, GL_DYNAMIC_DRAW); // Reserve space

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	
    // The shader program to be used for the rendering purposes
    shaderProgram = createShaderProgram("Rectangle/vertex_shader.glsl", "Rectangle/fragment_shader.glsl");
    std::cout << "Shader program ID of main program = " << shaderProgram << std::endl; // Just a helpful cout
    
    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program" << std::endl;
        return -1;
    }
   

    // Main loop
    // This loop is run while the window is not closed, and thus any responsive thing we want to do must be done here
    while (!glfwWindowShouldClose(window)) {
        setupImGui();

        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT);
         glClear(GL_DEPTH_BUFFER_BIT);



         glm::mat4 projection, view, model; // The three matrices for the Linear Algebra stuff
         // Use shader program
        glUseProgram(shaderProgram);

        if(topView)
        {
            // Just use plain identity matrices for the top view
            projection = glm::mat4(1.0f);
            view = glm::mat4(1.0f);
            model = glm::mat4(1.0f);
        }
        else
        {
            // Do some MATH for the 3D view
            // Set projection matrix
            projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

            // Set view matrix
            view = glm::lookAt(glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            // Set model matrix
            model = glm::mat4(1.0f);
        }


        // Send the matrices to the vertex shader to alter the view
        GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Set the viewport
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // Set the title of the window dynamically according to the mode
        if(topView)
        {
            glfwSetWindowTitle(window, "3D Objects Adder - Edit Mode");
        }
        else
        {
            glfwSetWindowTitle(window, "3D Objects Adder - View Mode");
        }
        
          // Draw the grid
        // Can be made to grid.draw()
    	glUseProgram(shaderProgram);
    	GLint modeLoc = glGetUniformLocation(shaderProgram, "typeToPaint");
    	if (modeLoc != -1) {
        	glUniform1i(modeLoc, 0); // No special mode for the grid
    	}
    	glBindVertexArray(gridVAO);
    	glDrawElements(GL_LINES, 56, GL_UNSIGNED_INT, 0);
    	glBindVertexArray(0);


        

    	// Draw the highlighted cell (if any)
        // Can be made into highlight.draw()
        if(mode == 0 && topView == true) // I want to add the object
        {
            if (modeLoc != -1) {
            glUniform1i(modeLoc, 10*int(size)); // Example: setting to 2 for green color
        }
        glBindVertexArray(highlightedCellVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Drawing the highlighted cell
        glBindVertexArray(0);

        }

        glClear(GL_DEPTH_BUFFER_BIT);


// Allocate memory for VAOs, VBOs, and EBOs of the objects
// This is just the memory where our "Object objects[]" will be stored
GLuint* cubeVAOs = new GLuint[numObjects];
GLuint* cubeVBOs = new GLuint[numObjects];
GLuint* cubeEBOs = new GLuint[numObjects]; // Added EBOs

for (int i = 0; i < numObjects; i++) {
    // Generate and bind VAO, VBO, and EBO for each object
    // Allocate memory for each object
    // Can be made into object.setup()
    glGenVertexArrays(1, &cubeVAOs[i]);
    glGenBuffers(1, &cubeVBOs[i]);
    glGenBuffers(1, &cubeEBOs[i]); // Added EBO generation

    glBindVertexArray(cubeVAOs[i]);

    // Bind and initialize VBO with dummy data
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBOs[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24 * 3, nullptr, GL_DYNAMIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind and initialize EBO with dummy data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBOs[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, nullptr, GL_DYNAMIC_DRAW); // Use GL_DYNAMIC_DRAW for EBO

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

for (int i = 0; i < numObjects; i++) {
    // Retrieve the properties for the current object
    // We can just use the object itself if used a friend function or something
    float xLeft = objects[i][0];
    float xRight = objects[i][1];
    float yTop = objects[i][2];
    float yBottom = objects[i][3];
    float size = objects[i][4];
    float height;

    if(size == 1.0) // This is a tree
    {
        height = 0.2;
    }

    if(size == 2.0) // This is a vehicle
    {
        height = 0.05;
    }

    if(size == 3.0) // This is a house
    {
        height = 0.1;
    }



    // Define the vertices for the current object
    float cubeVertices[] = {
        // Front face
        xLeft, yBottom, 0.0f,
        xRight, yBottom, 0.0f,
        xLeft, yTop, 0.0f,
        xRight, yTop, 0.0f,

        // Back face
        xLeft, yBottom, height,
        xRight, yBottom, height,
        xLeft, yTop, height,
        xRight, yTop, height,

        // Left face
        xLeft, yBottom, 0.0f,
        xLeft, yBottom, height,
        xLeft, yTop, height,
        xLeft, yTop, 0.0f,

        // Right face
        xRight, yBottom, 0.0f,
        xRight, yBottom, height,
        xRight, yTop, height,
        xRight, yTop, 0.0f,

        // Top face
        xLeft, yTop, 0.0f,
        xRight, yTop, 0.0f,
        xRight, yTop, height,
        xLeft, yTop, height,

        // Bottom face
        xLeft, yBottom, 0.0f,
        xRight, yBottom, 0.0f,
        xRight, yBottom, height,
        xLeft, yBottom, height
    };

    // Define the indices for the cube
    unsigned int cubeIndices[] = {
        // Front face
        0, 1, 2,
        1, 3, 2,

        // Back face
        4, 5, 6,
        5, 7, 6,

        // Left face
        8, 9, 10,
        9, 11, 10,

        // Right face
        12, 13, 14,
        13, 15, 14,

        // Top face
        16, 17, 18,
        17, 19, 18,

        // Bottom face
        20, 21, 22,
        20, 22, 23
    };

    // Bind the VAO, VBO, and EBO for the current object
    glBindVertexArray(cubeVAOs[i]);

    // Update the VBO with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBOs[i]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertices), cubeVertices);

    // Update the EBO with index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBOs[i]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(cubeIndices), cubeIndices);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Now that we have bound all the data for each object, it is time to render each object 

for (int i = 0; i < numObjects; i++) {
    glClear(GL_DEPTH_BUFFER_BIT);

    // Set model matrix for the cubes
    glm::mat4 cubeModel = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));

    glUniform1i(modeLoc, int(objects[i][4]));
    glBindVertexArray(cubeVAOs[i]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // Use glDrawElements to draw the cube
    glBindVertexArray(0);
}

// Cleanup (optional, after rendering is done)
for (int i = 0; i < numObjects; i++) {
    glDeleteVertexArrays(1, &cubeVAOs[i]);
    glDeleteBuffers(1, &cubeVBOs[i]);
}
    	
    	// Just another helpful cout, but is executed EVERY TIME a new frame is painted, so commented
    	//std::cout << "There are " << numObjects << "objects in the space" << std::endl;

        // Render ImGui
        // Render the GUI portion of the app
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteVertexArrays(1, &gridVAO);
    glDeleteBuffers(1, &gridVBO);
    glDeleteBuffers(1, &gridEBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


