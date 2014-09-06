#ifndef __CCTEXTURE2D_H__
#define __CCTEXTURE2D_H__

#include <string>
#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"
#include "ccTypes.h"

//Cocos2d命名空间
NS_CC_BEGIN
//需要用到CCImage，这里声明一下。
class CCImage;

//纹理格式:即每个纹理中的像素单位分别是怎么为颜色值进行实际内存分配的。这个非常重要，我们在进行游戏开发的过程中，会常常与各种图片类型打交通。每种图片往往也有各自的像素格式。但当它们一旦加载到游戏中后，就会根据我们的要求变成以下某种类型的纹理。不同的纹理格式所占据的内存大小可能不同，我们要根据实际情况和需求来选择相应的纹理格式。比如我们用RGBA8888纹理格式来创建纹理，它占据的内存容量很大，如果我们要显示的纹理中没有ALPHA值，那就不应该使用带ALPHA通道的纹理格式。我们就可以改成RGB565像素格式。

typedef enum {

    //32位真彩色，最真但最耗内存
    kCCTexture2DPixelFormat_RGBA8888,
    //24位真彩色，去掉了ALPHA通道
    kCCTexture2DPixelFormat_RGB888,
    //16位色，将RGB压缩在一个字中。绿色多了1位，因为人眼对绿色更敏感。
    kCCTexture2DPixelFormat_RGB565,
    //8位色，只存ALPHA值，做遮罩图用
    kCCTexture2DPixelFormat_A8,
    //8位色，只存灰度或者强度值，做灰度图用
    kCCTexture2DPixelFormat_I8,
    //16位色，只存ALPHA值与强度值，双功能
    kCCTexture2DPixelFormat_AI88,
    //16位色，RGBA四通道各占4位。
    kCCTexture2DPixelFormat_RGBA4444,
    //16位色，RGB三通道各占5位，多1位留做ALPHA镂空使用
    kCCTexture2DPixelFormat_RGB5A1,    
    // PVR的PVRTC4压缩格式
    kCCTexture2DPixelFormat_PVRTC4,
    // PVRTC的PVRTC2压缩格式
    kCCTexture2DPixelFormat_PVRTC2,

    //默认格式RGBA8888
    kCCTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_RGBA8888,

    // 为了兼容性而保留的枚举值
    kTexture2DPixelFormat_RGBA8888 = kCCTexture2DPixelFormat_RGBA8888,
    kTexture2DPixelFormat_RGB888 = kCCTexture2DPixelFormat_RGB888,
    kTexture2DPixelFormat_RGB565 = kCCTexture2DPixelFormat_RGB565,
    kTexture2DPixelFormat_A8 = kCCTexture2DPixelFormat_A8,
    kTexture2DPixelFormat_RGBA4444 = kCCTexture2DPixelFormat_RGBA4444,
    kTexture2DPixelFormat_RGB5A1 = kCCTexture2DPixelFormat_RGB5A1,
    kTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_Default

} CCTexture2DPixelFormat;

//需要使用Shader代码片段，这里声明一下
class CCGLProgram;

//定义了纹理的一些参数
typedef struct _ccTexParams {
    GLuint    minFilter;//纹理过滤器：缩小过滤器
    GLuint    magFilter;//纹理过滤器：放大过滤器
    GLuint    wrapS;//横向纹理寻址模式
    GLuint    wrapT;//纵向纹理寻址模式
} ccTexParams;


// CCTexture2D类可以方便的从图片，文本或raw数据文件中创建OpenGL所用贴图，创建的贴图会自动转为2的幂次方大小，所以要注意对于贴图坐标的影响。

class CC_DLL CCTexture2D : public CCObject
{
public:
	//构造
CCTexture2D();
//析构
    virtual ~CCTexture2D();
	//取得纹理的描述
    const char* description(void);

    //释放数据
void releaseData(void *data);
 //保存数据
    void* keepData(void *data, unsigned int length);

    //由数据指针和指定的像素格式，图片宽高，来生成OpenGL贴图。
    bool initWithData(const void* data, CCTexture2DPixelFormat pixelFormat, \
        unsigned int pixelsWide, unsigned int pixelsHigh, const CCSize& contentSize);

//在指定的位置绘制贴图
void drawAtPoint(const CCPoint& point);
    //纹制贴图上的一个图像块
void drawInRect(const CCRect& rect);

