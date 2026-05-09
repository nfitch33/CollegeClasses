"""
Grade simple-project problem.

difficulty: 2
objective: Students should be able to apply knowledge about GNU Make in creating
a simple Makefile for a project with multiple executable files.
"""

import re
import time
import unittest
from pathlib import Path

from grading_lib.common import (
    MinimalistTestResult,
    get_mtime_as_datetime,
    has_file_changed,
    run_executable,
    points,
)
from grading_lib.makefile import MakefileBaseTestCase, run_targets

DEBUG = False
target_pattern = re.compile(r"^(?P<targetname>.+:)")
COMMAND_FAILED_TEMPLATE = "An error occurred while trying to run '{command}'. The command's output is\n\n{output}"


def has_file(filepath: Path | str) -> bool:
    if isinstance(filepath, str):
        filepath = Path(filepath)
    return filepath.exists()


def has_files(filepaths: list[Path] | list[str]) -> bool:
    """Return True if all listed file exist."""
    return all([has_file(p) for p in filepaths])


def remove_file(filepath: Path | str):
    if isinstance(filepath, str):
        filepath = Path(filepath)
    filepath.unlink(missing_ok=True)


class TestAllRuleBehavior(MakefileBaseTestCase):
    makefile_path = Path("source") / "Makefile"

    @points(5.0)
    def test_target_all_has_empty_recipe(self):
        self.assertHasRuleForTarget("all")
        self.assertRuleRecipeIsEmpty("all")

    @points(10.0)
    def test_target_all_create_required_files(self):
        """
        Behavior of a rule for a target 'all'.

        'all' should be the goal target. When it is invoked, the executable files and the
        source distribution archive file are created. The recipe of this target must be empty.
        """
        self.assertHasRuleForTarget("all")

        #
        # Remove any existing file.
        #
        remove_file(Path("source") / "othello-game")
        remove_file(Path("source") / "othello-game-debug")
        remove_file(Path("source") / "othello-sdist.tar.gz")

        result = run_targets([], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        description = "one or more of the expected files ('othello-game', 'othello-game-debug', 'othello-sdist.tar.gz') does not exist after the make command is run."
        assert has_files(
            [
                Path("source") / "othello-game",
                Path("source") / "othello-game-debug",
                Path("source") / "othello-sdist.tar.gz",
            ]
        ), description

    @points(5.0)
    def test_target_all_executables_run(self):
        #
        # Check if the executables are working.
        #
        self.assertHasRuleForTarget("all")

        result = run_targets([], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        result = run_executable(["./othello-game", "--version"], cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            result.output == "2024.1\n"
        ), f"Output of './othello-game --version' is not as expected. Output of the command is\n\n{result.output}"

        result = run_executable(
            ["./othello-game-debug", "--version"], cwd=Path("source")
        )
        self.assertCommandSuccessful(result)
        assert (
            result.output == "2024.1d\n"
        ), f"Output of './othello-game-debug --version' is not as expected. Output of the command is\n\n{result.output}"

    def tearDown(self):
        super().tearDown()
        remove_file(Path("source") / "othello-game")
        remove_file(Path("source") / "othello-game-debug")
        remove_file(Path("source") / "othello-sdist.tar.gz")


class TestBuildRelatedTargetBehavior(MakefileBaseTestCase):
    makefile_path = Path("source") / "Makefile"

    @points(5.0)
    def test_target_build_create_required_files(self):
        """
        Behavior of target 'build'
        """
        #
        # Only check the target behavior when the target actually exist.
        #
        self.assertHasRuleForTarget("build")

        #
        # Remove any existing file.
        #
        remove_file(Path("source") / "othello-game")
        remove_file(Path("source") / "othello-game-debug")

        #
        # Running `make build`
        #
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        description = "one or more of the expected files ('othello-game', 'othello-game-debug') does not exist after the make command is run."
        assert has_files(
            [Path("source") / "othello-game", Path("source") / "othello-game-debug"]
        ), description

    @points(5.0)
    def test_target_build_only_recompile_when_necessary_1(self):
        """
        'build' should only re-compile when necessary.
        """
        self.assertHasRuleForTarget("build")

        #
        # Double invocation does not create the file again.
        #
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            "make: Nothing to be done for 'build'." in result.output
        ), "Rule for the target 'build' appears to create at least one of the executables again when nothing has changed."

    @points(5.0)
    def test_target_build_only_recompile_when_necessary_2(self):
        """
        'build' should only re-compile when necessary.
        """
        self.assertHasRuleForTarget("build")

    @points(5.0)
    def test_target_build_executables_run(self):
        self.assertHasRuleForTarget("build")

        #
        # Check if the executables are working.
        #
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        result = run_executable(["./othello-game", "--version"], cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            result.output == "2024.1\n"
        ), f"Output of './othello-game --version' is not as expected. Output of the command is\n\n{result.output}"

        result = run_executable(
            ["./othello-game-debug", "--version"], cwd=Path("source")
        )
        self.assertCommandSuccessful(result)
        assert (
            result.output == "2024.1d\n"
        ), f"Output of './othello-game-debug --version' is not as expected. Output of the command is\n\n{result.output}"

    def tearDown(self):
        remove_file(Path("source") / "othello-game")
        remove_file(Path("source") / "othello-game-debug")


class TestSdistTargetBehavior(MakefileBaseTestCase):
    makefile_path = Path("source") / "Makefile"

    @points(10.0)
    def test_sdist_behavior(self):
        """Behavior of target 'sdist'"""
        #
        # Only check the target behavior when the target actually exist.
        #
        self.assertHasRuleForTarget("sdist")

        expected_filepath = Path("source") / "othello-sdist.tar.gz"

        # Removing any existing othello-sdist.tar.gz.
        remove_file(expected_filepath)

        #
        # othello-sdist.tar.gz is created.
        #
        result = run_targets(["sdist"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert expected_filepath.exists(), "Rule for the target 'sdist' does not create the expected file named 'othello-sdist.tar.gz'."
        last_known_sdist_mtime = get_mtime_as_datetime(expected_filepath)

        time.sleep(1)

        #
        # Double invocation does not create the file again.
        #
        result = run_targets(["sdist"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert not has_file_changed(
            last_known_sdist_mtime, expected_filepath
        ), "Rule for the target 'sdist' appears to create 'othello-sdist.tar.gz' again when nothing has changed."

        #
        # Check content of othello-sdist.tar.gz
        #
        expected_files_in_archive = [
            "colors.hpp",
            "debug_main.cpp",
            "game.cpp",
            "game.hpp",
            "main.cpp",
            "Makefile",
            "othello.cpp",
            "othello.hpp",
            "piece.hpp",
        ]
        result = run_executable(["tar", "-tf", str(expected_filepath)])
        self.assertCommandSuccessful(result)

        # Process result from tar -tf.
        paths = [p for p in result.output.split("\n") if len(p.strip()) != 0]
        filenames = [Path(p).name for p in paths]
        for expected_file in expected_files_in_archive:
            assert (
                expected_file in filenames
            ), f"File '{expected_file}' is not in the othello-sdist.tar.gz"


class TestCleanTargetBehavior(MakefileBaseTestCase):
    makefile_path = Path("source") / "Makefile"
    files_expected_to_be_clean = [
        "game.o",
        "othello.o",
        "main.o",
        "debug_main.o",
        "othello-game",
        "othello-game-debug",
    ]

    def tearDown(self):
        super().tearDown()
        for f in [Path("source") / f for f in self.files_expected_to_be_clean]:
            if f.exists():
                f.unlink()

    @points(10.0)
    def test_clean_object_files_behavior(self):
        """
        Behavior of the rule for target 'clean'

        Running the command "make clean" should remove all the .o files
        and the executable file.

        Note: The executable file is not detected yet since the name can be arbitrary.
        """
        # Only check the target behavior when the target actually exist.
        self.assertHasRuleForTarget("clean")

        # Manually create .o file.
        for obj_f in self.files_expected_to_be_clean:
            with open(Path("source") / obj_f, "w") as f:
                f.write("object-file; created by the test cases")

        # Run the `make clean`
        result = run_targets(["clean"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        #
        # All required files should be deleted.
        #
        still_exist_files = [
            f
            for f in Path("source").glob("./*")
            if f.name in self.files_expected_to_be_clean
        ]
        files_text = ", ".join(str(f) for f in still_exist_files)
        assert (
            len(still_exist_files) == 0
        ), f"'make clean' does not remove all these files: {files_text}"


if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
