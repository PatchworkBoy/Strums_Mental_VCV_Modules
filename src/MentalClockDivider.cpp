///////////////////////////////////////////////////
//
//   Clock Divider VCV Module
//   Based on autodafe's clock divider but code cleaned up and extra outputs added.
//
//   Strum 2017
//
///////////////////////////////////////////////////



#include "mental.hpp"
#include "dsp/digital.hpp"

////////////////////////////////////////////////
struct MentalClockDivider : Module {
	enum ParamIds {
		RESET_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1,
		OUT2,
		OUT4,
		OUT8,
		OUT16,
		OUT32,
    OUT3,
		OUT5,
		OUT7,
		OUT12,
		NUM_OUTPUTS
	};
  
	int clock2Count = 0;
	int clock4Count = 0;
	int clock8Count = 0;
	int clock16Count = 0;
	int clock32Count = 0;
  
  int clock3Count = 0;
  int clock5Count = 0;
  int clock7Count = 0;
  int clock12Count = 0;

	SchmittTrigger trigger2;
	SchmittTrigger trigger4;
	SchmittTrigger trigger8;
	SchmittTrigger trigger16;
	SchmittTrigger trigger32;
  
  SchmittTrigger trigger3;
  SchmittTrigger trigger5;
  SchmittTrigger trigger7;
  SchmittTrigger trigger12;

	SchmittTrigger reset_trig;

  float lights[9] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

	MentalClockDivider();
	void step();
};

////////////////////////////////////////////////////////////////
MentalClockDivider::MentalClockDivider() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
	trigger2.setThresholds(0.0, 1.0);
	trigger4.setThresholds(0.0, 1.0);
	trigger8.setThresholds(0.0, 1.0);
	trigger16.setThresholds(0.0, 1.0);
	trigger32.setThresholds(0.0, 1.0);

  trigger3.setThresholds(0.0, 1.0);
  trigger5.setThresholds(0.0, 1.0);
  trigger7.setThresholds(0.0, 1.0);
  trigger12.setThresholds(0.0, 1.0);
  
	reset_trig.setThresholds(0.0, 1.0);
}

const float lightLambda = 0.075;
int divider2 = 2;
int divider4 = 4;
int divider8 = 8;
int divider16 = 16;
int divider32 = 32;

int divider3 = 3;
int divider5 = 5;
int divider7 = 7;
int divider12 = 12;

