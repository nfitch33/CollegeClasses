# Hash Tag 2

Given a repository in `repo.tar.gz`, you are to write Git commands that will
create the following tags (one command for one tag).

| Commit Id | Tag Name | Message |
| --- | --- | --- |
| `e6d8212` | `#cat` |  |
| `e6d8212` | `#dog` |  |
| `3f84c73` | `#ou` | `Go OHIO!` |
| `2866fb8` | `#100daysOfCode` | `Learning Git today!` |


Write your Git's commands in `answer.sh`. Put each Git command on its own line. Remember
that one Git command must only create one tag. The commands must not require human's input.
While running, the current working directory will be the root of the given repository.

## Tips

- The `#` must be part of the tag name, but it is also a shell's character for a comment. You will have to find a solution for this.
- Be careful with the spelling and case sensitivity. The backtick (\`) is not part of the names or messages.
