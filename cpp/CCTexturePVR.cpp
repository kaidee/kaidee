#include "CCTexture2D.h"
#include "CCTexturePVR.h"
#include "ccMacros.h"
#include "CCConfiguration.h"
#include "support/ccUtils.h"
#include "CCStdC.h"
#include "platform/CCFileUtils.h"
#include "support/zip_support/ZipUtils.h"
#include "shaders/ccGLStateCache.h"
#include <ctype.h>
#include <cctype>
//Cocos2d命名空间
NS_CC_BEGIN

#define PVR_TEXTURE_FLAG_TYPE_MASK    0xff

//PVR文件的信息标志位的各bit位意义
enum {
    kPVRTextureFlagMipmap         = (1<<8),        // 有多级纹理 
    kPVRTextureFlagTwiddle        = (1<<9),        // is twiddled
    kPVRTextureFlagBumpmap        = (1<<10),       // 是法线贴图（用于产生凹凸感）
    kPVRTextureFlagTiling         = (1<<11),       // is bordered for tiled pvr
    kPVRTextureFlagCubemap        = (1<<12),       // 是立方体环境映射贴图（一般用于做天空盒）
    kPVRTextureFlagFalseMipCol    = (1<<13),       // are there false coloured MIP levels
    kPVRTextureFlagVolume         = (1<<14),       // 立体纹理，相当于有多层的纹理。
    kPVRTextureFlagAlpha          = (1<<15),       // v2.1 is there transparency info in the texture
    kPVRTextureFlagVerticalFlip   = (1<<16),       // v2.1 is the texture vertically flipped
};
//PVR文件头标识
static char gPVRTexIdentifier[5] = "PVR!";
//所有PVR文件的格式
enum
{
	kPVRTexturePixelTypeRGBA_4444= 0x10,
	kPVRTexturePixelTypeRGBA_5551,
	kPVRTexturePixelTypeRGBA_8888,
	kPVRTexturePixelTypeRGB_565,
	kPVRTexturePixelTypeRGB_555,				// 这个Cocos2d-x暂不支持
	kPVRTexturePixelTypeRGB_888,
	kPVRTexturePixelTypeI_8,
	kPVRTexturePixelTypeAI_88,
	kPVRTexturePixelTypePVRTC_2,
	kPVRTexturePixelTypePVRTC_4,
	kPVRTexturePixelTypeBGRA_8888,
	kPVRTexturePixelTypeA_8,
};
//信息数组
static const unsigned int tableFormats[][7] = {
    //数组元素的结构为：
	// 1- PVR 文件格式
	// 2- OpenGL 内部格式
	// 3- OpenGL 格式
	// 4- OpenGL 数据类型
	// 5- 色深
	// 6- 是否压缩
	// 7- Cocos2d 像素格式
	{ kPVRTexturePixelTypeRGBA_4444, GL_RGBA,	GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4,			16, false, kCCTexture2DPixelFormat_RGBA4444	},
	{ kPVRTexturePixelTypeRGBA_5551, GL_RGBA,	GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,			16, false, kCCTexture2DPixelFormat_RGB5A1	},
	{ kPVRTexturePixelTypeRGBA_8888, GL_RGBA,	GL_RGBA, GL_UNSIGNED_BYTE,					32, false, kCCTexture2DPixelFormat_RGBA8888	},
	{ kPVRTexturePixelTypeRGB_565,	 GL_RGB,	GL_RGB,	 GL_UNSIGNED_SHORT_5_6_5,			16, false, kCCTexture2DPixelFormat_RGB565	},
	{ kPVRTexturePixelTypeRGB_888,	 GL_RGB,	GL_RGB,	 GL_UNSIGNED_BYTE,					24, false,	kCCTexture2DPixelFormat_RGB888	},
	{ kPVRTexturePixelTypeA_8,		 GL_ALPHA,	GL_ALPHA,	GL_UNSIGNED_BYTE,				8,	false, kCCTexture2DPixelFormat_A8		},
	{ kPVRTexturePixelTypeI_8,		 GL_LUMINANCE,	GL_LUMINANCE,	GL_UNSIGNED_BYTE,		8,	false, kCCTexture2DPixelFormat_I8		},
	{ kPVRTexturePixelTypeAI_88,	 GL_LUMINANCE_ALPHA,	GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,16,	false, kCCTexture2DPixelFormat_AI88	},
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	//如果程序运行在IOS上，还可支持以下信息
	{ kPVRTexturePixelTypePVRTC_2,	 GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, (unsigned int)-1, (unsigned int)-1,			2,	true, kCCTexture2DPixelFormat_PVRTC2	},
	{ kPVRTexturePixelTypePVRTC_4,	 GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, (unsigned int)-1, (unsigned int)-1,			4,	true, kCCTexture2DPixelFormat_PVRTC4	},

	{ kPVRTexturePixelTypeBGRA_8888, GL_RGBA,	GL_BGRA, GL_UNSIGNED_BYTE,					32,	false, kCCTexture2DPixelFormat_RGBA8888	},
#endif 
};

