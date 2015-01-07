### 计算机图形学作业
#### SA13231024 张鹏飞




**编译环境**：  

* *操作系统*：Windows 7 
* *IDE*：Visual Studio 2010 
* *OpenGL version*：3.2
* *GLSL version*：1.5
* *工具库*： glfw 和 GLEW glm数学库

*注*：这次使用了glfw工具库替代了GLUT工具库，是因为GLUT已经很久不更新了，而且各个平台下不一样，跨平台性弱一点。


**实现功能**：使用递归方法完成三维Sierpinski镂垫，实现三维变换、镜头漫游、模视变换、透视变换、添加光照功能，使用回调函数可以使用键盘、鼠标、滚轮控制三维物体。具体操作如下：

按键|功能|按键|功能
------|---- 
“W“|相机沿Z轴向前|“1”|切换光照颜色（）
“A”|相机沿X轴向左|“2”|切换光照颜色（） 
“S”|相机沿Z轴向后  |“3”|切换光照颜色（）
“D”|相机沿X轴向右 |“4”|切换光照颜色为白光
“Z”|相机沿Y轴向上 |“7”|切换旋转轴为X轴
“X”|相机沿Y轴向下 |“8”|切换旋转轴为Y轴
“T”|物体停止转动  |“9”|切换旋转轴为Z轴

另外鼠标滚轮可以改变视见体Fov，从而看到不同的投影变换效果（“R”键恢复默认视见体）
*注*菜单回调函数和拾取功能，在小作业中做过，这次没有重复。
 


**实现说明**  
程序用glfw库实现窗口显示，显示OpenGL上下文内容。由于使用OpenGL版本为3.2，使用了可编程流水线结构，用GLSL语言写顶点和片元着色器。源程序主要.cpp文件有: 

* Shader.cpp, Program.cpp 用来实现着色器文件读取，编译，链接和向着色器中输入顶点，颜色，或uniform类型数据，是CPU程序和着色器程序之间的桥梁。



* Camera.cpp 实现了一个相机类，可以设置和读取相机位置，规定视见体大小等操作。



* main.cpp 主程序，其中利用递归实现了三维镂垫，并向着色器代码中输入顶点坐标、模视变换矩阵和投影变换矩阵、光照数据等，最终显示在窗口上



* fragment.glsl,vertex.glsl，着色器代码，对物体的三维变换、视口变换和光照计算最终在着色器代码中实现。

main函数中 

```
void triangle(const point3& a, const point3& b, const point3& c, const int color)

void tetra(const point3& a, const point3& b, const point3& c, const point3& d)

void divide_tetra(const point3& a, const point3& b, const point3& c, const point3& d, int m)

```
实现了对三维Sierpinski镂垫顶点的计算，并在给各个顶点和位置相关的颜色，而且计算了顶点的向量，为后面的Phong光照模型做准备

```
//the normal of vertics
glm::vec3 normal = glm::normalize(glm::cross(b - a, c - b))
```
下面三个函数将顶点、颜色、顶点向量数据发送到着色器中，并对三维物体渲染。

```
static void LoadShaders()
static void LoadTriangle() 
static void Render() 

```


`Render（）`中向着色器发送Uniform类型变量，这是实现物体变换和镜头变换，光照的所需数据。  


```
void Update(float secondsElapsed)

```
函数用来实现回调函数，使得三维物体运动，并可以实现键盘和鼠标控制。

最后`void AppMain()`初始化glfw窗口和OpenGL环境，并对一些参数进行初始化设置。



**详细源代码见附件**

**运行截图**

![](/Users/pengfei/Desktop/1.png)
![](/Users/pengfei/Desktop/2.png)
![](/Users/pengfei/Desktop/3.png)





