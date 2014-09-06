#ifndef __CCPVRTEXTURE_H__
#define __CCPVRTEXTURE_H__

#include "CCStdC.h"
#include "CCGL.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
//Cocos2d命名空间
NS_CC_BEGIN

//用于多级纹理的结构
struct CCPVRMipmap {
    unsigned char *address;
    unsigned int len;
};

//最大的多级纹理级数
enum {
    CC_PVRMIPMAP_MAX = 16,
};


//所支持的 PVR 图片格式:
    - RGBA8888
    - BGRA8888
    - RGBA4444
    - RGBA5551
    - RGB565
    - A8
    - I8
    - AI88
    - PVRTC 4BPP
    - PVRTC 2BPP

class CCTexturePVR : public CCObject
{
public:
	//构造
    CCTexturePVR();
	//析构
    virtual ~CCTexturePVR();
    //成员函数：载入一个PVR图片文件
    bool initWithContentsOfFile(const char* path);

    //导出的静态函数：载入一个PVR图片文件。此函数为可供js调用。
    CC_DEPRECATED_ATTRIB一个UTE static CCTexturePVR* pvrTextureWithContentsOfFile(const char* path);
    //静态函数：载入一个PVR图片文件
    static CCTexturePVR* create(const char* path);
    
    //相关属性的获取
	//取得贴图索引
    inline unsigned int getName() { return m_uName; }
	//取得
    inline unsigned int getWidth() { return m_uWidth; }
    inline unsigned int getHeight() { return m_uHeight; }
	//取得是否有ALPHA通道
    inline bool hasAlpha() { return m_bHasAlpha; }
	//取得多级纹理的级数
    inline unsigned int getNumberOfMipmaps() { return m_uNumberOfMipmaps; }
	//取得图片格式
    inline CCTexture2DPixelFormat getFormat() { return m_eFormat; }
	//取得是否是供Retain显示屏使用的高清图片 。
    inline bool isRetainName() { return m_bRetainName; }
	//设置为供Retain显示屏使用的高清图片。
    inline void setRetainName(bool retainName) { m_bRetainName = retainName; }

private:
	//解压PVR图片数据
    bool unpackPVRData(unsigned char* data, unsigned int len);
	//创建OpenGL纹理
    bool createGLTexture();
    
protected:
	//多级纹理的各级信息结构。
    struct CCPVRMipmap m_asMipmaps[CC_PVRMIPMAP_MAX];   // pointer to mipmap images    
	//多级纹理的最大级别数
    unsigned int m_uNumberOfMipmaps;                    // number of mipmap used
    //
    unsigned int m_uTableFormatIndex;
    unsigned int m_uWidth, m_uHeight;
	//贴图索引
    GLuint m_uName;
	//是否有Alpha通道
    bool m_bHasAlpha;
    //是否是供Retain显示屏使用的高清图片 。
    bool m_bRetainName;
	//图片格式
    CCTexture2DPixelFormat m_eFormat;
};

NS_CC_END


#endif //__CCPVRTEXTURE_H__
