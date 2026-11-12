
#include "PluginEditor.h"

#include <functional>
#include <memory>
#include <utility>

using namespace zk;
namespace A = juce;

static constexpr float DW = 1376.0f;
static constexpr float DH = 768.0f;

// ========================================================================
// FONDO: CARCASA, PANELES Y SERIGRAFÍA
// ========================================================================

void ZayKeysEditor::Background::paint(juce::Graphics& g)
{
    g.addTransform(juce::AffineTransform::scale(scale));
    using namespace juce;

    // Metal cepillado
    g.setGradientFill(ColourGradient(
        Colour(0xffd9dbdd), 0, 0,
        Colour(0xffb2b4b7), 0, DH, false));

    g.fillRect(0.0f, 0.0f, DW, DH);

    Random rnd(42);

    for (int y = 0; y < (int) DH; ++y)
    {
        g.setColour(
            (rnd.nextBool() ? Colours::white : Colours::black)
                .withAlpha(rnd.nextFloat() * 0.055f));

        g.drawHorizontalLine(y, 0.0f, DW);
    }

    // Laterales gris plata oscuro
    for (float x : { 0.0f, DW - 30.0f })
    {
        g.setGradientFill(ColourGradient(
            Colour(0xff9ea1a5), x, 0,
            Colour(0xff7b7e82), x + 30.0f, 0, false));

        g.fillRect(x, 0.0f, 30.0f, DH);
    }

    g.setColour(Colour(0xff55575a));
    g.drawVerticalLine(30, 0.0f, DH);
    g.drawVerticalLine((int) DW - 30, 0.0f, DH);

    g.setColour(Colour(0xff6a6c70));
    g.fillRect(0.0f, 0.0f, DW, 18.0f);

    // Cabecera
    g.setColour(Colour(0xff6a6c70));
    g.drawRoundedRectangle(30.0f, 18.0f, DW - 60.0f, 108.0f, 6.0f, 1.5f);

    g.setColour(Colours::white.withAlpha(0.35f));
    g.drawRoundedRectangle(31.0f, 19.0f, DW - 62.0f, 106.0f, 6.0f, 1.0f);

    // Pestaña central con logo
    Path tab;

    tab.startNewSubPath(505.0f, 12.0f);
    tab.cubicTo(520.0f, 12.0f, 530.0f, 20.0f, 545.0f, 78.0f);
    tab.lineTo(545.0f, 110.0f);
    tab.quadraticTo(545.0f, 118.0f, 553.0f, 118.0f);
    tab.lineTo(823.0f, 118.0f);
    tab.quadraticTo(831.0f, 118.0f, 831.0f, 110.0f);
    tab.lineTo(831.0f, 78.0f);
    tab.cubicTo(846.0f, 20.0f, 856.0f, 12.0f, 872.0f, 12.0f);
    tab.closeSubPath();

    g.setGradientFill(ColourGradient(
        Colour(0xffd0d2d4), 0, 12,
        Colour(0xffa9abae), 0, 118, false));

    g.fillPath(tab);

    g.setColour(Colour(0xff55575a));
    g.strokePath(tab, PathStrokeType(1.5f));

    // Corona
    {
        const float cx = DW * 0.5f;

        Path c;

        c.startNewSubPath(cx - 36.0f, 66.0f);
        c.lineTo(cx - 40.0f, 26.0f);
        c.lineTo(cx - 21.0f, 44.0f);
        c.lineTo(cx - 10.0f, 20.0f);
        c.lineTo(cx, 42.0f);
        c.lineTo(cx + 10.0f, 20.0f);
        c.lineTo(cx + 21.0f, 44.0f);
        c.lineTo(cx + 40.0f, 26.0f);
        c.lineTo(cx + 36.0f, 66.0f);
        c.closeSubPath();

        g.setColour(Colour(0xff151515));
        g.fillPath(c);

        for (float px : { -40.0f, -10.0f, 10.0f, 40.0f })
        {
            g.fillEllipse(
                cx + px - 4.0f,
                (px == -40.0f || px == 40.0f) ? 22.0f : 16.0f,
                8.0f,
                8.0f);
        }

        g.fillRect(cx - 36.0f, 62.0f, 72.0f, 8.0f);

        g.setFont(Font(FontOptions("Arial Black", 27.0f, Font::bold)));

        g.drawText(
            "GOLDMINE",
            Rectangle<float>(cx - 100.0f, 72.0f, 200.0f, 28.0f).toNearestInt(),
            Justification::centred,
            false);

        g.setFont(zk::uiFont(14.0f));

        g.drawText(
            "AUDIO",
            Rectangle<float>(cx - 60.0f, 98.0f, 120.0f, 16.0f).toNearestInt(),
            Justification::centred,
            false);
    }

    // Nombre
    g.setColour(Colour(0xff35373a));
    g.setFont(Font(FontOptions("Arial", 52.0f, Font::plain)));

    g.drawText(
        "ZAY KEYS",
        Rectangle<float>(940.0f, 30.0f, 345.0f, 56.0f).toNearestInt(),
        Justification::centredRight,
        false);

    g.setFont(zk::uiFont(16.0f, false));

    g.drawText(
        "by GOLDMINE AUDIO",
        Rectangle<float>(980.0f, 80.0f, 305.0f, 20.0f).toNearestInt(),
        Justification::centredRight,
        false);

    // Marco del LCD
    {
        const Rectangle<float> r(490.0f, 138.0f, 395.0f, 252.0f);

        g.setGradientFill(ColourGradient(
            Colour(0xffa4a7ab), r.getX(), r.getY(),
            Colour(0xff777a7e), r.getX(), r.getBottom(), false));

        g.fillRoundedRectangle(r, 22.0f);

        g.setColour(Colour(0xff4a4c4f));
        g.drawRoundedRectangle(r, 22.0f, 2.0f);

        g.setColour(Colours::white.withAlpha(0.35f));
        g.drawRoundedRectangle(r.reduced(2.0f), 20.0f, 1.0f);

        g.setColour(Colour(0xff0a0a0a));
        g.fillRoundedRectangle(554.0f, 165.0f, 269.0f, 161.0f, 5.0f);

        for (float sx : { 522.0f, 853.0f })
        {
            g.setColour(Colour(0xff1b1b1b));
            g.fillEllipse(sx - 10.0f, 350.0f, 20.0f, 20.0f);

            g.setColour(Colour(0xff6a6a6a));
            g.drawEllipse(sx - 10.0f, 350.0f, 20.0f, 20.0f, 1.5f);
        }
    }

    // Paneles
    for (auto& p : panels)
    {
        const Rectangle<float> r(p.x, p.y, p.w, p.h);

        g.setColour(Colour(0xffc4c6c9));
        g.fillRoundedRectangle(r, 3.0f);

        g.setColour(Colour(0xff5d5f63));
        g.drawRoundedRectangle(r, 3.0f, 1.5f);

        g.setColour(Colours::white.withAlpha(0.4f));
        g.drawRoundedRectangle(r.reduced(1.5f), 2.0f, 1.0f);

        if (p.title.isNotEmpty())
        {
            g.setColour(Colour(0xff2a2a2c));
            g.fillRect(p.x + 1.0f, p.y + 1.0f, p.w - 2.0f, 17.0f);

            g.setColour(Colours::white);
            g.setFont(zk::uiFont(12.0f));

            g.drawText(
                p.title,
                Rectangle<float>(p.x, p.y + 1.0f, p.w, 17.0f).toNearestInt(),
                Justification::centred,
                false);
        }
    }

    // Rieles del teclado
    g.setGradientFill(ColourGradient(
        Colour(0xff8a8d91), 0, 514,
        Colour(0xff3a3c3f), 0, 543, false));

    g.fillRect(30.0f, 514.0f, DW - 60.0f, 29.0f);

    g.setColour(Colour(0xff222426));
    g.drawHorizontalLine(543, 30.0f, DW - 30.0f);

    // Bloque STYLE / SEQUENCER
    g.setColour(Colour(0xff3a3a3a));

    g.drawHorizontalLine(401, 66.0f, 245.0f);
    g.drawHorizontalLine(401, 330.0f, 498.0f);

    g.setFont(zk::uiFont(13.0f));

    g.drawText(
        "STYLE",
        Rectangle<float>(250.0f, 393.0f, 80.0f, 16.0f).toNearestInt(),
        Justification::centred,
        false);

    g.setColour(Colour(0xffb9bbbe));
    g.fillRoundedRectangle(517.0f, 408.0f, 350.0f, 40.0f, 3.0f);

    g.setColour(Colour(0xff5d5f63));
    g.drawRoundedRectangle(517.0f, 408.0f, 350.0f, 40.0f, 3.0f, 1.2f);

    g.setColour(Colour(0xff0c0c0c));
    g.fillRoundedRectangle(648.0f, 431.0f, 80.0f, 5.0f, 2.0f);

    g.setColour(Colour(0xff3a3a3a));
    g.fillRect(683.0f, 426.0f, 10.0f, 15.0f);

    for (auto& i : inerts)
    {
        HwButton::paintFace(
            g,
            {
                i.x - i.w * 0.5f,
                i.y - i.h * 0.5f,
                i.w,
                i.h
            },
            i.red ? HwButton::Style::Red : HwButton::Style::Rect,
            false,
            false,
            false);
    }

    // Textos serigrafiados
    g.setColour(Colour(0xff2a2a2a));

    for (auto& t : texts)
    {
        g.setFont(zk::uiFont(t.size));

        g.drawText(
            t.text,
            Rectangle<float>(
                t.x - 70.0f,
                t.y - t.size * 0.6f,
                140.0f,
                t.size * 1.2f).toNearestInt(),
            Justification::centred,
            false);
    }
}

