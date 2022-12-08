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

	// 原子计数器生成一个全新的索引
	uint index = atomicCounterIncrement(list_counter);
	
	// 将新的索引写入头指针图像(gl_FragCoord.xy)的位置上，并返回旧的索引（旧的索引代表上一个片段在list_buffer中的位置）
	uint old_head = imageAtomicExchange(head_pointer_image, ivec2(gl_FragCoord.xy), uint(index));
   
	// 构建一个新的listBuffer节点，记录上个片段在listBuffer中的位置（当作上一个片段的指针使用）,当前片段的颜色和深度等数据
	uvec4 item;
	item.x = old_head;
	item.y = packUnorm4x8(FragColor);
	item.z = floatBitsToUint(gl_FragCoord.z);
	// w分量暂时没有使用
	item.w = 0;
	
	// 将该节点插入全新索引的位置（即链表的末尾）
	imageStore(list_buffer, int(index), item);
}