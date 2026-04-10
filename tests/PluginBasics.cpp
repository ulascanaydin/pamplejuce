#include "helpers/test_helpers.h"
#include <PluginProcessor.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE ("Plugin metadata matches the compiled target", "[plugin][metadata]")
{
    PluginProcessor testPlugin;

    CHECK_THAT (testPlugin.getName().toStdString(),
        Catch::Matchers::Equals (std::string (JucePlugin_Name)));
    CHECK (testPlugin.getNumPrograms() == 1);
    CHECK (testPlugin.getTailLengthSeconds() == 0.0);
    CHECK (testPlugin.hasEditor());
}

TEST_CASE ("Plugin supports expected bus layouts", "[plugin][layout]")
{
    PluginProcessor testPlugin;

   #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (testPlugin);
    SUCCEED ("MIDI effects accept host-provided layouts");
   #else
    juce::AudioProcessor::BusesLayout stereoLayout;
    stereoLayout.inputBuses.add (juce::AudioChannelSet::stereo());
    stereoLayout.outputBuses.add (juce::AudioChannelSet::stereo());
    CHECK (testPlugin.isBusesLayoutSupported (stereoLayout));

    juce::AudioProcessor::BusesLayout surroundLayout;
    surroundLayout.inputBuses.add (juce::AudioChannelSet::create5point1());
    surroundLayout.outputBuses.add (juce::AudioChannelSet::create5point1());
    CHECK_FALSE (testPlugin.isBusesLayoutSupported (surroundLayout));
   #endif
}

TEST_CASE ("Plugin state round-trip is safe", "[plugin][state]")
{
    PluginProcessor testPlugin;
    juce::MemoryBlock state;

    testPlugin.getStateInformation (state);
    CHECK (state.getSize() == 0);
    CHECK_NOTHROW (testPlugin.setStateInformation (state.getData(), static_cast<int> (state.getSize())));
}

TEST_CASE ("Plugin editor can be created and torn down", "[plugin][editor]")
{
    runWithinPluginEditor ([&] (PluginProcessor& plugin) {
        auto* editor = plugin.getActiveEditor();
        REQUIRE (editor != nullptr);
        CHECK (editor->getWidth() > 0);
        CHECK (editor->getHeight() > 0);
    });
}

#ifdef ZEUSJUCE_IPP
    #include <ipp.h>

TEST_CASE ("IPP version", "[ipp]")
{
    #if defined(__APPLE__)
        // macOS uses 2021.9.1 from pip wheel (only x86_64 version available)
        CHECK_THAT (ippsGetLibVersion()->Version, Catch::Matchers::Equals ("2021.9.1 (r0x7e208212)"));
    #else
        CHECK_THAT (ippsGetLibVersion()->Version, Catch::Matchers::Equals ("2022.3.0 (r0x0fc08bb1)"));
    #endif
}
#endif
