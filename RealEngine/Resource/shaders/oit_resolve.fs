#version 430 core

layout(binding = 0, r32ui) uniform uimage2D head_pointer_image;
layout(binding = 1, rgba32ui) uniform uimageBuffer list_buffer;

layout(location = 0) out vec4 color;

#define MAX_FRAGMENTS 40

uvec4 fragment_list[MAX_FRAGMENTS];

void main()
{
   uint current_index;
   uint fragment_count = 0;
   
   current_index = imageLoad(head_pointer_image, ivec2(gl_FragCoord.xy)).x;
   
   // 记录当前片段所有的颜色值
   while(current_index != 0 && fragment_count < MAX_FRAGMENTS)
   {
		uvec4 fragment = imageLoad(list_buffer, int(current_index));
		
		fragment_list[fragment_count] = fragment;
		fragment_count++;
   }
   
   // 按照深度进行排序
   uint i, j;
   if(fragment_count > 1)
   {
		for(i = 0; i < fragment_count - 1; i++)
		{
			for(j = i; j < fragment_count; j++)
			{
				uvec4 fragment1 = fragment_list[i];
				uvec4 fragment2 = fragment_list[j];
				
				float depth1 = uintBitsToFloat(fragment1.z);
				float depth2 = uintBitsToFloat(fragment2.z);
				
				if (depth1 < depth2)
				{
					fragment_list[i] = fragment2;
					fragment_list[j] = fragment1;
				}
			}
		}
   }
   
   // 将该片段链表中记录的颜色混合
   vec4 final_color = vec4(0.0);
   for(i = 0; i < fragment_count; i++)
   {
		vec4 modulator = unpackUnorm4x8(fragment_list[i].y);
		
		final_color = mix(final_color, modulator, modulator.a);
   }
   
   color = final_color;
}