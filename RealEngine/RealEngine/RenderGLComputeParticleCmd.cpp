#include "RenderGLComputeParticleCmd.h"

#include "GLShaderCache.h"

#include "Vector.h"
#include "Math.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


RenderGLComputeParticleCmd::RenderGLComputeParticleCmd()
{

	// ����vao;
	glGenVertexArrays(1, &render_vao);
	glBindVertexArray(render_vao);

	// ����λ�ú��ٶȻ���
	glGenBuffers(2, buffers);

	// ��ʼ��λ�û���
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(Vector4f), NULL, GL_DYNAMIC_COPY);

	// ӳ��λ�û��岢��ʹ������������
	Vector4f* positions = (Vector4f *)glMapBufferRange(GL_ARRAY_BUFFER, 0, PARTICLE_COUNT * sizeof(Vector4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for (auto i = 0; i < PARTICLE_COUNT; i++)
	{
		Vector3f randVec = Math::random_vector(-10.f, 10.f);
		positions[i] = Vector4f(randVec.x, randVec.y, randVec.z, Math::random_float());
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);


	// ��ʼ���ٶȻ���
	glBindBuffer(GL_ARRAY_BUFFER, velocity_buffer);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(Vector4f), NULL, GL_DYNAMIC_COPY);

	// ӳ���ٶȻ��岢��ʹ������������
	Vector4f* velocities = (Vector4f *)glMapBufferRange(GL_ARRAY_BUFFER, 0, PARTICLE_COUNT * sizeof(Vector4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (auto i = 0; i < PARTICLE_COUNT; i++)
	{
		Vector3f randVec = Math::random_vector(-0.1f, 0.1f);

		velocities[i] = Vector4f(randVec.x, randVec.y, randVec.z, 0.0f);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	// ��ʼ������λ�ú��ٶȵ�������
	glGenTextures(2, tbos);
	for (auto i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_BUFFER, tbos[i]);

		// buffer �� target ����
		// (GLenum target, GLenum internalformat, GLuint buffer)
		glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, buffers[i]);
	}

	// ��ʼ���������Ļ���
	glGenBuffers(1, &attractor_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, attractor_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 32 * sizeof(Vector4f), NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, attractor_buffer);

	// �����ʼ��������������
	for (auto i = 0; i < MAX_ATTRACTORS; i++)
	{
		attractor_masses[i] = 0.5f + Math::random_float() * 0.5f;
	}

	glBindVertexArray(0);
}

RenderGLComputeParticleCmd::~RenderGLComputeParticleCmd()
{

}


void RenderGLComputeParticleCmd::execute()
{
	glBindVertexArray(render_vao);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	//glPointSize(2.0f);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
}


void RenderGLComputeParticleCmd::update(float deltaTime)
{
	// ������������λ�ú������Ļ���
	Vector4f * attractors = (Vector4f *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, 32 * sizeof(Vector4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	float time = (-100000 & 0xFFFFF) / float(0xFFFFF);
	for (auto i = 0; i < 32; i++)
	{
		attractors[i] = Vector4f(sinf(time * (float)(i + 4) * 7.5f * 20.0f) * 50.0f,
			cosf(time * (float)(i + 7) * 3.9f * 20.0f) * 50.0f,
			sinf(time * (float)(i + 3) * 5.3f * 20.0f) * cosf(time * (float)(i + 5) * 9.1f) * 100.0f,
			attractor_masses[i]);
	}
	glUnmapBuffer(GL_UNIFORM_BUFFER);


	// ���������ɫ��
	auto computeShader = GLShaderCache::getInstance().findOrCreate("ComputeParticle");
	computeShader->UseProgram();

	// ��λ�ú��ٶȻ���
	glBindImageTexture(0, velocity_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(1, position_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	
	// ����ʱ����
	auto dt_location = glGetUniformLocation(computeShader->getProgramID(), "dt");
	glUniform1f(dt_location, deltaTime);

	// ִ�м�����ɫ��
	computeShader->Dispatch(PARTICLE_GROUP_COUNT, 1, 1);

	// ȷ��������ɫ����д������Ѿ����
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);


	// ��Ⱦ���ӵ���Ļ
	auto renderShader = GLShaderCache::getInstance().findOrCreate("ComputeParticleRender");
	renderShader->UseProgram();

	glm::mat4 mvp = glm::rotate(glm::translate(glm::perspective(45.0f, 1920.f / 1080.f, 0.1f, 1000.0f), { 0.0f, 0.0f, -160.0f }), time * 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	renderShader->setUniformMatrix4fv("mvp", glm::value_ptr(mvp));
}