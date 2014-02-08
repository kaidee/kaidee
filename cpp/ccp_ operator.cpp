inline cocos2d::CCPoint operator + (const cocos2d::CCPoint& v1, const cocos2d::CCPoint v2)
{
    return ccp(v1.x + v2.x, v1.y + v2.y);
}

inline cocos2d::CCPoint operator - (const cocos2d::CCPoint& v1, const cocos2d::CCPoint v2)
{
    return ccp(v1.x - v2.x, v1.y - v2.y);
}

inline cocos2d::CCPoint operator - (const cocos2d::CCPoint& v)
{
    return ccp(-v.x, -v.y);
}

inline cocos2d::CCPoint operator * (const cocos2d::CCPoint& v1, float scale)
{
    return ccp(v1.x * scale, v1.y * scale);        
}

inline cocos2d::CCPoint operator * (float scale, const cocos2d::CCPoint& v1)
{
    return ccp(v1.x * scale, v1.y * scale);        
}

inline cocos2d::CCPoint operator / (const cocos2d::CCPoint& v1, float scale)
{
    return ccp(v1.x / scale, v1.y / scale);        
}

inline bool operator == (const cocos2d::CCPoint& v1, const cocos2d::CCPoint& v2)
{
    return (v1.x == v2.x) && (v1.y == v2.y);
}

inline bool operator != (const cocos2d::CCPoint& v1, const cocos2d::CCPoint& v2)
{
    return (v1.x != v2.x) || (v1.y != v2.y);
}