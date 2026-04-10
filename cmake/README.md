# CMake Includes for zeusJuce

This folder contains the CMake helper infrastructure used by `zeusJuce`.

It is now owned directly by the `zeusJuce` template and is no longer tracked as an external submodule.

## What is in here?

This folder contains most of the reusable CMake functionality behind the template, including:
- version handling
- tests and benchmarks wiring
- asset embedding
- JUCE-related defaults
- optional IPP integration
- GitHub/CI environment helpers
- Xcode organization helpers

## Maintenance policy

`cmake/` is template-owned infrastructure.

That means:
- ordinary plugin feature work should not modify it
- template/build-system maintenance may modify it deliberately
- if a helper needs improvement, update it here inside `zeusJuce`
- do not treat this folder as a separate upstream dependency

## Why keep it separate as a folder?

Because it keeps the root `CMakeLists.txt` readable while preserving reusable build logic in one obvious place.

## Change tracking

See [CHANGELOG.md](CHANGELOG.md).
