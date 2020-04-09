# Yet

***WARNING: This project has moved to [https://git.yzena.com/][10] for [these
reasons][11].***

Yet is a timing library written in C.

Yet is developed by [Yzena][1].

Yet is Free and Open Source Software (FOSS). It is licensed under a modified
[Apache License 2.0][2]. The [modification][3] was first used by
[Pixar Animation Studios][4] for use on the [OpenSubdiv][5] project.

## Getting Started

To get started, clone the repo, and then run the following commands in the root
directory:

```
git config --local include.path ../.gitconfig
git submodule update --init --recursive
```

## Dependencies

Yet depends on CMake. On Ubuntu, it can be installed with the following
command:

```
sudo apt install cmake cmake-curses-gui
```

It also depends on [Yc][6].

## Status

Yet is not even in Alpha stage yet. This software is nowhere near ready for use.

## Language

Yet is written in pure ISO C11.

## Git Workflow

Yet uses the git workflow described [here][7]. Developers who want to contribute
to Yet are encouraged to read that post carefully.

For feature branches, it uses `rebase + merge --no-ff` (option 3). It also uses
a `develop`/`master` split. (Main development is on `develop`, and `master` just
points to the latest tagged release to make it easy for users to get the latest
release.)

## Commit Messages

Projects under Yzena, including Yet, use the commit message guidelines laid out
in [this blog post][8].

## Semantic Versioning

Yet uses [semantic versioning][9].

## Contents Listing

Every folder contains a README file which lists the purposes for the files and
folders in that directory.

## Contents

Files:

	CMakeLists.txt  CMake is the build system used for Yet. This is the root
	                config file.
	LICENSE.md      A Markdown version of Pixar's modified Apache 2.0 license.
	NOTICE.md       The NOTICE file required by the Apache License.

Folders:

	docs        Contains all of the documentation for Yet (currently empty).
	include     Contains all of the public header files for Yet.
	src         All of Yet's source code.
	tests       Tests for Yet.

[1]: http://yzena.com/
[2]: https://www.apache.org/licenses/LICENSE-2.0.html
[3]: http://graphics.pixar.com/opensubdiv/docs/license.html
[4]: https://www.pixar.com/
[5]: http://graphics.pixar.com/opensubdiv/docs/intro.html
[6]: https://github.com/YzenaTech/Yc
[7]: http://endoflineblog.com/oneflow-a-git-branching-model-and-workflow
[8]: http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html
[9]: http://semver.org/
[10]: https://git.yzena.com/Yzena/Yet
[11]: https://gavinhoward.com/2020/04/i-am-moving-away-from-github/
