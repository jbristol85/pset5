# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

synonym for the disease known as silicosis

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be one of the following:

       RUSAGE_SELF
              Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

       RUSAGE_CHILDREN
              Return resource usage statistics for all children of the calling process that have terminated and been waited for.  These statistics will include the resources used
              by grandchildren, and further removed descendants, if all of the intervening descendants waited on their terminated children.

       RUSAGE_THREAD (since Linux 2.6.26)
              Return resource usage statistics for the calling thread.


## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

to conserve memory.  It allows the computer to reference the information rather copy and store it.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The main function uses a for loop with the fgetc function within.  Fgetc will get the next character in the file.  The for loop will continue to pull each character until it reaches the end of the file that is passed in.  Within the for loop the program will first check to verify that the character is alpha, or contains an ‘ and that the index of the character is greater than 0.  If those conditions are met, the character is appended to the word that is being built.  The program then checks to make sure that the word is not greater than the longest word in the dictionary (45 characters).  If it is greater, the program will basically absorb the remainder of the characters until the end of it and set the index back to 0. Similarly, the program will do the same process for a digit found as well.  If the program reaches a space, the program will append a \0 character onto the word denoting the end of the string and it will increase the word count by 1 and reset the index to 0.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc allows us to verify that the word's characters are alpha, an ', and not longer than the longest word in the dictionary.  Fscanf does not have that ability to do those kind of checks.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Const ensures that those variable are not changed in anyway.  If they could change then the program could become buggy.
