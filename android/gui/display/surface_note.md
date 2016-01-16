
#### point 
- draw翻译绘制，render翻译为渲染，含义接近，一般opengl会说render，3d不会用draw
- 应用绘制UI有两个途径：Canvas 或者 OpenGL
- Canvas只能绘制2D，一般的应用，系统UI用Canvas画，部分Canvas接口支持硬件加速
- Producer是dequeueBuffer和queueBuffer，Consumer是acquireBuffer和releaseBuffer
- 2个buffer和3个buffer区别：实际显示流程有三个角色，应用（绘制Surface），SurfaceFlinger（合成Surface），底层显示（显示Surface内容到屏幕），所以2个buffer理想情况下在一个VSYNC周期内，完成一帧的绘制，合成工作，显示延迟（从绘制到显示到屏幕）认为是一个VSYNC周期；如果是3个buffer的话，是两个VSYNC完成一帧的绘制，合成工作，显示的延迟变为2个VSYNC周期，但是时间要求宽松了，不容易丢帧


####各种名词
######Producer
######Consumer
######WindowManager
######Hardware Composer
######Gralloc
######BufferQueue
######SurfaceFlinger

######Synchronization framework???

######Surface, SurfaceHolder, EGLSurface, SurfaceView, GLSurfaceView, SurfaceTexture, TextureView




