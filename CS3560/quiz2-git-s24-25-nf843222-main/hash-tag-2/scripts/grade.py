"""
A grading script for hash-tag-2.

name: hash-tag-2
difficulty: 0
objective: Student is able to create tags with specific requirements.
"""

import unittest
from pathlib import Path

from git.refs.tag import Tag
from grading_lib.common import (MinimalistTestResult,
                                file_has_correct_sha512_checksum, points,
                                run_executable)
from grading_lib.repository import Repository, RepositoryBaseTestCase

PROBLEM_ROOT = Path(__file__).parent.parent

REPO_ARCHIVE_SHA512 = "bd8056e3cfd7970303bce62531c1100525d8fc2ec7c1a74f708f6291898eb1ac734caa8808cf1294333aa40fc707733a4732fbcf3459c49b1043cae5803c432c"

def is_contain_non_git_command(lines: list[str]) -> bool:
    """Check if the list of string contain tar command."""
    for raw_line in lines:
        line = raw_line.strip()
        if len(line) == 0 or line[0] == "#":
            continue

        if not line.startswith("git"):
            return True
    return False


class TestHashTagProblem(RepositoryBaseTestCase):

    def sanity_checks(self):
        # Sanity checks.
        # Test the sha512 of the repo.tar.gz.
        self.assertTrue(
            file_has_correct_sha512_checksum(REPO_ARCHIVE_SHA512, str(PROBLEM_ROOT / "repo.tar.gz")),
            "repo.tar.gz has different sha512 checksum value. Did you modify the file? repo.tar.gz must not be modified.",
        )
        if not (PROBLEM_ROOT / "answer.sh").exists():
            self.fail("Cannot find 'answer.sh' in 'hash-tag' folder. Did you move it somewhere and forget to move it back?")
        with open(PROBLEM_ROOT / "answer.sh", "r") as f:
            lines = f.readlines()
            self.assertFalse(is_contain_non_git_command(lines), msg="answer.sh appears to have non git command(s). Please comment out unrelated commands.")

    @points(10.0)
    def test_tag_1(self):
        self.sanity_checks()

        with Repository(PROBLEM_ROOT / "repo.tar.gz") as repo:
            # Run student's answer.sh file.
            result = run_executable(
                ["bash", str(PROBLEM_ROOT / "answer.sh")],
                cwd=repo.working_tree_dir,
            )
            self.assertCommandSuccessful(result)

            self.assertHasTagWithNameAt(
                repo, "#cat", "e6d82124918ae3b50be7d77949dc79011ba4573a"
            )

    @points(10.0)
    def test_tag_2(self):
        self.sanity_checks()

        with Repository(PROBLEM_ROOT / "repo.tar.gz") as repo:
            # Run student's answer.sh file.
            result = run_executable(
                ["bash", str(PROBLEM_ROOT / "answer.sh")],
                cwd=repo.working_tree_dir,
            )
            self.assertCommandSuccessful(result)

            self.assertHasTagWithNameAt(
                repo, "#dog", "e6d82124918ae3b50be7d77949dc79011ba4573a"
            )

    @points(10.0)
    def test_tag_3(self):
        self.sanity_checks()

        with Repository(PROBLEM_ROOT / "repo.tar.gz") as repo:
            # Run student's answer.sh file.
            result = run_executable(
                ["bash", str(PROBLEM_ROOT / "answer.sh")],
                cwd=repo.working_tree_dir,
            )
            self.assertCommandSuccessful(result)

            self.assertHasTagWithNameAndMessageAt(
                repo,
                "#ou",
                "Go OHIO!",
                "3f84c7384101d201769a5438c2732b52d1d2042e",
            )

    @points(10.0)
    def test_tag_4(self):
        self.sanity_checks()

        with Repository(PROBLEM_ROOT / "repo.tar.gz") as repo:
            # Run student's answer.sh file.
            result = run_executable(
                ["bash", str(PROBLEM_ROOT / "answer.sh")],
                cwd=repo.working_tree_dir,
            )
            self.assertCommandSuccessful(result)

            self.assertHasTagWithNameAndMessageAt(
                repo,
                "#100daysOfCode",
                "Learning Git today!",
                "2866fb8fefd9d3aa267610365ff0333082e561e8",
            )



if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)

