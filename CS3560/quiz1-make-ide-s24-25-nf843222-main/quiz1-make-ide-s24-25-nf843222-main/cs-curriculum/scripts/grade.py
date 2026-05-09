"""
Grade cs-curriculum problem.
"""

import unittest
from pathlib import Path

from grading_lib.common import MinimalistTestResult, points
from grading_lib.makefile import MakefileBaseTestCase, run_targets

ALL_EXPECTED_TARGETS = [
    "undergraduate-degree",
    "cs4560",
    "cs4561",
    "cs4100",
    "cs3200",
    "cs4000",
    "cs3610",
    "cs2401",
    "cs3560",
    "high-school-diploma",
]
ALL_EXPECTED_FILES = [Path(p) for p in ALL_EXPECTED_TARGETS]


class TestCsCurriculumProblem(MakefileBaseTestCase):
    makefile_path = "Makefile"

    def setUp(self) -> None:
        super().setUp()
        self._clean_all_files()

    def tearDown(self) -> None:
        super().tearDown()
        self._clean_all_files()

    def test_have_all_required_targets(self):
        for target_name in ALL_EXPECTED_TARGETS:
            self.assertHasRuleForTarget(target_name)

    @points(10.0)
    def test_cs_degree(self):
        result = run_targets(["undergraduate-degree"], makefile_name="Makefile")
        self.assertCommandSuccessful(result)
        self.assertAllFilesExist(ALL_EXPECTED_FILES)

        result = run_targets([], makefile_name="Makefile")
        self.assertCommandSuccessful(result)
        self.assertAllFilesExist(
            ALL_EXPECTED_FILES, "Is 'undergraduate-degree' the default target?"
        )

    @points(10.0)
    def test_hs_diploma(self):
        result = run_targets(["high-school-diploma"], makefile_name="Makefile")
        self.assertCommandSuccessful(result)
        self.assertFileExists(Path("high-school-diploma"))

    @points(10.0)
    def test_cs3560(self):
        result = run_targets(["cs3560"], makefile_name="Makefile")
        self.assertCommandSuccessful(result)
        self.assertFileExists(Path("cs3560"))

    @points(10.0)
    def test_cs4560(self):
        result = run_targets(["cs4560"], makefile_name="Makefile")
        self.assertCommandSuccessful(result)

        expected_names = [
            "cs4560",
            "cs3560",
            "cs3610",
            "cs2401",
            "high-school-diploma",
        ]
        self.assertAllFilesExist([Path(p) for p in expected_names])

    @points(10.0)
    def test_cs3200(self):
        result = run_targets(["cs3200"], makefile_name="Makefile")
        self.assertCommandSuccessful(result)

        expected_names = [
            "cs3200",
            "cs2401",
            "high-school-diploma",
        ]
        self.assertAllFilesExist([Path(p) for p in expected_names])

    def test_cs4000(self):
        result = run_targets(["cs4000"], makefile_name="Makefile")
        self.assertCommandSuccessful(result)

        expected_names = [
            "cs4000",
            "cs3610",
            "cs2401",
            "high-school-diploma",
        ]
        self.assertAllFilesExist([Path(p) for p in expected_names])

    def _clean_all_files(self) -> None:
        # Clean all the files.
        for file_name in ALL_EXPECTED_FILES:
            path = Path(file_name)
            if path.exists():
                path.unlink()


if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
