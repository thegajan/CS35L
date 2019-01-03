Gajan Nagaraj
904937784
Lab7
Assignment 6

When I began to multithread the ray tracer, I did not have trouble finding out what I needed to change to make the program
parallelized. However, I did have an issue finding out what variables I needed to make global so that my main function can
communicate with the function I abstracted to run in parallel. I did not realize I needed to do this at first and ended up with a
bunch of compilation errors. I quickly noticed this what the issue and realized I must make any variables that are accessed by both
global.

After running make clean check, I could see that my parallelization greatly improved the run time of the ray tracer. As the tracer
ran with more threads, the run time decreased by about half. this makes sense because if we double the amount of threads that are
used then the tracer should run in half the amount of time because the extra threads are helping to compute the output concurrently.

Lastly, I also checked the output of the images to see that they are correct. The diff also did not output anything, so I know I did
not incorrectly modify the ray tracer.
