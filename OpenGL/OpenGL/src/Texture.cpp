#include "Texture.h"
#include "stb_image/stb_image.h"
//#include "vendor/stb_image/stb_image.h"
Texture::Texture(const std::string& path)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{

	/*
	glGenTextures(1, &m_RendererID)��
���д�������һ��������󣬲�����ID�洢�ڱ��� m_RendererID �С�
����������ڴ洢ͼ�����ݣ��Ա�����Ⱦ�����н���ӳ�䵽����ͼ���ϡ�
glBindTexture(GL_TEXTURE_2D, m_RendererID)��
���д��뽫�������󶨵���ǰ��OpenGL�����ġ�
GL_TEXTURE_2D ��ʾ�������ڲ���2D����
����������ã�
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)�������������С������Ϊ���Թ��ˡ�
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)����������ķŴ������Ϊ���Թ��ˡ�
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)�����������ˮƽ����ģʽΪ��Ե�ضϡ�
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)����������Ĵ�ֱ����ģʽΪ��Ե�ضϡ�*/
	stbi_set_flip_vertically_on_load(1);// ������stb_image�ڼ���ͼ��ʱ��ֱ��תͼ�����ݣ��Ա���OpenGL����������ϵͳһ�¡���������Ͳ���Ҫ�ֶ���תͼ������������ˡ�
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	/*glTexImage2D �� OpenGL �е�һ�����������ڶ����ά����ͼ�����������������������Ĳ�����

GL_TEXTURE_2D������һ������Ŀ�꣬��ʾ�������ڲ�������һ����ά����
0�����������ϸ�ڼ����ţ�ͨ�����ڶ༶������mipmap�������������ʹ�û����������Ϊ0��
GL_RGBA8������������ڲ���ʽ�����������ʹ��RGBA��ɫͨ����ÿ��ͨ��8λ��
m_Width �� m_Height����������Ŀ�Ⱥ͸߶ȣ�������Ϊ��λ��
0�����Ǳ߿�Ŀ�ȡ�ͨ������£����ǲ�ʹ�ñ߿����Ϊ0��
GL_RGBA�������������ݵĸ�ʽ����������ÿ�����ص���ɫͨ��˳�����������ʹ��RGBA��
GL_UNSIGNED_BYTE�������������ݵ��������ͣ���ʾÿ����ɫͨ����ֵ���޷����ֽڡ�
m_LocalBuffer������ָ���������ݵ�ָ�룬ͨ����һ�����顣*/
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));//����������
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}