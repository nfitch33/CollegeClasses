import shutil
import unittest
from pathlib import Path

from grading_lib.common import BaseTestCase, MinimalistTestResult, run_executable, points
from grading_lib.repository import Repository

PROBLEM_ROOT = Path(__file__).parent.parent

class TestMakingCommitsProblem(BaseTestCase):
    with_temporary_dir = True

    @points(20.0)
    def test_commit_history_tree(self):
        # Copy answer1.sh to the temporary directory
        # then run it.
        shutil.copy(PROBLEM_ROOT / "answer.sh", self.temporary_dir_path / "answer.sh")
        
        # On GitHub Actions, user identity is not configured for git.
        # cmd_result = run_executable(["git", "init", "--initial-branch=main"], cwd=str(self.temporary_dir_path))
        # self.assertCommandSuccessful(cmd_result)
        # cmd_result = run_executable(["git", "config", "--local", "user.name", "ou-cs3560-grading-script"], cwd=str(self.temporary_dir_path))
        # self.assertCommandSuccessful(cmd_result)
        # cmd_result = run_executable(["git", "config", "--local", "user.email", "cs3560-grading-script@ohio.edu"], cwd=str(self.temporary_dir_path))
        # self.assertCommandSuccessful(cmd_result)

        # result = run_executable(["bash", "answer.sh"], cwd=self.temporary_dir_path)
        # self.assertCommandSuccessful(result)

        # repo = Repository(self.temporary_dir_path)
        # vis_res = repo.visualize()
        # print(f"Visualization:\n{vis_res}")

        self.fail("MANUAL GRADING NEEDED")

if __name__ == "__main__":
    runner = unittest.TextTestRunner(resultclass=MinimalistTestResult)
    unittest.main(testRunner=runner)
