import functools
import hashlib
import unittest
from pathlib import Path

from grading_lib.common import BaseTestCase, MinimalistTestResult, run_executable, points

PROBLEM_ROOT = Path(__file__).parent.parent


class TestMergeConflictProblem(BaseTestCase):
    def read_file(self, filepath: str | Path) -> str:
        if isinstance(filepath, str):
            filepath = Path(filepath)

        if not (PROBLEM_ROOT / "main.cpp").exists():
            raise FileNotFoundError(
                "Cannot find 'main.cpp' file in the problem's folder."
            )
        with open(PROBLEM_ROOT / "main.cpp", "r") as f:
            content = f.read()
        return content

    @points(5.0)
    def test_markers(self):
        content = self.read_file("main.cpp")
        lines = content.split("\n")
        for line in lines:
            part = line[0:7]
            self.assertFalse(
                part in ["<<<<<<<", "|||||||", "=======", ">>>>>>>"],
                "Merge conflict marker is still present in the file.",
            )

    @points(5.0)
    def test_result(self):
        # Build the file.
        result = run_executable(["make", "build"], cwd=PROBLEM_ROOT)
        self.assertCommandSuccessful(result)

        # Run the executable.
        result = run_executable(["./calc-fibonacci", "6"], cwd=PROBLEM_ROOT)
        self.assertCommandSuccessful(result)
        self.assertCommandOutputEqual(result, "1\n1\n2\n3\n5\n8\n")
        


if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
