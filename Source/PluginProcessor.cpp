/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ApdelayAudioProcessor::ApdelayAudioProcessor():
    m_numberOfDelays(1),
    m_maxNumberOfDelays(16),
    m_leftDelayMS(20.0f),
    m_rightDelayMS(20.0f),
    m_leftFeedback(0.0f),
    m_rightFeedback(0.0f),
    m_samplerate(44100.0f),
    m_wet(0.5f),
    m_depth(0.2f),
    m_speed(0.2f),
    m_frequencyDiff(0.5f)
{
    
    for (int i = 0; i < m_maxNumberOfDelays ; i++) {
        
        m_leftDelay.add(new ModulatedDelayUnit(m_samplerate,
                                               ModulatedDelayUnit::frequencyFromSpeed(m_speed) + (m_frequencyDiff * i),
                                               OcillatorUnit::SINE,
                                               m_samplerate,
                                               m_depth));
        
        m_rightDelay.add(new ModulatedDelayUnit(m_samplerate,
                                                ModulatedDelayUnit::frequencyFromSpeed(m_speed) + (m_frequencyDiff * i),
                                                OcillatorUnit::SINE,
                                                m_samplerate,
                                                m_depth));
    }
}

ApdelayAudioProcessor::~ApdelayAudioProcessor()
{
}

//==============================================================================
const String ApdelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int ApdelayAudioProcessor::getNumParameters()
{
    return Parameters::NumberOfParameters;
}

float ApdelayAudioProcessor::getParameter (int index)
{
    switch (index) {
        case LeftDelayTimeMS :
            return m_leftDelayMS;
        case RightDelayTimeMS :
            return m_rightDelayMS;
        case LeftFeedback :
            return m_leftFeedback * 100;
        case RightFeedback :
            return m_rightFeedback * 100;
        case DryWet :
            return m_wet * 100;
        case nUnits:
            return m_numberOfDelays;
        case Depth:
            return m_depth * 100;
        case Speed:
            return m_speed * 100;
        default:
            break;
    }

    return 0.0f;
}

void ApdelayAudioProcessor::setParameter (int index, float value)
{
    
    switch (index) {
        case LeftDelayTimeMS :
            m_leftDelayMS = value;
            break;
        case RightDelayTimeMS :
            m_rightDelayMS = value;
            break;
        case LeftFeedback :
            if (value < 0.0f) value = 0.0f;
            if (value > 99.0f) value = 99.0f;
            m_leftFeedback = value / 100.0f;
            break;
        case RightFeedback :
            if (value < 0.0f) value = 0.0f;
            if (value > 99.0f) value = 99.0f;
            m_rightFeedback = value / 100.0f;
            break;
        case DryWet :
            m_wet = value / 100.0f;
            break;
        case nUnits :
            m_numberOfDelays = value;
            break;
        case Depth :
            m_depth = value / 100.0f;
            for (int i = 0; i < m_maxNumberOfDelays; i++) {
                m_leftDelay[i]->setDepth(m_depth);
                m_rightDelay[i]->setDepth(m_depth);
            }
            break;
        case Speed :
            m_speed = value / 100.0f;
            for (int i = 0; i < m_maxNumberOfDelays; i++) {
                m_leftDelay[i]->setFrequency(ModulatedDelayUnit::frequencyFromSpeed(m_speed) +
                                             (m_frequencyDiff * i));
                
                m_rightDelay[i]->setFrequency(ModulatedDelayUnit::frequencyFromSpeed(m_speed) +
                                              (m_frequencyDiff * i));
            }
            break;
        default:
            break;
    }
}

const String ApdelayAudioProcessor::getParameterName (int index)
{
    
    switch (index) {
        case LeftDelayTimeMS :
            return "Left Delay Time";
        case RightDelayTimeMS :
            return "Right Delay Time";
        case LeftFeedback :
            return "Left Feedback";
        case RightFeedback :
            return "Right Feedback";
        case DryWet :
            return "Dry/Wet";
        case nUnits :
            return "Number of Units";
        case Depth :
            return "Depth";
        case Speed :
            return "Speed";
        default:
            break;
    }
    return String();
}

const String ApdelayAudioProcessor::getParameterText (int index)
{
    switch (index) {
        case LeftDelayTimeMS :
            return "Left Delay Time";
        case RightDelayTimeMS :
            return "Right Delay Time";
        case LeftFeedback :
            return "Left Feedback";
        case RightFeedback :
            return "Right Feedback";
        case DryWet :
            return "Dry/Wet";
        case nUnits :
            return "Number of Units";
        case Depth :
            return "Depth";
        case Speed :
            return "Speed";
        default:
            break;
    }
    
    
    return String();
}

const String ApdelayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ApdelayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ApdelayAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ApdelayAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ApdelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ApdelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ApdelayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double ApdelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ApdelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ApdelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ApdelayAudioProcessor::setCurrentProgram (int index)
{
}

