"""
Internal unit testing for the grading script.
"""

import pytest
from grade import TestOddOrEvenMakefileProblem, populate_folder

# Prevent pytest from running test in this class since
# we want actually test them.
TestOddOrEvenMakefileProblem.__test__ = False


def test_populate_folder(tmp_path):
    file_names, folder_names = populate_folder(tmp_path, 5, 1)

    assert len(file_names) == 5
    assert len(folder_names) == 1


def test_makefile_detection(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)

    test_item = TestOddOrEvenMakefileProblem()
    test_item.setUp()
    with pytest.raises(FileNotFoundError, match="Cannot find 'Makefile'"):
        test_item.test_even_case()
    test_item.tearDown()
    test_item.setUp()
    with pytest.raises(FileNotFoundError, match="Cannot find 'Makefile'"):
        test_item.test_odd_case()
    test_item.tearDown()


def test_even_case_checker(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)

    with open(tmp_path / "Makefile", "w") as out_f:
        out_f.write("""
.PHONY: ItIsSurelyOdd

ItIsSurelyOdd:
\t@echo odd
""")
    test_item = TestOddOrEvenMakefileProblem()
    test_item.setUp()
    with pytest.raises(AssertionError, match="Expect the output to be even"):
        test_item.test_even_case()
    test_item.tearDown()

    with open(tmp_path / "Makefile", "w") as out_f:
        out_f.write("""
.PHONY: ItIsSurelyOdd

ItIsSurelyOdd:
\t@echo even
""")
    test_item.setUp()
    test_item.test_even_case()
    test_item.tearDown()


def test_odd_case_checker(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)

    with open(tmp_path / "Makefile", "w") as out_f:
        out_f.write("""
.PHONY: ItIsSurelyOdd

ItIsSurelyOdd:
\t@echo some answer
""")
    test_item = TestOddOrEvenMakefileProblem()
    test_item.setUp()
    with pytest.raises(AssertionError, match="Expect the output to be odd"):
        test_item.test_odd_case()
    test_item.tearDown()

    with open(tmp_path / "Makefile", "w") as out_f:
        out_f.write("""
.PHONY: ItIsSurelyOdd

ItIsSurelyOdd:
\t@echo odd
""")
    test_item.setUp()
    test_item.test_odd_case()
    test_item.tearDown()