//信息表的元素数量
#define MAX_TABLE_ELEMENTS (sizeof(tableFormats) / sizeof(tableFormats[0]))
//
enum {
    kCCInternalPVRTextureFormat,
    kCCInternalOpenGLInternalFormat,
    kCCInternalOpenGLFormat,
    kCCInternalOpenGLType,
    kCCInternalBPP,
    kCCInternalCompressedImage,
    kCCInternalCCTexture2DPixelFormat,
};
//PVR文件头信息结构
typedef struct _PVRTexHeader
{
    unsigned int headerLength;	//头信息长度
    unsigned int height;			//高
    unsigned int width;			//宽
    unsigned int numMipmaps;	//是否有多级纹理
    unsigned int flags;			//标记位
    unsigned int dataLength;	//后面的像素数据长度
    unsigned int bpp;			//色深
    unsigned int bitmaskRed;	//对应红色的像素位
    unsigned int bitmaskGreen;	//对应绿色的像素位
    unsigned int bitmaskBlue; 	//对应蓝色的像素位
    unsigned int bitmaskAlpha; //对应ALPHA色的像素位
    unsigned int pvrTag;			//
    unsigned int numSurfs;		//是否有多层
} PVRTexHeader;
//构造函数
CCTexturePVR::CCTexturePVR() 
: m_uTableFormatIndex(0)
, m_uNumberOfMipmaps(0)
, m_uWidth(0)
, m_uHeight(0)
, m_bRetainName(false)
, m_bHasAlpha(false)
, m_uName(0)
, m_eFormat(kCCTexture2DPixelFormat_Default)
{
}
//析构函数
CCTexturePVR::~CCTexturePVR()
{
    CCLOGINFO( "cocos2d: deallocing CCTexturePVR" );
	//释放OpenGL贴图
    if (m_uName != 0 && ! m_bRetainName)
    {
        ccGLDeleteTexture(m_uName);
    }
}
//解压PVR像素数据
bool CCTexturePVR::unpackPVRData(unsigned char* data, unsigned int len)
{
    bool success = false;
    PVRTexHeader *header = NULL;
    unsigned int flags, pvrTag;
    unsigned int dataLength = 0, dataOffset = 0, dataSize = 0;
    unsigned int blockSize = 0, widthBlocks = 0, heightBlocks = 0;
    unsigned int width = 0, height = 0, bpp = 4;
    unsigned char *bytes = NULL;
    unsigned int formatFlags;

    //将数据地址转为头信息指针，这个就可以直接通过结构指针进行存取。
    header = (PVRTexHeader *)data;

    //格式有效性检查
    pvrTag = CC_SWAP_INT32_LITTLE_TO_HOST(header->pvrTag);

    /*
        Check that given data really represents pvrtexture

        [0] = 'P'
        [1] = 'V'
        [2] = 'R'
        [3] = '!'
    */
    if (gPVRTexIdentifier[0] != ((pvrTag >>  0) & 0xff) ||
        gPVRTexIdentifier[1] != ((pvrTag >>  8) & 0xff) ||
        gPVRTexIdentifier[2] != ((pvrTag >> 16) & 0xff) ||
        gPVRTexIdentifier[3] != ((pvrTag >> 24) & 0xff))
    {
        CCLOG("Unsupported PVR format. Use the Legacy format until the new format is supported");
        return false;
    }
    //取得配置信息
    CCConfiguration *configuration = CCConfiguration::sharedConfiguration();
	//取得标记
    flags = CC_SWAP_INT32_LITTLE_TO_HOST(header->flags);
    formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;
    bool flipped = (flags & kPVRTextureFlagVerticalFlip) ? true : false;
    if (flipped)
    {
        CCLOG("cocos2d: WARNING: Image is flipped. Regenerate it using PVRTexTool");
    }
	//查看是否支持非2的幂次方大小的纹理
    if (! configuration->supportsNPOT() &&
        (header->width != ccNextPOT(header->width) || header->height != ccNextPOT(header->height)))
    {
        CCLOG("cocos2d: ERROR: Loding an NPOT texture (%dx%d) but is not supported on this device", header->width, header->height);
        return false;
    }
	//遍历所有的格式信息数据，找到对应的格式信息。
    for (m_uTableFormatIndex = 0; m_uTableFormatIndex < (unsigned int)MAX_TABLE_ELEMENTS; m_uTableFormatIndex++)
    {
        if (tableFormats[m_uTableFormatIndex][kCCInternalPVRTextureFormat] == formatFlags)
        {
            //Reset num of mipmaps
            m_uNumberOfMipmaps = 0;

            //取得图片大小
            m_uWidth = width = CC_SWAP_INT32_LITTLE_TO_HOST(header->width);
            m_uHeight = height = CC_SWAP_INT32_LITTLE_TO_HOST(header->height);
            
            //检查是否有ALPHA通道
            if (CC_SWAP_INT32_LITTLE_TO_HOST(header->bitmaskAlpha))
            {
                m_bHasAlpha = true;
            }
            else
            {
                m_bHasAlpha = false;
            }
            
            //取得数据长度
            dataLength = CC_SWAP_INT32_LITTLE_TO_HOST(header->dataLength);

            //将数据指针偏移到头信息之后，即像素数据所在位置
            bytes = ((unsigned char *)data) + sizeof(PVRTexHeader);
            m_eFormat = (CCTexture2DPixelFormat)(tableFormats[m_uTableFormatIndex][kCCInternalCCTexture2DPixelFormat]);
            bpp = tableFormats[m_uTableFormatIndex][kCCInternalBPP];
            
            // 遍历每个多级纹理图像块
            while (dataOffset < dataLength)
            {
                switch (formatFlags) {
                    case kPVRTexturePixelTypePVRTC_2:
                        blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
                        widthBlocks = width / 8;
                        heightBlocks = height / 4;
                        break;
                    case kPVRTexturePixelTypePVRTC_4:
                        blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
                        widthBlocks = width / 4;
                        heightBlocks = height / 4;
                        break;
                    case kPVRTexturePixelTypeBGRA_8888:
                        if (CCConfiguration::sharedConfiguration()->supportsBGRA8888() == false) 
                        {
                            CCLOG("cocos2d: TexturePVR. BGRA8888 not supported on this device");
                            return false;
                        }
                    default:
                        blockSize = 1;
                        widthBlocks = width;
                        heightBlocks = height;
                        break;
                }
                
                // Clamp to minimum number of blocks
                if (widthBlocks < 2)
                {
                    widthBlocks = 2;
                }
                if (heightBlocks < 2)
                {
                    heightBlocks = 2;
                }

                dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
                unsigned int packetLength = (dataLength - dataOffset);
                packetLength = packetLength > dataSize ? dataSize : packetLength;
                
                //记录每个多级纹理图像块的像素数据地址和长度。
                m_asMipmaps[m_uNumberOfMipmaps].address = bytes + dataOffset;
                m_asMipmaps[m_uNumberOfMipmaps].len = packetLength;
                m_uNumberOfMipmaps++;
                
                //检查是否超出最大级数
                CCAssert(m_uNumberOfMipmaps < CC_PVRMIPMAP_MAX, 
                         "TexturePVR: Maximum number of mimpaps reached. Increate the CC_PVRMIPMAP_MAX value");
                //偏移到下一个多级纹理图像块。
                dataOffset += packetLength;
                
                //大小减为原来1/2。
                width = MAX(width >> 1, 1);
                height = MAX(height >> 1, 1);
            }
            
            //读取完成
            success = true;
            break;
        }
    }
	//成功判断
    if (! success)
    {
        CCLOG("cocos2d: WARNING: Unsupported PVR Pixel Format: 0x%2x. Re-encode it with a OpenGL pixel format variant", formatFlags);
    }
    
    return success;
}
//创建OpenGL贴图
bool CCTexturePVR::createGLTexture()
{	
	//保存宽高
    unsigned int width = m_uWidth;
    unsigned int height = m_uHeight;
    GLenum err;
    //如果文件中有多级纹理
    if (m_uNumberOfMipmaps > 0)
    {
		//先释放原来的纹理
        if (m_uName != 0)
        {
            ccGLDeleteTexture(m_uName);
        }
        //像素数据每字节对齐
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        //产生OpenGL贴图
        glGenTextures(1, &m_uName);
        glBindTexture(GL_TEXTURE_2D, m_uName);
        
        // 如果无多级纹理，设置最小滤波方式为线性过滤，产生抗锯齿效果。
		if (m_uNumberOfMipmaps == 1)
        {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
		else
        {  //设置最小滤波方式为最近点采样,这种方式有锯齿。
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }
		//设置最大滤波方式为线性过滤
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//设置贴图的横向纹理寻址模式为边缘截取模式。总是忽略边界。
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//设置贴图的纵向纹理寻址模式为边缘截取模式。总是忽略边界。
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    //检错
    CHECK_GL_ERROR_DEBUG(); // clean possible GL error
    //取得对应格式的相关信息。
	GLenum internalFormat = tableFormats[m_uTableFormatIndex][kCCInternalOpenGLInternalFormat];
	GLenum format = tableFormats[m_uTableFormatIndex][kCCInternalOpenGLFormat];
	GLenum type = tableFormats[m_uTableFormatIndex][kCCInternalOpenGLType];
    bool compressed = (0 == tableFormats[m_uTableFormatIndex][kCCInternalCompressedImage]) ? false : true;

    // 循环产生多级纹理贴图。
    for (unsigned int i = 0; i < m_uNumberOfMipmaps; ++i)
    {	
		//检查配置信息是否支持压缩格式。
        if (compressed && ! CCConfiguration::sharedConfiguration()->supportsPVRTC()) 
        {
			CCLOG("cocos2d: WARNING: PVRTC images are not supported");
			return false;
		}
        //取得当前级别的图像块的像素数据地址和长度。
		unsigned char *data = m_asMipmaps[i].address;
		unsigned int datalen = m_asMipmaps[i].len;
        //如果是压缩格式，则产生压缩格式的贴图。
		if (compressed)
        {
			glCompressedTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, datalen, data);
        }
		else
        {//产生一般格式的贴图。
			glTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, format, type, data);
        }
        //如果是非2的幂次方大小，则提示。
		if (i > 0 && (width != height || ccNextPOT(width) != width ))
        {
			CCLOG("cocos2d: TexturePVR. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%u != height=%u", i, width, height);
        }
        //检错
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			CCLOG("cocos2d: TexturePVR: Error uploading compressed texture level: %u . glError: 0x%04X", i, err);
			return false;
		}
        //变为原来大小的1/2。
		width = MAX(width >> 1, 1);
		height = MAX(height >> 1, 1);
    }
        
    return true;
}