    //由CCImage指针生成OpenGL贴图
    bool initWithImage(CCImage * uiImage);

    //由一个字符串生成OpenGL贴图。
    bool initWithString(const char *text, const CCSize& dimensions, \
        CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment, const char *fontName, float fontSize);
    //由一个字符串和指定的字体与大小生成OpenGL贴图
    bool initWithString(const char *text, const char *fontName, float fontSize);

//如果支持PVR的压缩格式
#ifdef CC_SUPPORT_PVRTC    
    //由一个PVR压缩格式的数据生成OpenGL贴图
    bool initWithPVRTCData(const void *data, int level, int bpp, \
        bool hasAlpha, int length, CCTexture2DPixelFormat pixelFormat);
#endif // CC_SUPPORT_PVRTC
    
    //从普通PVR文件生成OpenGL贴图
    bool initWithPVRFile(const char* file);

   //设置贴图参数
    void setTexParameters(ccTexParams* texParams);

    //设置为抗锯齿的贴图过滤方式（线性过滤）
    void setAntiAliasTexParameters();

    //设置为非抗锯齿的贴图过滤方式（最近点采样）
    void setAliasTexParameters();


    //生成多级贴图: 由图片数据生成一系列尺寸为2的幂次方直至当前贴图大小的贴图。系统会根据距离自动选择纹理图片。可以解决大图片显示在小空间时的闪烁问题。
    void generateMipmap();

    //取得像素格式名称
    const char* stringForFormat();

    //返回当前贴图色深，即每个像素占多少位
    unsigned int bitsPerPixelForFormat();  

//通过参数贴图格式返回纹理色深
unsigned int bitsPerPixelForFormat(CCTexture2DPixelFormat format);


	//静态函数，用于设置默认带ALPHA通道的贴图像素格式。则图片创建为贴图时，如果有ALPHA通道，则生成此默认贴图像素格式。
    static void setDefaultAlphaPixelFormat(CCTexture2DPixelFormat format);

    //静态函数，取得默认带ALPHA通道的贴图像素格式。
    static CCTexture2DPixelFormat defaultAlphaPixelFormat();

    //静态函数，设置载入PVR时是否开启ALPHA渐变，默认不开启，则ALPHA值只有是与否，无渐变。
    static void PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);

    //取得图片大小（以像素为单位）
    const CCSize& getContentSizeInPixels();
    //是否有ALPHA渐变值
bool hasPremultipliedAlpha();
//是否有多级贴图
    bool hasMipmaps();
private:
    //加载一个带ALPHA渐变的图片生成OpenGL贴图
    bool initPremultipliedATextureWithImage(CCImage * image, unsigned int pixelsWide, unsigned int pixelsHigh);
    
    //ALPHA渐变开关
    bool m_bPVRHaveAlphaPremultiplied;

    //贴图格式变量及get接口
    CC_PROPERTY_READONLY(CCTexture2DPixelFormat, m_ePixelFormat, PixelFormat)
    //贴图宽度及get接口
    CC_PROPERTY_READONLY(unsigned int, m_uPixelsWide, PixelsWide)
    //贴图高度及get接口
    CC_PROPERTY_READONLY(unsigned int, m_uPixelsHigh, PixelsHigh)

    //OpenGL贴图索引及get接口
    CC_PROPERTY_READONLY(GLuint, m_uName, Name)

    //横向贴图坐标终点。因为图片如果不是2的幂次方，图片大小会小于贴图的大小，贴图一定是2的幂次方嘛，这时候横向的贴图坐标终点不是1.0。
    CC_PROPERTY(GLfloat, m_fMaxS, MaxS)
    //纵向贴图坐标终点。
    CC_PROPERTY(GLfloat, m_fMaxT, MaxT)
    //图片大小及get接口
    CC_PROPERTY_READONLY(CCSize, m_tContentSize, ContentSize)

    // ALPHA渐变开关
    bool m_bHasPremultipliedAlpha;
	// 多级纹理开关
    bool m_bHasMipmaps;

    //Shader代码片段指针
    CC_PROPERTY(CCGLProgram*, m_pShaderProgram, ShaderProgram);
};

NS_CC_END

#endif //__CCTEXTURE2D_H__
