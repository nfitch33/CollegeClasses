"""
Check for students' deeper understanding of GNU Make. Students should know
some functions/structure that will help with this problem. Students should
know how to interoperate GNU Make with shell commands.

name: odd-or-even-makefile
difficulty: 3
"""

import itertools
import random
import shutil
import typing as ty
import unittest
from pathlib import Path

from grading_lib.common import BaseTestCase, MinimalistTestResult, points
from grading_lib.makefile import run_targets

FILE_NAME_POOL = [
    "main",
    "split_by",
    "app",
    "data",
    "index",
    "certs",
    "cookies",
    "help",
    "utils",
    "sessions",
    "status_code",
]
FILE_EXTENSION_POOL = [
    "txt",
    "pdf",
    "docx",
    "pptx",
    "zip",
    "rar",
    "jpg",
    "png",
    "webp",
    "mov",
    "json",
    "yml",
]
MIN_FILE_AMOUNT = 5
MAX_FILE_AMOUNT = 15

FOLDER_NAME_POOL = [
    "source",
    "dist",
    "build",
    "_build",
    "assets",
    "scripts",
    "node_modules",
    "libs",
]
MIN_FOLDER_AMOUNT = 1
MAX_FOLDER_AMOUNT = 5


def populate_folder(
    path: Path | str, file_amount: int, folder_amount: int = 0
) -> ty.Tuple[ty.List[str], ty.List[str]]:
    """
    Randomly populates the folder data folder full of files.

    It assumes that the folder is empty.
    """
    if isinstance(path, str):
        path = Path(path)

    if not path.exists():
        raise ValueError("'path' does not exist")

    if not path.is_dir():
        raise ValueError("'path' is not a directory")

    filename_pool = [
        f"{name}.{ext}"
        for name, ext in itertools.product(FILE_NAME_POOL, FILE_EXTENSION_POOL)
    ]

    if len(filename_pool) < file_amount:
        raise ValueError(
            f"Does not have enough unique filenames. The requested {file_amount} names cannot be fulfill with {len(filename_pool)} names"
        )
    if len(FOLDER_NAME_POOL) < folder_amount:
        raise ValueError(
            f"Does not have enough unique folder's names. The requested {folder_amount} names cannot be fulfill with {len(FOLDER_NAME_POOL)} names"
        )

    file_names = random.sample(filename_pool, k=file_amount)
    for file_name in file_names:
        with open(path / file_name, "w") as f:
            f.write("")

    folder_names = []
    for name in random.sample(FOLDER_NAME_POOL, folder_amount):
        (path / name).mkdir()
        folder_names.append(f"{name}/")

    return file_names, folder_names


class TestOddOrEvenMakefileProblem(BaseTestCase):
    with_temporary_dir = True

    def setUp(self):
        super().setUp()

        random.seed(self.seed)
        print(f"[{self.id()}]: seed={self.seed}")
        if self.is_debug_mode:
            print(
                f"[{self.id()}]: DEBUG mode is active. The temporary directory will not be deleted."
            )

    def even_case(self):
        """
        Testing the Makefile with a test case (even)
        """

        file_choices = [
            v for v in range(MIN_FILE_AMOUNT, MAX_FILE_AMOUNT) if v % 2 == 1
        ]
        file_amount = random.choice(file_choices)
        folder_amount = random.choice(range(MIN_FOLDER_AMOUNT, MAX_FOLDER_AMOUNT))
        file_names, folder_names = populate_folder(
            self.temporary_dir_path, file_amount, folder_amount
        )

        if not Path("Makefile").exists():
            raise FileNotFoundError(
                "Cannot find 'Makefile'. Expect to see 'Makefile' in odd-or-even-makefile folder. Did you move this Makefile into testcases/1/ or testcases/2/ and forget to move it back?"
            )

        shutil.copy(Path("Makefile"), self.temporary_dir_path / "answer.mk")

        result = run_targets([], cwd=str(self.temporary_dir_path))
        self.assertCommandSuccessful(result)

        assert (
            result.output == "even\n"
        ), f"Note: there are {file_amount+1} files and {folder_amount} folders in the './data' folder.\n\nExpect the output to be even, but the output is\n\n{result.output}\n\nFiles and folders in data/\nFiles: {file_names}\nFolders: {folder_names}"

    def odd_case(self):
        """
        Testing the Makefile with a test case (odd)
        """

        file_choices = [
            v for v in range(MIN_FILE_AMOUNT, MAX_FILE_AMOUNT) if v % 2 == 0
        ]
        file_amount = random.choice(file_choices)
        folder_amount = random.choice(range(MIN_FOLDER_AMOUNT, MAX_FOLDER_AMOUNT))
        file_names, folder_names = populate_folder(
            self.temporary_dir_path, file_amount, folder_amount
        )

        if not Path("Makefile").exists():
            raise FileNotFoundError(
                "Cannot find 'Makefile'. Expect to see 'Makefile' in odd-or-even-makefile folder. Did you move this Makefile into testcases/1/ or testcases/2/ and forget to move it back?"
            )

        shutil.copy(Path("Makefile"), self.temporary_dir_path / "answer.mk")

        result = run_targets([], cwd=str(self.temporary_dir_path))
        self.assertCommandSuccessful(result)

        assert (
            result.output == "odd\n"
        ), f"Note: there are {file_amount+1} files and {folder_amount} folders in the './data' folder.\n\nExpect the output to be odd, but the output is\n\n{result.output}\n\nFiles and folders in data/\nFiles: {file_names}\nFolders: {folder_names}"

    @points(2.5)
    def test_even_case_1(self):
        self.even_case()

    @points(2.5)
    def test_even_case_2(self):
        self.even_case()

    @points(2.5)
    def test_odd_case_1(self):
        self.odd_case()

    @points(2.5)
    def test_odd_case_2(self):
        self.odd_case()


if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
