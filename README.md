# zeusJuce

`zeusJuce` is the ZEUS-owned JUCE plugin template baseline.

It provides a production-oriented JUCE+CMake starting point for ZEUS-driven plugin projects.

## What zeusJuce includes

Out of the box, `zeusJuce` gives you:

1. C++23-based JUCE plugin setup
2. JUCE as a git submodule
3. ZEUS-owned `cmake/` helper infrastructure
4. Catch2 tests and benchmarks
5. packaging placeholders, baseline template icons, and installer resources
6. CLAP integration scaffolding via `clap-juce-extensions`
7. a repository layout that ZEUS workflows can reason about consistently

## Dependency model

### Template-owned infrastructure
- `cmake/`
- packaging placeholders
- template metadata such as `ZEUS-TEMPLATE.yaml`

### Dependency-managed submodules
- `JUCE/`
- `modules/clap-juce-extensions/`
- nested CLAP helper submodules
- `modules/melatonin_inspector/`

Rules:
- ordinary feature work should not edit dependency-managed submodules
- `cmake/` should only be changed during explicit template/build-system maintenance

## Repository structure

- `CMakeLists.txt` - root build definition
- `cmake/` - ZEUS-owned helper CMake files
- `source/` - plugin source code
- `tests/` - test sources
- `benchmarks/` - benchmark sources
- `assets/` - embedded assets
- `packaging/` - installer and release resources, including template placeholder icons/EULA/README
- `modules/` - third-party plugin-related submodules
- `JUCE/` - JUCE framework submodule
- `ZEUS-TEMPLATE.yaml` - template identity and maintenance metadata
- `AGENTS.md` - coding-agent guidance

## Build commands

```bash
# Configure
cmake -B Builds -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build Builds --config Release

# Run unit tests
ctest --test-dir Builds --verbose --output-on-failure

# Run benchmarks explicitly
./Builds/Benchmarks
```

Notes:
- plugin copying into system plugin folders is disabled by default for safer local builds
- enable it explicitly with `-DZEUSJUCE_COPY_PLUGIN_AFTER_BUILD=ON` when you want install-after-build behaviour
- benchmarks build by default, but they are not registered with `ctest` unless you opt in with `-DZEUSJUCE_REGISTER_BENCHMARKS_WITH_CTEST=ON`

For faster local builds, Ninja is recommended:

```bash
cmake -B Builds -G Ninja -DCMAKE_BUILD_TYPE=Release
```

The template also ships `CMakePresets.json` for a lightweight standard setup:

```bash
cmake --preset dev
cmake --build --preset build-dev
ctest --preset test-dev
```

## Bootstrap into a ZEUS project

The normal ZEUS flow is not to do product development directly in this template repo.
Instead, create a project from it and install ZEUS on top:

```bash
zeus-init-plugin MyPlugin
cd MyPlugin
./bin/zeus create-plugin-brief
```

`zeus-init-plugin` now personalizes the cloned template to the target directory name, deriving a project name, product name, bundle identifier, and plugin codes so new projects do not all ship the same template identity.

Packaging assets are still template placeholders. Before shipping a real product, replace the baseline icons and installer copy under `packaging/`.

## Maintenance reality

`zeusJuce` is ZEUS-owned.

That means:
- ZEUS decides template structure and releases
- JUCE and selected third-party components move through submodule upstreams
- `cmake/` is owned directly inside the template

## License note

This repository is MIT-licensed.
