<h1 align="center">objects_adder</h1>

<p align="center">
  A <b>C++ OpenGL-based application</b> that renders a basic 3D world, including the ability to map and display 3D objects. This project explores foundational concepts in computer graphics and 3D rendering.
</p>

---

<h2>Features</h2>
<ul>
  <li><b>3D World Rendering</b>: Generates a basic 3D environment with camera controls.</li>
  <li><b>Object Mapping</b>: Load, render, and manipulate 3D objects within the scene.</li>
  <li><b>Lighting and Shading</b>: Implements basic lighting models to enhance visual realism.</li>
  <li><b>Keyboard Interaction</b>: Use keyboard inputs to navigate or modify the scene.</li>
  <li><b>Scalable Design</b>: Extend the project to add more 3D objects and features.</li>
</ul>

---

<h2>Technologies Used</h2>
<ul>
  <li><b>Programming Language:</b> C++</li>
  <li><b>Graphics Library:</b> OpenGL</li>
  <li><b>Development Tools:</b>
    <ul>
      <li>GLFW (for window and input management)</li>
      <li>GLEW (for OpenGL extension handling)</li>
      <li>GLM (for math operations, like transformations and projections)</li>
    </ul>
  </li>
</ul>

---

<h2>Getting Started</h2>

<h3>Prerequisites</h3>
<ul>
  <li><b>C++ Compiler:</b> Make sure a C++17-compatible compiler is installed.</li>
  <li><b>OpenGL Environment:</b> Ensure OpenGL drivers are installed and up-to-date.</li>
  <li><b>Dependencies:</b> GLFW, GLEW, GLM</li>
</ul>

<h3>Clone the Repository</h3>
<pre>
<code>
git clone https://github.com/mee-lan/objects_adder.git
cd objects_adder
</code>
</pre>

<h3>Build and Run</h3>
<ol>
  <li>Use any C++ IDE like <b>Visual Studio</b>, <b>CLion</b>, or <b>Code::Blocks</b>, or build manually using <code>g++</code>:
    <pre>
    <code>
    g++ main.cpp -lglfw -lGLEW -lGL -o 3dworld
    ./3dworld
    </code>
    </pre>
  </li>
  <li>Execute the application to render the 3D world.</li>
</ol>

---

<h2>Controls</h2>
<ul>
  <li><b>W/A/S/D:</b> Move camera</li>
  <li><b>Arrow Keys:</b> Rotate view</li>
  <li><b>Space:</b> Add/Remove objects</li>
</ul>

---

---

<h2>Acknowledgments</h2>
<ul>
  <li>OpenGL tutorials and documentation for guidance.</li>
  <li>GLFW and GLEW communities for maintaining essential tools for OpenGL development.</li>
</ul>

<p align="center">Feel free to explore, enhance, or contribute to the project!</p>
