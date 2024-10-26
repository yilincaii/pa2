Question 1
Real password crackers try many more variations than just uppercasing and lowercasing.
 Do a little research on password cracking and suggest at least 2 other ways 
 to vary a password to crack it. Describe them both, and for each, 
 write a sentence or two about what modifications you would make to your code to implement them.

Answer:

The most brainless approach is to try every possible combination of 
characters, including adding numbers and symbols. This method is computationally intensve, 
but works well for weak passwords.
Code modification, in my current crack_password function, 
we can modify the loop to generate passwords that contain numbers and symbol
we will iterate thorugh each char in the password annd append either a 
number (0-9) or any symbol. After each modification, we can call check_password
 to see if the modified password matches the hash

 The second way is Lett speak, which means replacing letters with similar number or symbols. 
 e.g. "a becomes"4", "f"->"1"
 this way can make password harder to gusess
 For modify code, we can try to add a mapping of chars to their 
 common leet equivalents substistution.

 Question 2:
 How much working memory is needed to store all of the variables needed to execute the password cracker? 
 Based on your response would you say that a password cracker is more memory-limited 
 or is it more limited by how fast the process can run the code?

 Answer:
 I think  the password cracking is more limited by speed than by memory.
 analyze: first, let's calculate the memory. The password variables are an array of 256 bytes(max value)
 and each of the hash and given _hash are 32 bytes.
 for the other variables, such as pointers, loop index... the minimum additional overhead are likely equal to 10-20 bytes
 So the total memory consumption is : 256+64+20 = 340 bytes

 Now let's think about the speed of cracking. each tima a password is changed, the SHA256 hash
 must be computed, which involves uncomplicated calculations.
 The process requires checking all the variants and comparing hashes, which makes the speed of processing each password a bottle neck.
 