// ========================================================================
// HELPERS
// ========================================================================

void ZayKeysEditor::place(
    juce::Component& c,
    float cx,
    float cy,
    float w,
    float h)
{
    placed.push_back({ &c, cx, cy, w, h });
}

void ZayKeysEditor::knob(
    juce::Slider& s,
    const juce::String& id,
    float cx,
    float cy,
    float size)
{
    s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    s.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    s.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f,
        true);

    s.setLookAndFeel(&lnf);
    s.setPopupDisplayEnabled(true, true, this);

    addAndMakeVisible(s);

    sliderAtt.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            proc.apvts,
            id,
            s));

    place(s, cx, cy, size + 14.0f, size + 14.0f);
}

void ZayKeysEditor::vslider(
    juce::Slider& s,
    const juce::String& id,
    float cx,
    float cy)
{
    s.setSliderStyle(juce::Slider::LinearVertical);
    s.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    s.setLookAndFeel(&lnf);
    s.setPopupDisplayEnabled(true, true, this);

    addAndMakeVisible(s);

    sliderAtt.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            proc.apvts,
            id,
            s));

    place(s, cx, cy, 30.0f, 104.0f);
}

// IMPORTANTE: tipo explícito zk::HwButton para coincidir con PluginEditor.h.
zk::HwButton& ZayKeysEditor::button(
    zk::HwButton& b,
    float cx,
    float cy,
    float w,
    float h,
    const juce::String& symbol,
    std::function<void()> fn)
{
    b.setSymbol(symbol);
    b.onClick = std::move(fn);

    addAndMakeVisible(b);
    place(b, cx, cy, w, h);

    return b;
}

