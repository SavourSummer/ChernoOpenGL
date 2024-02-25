#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<sstream>

#include"Renderer.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include "Texture.h"
//ע�����ɵ�exeͬһĿ¼����res/shaders/Basic.shader




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    //����Opengl�汾3.3��ԭ4.6,�������ú��İ汾���鿴������
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /**
     * �������������������֮ǰ�ȴ���֡����ͨ����Ϊv-sync
     * Ĭ������£��������Ϊ0
     * ��������Ϊ1����ÿ֡����һ��
     **/
    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    unsigned char* glVersion;
    GLCall(glVersion = (unsigned char*)glGetString(GL_VERSION));
    std::cout << "Status: Using GL " << glVersion << std::endl;

    /* ����λ�ø��������� */
    //float positions[] = {
    //    -0.5f, -0.5f, // 0
    //    0.5f, -0.5f,  // 1
    //    0.5f, 0.5f,   // 2
    //    -0.5f, 0.5f,  // 3
    //};
    //ע��ֻ�о������������������Ӧ������ȷ��ͼ��
    float positions[] = {
            0.0f, 0.0f, 0.0f, 0.0f, // 0
            1.0f, 0.0f, 1.0f, 0.0f,  // 1
            1.0f, 1.0f, 1.0f, 1.0f,    // 2
            0.0f, 1.0f, 0.0f, 1.0f   // 3
    };
    /* ���������������������� */
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    VertexArray va;
    VertexBuffer vb(positions,4*4*sizeof(float));//��4*2��Ϊ4*4��Ϊ������4����������

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    
    //unsigned int vao;//����Vertex Array Object,����ͳһ�������Ƶ��н�
    //GLCall(glGenVertexArrays(1, &vao));
    //GLCall(glBindVertexArray(vao));
    //VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    //unsigned int buffer;
    //GLCall(glGenBuffers(1, &buffer)); /* ���ɻ����� */
    //GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); /* �󶨻����� */
    //GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW)); /* ���û��������� */

    //GLCall(glEnableVertexAttribArray(0)); /* ���������-����0-λ�� */
    //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0)); /* ���ö�������-����0 */

    /*unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));*/
    IndexBuffer ib(indices, 6);

    /* ���ļ��н�����ɫ��Դ�� */
    //ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    //unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    //GLCall(glUseProgram(shader)); /* ʹ����ɫ������ */


    //int location;
    //GLCall(location = glGetUniformLocation(shader, "u_Color")); /* ��ȡָ������ͳһ������λ�� */
    //ASSERT(location != -1);
    //GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f)); /* ���ö�Ӧ��ͳһ���� */
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f,1.0f);

    Texture texture("res/textures/ChernoLogo.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);//��������0�Ų��
    va.Bind();
    ib.Bind();
    Renderer renderer;
    //���
    /*GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));*/
    //GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        //GLCall(glClear(GL_COLOR_BUFFER_BIT));
        renderer.Clear();
       // GLCall(glUseProgram(shader));
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
       // GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
       // GLCall(glBindVertexArray(vao));
        /* ���� */
       /* GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));*/
        vb.Bind();
       // GLCall(glEnableVertexAttribArray(0));
       // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        ib.Bind();

        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        renderer.Draw(va, ib, shader);
        if (r > 1.0f) {
            increment = -0.05f;
        }
        else if (r < 0.0f) {
            increment = 0.05f;
        }
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    //GLCall(glDeleteProgram(shader)); /* ɾ����ɫ������ */

    glfwTerminate();
    return 0;
}