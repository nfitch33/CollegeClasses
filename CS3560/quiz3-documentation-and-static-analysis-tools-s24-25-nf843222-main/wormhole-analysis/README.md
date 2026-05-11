# Wormhole (Analysis)

Given the program that solves the wormhole problem (problem description is given in Appendix B). Using any of the profiling tools/methods you learn in class, profile the runtime and/or memory usage of the program.

Answer **two** of the following questions.

1. On average (across the 10 given input files), how long (in milliseconds) does the program take to execute the `recursion` function?
2. On average (across the 10 given input files), how much memory (in MB) does the program use?
3. If there is a runtime limit of 300 milliseconds, would the program be able to sastisfy this requirement given the data you collect? Provide a brief justification.

## Submission

1. Prepare a report (e.g. a Microsoft Word document) with the answers to two of the questions above.
2. Check in the report file into this folder (aka make a commit).
3. If you modify the code to add your custom profiling code, make a commit of the changes as well.
4. Push your commits to GitHub.

## Appendix A - Tips

Here is the command to build the C++ version of the program

```console
make build
```

Here is an example of running the program with `testdata/1.in` as its input (using input redirection).

```console
$ ./wormhole-program < ./testdata/1.in
Waiting for inputs ...
2
```

If you prefer, a python implementation is also available in `program.py`.

## Appendix B - Original Problem Prompt

Farmer John's hobby of conducting high-energy physics experiments on
weekends has backfired, causing N wormholes (`2 <= N <= 12`, `N` even) to
materialize on his farm, each located at a distinct point on the 2D map of
his farm.  

According to his calculations, Farmer John knows that his wormholes will
form `N/2` connected pairs.  For example, if wormholes A and B are connected
as a pair, then any object entering wormhole A will exit wormhole B moving
in the same direction, and any object entering wormhole B will similarly
exit from wormhole A moving in the same direction.  This can have rather
unpleasant consequences.  For example, suppose there are two paired
wormholes `A` at `(0,0)` and `B` at `(1,0)`, and that Bessie the cow starts from
position `(1/2,0)` moving in the +x direction.  Bessie will enter wormhole B,
exit from A, then enter B again, and so on, getting trapped in an infinite
cycle!

Farmer John knows the exact location of each wormhole on his farm.  He
knows that Bessie the cow always walks in the +x direction, although he
does not remember where Bessie is currently located.  Please help Farmer
John count the number of distinct pairings of the wormholes such that
Bessie could possibly get trapped in an infinite cycle if she starts from
an unlucky position.

**PROBLEM NAME:** wormhole

**INPUT FORMAT:**


* Line 1: The number of wormholes, N.

* Lines 2..1+N: Each line contains two space-separated integers
        describing the (x,y) coordinates of a single wormhole.  Each
        coordinate is in the range 0..1,000,000,000.

**SAMPLE INPUT (file wormhole.in):**

```
4
0 0
1 0
1 1
0 1
```

**INPUT DETAILS:**

There are 4 wormholes, forming the corners of a square.

**OUTPUT FORMAT:**

* Line 1: The number of distinct pairings of wormholes such that
        Bessie could conceivably get stuck in a cycle walking from
        some starting point in the +x direction.

**SAMPLE OUTPUT (file wormhole.out):**

```
2
```

**OUTPUT DETAILS:**

If we number the wormholes 1..4, then by pairing 1 with 2 and 3 with 4,
Bessie can get stuck if she starts anywhere between (0,0) and (1,0) or
between (0,1) and (1,1).  Similarly, with the same starting points, Bessie
can get stuck in a cycle if the pairings are 1-3 and 2-4.  Only the
pairings 1-4 and 2-3 allow Bessie to walk in the +x direction from any
point in the 2D plane with no danger of cycling.
