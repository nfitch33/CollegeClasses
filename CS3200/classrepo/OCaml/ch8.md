## ch8.5. Memoization
## ch8.7. [Promises](promise)

In Lwt, a `promise` is a reference: a value that is permitted to mutate at most once. When created, it is like an empty box that contains nothing. We say that the promise is `pending`. Eventually the promise can be `fulfilled`, which is like putting something inside the box.
