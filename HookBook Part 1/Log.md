# Author
Log.md
Meghana Chamarty
mc3547
CS223 HW#3
3/14/2023
This file outlines the time spent on the HookBook part 1 assignment

# Estimate of time to complete assignment
19 hours 

# Actual time to complete assignment
| Date | Time Started | Time Spent | Work completed |
| :--: | -----------: | ---------: | :------------- |
| 2/20 |       5:00pm |       8:00 | read assignment, began planning out program|
| 2/21 |       5:00pm |       8:00 | read assignment, began planning out program|
| 2/22 |       5:00pm |       8:00 | began writing functions outlined in pirate_list.h|
| 2/26 |       3:00pm |       5:00 | debugged pirate_list.c functions|
| 3/03 |       7:00pm |      11:00 | started hookbook.c. worked on the file I/O part|
| 3/05 |       7:00pm |      9:00pm| wrote the rest of hookbook.c|
| 3/11 |       3:00pm |     11:00 pm | debugged and figured out edge cases|
| 3/12 |       3:00pm |     7:00 pm| debugged and figured out edge cases|
| 3/13 |       6:00pm |     10:00 pm | debugged and figured out edge cases|
| 3/14 |       4:00pm |     8:00 pm  | debugged and figured out edge cases|
|      |              |       37:00 | total time spent |

# Collaboration
I discussed my solution with: ULAs at office hours 

# Discussion
I had some issues with initialization and freeing memory. At first, I found it difficult to conceptualize the memory structure. Once I was able to determine that it was a struct pointing to a list of pointers to structs, I was able to write the main function and smaller functions easier. I found it difficult to keep track of what to allocate on the heap and what not to allocate in the heap which is why debugging took a while. I also had issues with character formatting and dealing with newline characters in fget. Once I sorted those issues out the program ran well on the public tests and my own test cases. 