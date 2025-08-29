#include<GLFW/glfw3.h>
#include<stdio.h>
int main()
{
GLFWwindow window;
GLFWmonitor monitor;
const GLFWvidmode video_mode;
int desktop_width,desktop_height;
int window_width,window_height;
if(!glfwInit())
{
printf("Unable to create graph template\n");
return 0;
}
monitor=glfwGetPrimaryMonitor();
video_mode=glfwGetVideoMode(monitor);
desktop_width=video_mode->width;
desktop_height=video_mode->height;
window_width=1080;
window_height=720;
window_position_x=(desktop_width/2)-(window_width/2);
window_position_y=(desktop_height/2)-(window_height/2);

window=glfwCreateWindow(window_width,window_height,"Graph Plot",NULL,NULL);
if(!window)
{
printf("Uable to create window\n");
glfwTerminate();
return 0;
}
glfwSetWindowPos(window,window_position_x,window_position_y);
glfwMakeContextCurrent(window);
while(!glfwWindowShouldClose(window))
{
glClear(GL_COLOR_CUFFER_BIT);
//update_view(window_width,window_height);
glfwSwapBuffers(window);
glfwPollEvent();
}
glfwDestroyWindow(window);
glfwTerminate();

return 0;
}