// ========================================================================
// CONSTRUCCIÓN DEL EDITOR
// ========================================================================

ZayKeysEditor::ZayKeysEditor(ZayKeysProcessor& p)
    : juce::AudioProcessorEditor(p),
      proc(p),
      lcd(p),
      keyboard(p)
{
    addAndMakeVisible(bg);

    // ---- Sound control (izquierda) ----
    knob(sMaster, zk::pid::master, 79, 181, 40);
    knob(sPan, zk::pid::pan, 147, 181, 40);

    text("MASTER VOL", 79, 146, 12);
    text("PAN", 147, 146, 12);

    addAndMakeVisible(meter);
    place(meter, 200, 181, 24, 62);
    text("OUT", 200, 146, 10);

    bg.panels.push_back({ 55.0f, 222.0f, 190.0f, 128.0f, "" });

    vslider(vRevSend, zk::pid::reverbSend, 78, 298);
    text("REVERB", 78, 234, 10);

    vslider(vChoSend, zk::pid::chorusSend, 122, 298);
    text("CHORUS", 122, 234, 10);

    vslider(vVolume, zk::pid::volume, 165, 298);
    text("VOLUME", 165, 234, 10);

    vslider(vDlySend, zk::pid::delaySend, 217, 298);
    text("DELAY", 217, 234, 10);

    // ---- Preset select ----
    text("PRESET SELECT", 359, 232, 13);

    auto mk = [this](const juce::String& n) -> zk::HwButton&
    {
        buttons.push_back(std::make_unique<zk::HwButton>(n));
        return *buttons.back();
    };

    button(mk("presetPrev"), 270, 270, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xB2"),
        [this] { proc.stepPreset(-1); });

    button(mk("presetNext"), 314, 270, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xBC"),
        [this] { proc.stepPreset(1); });

    button(mk("loadSf2"), 369, 270, 30, 18, "SF2",
        [this] { chooseSoundFont(); });

    text("PRESET", 292, 254, 10);
    text("LOAD", 369, 254, 10);
    text("BANK", 292, 304, 11);

    button(mk("bankUp"), 270, 332, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xB2"),
        [this] { proc.stepBank(-1); });

    button(mk("bankDown"), 314, 332, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xBC"),
        [this] { proc.stepBank(1); });

    addAndMakeVisible(seg);
    place(seg, 373, 328, 38, 30);

    text("INSTR", 435, 250, 10);

    button(mk("instPrev"), 418, 270, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xB2"),
        [this] { proc.stepInstrument(-1); });

    button(mk("instNext"), 452, 270, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xBC"),
        [this] { proc.stepInstrument(1); });

    text("SAVE", 418, 314, 10);
    text("RECALL", 452, 314, 10);

    button(mk("save"), 418, 332, 30, 18, "",
        [this] { askSaveName(); });

    button(mk("recall"), 452, 332, 30, 18, "",
        [this] { proc.loadPreset(proc.getPresetIndex()); });

    // ---- LCD ----
    addAndMakeVisible(lcd);
    place(lcd, 689, 246, 256, 148);

    lcd.onLoadSoundFont = [this] { chooseSoundFont(); };
    lcd.onSavePreset = [this] { askSaveName(); };

    for (int i = 0; i < 5; ++i)
    {
        const float y = 219.0f + 19.0f * (float)i;

        button(mk("lcdL" + juce::String(i)),
            519, y, 26, 13, "",
            [this, i] { lcd.pickRow(i); });

        const int r = i;

        button(mk("lcdR" + juce::String(i)),
            857, y, 26, 13, "",
            [this, r]
            {
                if (r == 0)
                    lcd.scroll(-1);
                else if (r == 1)
                    lcd.scroll(1);
                else if (r == 2)
                    lcd.enter();
                else if (r == 3)
                    lcd.movePage(-1);
                else
                    lcd.movePage(1);
            });
    }

    const float bx[6] = { 581, 624, 666, 709, 752, 794 };

    for (int i = 0; i < 6; ++i)
    {
        button(mk("soft" + juce::String(i)),
            bx[i], 354, 30, 14, "",
            [this, i] { lcd.softKey(i); });
    }

    addAndMakeVisible(wheel);
    place(wheel, 953, 203, 100, 100);

    wheel.onTurn = [this](int steps)
    {
        lcd.turnValue(steps);
    };

    text("DOWN", 922, 267, 10);
    text("UP", 982, 267, 10);
    text("INFO", 922, 316, 10);
    text("ENTER", 982, 316, 10);

    button(mk("down"), 922, 284, 30, 18, "",
        [this] { lcd.scroll(1); });

    button(mk("up"), 982, 284, 30, 18, "",
        [this] { lcd.scroll(-1); });

    button(mk("info"), 922, 333, 30, 18, "",
        [this] { lcd.setPage(zk::LCDDisplay::Info); });

    button(mk("enter"), 982, 333, 30, 18, "",
        [this] { lcd.enter(); });

    // ---- Efectos ----
    bg.panels.push_back({ 1019.0f, 137.0f, 101.0f, 195.0f, "REVERB" });
    bg.panels.push_back({ 1122.0f, 137.0f, 100.0f, 195.0f, "CHORUS" });
    bg.panels.push_back({ 1224.0f, 137.0f, 102.0f, 195.0f, "DELAY" });

    knob(sRevDry, zk::pid::revDry, 1047, 185, 24);
    knob(sRevWet, zk::pid::revWet, 1093, 185, 24);

    knob(sChoDry, zk::pid::choDry, 1148, 185, 24);
    knob(sChoWet, zk::pid::choWet, 1194, 185, 24);

    knob(sDlyDry, zk::pid::dlyDry, 1251, 185, 24);
    knob(sDlyWet, zk::pid::dlyWet, 1297, 185, 24);

    for (float x : { 1047.0f, 1148.0f, 1251.0f })
        text("DRY", x, 162, 9);

    for (float x : { 1093.0f, 1194.0f, 1297.0f })
        text("WET", x, 162, 9);

    vslider(vRevTime, zk::pid::revTime, 1047, 278);
    vslider(vRevDamp, zk::pid::revDamp, 1093, 278);

    vslider(vChoRate, zk::pid::choRate, 1148, 278);
    vslider(vChoDepth, zk::pid::choDepth, 1194, 278);

    vslider(vDlyTime, zk::pid::dlyTime, 1251, 278);
    vslider(vDlyFb, zk::pid::dlyFeedback, 1297, 278);

    text("TIME", 1047, 224, 9);
    text("DAMP", 1093, 224, 9);
    text("RATE", 1148, 224, 9);
    text("DEPTH", 1194, 224, 9);
    text("TIME", 1251, 224, 9);
    text("FDBK", 1297, 224, 9);

    // ---- Envelope / filtro ----
    bg.panels.push_back({ 1019.0f, 337.0f, 203.0f, 81.0f, "ENVELOPE (ADSR)" });
    bg.panels.push_back({ 1224.0f, 337.0f, 102.0f, 81.0f, "FILTER" });

    knob(sAttack, zk::pid::attack, 1047, 378, 28);
    knob(sDecay, zk::pid::decay, 1096, 378, 28);
    knob(sSustain, zk::pid::sustain, 1146, 378, 28);
    knob(sRelease, zk::pid::release, 1195, 378, 28);

    knob(sCutoff, zk::pid::cutoff, 1250, 378, 28);
    knob(sResonance, zk::pid::resonance, 1298, 378, 28);

    text("ATTACK", 1047, 409, 9);
    text("DECAY", 1096, 409, 9);
    text("SUSTAIN", 1146, 409, 9);
    text("RELEASE", 1195, 409, 9);
    text("CUTOFF", 1250, 409, 9);
    text("RESONANCE", 1298, 409, 9);

    // ---- Polifonía ----
    text("POLYPHONY", 952, 413, 12);

    const char* pl[4] = { "16", "32", "64", "128" };
    const float px[4] = { 908, 937, 966, 994 };

    for (int i = 0; i < 4; ++i)
    {
        poly[i].setSymbol(pl[i]);

        poly[i].onClick = [this, i]
        {
            if (polyAtt)
                polyAtt->setValueAsCompleteGesture((float)i);
        };

        addAndMakeVisible(poly[i]);
        place(poly[i], px[i], 435, 28, 17);
    }

    if (auto* prm = proc.apvts.getParameter(zk::pid::polyphony))
    {
        polyAtt = std::make_unique<juce::ParameterAttachment>(
            *prm,
            [this](float v)
            {
                for (int i = 0; i < 4; ++i)
                {
                    poly[i].setToggleState(
                        i == juce::roundToInt(v),
                        juce::dontSendNotification);
                }
            });

        polyAtt->sendInitialUpdate();
    }

    text("TUNE-", 922, 466, 9);
    text("PANIC", 957, 466, 9);
    text("TUNE+", 990, 466, 9);

    button(mk("tuneDown"), 922, 482, 30, 18,
        juce::String::fromUTF8("\xE2\x97\x84"),
        [this] { proc.nudgeParam(zk::pid::tune, -5); });

    button(mk("panic"), 957, 482, 30, 18, "!",
        [this] { proc.panic(); });

    button(mk("tuneUp"), 990, 482, 30, 18,
        juce::String::fromUTF8("\xE2\x96\xBA"),
        [this] { proc.nudgeParam(zk::pid::tune, 5); });

    // ---- Glide / transpose / octave ----
    bg.panels.push_back({ 1019.0f, 427.0f, 70.0f, 76.0f, "GLIDE" });

    knob(sGlide, zk::pid::glide, 1053, 475, 28);

    text("SWITCH", 1127, 466, 10);

    glideSwitch.setClickingTogglesState(true);

    addAndMakeVisible(glideSwitch);
    place(glideSwitch, 1127, 486, 24, 20);

    glideAtt = std::make_unique<
        juce::AudioProcessorValueTreeState::ButtonAttachment>(
            proc.apvts,
            zk::pid::glideOn,
            glideSwitch);

    text("TRANSPOSE", 1210, 459, 10);
    text("OCTAVE", 1279, 459, 10);

    button(mk("trMinus"), 1192, 482, 30, 18, "-",
        [this] { proc.nudgeParam(zk::pid::transpose, -1); });

    button(mk("trPlus"), 1227, 482, 30, 18, "+",
        [this] { proc.nudgeParam(zk::pid::transpose, 1); });

    button(mk("ocMinus"), 1262, 482, 30, 18, "-",
        [this] { proc.nudgeParam(zk::pid::octave, -1); });

    button(mk("ocPlus"), 1296, 482, 30, 18, "+",
        [this] { proc.nudgeParam(zk::pid::octave, 1); });

    // ---- Bloque STYLE / SEQUENCER (no interactivo) ----
    for (int i = 0; i < 13; ++i)
    {
        bg.inerts.push_back({
            79.0f + 34.0f * (float)i,
            434.0f,
            28.0f,
            17.0f,
            false
        });
    }

    for (float x : {
        79.0f, 144.0f, 215.0f, 250.0f, 285.0f, 320.0f,
        384.0f, 418.0f, 453.0f, 487.0f, 522.0f, 582.0f,
        617.0f, 760.0f, 803.0f, 848.0f
    })
    {
        bg.inerts.push_back({ x, 482.0f, 28.0f, 17.0f, false });
    }

    bg.inerts.push_back({ 688.0f, 482.0f, 40.0f, 17.0f, true });

    for (float x : { 535.0f, 582.0f, 617.0f, 759.0f, 802.0f, 848.0f })
    {
        bg.inerts.push_back({ x, 435.0f, 28.0f, 17.0f, false });
    }

    text("SEQUENCER", 580, 414, 9);
    text("BALANCE", 688, 414, 9);

    // Teclado virtual
    addAndMakeVisible(keyboard);

    // Ventana
    setResizable(true, true);

    getConstrainer()->setFixedAspectRatio(
        (double)DW / (double)DH);

    setResizeLimits(688, 384, 2752, 1536);
    setSize(1032, 576);

    startTimerHz(30);
}