//////////////////////////////////////////////////////////////////////////////////
void MentalClockDivider::step()
{
	bool reset = false;

	if (reset_trig.process(params[RESET_PARAM].value))
	{
		clock2Count = 0;
		clock4Count = 0;
		clock8Count = 0;
		clock16Count = 0;
		clock32Count = 0;

    clock3Count = 0;
    clock5Count = 0;
    clock7Count = 0;
    clock12Count = 0;

		reset = true;
	}
  
  //if ((clock2Count >= divider2) || (reset_trig.process(inputs[RESET_INPUT].value)))
	if (clock2Count >= divider2)
	{
		clock2Count = 0;		
		reset = true;
	}
	if (clock4Count >= divider4)
	{
		clock4Count = 0;		
		reset = true;
	}
	if (clock8Count >= divider8)
	{
		clock8Count = 0;		
		reset = true;
	}
	if (clock16Count >= divider16)
	{
		clock16Count = 0;		
		reset = true;
	}
	if (clock32Count >= divider32)
	{
		clock32Count = 0;	
		reset = true;
	}  
  if (clock3Count >= divider3)
	{
		clock3Count = 0;		
		reset = true;
	}
  if (clock5Count >= divider5)
	{
		clock5Count = 0;		
		reset = true;
	}
  if (clock7Count >= divider7)
	{
		clock7Count = 0;		
		reset = true;
	}
  if (clock12Count >= divider12)
	{
		clock12Count = 0;		
		reset = true;
	}
  
/////////////////////////////////////////////////////////////
	if (clock2Count < divider2 / 2)
	{
		outputs[OUT2].value= 10.0;
		if (clock2Count == 0)
		{
			lights[0] = 1.0;
		}
		else
		{
       // sample rate has changed, update this.
			lights[0] -= lights[0] / lightLambda / gSampleRate;
		}		
	}
	else
	{
		outputs[OUT2].value= 0.0;
		lights[0] = 0.0;		
	}

	if (clock4Count < divider4 / 2)
	{
		outputs[OUT4].value= 10.0;
		if (clock4Count == 0)
		{
			lights[1] = 1.0;
		}
		else
		{
			lights[1] -= lights[1] / lightLambda / gSampleRate;
		}		
	}
	else
	{
		outputs[OUT4].value= 0.0;
		lights[1] = 0.0;		
	}
  
	if (clock8Count < divider8 / 2)
	{
		outputs[OUT8].value= 10.0;
		if (clock8Count == 0)
		{
			lights[2] = 1.0;
		}
		else
		{
			lights[2] -= lights[2] / lightLambda / gSampleRate;
		}	
	}
	else
	{
		outputs[OUT8].value= 0.0;
		lights[2] = 0.0;		
	}

	if (clock16Count < divider16 / 2)
	{
		outputs[OUT16].value= 10.0;
		if (clock16Count == 0)
		{
			lights[3] = 1.0;
		}
		else
		{
			lights[3] -= lights[3] / lightLambda / gSampleRate;
		}		
	}
	else
	{
		outputs[OUT16].value= 0.0;
		lights[3] = 0.0;	
	}

	if (clock32Count < divider32 / 2)
	{
		outputs[OUT32].value= 10.0;
		if (clock16Count == 0)
		{
			lights[4] = 1.0;
		}
		else
		{
			lights[4] -= lights[4] / lightLambda / gSampleRate;
		}		
	}
	else
	{
		outputs[OUT32].value= 0.0;
		lights[4] = 0.0;	
	}
  
  if (clock3Count < divider3 / 2) outputs[OUT3].value = 10.0;	else outputs[OUT3].value = 0.0;
  if (clock5Count < divider5 / 2) outputs[OUT5].value = 10.0;	else outputs[OUT5].value = 0.0;
  if (clock7Count < divider7 / 2) outputs[OUT7].value = 10.0;	else outputs[OUT7].value = 0.0;
  if (clock12Count <divider12/2) outputs[OUT12].value = 10.0; else outputs[OUT12].value = 0.0;
  
//////////////////////////////////////////////////////////////////////////////
	if (reset == false)
	{
		if (trigger2.process(inputs[CLOCK_INPUT].value) && clock2Count <= divider2)
					clock2Count++;			
		if (trigger4.process(inputs[CLOCK_INPUT].value) && clock4Count <= divider4)
					clock4Count++;			
		if (trigger8.process(inputs[CLOCK_INPUT].value) && clock8Count <= divider8)
					clock8Count++;			
		if (trigger16.process(inputs[CLOCK_INPUT].value) && clock16Count <= divider16)		
			clock16Count++;			
		if (trigger32.process(inputs[CLOCK_INPUT].value) && clock32Count <= divider32)		
			clock32Count++;	
    if (trigger3.process(inputs[CLOCK_INPUT].value) && clock3Count <= divider3)		
			clock3Count++;
    if (trigger5.process(inputs[CLOCK_INPUT].value) && clock5Count <= divider5)		
			clock5Count++;
    if (trigger7.process(inputs[CLOCK_INPUT].value) && clock7Count <= divider7)		
			clock7Count++;
    if (trigger12.process(inputs[CLOCK_INPUT].value) && clock12Count <= divider12)		
			clock12Count++;	
	}
}

/////////////////////////////////////////////////////////////////////////////////////
MentalClockDividerWidget::MentalClockDividerWidget() {
	MentalClockDivider *module = new MentalClockDivider();
	setModule(module);
	box.size = Vec(15 * 3, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/MentalClockDivider.svg")));
		addChild(panel);
	}

	addInput(createInput<PJ301MPort>(Vec(3, 20), module, MentalClockDivider::CLOCK_INPUT));
	addInput(createInput<PJ301MPort>(Vec(3, 55), module, MentalClockDivider::RESET_INPUT));
	addParam(createParam<LEDButton>(Vec(5, 80), module, MentalClockDivider::RESET_PARAM, 0.0, 1.0, 0.0));
	 
	addOutput(createOutput<PJ301MPort>(Vec(2, 120), module, MentalClockDivider::OUT2));  
	addOutput(createOutput<PJ301MPort>(Vec(2, 145), module, MentalClockDivider::OUT4));  
	addOutput(createOutput<PJ301MPort>(Vec(2, 170), module, MentalClockDivider::OUT8));  
	addOutput(createOutput<PJ301MPort>(Vec(2, 195), module, MentalClockDivider::OUT16));
	addOutput(createOutput<PJ301MPort>(Vec(2, 220), module, MentalClockDivider::OUT32));
  
  addOutput(createOutput<PJ301MPort>(Vec(2, 250), module, MentalClockDivider::OUT3));
  addOutput(createOutput<PJ301MPort>(Vec(2, 275), module, MentalClockDivider::OUT5));
  addOutput(createOutput<PJ301MPort>(Vec(2, 300), module, MentalClockDivider::OUT7));
  addOutput(createOutput<PJ301MPort>(Vec(2, 325), module, MentalClockDivider::OUT12));

	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 125), &module->lights[0]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 150), &module->lights[1]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 175), &module->lights[2]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 200), &module->lights[3]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 225), &module->lights[4]));
  
  addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 255), &module->lights[5]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 280), &module->lights[6]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 305), &module->lights[7]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(33, 330), &module->lights[8]));
	

}
