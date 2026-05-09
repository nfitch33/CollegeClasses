import unittest

from grading_lib.common import (
    BaseTestCase,
    MinimalistTestResult,
    points,
)


class TestGitInternalsProblem(BaseTestCase):
    
    @points(15.0)
    def test_answer(self):
        """Student answers."""
        with open("answer.txt", "r") as f:
            content = f.read()
            print(content)

            self.fail("NEED MANUAL GRADING")


if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