// ========================================================================
// DESTRUCTOR
// ========================================================================

ZayKeysEditor::~ZayKeysEditor()
{
    stopTimer();

    for (auto* s : {
        &sMaster, &sPan,
        &sRevDry, &sRevWet,
        &sChoDry, &sChoWet,
        &sDlyDry, &sDlyWet,
        &sAttack, &sDecay,
        &sSustain, &sRelease,
        &sCutoff, &sResonance,
        &sGlide,
        &vRevSend, &vChoSend, &vVolume, &vDlySend,
        &vRevTime, &vRevDamp,
        &vChoRate, &vChoDepth,
        &vDlyTime, &vDlyFb
    })
    {
        s->setLookAndFeel(nullptr);
    }
}

// ========================================================================
// RESIZE
// ========================================================================

void ZayKeysEditor::resized()
{
    const float s = (float)getWidth() / DW;

    bg.scale = s;
    bg.setBounds(getLocalBounds());
    bg.repaint();

    for (auto& p : placed)
    {
        p.c->setBounds(
            juce::Rectangle<float>(
                (p.cx - p.w * 0.5f) * s,
                (p.cy - p.h * 0.5f) * s,
                p.w * s,
                p.h * s).toNearestInt());
    }

    keyboard.setBounds(
        juce::Rectangle<float>(
            35.0f * s,
            543.0f * s,
            1306.0f * s,
            225.0f * s).toNearestInt());
}

