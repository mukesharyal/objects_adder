#include "Setup.h"

// We handle the GUI portion of our project in this file

void onAddObjectSelection(int selectedItem) {
    // Handle the object selection callback
    switch (selectedItem) {
        case 0: // House
            size = 3.0f; // The variable size is used to identify the object selected
            mode = 0; // The value of mode is used to identify the mode. 0 indicates the ADD mode
            topView = true;
            break;
        case 1: // Tree
            size = 1.0f;
            mode = 0;
            topView = true;
            break;
        case 2: // Vehicle
            size = 2.0f;
            mode = 0;
            topView = true;
            break;
        default:
            std::cout << "Unknown selection" << std::endl;
            break;
    }
}

void onMoveObjectClick() {
    // Handle move object button click
    mode = 1; // The MOVE mode
    topView = true;
}

void onRemoveObjectClick() {
    // Handle remove object button click
    mode = 2; // The REMOVE mode
    topView = true;
}

void setupImGui()
{
    // Poll for and process events
    glfwPollEvents();

    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    // ImGui UI code
    ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoResize);

    // Dropdown menu with placeholder
    static const char* items[] = { "House", "Tree", "Vehicle" };
    static int selectedItem = -1; // -1 means no selection
    const char* currentItem = (selectedItem == -1) ? "Select..." : items[selectedItem];
    
    if (ImGui::BeginCombo("Add Object", currentItem)) {
        for (int i = 0; i < IM_ARRAYSIZE(items); ++i) {
            bool isSelected = (selectedItem == i);
            if (ImGui::Selectable(items[i], isSelected)) {
                selectedItem = i;
                onAddObjectSelection(i);
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus(); // Keep the selected item focused
            }
        }
        ImGui::EndCombo();
    }

    // Buttons
    if (ImGui::Button("Move Object")) {
        onMoveObjectClick();
    }
    if (ImGui::Button("Remove Object")) {
        onRemoveObjectClick();
    }

    if (ImGui::Button((topView == true ? "Go To View Mode" : "Go To Edit Mode"))) {
        topView = !topView;
    }
    
    ImGui::End();
}

