# AssemblyComparer

```
    _                           _     _       
   / \   ___ ___  ___ _ __ ___ | |__ | |_   _ 
  / _ \ / __/ __|/ _ \ '_ ` _ \| '_ \| | | | |
 / ___ \\__ \__ \  __/ | | | | | |_) | | |_| |
/_/   \_\___/___/\___|_| |_| |_|_.__/|_|\__, |
                                        |___/ 
  ____                                          
 / ___|___  _ __ ___  _ __   __ _ _ __ ___ _ __ 
| |   / _ \| '_ ` _ \| '_ \ / _` | '__/ _ \ '__|
| |__| (_) | | | | | | |_) | (_| | | |  __/ |   
 \____\___/|_| |_| |_| .__/ \__,_|_|  \___|_|   
                     |_|                        

```

In this project i decided to use SIMD instructions to see how the clock cicles vary from C++ to SIMD.

**(The project just uses the xmm and ymm, i didnt use Zmm for lack of a computer it a CPU that uses AVX-512)**

First it was presented to me a **Simple Function in C++** 

```
void binarize(unsigned char *pt, unsigned char limit, int len)
{
	for(int x=0;x<len;x++)
	{
		if(pt[x]<limite){
			pt[x] = 0;		
		}else{
			pt[x] = 255;
		}
	}
}
```

Then i started the project, first i had to do a research, since i lack the proper instructions to made this project work, and i encounter the main instruction:

* PCMPGTB (Compare Packed Signed Integers for Greater Than)