const String ApdelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void ApdelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ApdelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // Clear all delay buffers
    for (int i = 0; i < m_maxNumberOfDelays; i++) {
        m_rightDelay[i]->clear();
        m_leftDelay[i]->clear();
    }
    
    m_samplerate = sampleRate;
    
    
}

void ApdelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    //Clear all delay buffers
    for (int i = 0; i < m_maxNumberOfDelays; i++) {
        m_leftDelay[i]->clear();
        m_rightDelay[i]->clear();
    }
}

float processSignal(int numberOfDelays, float wet, float input,
           DelayArray &delayUnit, float delayMS, float feedback)
{
    float dry = 1.0f - wet;
    float output = 0.0f;
    float volumeRatio = 1.0f / ((float) numberOfDelays);
    
    for (int i = 0 ; i < numberOfDelays; i++) {
        // Write dry signal to delay buffer
        delayUnit[i]->write(input);
        
        // Calculate wet signal
        // Allow users to change number of active delay units mid play
        // without popps and clicks by calculating the wet signal for all voices
        float wetSignal = delayUnit[i]->chorusDelay(delayMS);
        
        // Write feedback to delay buffer
        delayUnit[i]->sum(feedback * wetSignal);
        
        // Move write position
        delayUnit[i]->tick();
        
        // Only output delay from active units
        if (i < numberOfDelays) {
            output += wetSignal;
        }
    }
    // Normalize wet signal
    output = wet * output * volumeRatio;
    // Add dry signal
    output +=  dry * input;
    return output;
}

void ApdelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

  
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    
    int blockSize = buffer.getNumSamples();
    
    for(int n = 0 ; n < blockSize;++n){
        
        // Better spatial locality is achived by having seperate loops for
        // left and right channel, meaning values accessed are more likely to
        // still riside in memmory as arrays are traversed
        leftChannel[n] = processSignal(m_numberOfDelays,
                                       m_wet,
                                       leftChannel[n],
                                       m_leftDelay,
                                       m_leftDelayMS,
                                       m_leftFeedback);
        
        rightChannel[n] = processSignal(m_numberOfDelays,
                                        m_wet,
                                        rightChannel[n],
                                        m_rightDelay,
                                        m_rightDelayMS,
                                        m_rightFeedback);
    }
}

//==============================================================================
bool ApdelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ApdelayAudioProcessor::createEditor()
{
    return new ApdelayAudioProcessorEditor (*this);
}

//==============================================================================
void ApdelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    XmlElement root("Root");
    XmlElement *el;
    
    el = root.createNewChildElement("LeftDelayTimeMS");
    el->addTextElement(String(m_leftDelayMS));
    el = root.createNewChildElement("RightDelayTimeMS");
    el->addTextElement(String(m_rightDelayMS));
    el = root.createNewChildElement("LeftFeedback");
    el->addTextElement(String(m_leftFeedback * 100));
    el = root.createNewChildElement("RightFeedback");
    el->addTextElement(String(m_rightFeedback * 100));
    el = root.createNewChildElement("DryWet");
    el->addTextElement(String(m_wet * 100));
    el = root.createNewChildElement("nUnits");
    el->addTextElement(String(m_numberOfDelays));
    el = root.createNewChildElement("Depth");
    el->addTextElement(String(m_depth * 100));
    el = root.createNewChildElement("Speed");
    el->addTextElement(String(m_speed * 100));
    
    copyXmlToBinary(root,destData);
}

void ApdelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    XmlElement* pRoot = getXmlFromBinary(data,sizeInBytes);
    
    if(pRoot!=NULL)
        
    {
        String text;
        forEachXmlChildElement((*pRoot),pChild)
        
        {
            if (pChild->hasTagName("LeftDelayTimeMS")) {
                 text = pChild->getAllSubText();
                setParameter(LeftDelayTimeMS, text.getFloatValue());
            }
            else if (pChild->hasTagName("RightDelayTimeMS")) {
                text = pChild->getAllSubText();
                setParameter(RightDelayTimeMS, text.getFloatValue());
            }
            else if (pChild->hasTagName("LeftFeedback")) {
                text = pChild->getAllSubText();
                setParameter(LeftFeedback, text.getFloatValue());
            }
            else if (pChild->hasTagName("RightFeedback")) {
                text = pChild->getAllSubText();
                setParameter(RightFeedback, text.getFloatValue());
            }
            else if (pChild->hasTagName("DryWet")) {
                text = pChild->getAllSubText();
                setParameter(DryWet, text.getFloatValue());
            }
            else if (pChild->hasTagName("nUnits")) {
                text = pChild->getAllSubText();
                setParameter(nUnits, text.getIntValue());
            }
            else if (pChild->hasTagName("Depth")) {
                text = pChild->getAllSubText();
                setParameter(Depth, text.getFloatValue());
            }
            else if (pChild->hasTagName("Speed")) {
                text = pChild->getAllSubText();
                setParameter(Speed, text.getFloatValue());
            }
            
        }
        
        delete pRoot;
        
        //UIUpdateFlag=true;//Request UI update
        
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ApdelayAudioProcessor();
}
