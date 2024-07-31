#!/bin/sh

g++ -I/usr/include -I/usr/local/include -I./ImGui -DIMGUI_IMPL_OPENGL_LOADER_GLEW -o my_program Rectangle/rectangle.cpp Rectangle/Setup.cpp Rectangle/ImGui.cpp ImGui/imgui.o ImGui/imgui_draw.o ImGui/imgui_widgets.o ImGui/imgui_tables.o ImGui/imgui_impl_glfw.o ImGui/imgui_impl_opengl3.o -lglfw -lGLEW -lGL

./my_program
