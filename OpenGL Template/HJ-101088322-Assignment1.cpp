
//***********************************************************************************************
// HJ-101088322-Assignment1.cpp by Jamie Ching-chun Huang,101088322 (C) 2018 All Rights Reserved.
//
// Assignment 1 submission.
//
// Description:
// Click run to see the results.
// Enter the numbers and rotate angles of the squares in the console
// I create 10 colours and randomly apply them on to the squares.
//
//***********************************************************************************************


#include "stdlib.h"
#include <glew.h>
#include "time.h"
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <GLUT/GLUT.h>
#include <LoadShaders.h>
#include <type_ptr.hpp>
#include <iostream>

GLuint program;
GLuint vao;
GLuint points_vbo;
GLuint colours_vbo;
GLint model;
glm::mat4 Model;
glm::mat4 myIdentityMatrix;
glm::mat4 ScaleMatrix;
glm::mat4 RotationMatrix;

float rotAngle;
int numbers;
float* colours;
float** colourIndex;

void setupVBO()
{
    float points[] = {
        -0.9f, 0.9f, 0.0f,
        0.9f, 0.9f, 0.0f,
        0.9f, -0.9f, 0.0f,
        -0.9f, -0.9f, 0.0f,
    };
    points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

    float olive[] = {0.8f, 0.8f, 0.2f,};
    float white[] = {1.0f, 1.0f, 1.0f,};
    float red[] = {0.9f, 0.1f, 0.2f,};
    float green[] = {0.1f, 0.9f, 0.5f,};
    float peach[] = {1.0f, 0.5f, 0.7f,};
    float purple[] = {0.7f, 0.5f, 0.1f,};
    float orange[] = {0.9f,0.6f,0.1f,};
    float sky[] = {0.6f,1.0f,1.0f,};
    float yellow[] = {1.0f,0.9f,0.3f,};
    float burgundy[] = {0.6f,0.0f,0.2f,};
    
    colourIndex = new float*[numbers];
    
    for(int i=0; i<numbers; i++)
    {
        colourIndex[i] = new float[12];
        float* currentColor;
        if(i % 10 == 0){currentColor = olive;}
        if(i % 10 == 1){currentColor = white;}
        if(i % 10 == 2){currentColor = red;}
        if(i % 10 == 3){currentColor = green;}
        if(i % 10 == 4){currentColor = peach;}
        if(i % 10 == 5){currentColor = purple;}
        if(i % 10 == 6){currentColor = orange;}
        if(i % 10 == 7){currentColor = sky;}
        if(i % 10 == 8){currentColor = yellow;}
        if(i % 10 == 9){currentColor = burgundy;}
        
        float** myColors = new float*[10];
        myColors[0] = olive;
        myColors[1] = white;
        myColors[2] = red;
        myColors[3] = green;
        myColors[4] = peach;
        myColors[5] = purple;
        myColors[6] = orange;
        myColors[7] = sky;
        myColors[8] = yellow;
        myColors[9] = burgundy;
        currentColor = myColors[rand() % 10];

        for (int j = 0; j < 12; j+=3) {
            colourIndex[i][j] = currentColor[0];
            colourIndex[i][j + 1] = currentColor[1];
            colourIndex[i][j + 2] = currentColor[2];
        }
    }
    
    colours_vbo = 0;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colourIndex, GL_STATIC_DRAW);
}

void setupVAO()
{
    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //layout(location = 0) in vec3 vPosition; 0 =>(location = 0); 3 => vec3
    glEnableVertexAttribArray(0);
  
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

}

void init(void)
{
    //Specifying the name of vertex and fragment shaders.
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };
    
    //Loading and compiling shaders
    program = LoadShaders(shaders);
    glUseProgram(program);    //My Pipeline is set up
    
    //glBindAttribLocation(program, 0, "vertex_position");
    //glBindAttribLocation(program, 0, "frag_colour");
    
    // Get a reference of the location in the shader
    model = glGetUniformLocation(program, "Model" );
    
    setupVBO();
    setupVAO();

}


//---------------------------------------------------------------------
//
// display
//

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3, 0.5, 0.7, 1.0);
    
    float angle = 0.0;
    float scale = 1.0;

    
    for(int i = 0; i<numbers; ++i)
    {
//        glBindVertexArray(vao);
//        ScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
//        RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//        Model = RotationMatrix * ScaleMatrix;
//        //Link the matrix with the shader uniform variable
//        glUniformMatrix4fv(model, 1, GL_FALSE, value_ptr(Model));
//        glDrawArrays(GL_LINE_LOOP, 0, 4);
        
        colours = colourIndex[i];
        glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colours, GL_STATIC_DRAW);

        glBindVertexArray(vao);
        ScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
        RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        Model = RotationMatrix * ScaleMatrix;
        glUniformMatrix4fv(model, 1, GL_FALSE, value_ptr(Model));
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        scale *=0.7;
        angle +=rotAngle;
        
    }

    glFlush();
//    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay();
}

//---------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv)
{
    srand(time(0));
    
    std::cout<< "Enter the numers of squares you like: ";
    std::cin>>numbers;
    std::cout<<std::endl<<"Enter the angle of rotation: ";
    std::cin>>rotAngle;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Huang, Jamie Ching-chun, 101088322");
    
    glewExperimental = true;
    glewInit();    //Initializes the glew and prepares the drawing pipeline.
    
    
    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}


