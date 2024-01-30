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
//ע�����ɵ�exeͬһĿ¼����res/shaders/Basic.shader


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath); /* ����û�ж��ļ��Ƿ��������� is_open */
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) { /* �ҵ�#shader��� */
            if (line.find("vertex") != std::string::npos) { /* ������ɫ����� */
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) { /* Ƭ����ɫ����� */
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id;
    /* ���������� */
    GLCall(id = glCreateShader(type)); /* ������Ӧ���͵���ɫ�� */
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr)); /* ������ɫ��Դ�� */
    GLCall(glCompileShader(id)); /* ������ɫ�� */

    /* ��������� */
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // ��ȡ��ǰ��ɫ������״̬
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)); // ��ȡ��־����
        char* msg = (char*)_malloca(length * sizeof(char)); /* Cherno������õ�alloca, ����IDE��ʾ, ������ĳ���_malloca���� */
        GLCall(glGetShaderInfoLog(id, length, &length, msg)); // ��ȡ��־��Ϣ
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << msg << std::endl;
        GLCall(glDeleteShader(id)); // ɾ����ɫ��
        return 0;
    }

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program;
    GLCall(program = glCreateProgram()); /* �������� */
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    /* ����ɫ�����ӵ������� */
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program)); /* ���ӳ��� */
    GLCall(glValidateProgram(program)); /* ��֤ */

    /* ɾ����ɫ�� */
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

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
    float positions[] = {
        -0.5f, -0.5f, // 0
        0.5f, -0.5f,  // 1
        0.5f, 0.5f,   // 2
        -0.5f, 0.5f,  // 3
    };

    /* ���������������������� */
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int vao;//����Vertex Array Object,����ͳһ�������Ƶ��н�
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    //unsigned int buffer;
    //GLCall(glGenBuffers(1, &buffer)); /* ���ɻ����� */
    //GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); /* �󶨻����� */
    //GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW)); /* ���û��������� */

    GLCall(glEnableVertexAttribArray(0)); /* ���������-����0-λ�� */
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0)); /* ���ö�������-����0 */

    /*unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));*/
    IndexBuffer ib(indices, 6);

    /* ���ļ��н�����ɫ��Դ�� */
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader)); /* ʹ����ɫ������ */


    int location;
    GLCall(location = glGetUniformLocation(shader, "u_Color")); /* ��ȡָ������ͳһ������λ�� */
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f)); /* ���ö�Ӧ��ͳһ���� */


    //���
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glUseProgram(shader));

        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        GLCall(glBindVertexArray(vao));
        /* ���� */
       /* GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));*/
        vb.Bind();
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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
    GLCall(glDeleteProgram(shader)); /* ɾ����ɫ������ */

    glfwTerminate();
    return 0;
}