# Problem 1 - Analysis of curl and wc with Valgrind

Here are the steps for this problem.

1. Use Valgrind to check curl while retrieving a page from `https://www.cnn.com/` and save it as `curl-output.html`.

2. Use Valgrind to check the `wc` utility while counting the line number in `curl-output.html` you saved in the previous command.

3. Create a report (PDF or Microsoft Word) that answers the following questions. **Use screenshots to support your findings.**

   - Q1: Does curl leak memory while trying to retrieve a page from `https://www.cnn.com/`?
   - Q2: How much memory in bytes does curl use while retrieving a page from `https://www.cnn.com/`?
   - Q3: Does wc leak memory while trying to count number of characters/lines in file `curl-output.html`?
   - Q4: How much memory in bytes does `wc` use?
   - Q5: How many lines are in `curl-output.html`?

4. Add (check in) the `curl-output.html` and the report to this repository in this folder (aka making a commit).

5. Push your commits out.

6. Create a tag `task-1` and push this tag out.
