#version 430 core
layout(early_fragment_tests) in;

layout (binding = 0, r32ui) uniform uimage2D head_pointer_image;
layout (binding = 1, rgba32ui) uniform writeonly uimageBuffer list_buffer;

layout (binding = 0, offset = 0) uniform atomic_uint list_counter;

layout (location = 0) out vec4 FragColor;

void main()
{

	// 这里简单的设置为白色
	FragColor = vec4(1.0);

	uint index = atomicCounterIncrement(list_counter);
	uint old_head = imageAtomicExchange(head_pointer_image, ivec2(gl_FragCoord.xy), uint(index));
   
	uvec4 item;
	item.x = old_head;
	item.y = packUnorm4x8(FragColor);
	item.z = floatBitsToUint(gl_FragCoord.z);
	item.w = 0;
	
	imageStore(list_buffer, int(index), item);
}