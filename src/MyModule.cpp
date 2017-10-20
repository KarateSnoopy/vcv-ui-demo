#include "rack.hpp"
using namespace rack;
extern Plugin *plugin;

struct MyModuleWidget : ModuleWidget
{
    MyModuleWidget();
};

Plugin *plugin;

void init(rack::Plugin *p)
{
    plugin = p;
    plugin->slug = "vcv-ui-demo";
    plugin->name = "UI Demo";
    plugin->homepageUrl = "https://github.com/KarateSnoopy/vcv-ui-demo";

    createModel<MyModuleWidget>(plugin, "UI Demo", "UI Demo");
}

struct WarpsModeLight : ModeValueLight
{
    WarpsModeLight()
    {
        addColor(COLOR_BLACK_TRANSPARENT);
        addColor(COLOR_GREEN);
        addColor(COLOR_YELLOW);
        addColor(COLOR_RED);
    }
};

struct MyModule : Module
{
    enum ParamIds
    {
        PITCH_PARAM,
        NUM_PARAMS
    };
    enum InputIds
    {
        PITCH_INPUT1,
        PITCH_INPUT2,
        PITCH_INPUT3,
        NUM_INPUTS
    };
    enum OutputIds
    {
        SINE_OUTPUT1,
        SINE_OUTPUT2,
        SINE_OUTPUT3,
        NUM_OUTPUTS
    };

    float runningLight = 1.0;
    float runningLight2 = 0.0;

    MyModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
    void step();
};

void MyModule::step()
{
    // Implement a simple sine oscillator
    runningLight += 0.0001f;
    if (runningLight > 1.0f)
        runningLight = -1.0f;

    runningLight2 += 0.0001f;
    if (runningLight2 > 5.0f)
        runningLight2 = 0.0f;
}

MyModuleWidget::MyModuleWidget()
{
    MyModule *module = new MyModule();
    setModule(module);
    box.size = Vec(100 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

    {
        SVGPanel *panel = new SVGPanel();
        panel->box.size = box.size;
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/MyModule.svg")));
        addChild(panel);
    }

    addChild(createScrew<ScrewSilver>(Vec(15, 0)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
    addChild(createScrew<ScrewSilver>(Vec(15, 365)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));

    int x = 10;
    int dx = 70;
    int ix = 0;

    int y = 10;
    int dy = 50;
    int iy = 0;

    iy = 0;
    ix = 0;

    addParam(createParam<Davies1900hWhiteKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hRedKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hLargeWhiteKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hLargeBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hLargeRedKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));

    iy++;
    ix = 0;

    addParam(createParam<RoundBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<RoundSmallBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<RoundLargeBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<RoundHugeBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<RoundSmallBlackSnapKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hSmallBlackKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));
    addParam(createParam<Davies1900hSmallBlackSnapKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, -3.0, 3.0, 0.0));

    iy++;
    ix = 0;

    addParam(createParam<Rogan6PSWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan5PSGray>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PSBlue>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PSRed>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PSGreen>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PSWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PBlue>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));

    iy++;
    ix = 0;

    addParam(createParam<Rogan3PRed>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PGreen>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan3PWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2SGray>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PSBlue>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PSRed>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PSGreen>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PSWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PBlue>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));

    iy++;
    ix = 0;

    addParam(createParam<Rogan2PRed>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PGreen>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan2PWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PSBlue>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PSRed>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PSGreen>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PSWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PBlue>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PRed>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PGreen>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Rogan1PWhite>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));

    iy++;
    ix = 0;

    addParam(createParam<SynthTechAlco>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<Trimpot>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<BefacoBigKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<BefacoBigSnapKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<BefacoTinyKnob>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addParam(createParam<BefacoSlidePot>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));

    iy = 0;
    x = 12 * dx;
    ix = 0;

    addInput(createInput<PJ301MPort>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_INPUT1));
    addInput(createInput<PJ3410Port>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_INPUT2));
    addInput(createInput<CL1362Port>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_INPUT3));
    addOutput(createOutput<PJ301MPort>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::SINE_OUTPUT1));
    addOutput(createOutput<PJ3410Port>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::SINE_OUTPUT2));
    addOutput(createOutput<CL1362Port>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::SINE_OUTPUT3));

    iy++;
    ix = 0;

    addChild(createValueLight<LargeLight<RedValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<LargeLight<YellowValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<LargeLight<GreenValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<LargeLight<GreenRedPolarityLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<LargeLight<WarpsModeLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight2));

    iy++;
    ix = 0;

    addChild(createValueLight<MediumLight<RedValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<MediumLight<YellowValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<MediumLight<GreenValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<MediumLight<GreenRedPolarityLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<MediumLight<WarpsModeLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight2));

    iy++;
    ix = 0;

    addChild(createValueLight<SmallLight<RedValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<SmallLight<YellowValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<SmallLight<GreenValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<SmallLight<WarpsModeLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight2));

    iy++;
    ix = 0;

    addChild(createValueLight<TinyLight<RedValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<TinyLight<YellowValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<TinyLight<GreenValueLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<TinyLight<GreenRedPolarityLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight));
    addChild(createValueLight<TinyLight<WarpsModeLight>>(Vec(x + (dx * ix++), y + (dy * iy)), &module->runningLight2));

    iy++;
    ix = 0;

    addChild(createParam<NKK>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<CKSS>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<CKD6>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<TL1105>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<LEDButton>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<BefacoSwitch>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<BefacoPush>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
    addChild(createParam<PB61303>(Vec(x + (dx * ix++), y + (dy * iy)), module, MyModule::PITCH_PARAM, 0.0, 1.0, 0.0));
}
