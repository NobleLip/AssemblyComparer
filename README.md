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

After this , it was just programming it using all the SIMD registers that i had available.

For Array it length bigger than:

* **32 Bytes** : It uses Ymm, Xmm and Compares one by one.
* **16 Bytes** : Xmm and Compares one by one.
* **Less than 16 Bytes** : Compares one by one.

## Analyze Clock Cycles

After all is properly working i started to test the values by counting the clock cycles used in each function, but i noticed that the CPU sometimes stopped the program because it was needed for more important tasks, so i had to ignore the Max number of clock and the average number since the max would not give me a accurate number, soo i had to look for the median of all the results.

#### Clock Cicles in C++**

![C++](/img/ProvaC.PNG)

#### Clock Cicles in Assembly**

![Assembly](/img/ProvaAssembly.PNG)

#### Comparing Values

![Comapred](/img/GRaficos.PNG)

![Differences](/img/Diferen.PNG)
