"""
A script that grade this problem.

Steps:
1. Make a copy of the student Makefile to `answer.mk`
2. In this new Makefile, overwrite the `SHELL` variable with our `shell.py`
3. Run `make -f answer.mk` in the source folder.

objective: Dicourage students from compiling the project with g++ *.cpp
difficulty: 1
"""

import unittest
from pathlib import Path

from grading_lib.common import (
    BaseTestCase,
    MinimalistTestResult,
    MinimalistTestRunner,
    points,
    run_executable,
)


class TestLimitedResourcesPuzzle(BaseTestCase):
    @points(10.0)
    def test_makefile(self):
        student_makefile_path = Path("source") / "Makefile"
        our_makefile_path = Path("source") / "answer.mk"

        if not student_makefile_path.exists():
            assert False, "Makefile not found in the source folder."

        # Copy the student Makefile to answer.mk
        with open(student_makefile_path, "r") as in_f:
            lines = in_f.readlines()

            lines = ["SHELL=../scripts/shell.py\n"] + lines

            with open(our_makefile_path, "w") as out_f:
                for line in lines:
                    out_f.write(line)

        result = run_executable(["make", "-f", "answer.mk"], cwd=Path("source"))
        self.assertCommandSuccessful(result)

        # print(result.output)
        output_block = (
            f"\n\nThe output from running your Makefile is:\n\n{result.output}"
        )

        #
        # The file 'money-printer' must exist.
        # Or to account for Windows user.
        #
        linux_style_executable_name = "money-printer"
        windows_style_executable_name = "money-printer.exe"
        invalid_executable_names = ["a.out", "a.exe"]
        if any([(Path("source") / p).exists() for p in invalid_executable_names]):
            self.fail(
                f"There is a find name 'a.out' (or a.exe). Please make sure that the executable name is 'money-printer' (on Windows, you may add .exe).{output_block}"
            )

        if (Path("source") / linux_style_executable_name).exists():
            #
            # Running it with some data should produce the correct answer.
            #
            result = run_executable(
                ["./money-printer", "Become a Bobcat, for life."], cwd=Path("source")
            )
        elif (Path("source") / windows_style_executable_name).exists():
            result = run_executable(
                ["./money-printer.exe", "Become a Bobcat, for life."],
                cwd=Path("source"),
            )
        else:
            self.fail(
                f"The executable, 'money-printer' (or 'money-printer.exe'), cannot be found after the Makefile is run. Did you give it the correct name?{output_block}"
            )

        self.assertCommandSuccessful(result)
        assert (
            int(result.output) == 5
        ), f"The behavior of the money-printer is not as expected. Expect 5 from a command './money-printer \"Become a Bobcat, for life.\"'. However, the output is\n\n{result.output}"

    def tearDown(self) -> None:
        # Clean up the executable
        executable_path = Path("source") / "money-printer"
        if executable_path.exists():
            executable_path.unlink()

        executable_path = Path("source") / "money-printer.exe"
        if executable_path.exists():
            executable_path.unlink()

        # Clean up the answer.mk
        our_makefile_path = Path("source") / "answer.mk"
        if our_makefile_path.exists():
            our_makefile_path.unlink()


if __name__ == "__main__":
    unittest.main(testRunner=MinimalistTestRunner(resultclass=MinimalistTestResult))
