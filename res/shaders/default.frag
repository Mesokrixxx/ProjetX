#version 330 core

flat in int	color;

out vec4	FragColor;

void	main()
{
	FragColor = 
		vec4((color >> 24) & 0xFF,
			(color >> 16) & 0xFF,
			(color >> 8) & 0xFF,
			color & 0xFF);
}
