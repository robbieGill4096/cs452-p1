Task 6 - Complete the Analysis (ABET Outcome 1)

 ## Analysis

![Graph of threads vs time for multi-threaded implimentation of mergesort](student_plot.png)

Were you able to generate something close to what the example showed? Why or why not.
Did you see a slow down at some point why or why not?

The graph I was able to create looked very similar to the one shown. I tested my code on the Boise State ONYX cluster. I did this because my local pc aswell as github codespaces only support up to 2 parallel threads, this would severerly impact my ability to test a multithreaded application because after 2 threads are reached any testing beyound that is going to just add incredible amounts of overhead to the program.
Onyx supports up to 32 seperate threads, so I had a larger number of threads to work with than shanes Mac book. This explains the positive difference in performance on my tests compared to shanes loss of speed starting around 9 threads which seemed to be the limit for for his M1 Macbook. where in my case Onyx still had plently of free threads so my graph continued to speed up linearly positive with some small deviation up until 32 threads running in parallel. There were some marginal slow downs, I would attribute to the load of other students working in the labs on the cluster. If I were to test it again perhaps running it very early or late perhaps I could get a faster performance.

Did your program run faster and faster when you added more threads? Why or why not?

Yes the program continued to speed up as more threads were added, I think for the ONYX system a larger upper limit than 32 threads would have been a better test but would take alot of time. One aspect to note is that the size of the number of elements in the array matters for this question. for a large number of elements being sorted in the example the larger thread count positivly impacted the perfomance. for smaller numbers this could be detrimental because of the overhead created by the switching. In the time it took for all the threads to switch a smaller number of threads could complete the sorting computation, so finding the correct balance of threads motivates this analysis. 

What was the optimum number of threads for your machine?

32, This is the max number of physical threads avaiable on the Onyx cluster for a single user to utilize at once. 

What was the slowest number of threads for your machine?

1 thread. The greatest increase was from 1 thread to 2 nearly doubling perfomance.after that each thread seemed to add logarithmic diminishing returns up until the physical number of seperate avaialble processors was reached. 
Like stated above if the number of elements n was much smaller 1 thread could be the fastest if n was small enough. Or if the elements are already in nearly sorted order. 
