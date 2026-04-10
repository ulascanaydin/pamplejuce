# AGENTS.md

This file provides guidance to coding agents working with the `zeusJuce` template repository.

## About This Project

`zeusJuce` is the ZEUS-owned JUCE plugin template baseline for ZEUS-driven plugin projects.

The template provides the build system, packaging placeholders, CI-friendly project structure, and dependency layout.
Plugin-specific product logic belongs in downstream projects created from this template, not in the template itself unless the task is explicitly template maintenance.

## Build Commands

```bash
# Configure (run once, or after CMakeLists.txt changes)
cmake -B Builds -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build Builds --config Release

# Run tests (from project root)
ctest --test-dir Builds --verbose --output-on-failure

# Or run tests directly
./Builds/Tests

# Run a single test by name
./Builds/Tests "[test name]"

# Run benchmarks
./Builds/Benchmarks
```

For faster builds, add Ninja: `cmake -B Builds -G Ninja -DCMAKE_BUILD_TYPE=Release`

On macOS for universal binary: `-DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"`

## Project Structure

- `source/` - plugin source code
- `tests/` - Catch2 test files
- `benchmarks/` - Catch2 benchmark files
- `cmake/` - ZEUS-owned CMake helper infrastructure
- `modules/` - third-party plugin-related submodules
- `JUCE/` - JUCE framework submodule
- `assets/` - binary resources
- `packaging/` - installer resources and release placeholders
- `ZEUS-TEMPLATE.yaml` - template metadata and maintenance model

## Dependency-managed paths

The following paths are dependency-managed and are not normal implementation targets:
- `JUCE/`
- `modules/clap-juce-extensions/`
- other third-party submodules under `modules/`

The following path is template-owned infrastructure and also not a normal feature-work area:
- `cmake/`

Rules:
- do not edit files inside dependency-managed paths during ordinary feature work
- do not treat dependency-managed paths or `cmake/` as normal agent ownership zones
- only touch dependency-managed paths during explicit dependency maintenance tasks
- only touch `cmake/` during explicit template/build-system maintenance tasks
- preferred dependency maintenance is to update submodule pointers intentionally at the template root
- if submodules are missing or empty, run `git submodule update --init --recursive`

## Architecture

**SharedCode Library**: The `SharedCode` INTERFACE library links plugin source code to both the main plugin target and the Tests target, avoiding ODR violations.

**CMake Modules**:
- `ZeusJuceVersion.cmake` - reads `VERSION`, optional auto-bump patch level
- `Assets.cmake` - auto-includes asset files as binary data
- `Tests.cmake` - configures Catch2 test target
- `Benchmarks.cmake` - configures Catch2 benchmark target
- `ZeusJuceIPP.cmake` - Intel IPP integration (optional)

These CMake helper files live in `cmake/`, which is template-owned infrastructure inside `zeusJuce`, not an external submodule.

**Test Discovery**: Uses `catch_discover_tests()` with `PRE_TEST` discovery mode for Xcode compatibility.

## Key Configuration

Edit `CMakeLists.txt` to customize:
- `PROJECT_NAME` - internal name (no spaces)
- `PRODUCT_NAME` - display name in DAWs (can have spaces)
- `COMPANY_NAME` - bundle/install identity
- `BUNDLE_ID` - macOS bundle identifier
- `FORMATS` - plugin formats to build (Standalone AU VST3 AUv3 CLAP, depending on template configuration)
- `PLUGIN_MANUFACTURER_CODE` / `PLUGIN_CODE` - 4-character plugin IDs

Version is read from the `VERSION` file in project root.

## Code Quality

Always resolve compile warnings encountered during builds. Treat warnings as errors for maintenance-quality work.

Note: LSP/clangd may report false positives because JUCE module context can confuse tooling. Trust the actual build over editor diagnostics when they conflict.

## Realtime Safety

For anything in the audio thread / hot DSP path (e.g. `processBlock`):
- allocate in constructors or `prepareToPlay`, not while rendering audio
- avoid dynamic allocations and container growth
- prefer fixed-size storage and preallocated buffers
- keep operations deterministic and lock-free where possible

## Code Style

Uses `.clang-format` with Allman-style braces, 4-space indentation, no column limit.
