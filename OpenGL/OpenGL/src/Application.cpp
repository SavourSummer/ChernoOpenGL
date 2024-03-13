//#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
//#include<string>
//#include<fstream>
//#include<sstream>

#include"Renderer.h"
//#include"IndexBuffer.h"
//#include"VertexBuffer.h"
//#include"VertexArray.h"
//#include"Shader.h"
//#include "Texture.h"
//ע�����ɵ�exeͬһĿ¼����res/shaders/Basic.shader

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Test/TestClearColor.h"
#include "Test/TestTexture2D.h"
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
    // �����Ƕ��������
    ////  -100.0f, -100.0f, 0.0f, 0.0f, // 0
    //    100.0f, -100.0f, 1.0f, 0.0f,  // 1
    //    100.0f, 100.0f, 1.0f, 1.0f,    // 2
    //    -100.0f, 100.0f, 0.0f, 1.0f   // 3
    // 100.0f, 100.0f, 0.0f, 0.0f, // 0
    //200.0f, 100.0f, 1.0f, 0.0f,  // 1
    //    200.0f, 200.0f, 1.0f, 1.0f,    // 2
    //    100.0f, 200.0f, 0.0f, 1.0f   // 3
    ////};
    //ע��ֻ�о������������������Ӧ������ȷ��ͼ��
    //float positions[] = {
    //        -50.0f, -50.0f, 0.0f, 0.0f, // 0
    //         50.0f, -50.0f, 1.0f, 0.0f, // 1
    //         50.0f, 50.0f, 1.0f, 1.0f,  // 2
    //        -50.0f, 50.0f, 0.0f, 1.0f   // 3
    //        
    //       
    //};//��C������x=0,y=0�㣬�����½�λ��
    /* ���������������������� */
   /* unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };*/
    /**
         * ���:
         * �������ɫ(�ж���ɫ���������ɫ)��Ŀ�껺�������е���ɫ���
         * glEnable/glDisable(����&�ر�) => glBlendFunc(ָ����ɫ����) => glBlendEquation(ָ�����ģʽ)
         * glBlendEquation(mode) mode: src��dest�Ļ�Ϸ�ʽ(Ĭ��GL_FUNC_ADD, ����)
         *
         **/
         /* ���û��(Ĭ�ϲ�������) */
    GLCall(glEnable(GL_BLEND));
    /**
         * glBlendFunc(src, dest) ָ����ɫ����
         * src ָ�������ɫ(RGBA)���ӵļ��㷽ʽ, Ĭ��ΪGL_ONE
         * dest ָ��Ŀ����ɫ���ӵļ��㷽ʽ, Ĭ��ΪGL_ZERO
         * GL_SRC_ALPHA ��Ϊsrc��alphaΪ0, GL_ONE_MINUS_SRC_ALPHA 1-src.alpha
         * RGBA = Srgba * GL_SRC_ALPHA + Drgba * GL_ONE_MINUS_SRC_ALPHA
         **/
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //VertexArray va;
    //VertexBuffer vb(positions,4*4*sizeof(float));//��4*2��Ϊ4*4��Ϊ������4����������

    //VertexBufferLayout layout;
    //layout.Push<float>(2);
    //layout.Push<float>(2);
    //va.AddBuffer(vb, layout);
    //
    ////unsigned int vao;//����Vertex Array Object,����ͳһ�������Ƶ��н�
    ////GLCall(glGenVertexArrays(1, &vao));
    ////GLCall(glBindVertexArray(vao));
    ////VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    ////unsigned int buffer;
    ////GLCall(glGenBuffers(1, &buffer)); /* ���ɻ����� */
    ////GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); /* �󶨻����� */
    ////GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW)); /* ���û��������� */

    ////GLCall(glEnableVertexAttribArray(0)); /* ���������-����0-λ�� */
    ////GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0)); /* ���ö�������-����0 */

    ///*unsigned int ibo;
    //GLCall(glGenBuffers(1, &ibo));
    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    //GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));*/
    //IndexBuffer ib(indices, 6);
    ////glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    ///* ����Ӧ���� 960x720 ������ 960x540 �ķֱ��� */
    //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    ////glm::vec4 vp(100.0f, 100.0f, 0.0f, 1.0f);
    ///* ���λ�� ��ͼ���� x&y&z */
    ////glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    ///* ģ�;��� ����λ�� */
    ////glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    ////glm::mat4 mvp = proj * view * model; /* ģ����ͼͶӰ���� */

    ///* ���ļ��н�����ɫ��Դ�� */
    ////ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    ////unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    ////GLCall(glUseProgram(shader)); /* ʹ����ɫ������ */


    //int location;
    //GLCall(location = glGetUniformLocation(shader, "u_Color")); /* ��ȡָ������ͳһ������λ�� */
    //ASSERT(location != -1);
    //GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f)); /* ���ö�Ӧ��ͳһ���� */
    //Shader shader("res/shaders/Basic.shader");
    //shader.Bind();
    //shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f,1.0f);
    ////shader.SetUniformMat4f("u_MVP", proj
    ////shader.SetUniformMat4f("u_MVP", mvp);//���󶨣�����������C
    //Texture texture("res/textures/ChernoLogo.png");
    //texture.Bind();
    //shader.SetUniform1i("u_Texture", 0);//��������0�Ų��
    ///* ��� */
    //va.UnBind();
    //shader.UnBind();
    //vb.UnBind();
    //ib.UnBind();
    Renderer renderer;


    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();

    // ��Ҫָ��glsl�汾, Ҳ����shader�е�version
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    //���
    /*GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));*/
    //GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    /*float r = 0.0f;
    float increment = 0.05f;*/
   // test::TestClearColor test;
    //���д��봴����һ���µ� test::TestMenu ���󣬲��� currentTest ��Ϊ�������ݸ� test::TestMenu �Ĺ��캯����Ȼ�������´����� test::TestMenu ����ĵ�ַ��ֵ�� testMenu ָ�롣

    //    ����ζ�� testMenu ����ָ��һ�� test::TestMenu ��������������һ��ָ�� currentTest ��ָ��ָ��� Test ��������á���������Ϳ���ͨ�� testMenu �����ʺͲ��� currentTest��
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("ClearColor");
    testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
    /*glm::vec3 tranlation(200, 100, 0);*///����C�ĳ�ʼλ��
    //glm::vec3 tranlationA(200, 100, 0);//��������C����
    //glm::vec3 tranlationB(400, 100, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        /* Render here */
        //GLCall(glClear(GL_COLOR_BUFFER_BIT));
        renderer.Clear();
        //test.OnUpdate(0.0f);
       // test.OnRender();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       // {
       //     glm::mat4 model = glm::translate(glm::mat4(1.0f), tranlationA);
       //     //glm::mat4 mvp = proj * view * model;

       // glm::mat4 mvp = proj * view * model; /* ģ����ͼͶӰ���� */
       //// GLCall(glUseProgram(shader));
       // shader.Bind();
       //// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
       // shader.SetUniformMat4f("u_MVP", mvp); /*  */
       //// GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
       //// GLCall(glBindVertexArray(vao));
       // /* ���� */
       ///* GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
       // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));*/
       // //va.Bind();
       // //vb.Bind();
       //// GLCall(glEnableVertexAttribArray(0));
       //// GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

       // //ib.Bind();

       // //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
       // renderer.Draw(va, ib, shader);
       // }
       // {
       //     glm::mat4 model = glm::translate(glm::mat4(1.0f), tranlationB);
       //     glm::mat4 mvp = proj * view * model;

       //     shader.Bind();
       //     shader.SetUniformMat4f("u_MVP", mvp);

       //     renderer.Draw(va, ib, shader);
       // }
        /*if (r > 1.0f) {
            increment = -0.05f;
        }
        else if (r < 0.0f) {
            increment = 0.05f;
        }
        r += increment;*/
        //{
        //    ImGui::Begin("ImGui");
        //    ImGui::SliderFloat3("TranlationA", &tranlationA.x, 0.0f, 960.0f);
        //    ImGui::SliderFloat3("TranlationB", &tranlationB.x, 0.0f, 960.0f);//���ÿ��ƶ����룬����x��y
        //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //    ImGui::End();
        //}
        //test.OnImGuiRender();
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("ImGui-Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    delete currentTest;
    if (currentTest != testMenu)
    {
        delete testMenu;
    }
    //GLCall(glDeleteProgram(shader)); /* ɾ����ɫ������ */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
