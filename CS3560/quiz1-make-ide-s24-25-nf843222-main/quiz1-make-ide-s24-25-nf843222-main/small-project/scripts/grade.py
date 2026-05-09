"""
Grade simple-project problem.
"""

import re
import time
import unittest
from pathlib import Path

from grading_lib.common import (
    MinimalistTestResult,
    get_mtime_as_datetime,
    has_file_changed,
    points,
    run_executable,
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

    @points(2.0)
    def test_target_all_has_empty_recipe(self):
        self.assertHasRuleForTarget("all")
        self.assertRuleRecipeIsEmpty("all")

    @points(5.0)
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
        remove_file(Path("source") / "split-by")
        remove_file(Path("source") / "project-sdist.tar.gz")

        result = run_targets([], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        description = "one or more of the expected files ('split-by', 'project-sdist.tar.gz') does not exist after the make command is run."
        assert has_files(
            [
                Path("source") / "split-by",
                Path("source") / "project-sdist.tar.gz",
            ]
        ), description

    @points(3.0)
    def test_target_all_executables_run(self):
        #
        # Check if the executables are working.
        #
        self.assertHasRuleForTarget("all")

        #
        # Remove any existing file.
        #
        remove_file(Path("source") / "split-by")
        remove_file(Path("source") / "split_by.o")
        remove_file(Path("source") / "main.o")

        #
        # Check if the executables are working.
        #
        result = run_targets([], makefile_name="Makefile", cwd=Path("source"))
        result = run_executable(["./split-by", "--version"], cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            result.output == "0.0.1\n"
        ), f"Output of './split-by --version' is not as expected. Output of the command is\n\n{result.output}"

    def tearDown(self):
        super().tearDown()
        remove_file(Path("source") / "split-by")
        remove_file(Path("source") / "project-sdist.tar.gz")


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
        self.assertRuleRecipeIsEmpty("build")

        #
        # Remove any existing file.
        #
        remove_file(Path("source") / "split-by")

        #
        # Running `make build`
        #
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        description = "one or more of the expected files, 'split-by', does not exist after the make command is run."
        assert has_files([Path("source") / "split-by"]), description

    @points(5.0)
    def test_target_build_only_recompile_when_necessary_1(self):
        #
        # Double invocation does not create the file again.
        #
        self.assertHasRuleForTarget("build")

        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            "make: Nothing to be done for 'build'." in result.output
        ), "Rule for the target 'build' appears to create at least one of the executables again when nothing has changed."

    @points(5.0)
    def test_target_build_only_recompile_when_necessary_2(self):
        #
        # Double invocations create new executable files if any of the source files has been modified.
        #
        self.assertHasRuleForTarget("build")

        # Ensure build is up to date
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        # Capture the modification time of the target executable
        target_path = Path("source") / "split-by"
        old_mtime = get_mtime_as_datetime(target_path)

        time.sleep(1)  # Ensure timestamp difference

        # Modify one of the source files
        source_file = Path("source") / "main.cpp"
        with open(source_file, "a") as f:
            f.write("// Modified by test\n")

        # Run build again
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)

        # Ensure target was recompiled
        new_mtime = get_mtime_as_datetime(target_path)
        assert new_mtime > old_mtime, "Target 'split-by' was not recompiled when a source file changed."

        # Cleanup the modification (optional)
        with open(source_file, "r") as f:
            content = f.readlines()
        with open(source_file, "w") as f:
            f.writelines(content[:-1])  # Remove last line

    @points(5.0)
    def test_target_build_executables_run(self):
        self.assertHasRuleForTarget("build")

        #
        # Remove any existing file.
        #
        remove_file(Path("source") / "split-by")
        remove_file(Path("source") / "split_by.o")
        remove_file(Path("source") / "main.o")

        #
        # Check if the executables are working.
        #
        result = run_targets(["build"], makefile_name="Makefile", cwd=Path("source"))
        result = run_executable(["./split-by", "--version"], cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            result.output == "0.0.1\n"
        ), f"Output of './split-by --version' is not as expected. Output of the command is\n\n{result.output}"

    def tearDown(self):
        remove_file(Path("source") / "split-by")


class TestSdistTargetBehavior(MakefileBaseTestCase):
    makefile_path = Path("source") / "Makefile"

    @points(10.0)
    def test_target_sdist_behavior(self):
        """Behavior of target 'sdist'"""
        #
        # Only check the target behavior when the target actually exist.
        #
        self.assertHasRuleForTarget("sdist")

        expected_filepath = Path("source") / "project-sdist.tar.gz"

        # Removing any existing project-sdist.tar.gz.
        remove_file(expected_filepath)

        #
        # project-sdist.tar.gz is created.
        #
        result = run_targets(["sdist"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert (
            expected_filepath.exists()
        ), "Rule for the target 'sdist' does not create the expected file named 'project-sdist.tar.gz'."
        last_known_sdist_mtime = get_mtime_as_datetime(expected_filepath)

        time.sleep(1)

        #
        # Double invocation does not create the file again.
        #
        result = run_targets(["sdist"], makefile_name="Makefile", cwd=Path("source"))
        self.assertCommandSuccessful(result)
        assert not has_file_changed(
            last_known_sdist_mtime, expected_filepath
        ), "Rule for the target 'sdist' appears to create 'project-sdist.tar.gz' again when nothing has changed."

        #
        # Check content of project-sdist.tar.gz
        #
        expected_files_in_archive = [
            "split_by.hpp",
            "split_by.cpp",
            "main.cpp",
            "Makefile",
        ]
        result = run_executable(["tar", "-tf", str(expected_filepath)])
        self.assertCommandSuccessful(result)

        # Process result from tar -tf.
        paths = [p for p in result.output.split("\n") if len(p.strip()) != 0]
        filenames = [Path(p).name for p in paths]
        for expected_file in expected_files_in_archive:
            assert (
                expected_file in filenames
            ), f"File '{expected_file}' is not in the project-sdist.tar.gz"


class TestCleanTargetBehavior(MakefileBaseTestCase):
    makefile_path = Path("source") / "Makefile"
    files_expected_to_be_clean = [
        "split_by.o",
        "main.o",
        "split-by",
    ]

    def tearDown(self):
        super().tearDown()
        for f in [Path("source") / f for f in self.files_expected_to_be_clean]:
            if f.exists():
                f.unlink()

    @points(10.0)
    def test_target_clean_object_files_behavior(self):
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
