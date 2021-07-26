# Source:
# https://github.com/arduino/tooling-project-assets/blob/main/workflow-templates/assets/test-integration/test_all.py
# Copyright 2021 ARDUINO SA (http://www.arduino.cc/)
#
# This software is released under the GNU General Public License version 3,
# The terms of this license can be found at:
# https: // www.gnu.org/licenses/gpl-3.0.en.html
#
# You can be released from the requirements of the above licenses by purchasing
# a commercial license. Buying such a license is mandatory if you want to
# modify or otherwise use the software for commercial activities involving the
# Arduino software without disclosing the source code of your own applications.
# To purchase a commercial license, send an email to license@arduino.cc.
import os
import pathlib
import platform
import shutil
import typing

import invoke.context
import pytest

test_data_path = pathlib.Path(__file__).resolve().parent.joinpath("testdata")


@pytest.mark.parametrize(
    "test_file, success_assertion",
    [
        ("", False),
        ("nonexistent.txt", False),
        ("invalid-data-format.txt", False),
        ("invalid-url-format.txt", False),
        ("no-type.txt", False),
        ("invalid-type.txt", False),
        ("duplicate-url.txt", False),
        ("duplicate-name.txt", False),
        ("valid.txt", True),
    ],
)
def test_all(run_command, test_file, success_assertion):
    result = run_command(cmd=[test_data_path.joinpath(test_file)])
    assert result.ok == success_assertion


@pytest.fixture(scope="function")
def run_command(pytestconfig, working_dir) -> typing.Callable[..., invoke.runners.Result]:
    """Provide a wrapper around invoke's `run` API so that every test will work in the same temporary folder.

    Useful reference:
        http://docs.pyinvoke.org/en/1.4/api/runners.html#invoke.runners.Result
    """

    executable_path = pathlib.Path(pytestconfig.rootdir).parent / "validate-registry"

    def _run(
        cmd: list,
        custom_working_dir: typing.Optional[str] = None,
        custom_env: typing.Optional[dict] = None,
    ) -> invoke.runners.Result:
        if cmd is None:
            cmd = []
        if not custom_working_dir:
            custom_working_dir = working_dir
        quoted_cmd = []
        for token in cmd:
            quoted_cmd.append(f'"{token}"')
        cli_full_line = '"{}" {}'.format(executable_path, " ".join(quoted_cmd))
        run_context = invoke.context.Context()
        # It might happen that we need to change directories between drives on Windows,
        # in that case the "/d" flag must be used otherwise directory wouldn't change
        cd_command = "cd"
        if platform.system() == "Windows":
            cd_command += " /d"
        # Context.cd() is not used since it doesn't work correctly on Windows.
        # It escapes spaces in the path using "\ " but it doesn't always work,
        # wrapping the path in quotation marks is the safest approach
        with run_context.prefix(f'{cd_command} "{custom_working_dir}"'):
            return run_context.run(
                command=cli_full_line,
                echo=False,
                hide=True,
                warn=True,
                env=custom_env,
                encoding="utf-8",
            )

    return _run


@pytest.fixture(scope="function")
def working_dir(tmpdir_factory) -> str:
    """Create a temporary folder for the test to run in. It will be created before running each test and deleted at the
    end. This way all the tests work in isolation.
    """
    work_dir = tmpdir_factory.mktemp(basename="IntegrationTestWorkingDir")
    yield os.path.realpath(work_dir)
    shutil.rmtree(work_dir, ignore_errors=True)
