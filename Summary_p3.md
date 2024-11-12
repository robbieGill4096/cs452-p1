
CSC 452/552 Operations Systems Project 3 Threads Name:Robbie Gill Bronco ID:114085011 Date:11/12/2024

link to project Descripton:  [https://shanepanter.com/cs452/projects/p5](https://shanepanter.com/cs452/projects/p5)

1.  Project Overview In this project I'm tasked with taking an existing single threaded implimentation of merge sort and wrapping it so that it can be run in a multithreaded environment. Finally I will run a test script and performe an analysis to find the optimal number of executing threads on my target machine.
    
2.  Project Management Plan
    Timeline of development: 
    Friday - *start summary *add source code to project *review merge sort *review code implimentation *check tests/write tests *create simplified example
    Saturday 
    Sunday - completed implimentation created analysis
    Monday- Completed summary wrote finalized project and added all deliverables. 
    
    a) Task 3: Make Thread Safe (15 pts) * Code check b) Task 4: Driver app (15 pts) * Snapshots of output  [![snapshots of output with varying numbers of threads](https://github.com/robbieGill4096/cs452-p1/raw/CS452-p3/Task4testing.png)](https://github.com/robbieGill4096/cs452-p1/blob/CS452-p3/Task4testing.png)
    
    c) Task 5: Task 5 Add bash files (15 pts) * Code check (createplot.sh & graph.plt & data.dat) d) Task 6: Complete the Analysis (15 pts) * Analysis.md & Graph (Threads vs. Time to sort)
    [Link to the Analysis](Analysis.md)
  
3.  Project Deliveries a) How to compile and use my code? make clean //remove any existing code
    
    ```
    make check  //verify that the code is correct
    
    make //build source
    
    ./createplot.sh -s <numer of elements in list> <name_of_plot_file> // test perfomance of the mulithreading sort up to 32 threads 
    
    ```
    
    b) Any self-modification? The createplot.sh script had to be modified to run on the current project path, gnuplot was required to be installed to build the graph.
    
    c) Summary of Results.
    
4.  Self-Reflection of Project Overall this project was my favorite we've done so far, the memory layout question on homework3 really helped me get a grasp of how to manipulate the mergesort list efficently and understand the methodoly / design pardigram of the lab.h functions. Suprisingly the most difficult part of this project was testing it. I've been developing within github code spaces and found that there are only two available core, which is the same case for my local pc. Leaving me with the option of running the test script on onyx. Even running through onyx the test took a suprising amount of time to execute.
    
5.  Comments for Project (optional) An idea I had that for improving the speed of the project which I didn't impliment was checking the first and last elements of each sorted chunk, so that the chunks could be rearranged in a more sorted order before the final merge. However this approach could reduce the cache locality. In any case I believe to fully optimize the sorting the final merge needs to be optimized.
    
6.  Use of AI for debugging (optional)
