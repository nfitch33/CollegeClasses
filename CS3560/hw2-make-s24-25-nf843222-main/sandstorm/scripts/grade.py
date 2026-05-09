"""
Grade the sandstorm problem.

The name `test_sandstorm_happening` and `test_sandstorm_not_active` are because we
are using the command line option `-k <text>` to run specific test case. Originally
the name is `test_sandstorm_active`, but using `-k active` will run both test cases
since `active` is a substring of `inactive`.

difficulty: 1
objective: Student should know the fundamental concept about rule in GNU Make.
"""

import subprocess
import unittest
from time import sleep

from grading_lib.common import (
    BaseTestCase,
    MinimalistTestResult,
    run_executable,
    points,
)

WAIT_AFTER_TOUCH = 0.8


class TestSandstormProblem(BaseTestCase):
    @points(5.0)
    def test_sandstorm_happening(self):
        subprocess.run("touch sandstorm.txt", shell=True)
        sleep(WAIT_AFTER_TOUCH)

        result = run_executable(["make", "--silent"])
        self.assertCommandSuccessful(result)

        assert (
            result.output == "warning, a sandstorm is active!\n"
        ), f"Modification date (and time) of 'sandstorm.txt' is newer than the 'calm.txt', but make output is not as expected. The output is\n\n{result.output}"

    @points(5.0)
    def test_sandstorm_not_active(self):
        subprocess.run("touch calm.txt", shell=True)
        sleep(WAIT_AFTER_TOUCH)

        result = run_executable(["make", "--silent"])
        self.assertCommandSuccessful(result)

        assert (
            result.output == ""
        ), f"Modification date (and time) of 'calm.txt' is newer than the 'sandstorm.txt', but make output is not as expected. The output is\n\n{result.output}"


if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
