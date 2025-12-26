#pragma once

static float vertices[] = {
        // front
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        // top
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        // left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 
        // right
        0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 
        0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,  
        0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,   
        0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,  
        // back
        -0.5f, -0.5f, 0.5f, 0.7f, 0.7f, 0.7f,
        0.5f, -0.5f, 0.5f, 0.7f, 0.7f, 0.7f, 
        0.5f, 0.5f, 0.5f, 0.7f, 0.7f, 0.7f,  
        -0.5f, 0.5f, 0.5f, 0.7f, 0.7f, 0.7f, 
        // bottom
        -0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f, 
        0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f,  
        0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, 
        -0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f 
};

static unsigned int indices[] =  {
    // front
    0, 1, 2, // first triangle
    2, 3, 0, // second triangle

    // top
    4, 5, 6, // first triangle
    6, 7, 4, // second triangle

    // left
    8, 9, 10,  // first triangle
    10, 11, 8, // second triangle

    // right
    14, 13, 12, // 12, 13, 14, // first triangle
    12, 15, 14, // 14, 15, 12, // second triangle

    // back
    18, 17, 16, // 16, 17, 18, // first triangle
    16, 19, 18, // 18, 19, 16, // second triangle

    // bottom
    20, 21, 22, // first triangle
    22, 23, 20  // second triangle
};