// ========================================================================
// TIMER
// ========================================================================

void ZayKeysEditor::timerCallback()
{
    meter.setLevels(proc.getMeterL(), proc.getMeterR());

    int banks = 0;
    int last = -1;

    if (auto fi = proc.getFontInfo())
    {
        for (auto& e : fi->entries)
        {
            if (e.bank != last)
            {
                ++banks;
                last = e.bank;
            }
        }
    }

    seg.setValue(proc.getBankIndex(), banks > 10);
}

// ========================================================================
// SOUND FONT
// ========================================================================

void ZayKeysEditor::chooseSoundFont()
{
    juce::File start =
        proc.getLastDirectory().isNotEmpty()
            ? juce::File(proc.getLastDirectory())
            : juce::File::getSpecialLocation(
                juce::File::userDocumentsDirectory);

    chooser = std::make_unique<juce::FileChooser>(
        "Abrir SoundFont 2",
        start,
        "*.sf2;*.SF2");

    chooser->launchAsync(
        juce::FileBrowserComponent::openMode
            | juce::FileBrowserComponent::canSelectFiles,
        [this](const juce::FileChooser& fc)
        {
            const auto f = fc.getResult();

            if (f.existsAsFile())
                proc.loadSoundFontFile(f);
        });
}

// ========================================================================
// GUARDAR PRESET
// ========================================================================

void ZayKeysEditor::askSaveName()
{
    auto* w = new juce::AlertWindow(
        "Guardar preset",
        "Nombre del preset:",
        juce::MessageBoxIconType::NoIcon);

    w->addTextEditor("name", proc.getPresetName());

    w->addButton(
        "Guardar",
        1,
        juce::KeyPress(juce::KeyPress::returnKey));

    w->addButton(
        "Cancelar",
        0,
        juce::KeyPress(juce::KeyPress::escapeKey));

    juce::Component::SafePointer<ZayKeysEditor> safe(this);

    w->enterModalState(
        true,
        juce::ModalCallbackFunction::create(
            [safe, w](int r)
            {
                if (r == 1 && safe != nullptr)
                {
                    safe->proc.saveUserPreset(
                        w->getTextEditorContents("name"));
                }
            }),
        true);
}
