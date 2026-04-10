# zeusJuce

`zeusJuce` is the ZEUS-owned JUCE plugin template baseline.

It was initially seeded from [Pamplejuce](https://github.com/sudara/pamplejuce), but it is now maintained as its own template for ZEUS-driven plugin projects.

## What zeusJuce is for

Use `zeusJuce` when you want a production-oriented JUCE+CMake starting point with:
- JUCE as a git submodule
- ZEUS-owned `cmake/` helper infrastructure
- Catch2 tests and benchmarks
- packaging resources
- CLAP integration scaffolding via `clap-juce-extensions`
- a repository shape that ZEUS workflows can reason about consistently

## What zeusJuce is not

- not the JUCE framework itself
- not a generic CMake tutorial repo
- not a one-off educational course project
- not a live upstream-tracking mirror of Pamplejuce

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

Rule:
- ordinary feature work should not edit dependency-managed submodules
- `cmake/` should only be changed during explicit template/build-system maintenance

## Repository structure

- `CMakeLists.txt` - root build definition
- `cmake/` - ZEUS-owned helper CMake files
- `source/` - plugin source code
- `tests/` - test sources
- `benchmarks/` - benchmark sources
- `assets/` - embedded assets
- `packaging/` - installer and release resources
- `modules/` - third-party plugin-related submodules
- `JUCE/` - JUCE framework submodule
- `ZEUS-TEMPLATE.yaml` - template identity and maintenance metadata
- `AGENTS.md` / `CLAUDE.md` - coding-agent guidance

## Build commands

```bash
# Configure
cmake -B Builds -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build Builds --config Release

# Run tests
ctest --test-dir Builds --verbose --output-on-failure

# Run benchmarks
./Builds/Benchmarks
```

For faster local builds, Ninja is recommended:

```bash
cmake -B Builds -G Ninja -DCMAKE_BUILD_TYPE=Release
```

## Bootstrap into a ZEUS project

The normal ZEUS flow is not to work directly in this template repo for product development.
Instead, bootstrap a new project from it and then install ZEUS on top:

```bash
zeus-init-plugin MyPlugin
cd MyPlugin
./bin/zeus create-plugin-brief
```

## Maintenance reality

`zeusJuce` is ZEUS-owned.

That means:
- ZEUS decides template structure and releases
- Pamplejuce remains a seed/reference, not the controlling upstream
- JUCE and selected third-party components still move through submodule upstreams

## License note

This repository remains MIT-licensed. It contains ZEUS-owned modifications on top of material originally seeded from Pamplejuce.