//成员函数：加载PVR图片
bool CCTexturePVR::initWithContentsOfFile(const char* path)
{
    unsigned char* pvrdata = NULL;
    int pvrlen = 0;
 	//定义字符串变量，存储转换为小写的路径字符串。   
    std::string lowerCase(path);
    for (unsigned int i = 0; i < lowerCase.length(); ++i)
    {
        lowerCase[i] = tolower(lowerCase[i]);
    }
    //检查是否是ccz格式。
    if (lowerCase.find(".ccz") != std::string::npos)
    {
		//调用压缩库函数将文件数据读取到为pvrdata申请的内存中。取得其大小存入pvrlen变量中。
        pvrlen = ZipUtils::ccInflateCCZFile(path, &pvrdata);
    }
	//检查是否是gz格式。
    else if (lowerCase.find(".gz") != std::string::npos)
    {	
		//调用压缩库函数将文件数据读取到为pvrdata申请的内存中。取得其大小存入pvrlen变量中。
        pvrlen = ZipUtils::ccInflateGZipFile(path, &pvrdata);
    }
    else
    {
		 //普通PVR文件，将文件数据读取到一块内存中返回给pvrdata。取得其大小存入pvrlen变量中。
        pvrdata = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", (unsigned long *)(&pvrlen));
    }
    //如果读取失败则返回
    if (pvrlen < 0)
    {
        this->release();
        return false;
    }
    
    m_uNumberOfMipmaps = 0;

    m_uName = 0;
    m_uWidth = m_uHeight = 0;
    m_bHasAlpha = false;

    m_bRetainName = false; 
	//如果解压数据失败则返回。
	//解压后，如果创建贴图失败则返回。
    if (!unpackPVRData(pvrdata, pvrlen)  || !createGLTexture())
    {
        CC_SAFE_DELETE_ARRAY(pvrdata);
        this->release();
        return false;
    }
	//释放数据占用的内存。
    CC_SAFE_DELETE_ARRAY(pvrdata);
    
    return true;
}
//导出的静态函数：加载PVR图片
CCTexturePVR * CCTexturePVR::pvrTextureWithContentsOfFile(const char* path)
{
    return CCTexturePVR::create(path);
}
//静态函数：加载PVR图片
CCTexturePVR * CCTexturePVR::create(const char* path)
{
	//new 一个新的CCTexturePVR
    CCTexturePVR * pTexture = new CCTexturePVR();
    if (pTexture)
    {
		//调用成员函数加载PVR图片
        if (pTexture->initWithContentsOfFile(path))
        {
			//如果成功,设置交由内存管理器使用引用计数器进行内存管理。
            pTexture->autorelease();
        }
        else
        {	
			  //否则释放纹理
            delete pTexture;
            pTexture = NULL;
        }
    }
	//返回这个CCTexturePVR
    return pTexture;
}

NS_CC_END
