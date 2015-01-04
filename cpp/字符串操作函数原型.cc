//

#include<iostream>
using namespace std;

/*

Strcat函数原型

*/

char *strcat(char *strDest, const char *strScr) //将源字符串加const，表明其为输入参数
{
       char * address = strDest;             //该语句若放在assert之后，编译出错
       assert((strDest != NULL) && (strScr != NULL)); //对源地址和目的地址加非0断言
       while(*strDest)             //是while(*strDest!=’/0’)的简化形式
       {                        //若使用while(*strDest++)，则会出错，因为++是不受循环
              strDest++;               //约束的。所以要在循环体内++；因为要是*strDest最后指
       }                        //向该字符串的结束标志’/0’。
       while(*strDest++ = *strScr++) 
       {
              NULL;                 //该循环条件内可以用++，
       }                          //此处可以加语句*strDest=’/0’;有无必要？
return address;               //为了实现链式操作，将目的地址返回
}

char *strcpy(char *strDest,  const char *strSrc)
{
       char *address=strDest;
       assert((strDest!=NULL) &&  (strSrc!=NULL));
       while(*strSrc!='\0')
       {
              *strDest++=*strSrc++;
       }
      *strDest='\0';
       return address;
}

// 将两个char类型链接
char *strcat(char *strDest,const char *strSrc)
{
      char *address=strDest;
      assert((strDest!=NULL) &&  (strSrc!=NULL));
      while(*strDest!='\0')
            strDest++;
      while(*strSrc!='\0')
            *strDest++=*strSrc++;
      *strDest='\0';
      return adress
}


int strcmp(const char *str1,const char *str2)
{
      assert((*str1!='\0' && *str2!='\0')
      while(*str1 && *str2 && *str1==*str2)
      {
         str1++;
         str2++;
      }
      return *str1-*str2;
}

int strlen(const char *str)
{
       int len;
       assert(str!=NULL);
       while(*str!='\0')
       {
              len++;
       }
       return len;
}

void *memcpy(void *dst, void *src, size_t n)
{
      char *dp = (char*)dst;
      char *sp = (char*)src;
      assert((src!=0) && (dst!=0) && n>0));
      while(n--)
             *(dp++)=*(sp++);
      *dp='\0';
      return dst;
}


// 注意对于重合的要反向拷贝
void *memmove(void *dst,const void *src,int n) 
{ 
     char *dp = (char *)dst; 
     char *sp = (char *)src; 
     assert((src!=0)&&(dst!=0)&&(n>0));
     if(sp>dp || (sp+n)<dp)
     {
              while(n--)
                     *(dp++)=*(sp++);
              *dp='\0';
     }else if(sp<dp)
     {
              sp += n;
              dp += n;
              *dp = '\0';
              while(n--)
                  *(--dp) = *(--sp);
     }
     return dst;
}

int main()
{	
	

	cout<<endl;
}