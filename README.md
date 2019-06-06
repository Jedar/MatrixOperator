# Big Number Matrix Operator  
```  
 ____ ___ ____   _   _ _   _ __  __ ____  _____ ____    
| __ )_ _/ ___| | \ | | | | |  \/  | __ )| ____|  _ \   
|  _ \| | |  _  |  \| | | | | |\/| |  _ \|  _| | |_) |  
| |_) | | |_| | | |\  | |_| | |  | | |_) | |___|  _ <   
|____/___\____| |_| \_|\___/|_|  |_|____/|_____|_| \_\  
                                                      
 __  __    _  _____ ____  _____  __  
|  \/  |  / \|_   _|  _ \|_ _\ \/ /  
| |\/| | / _ \ | | | |_) || | \  /   
| |  | |/ ___ \| | |  _ < | | /  \   
|_|  |_/_/   \_\_| |_| \_\___/_/\_\  
```

## Explain  
   This is Lab4 of course OOP  

## How to build  
1. build main  
   `make`  
2. run main  
   `make run`  
3. build cmder tool  
   `make cmder`  
4. clean  
   `make clean`  

## How to use  
1. for main  
   Input file:  
   matrix.in  
   expression.in  

   Output file:  
   result.out  

   you can change default file in FileUtil.h  

2. for cmder  
   use  
   `cd bin`  
   `./cmder`  
   to run  

   type "help" get help message  

## Change Log
2019.6.6  
Fix error in big number subtraction  
  
2019.6.6  
Add test case of TA  
  
2019.6.6  
Fix Polish RPN, let operation in one expression won't affect next expression  
  
2019.6.6  
Fix output file format, add separator  

2019.6.6  
Fix memory leak problem, free matrix after single operation  
