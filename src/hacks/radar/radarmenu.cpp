#include "Radar.h"
#include"../../GUI/Gui.h"

void CRadar::Menu()
{

	VectorEx<const char*> RadTraceStyleItem = { lolc("Line"), lolc("FOV"),lolc("FOV + Line") };
	VectorEx<const char*> PointStyleItem = { lolc("Filled box"), lolc("Box"), lolc("Filled circle"), lolc("Circle"), lolc("None") };

	tahaGUI().PushItemWidth(360);

	DCheckBox("Engine Radar", RadarInGame);
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	DCheckBox("Draw radar", RadarActive);
	if (RadarActive)
	{
		tahaGUI().SameLine();
		DCheckBox("With map", TexturedRadar);
	}
	tahaGUI().Spacing();
	tahaGUI().Separator();
	tahaGUI().Spacing();
	if (RadarActive)
	{
		DCheckBox("Enemy", Enemy);

		tahaGUI().SameLine();
		DCheckBox("Team", Team);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DColorEdit("CT color", ColorCT);
		tahaGUI().SameLine();
		DColorEdit("Visible CT color", ColorVisbleCT);


		DColorEdit("T color", ColorTT);
		tahaGUI().SameLine();
		DColorEdit("Visible T color", ColorVisbleTT);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();
		SliderInts("Zoom", Range, 1, 4000);
		tahaGUI().Spacing();

		SliderInts("Position X", RadarPosX, 1, CGlobal::iScreenWidth);
		SliderInts("Position Y", RadarPosY, 1, CGlobal::iScreenHeight);


		tahaGUI().Spacing();

		SliderInts("Size X", RadarSizeX, 1, 900);
		SliderInts("Size Y", RadarSizeY, 1, 900);


		tahaGUI().Spacing();

		SliderInts("Alpha", Alpha, 1, 255);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DCheckBox("Fov", Fov);

		tahaGUI().SameLine();
		DCheckBox("Line", Line);
		tahaGUI().SameLine();
		DCheckBox("Outline", OutLine);
		tahaGUI().SameLine();
		DCheckBox("Only in radar", OnlyInRadar);
		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DColorEdit("Background color", ColorBackground);
		DColorEdit("Line color", ColorLine);

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		SliderInts("Size##point", PointSize, 2, 50);
		DComboBox("Style##point", PointStyle, PointStyleItem);

//		tahaGUI().Spacing();
//		tahaGUI().Separator();
//		tahaGUI().Spacing();

/*		DCheckBox("Sound", Sound);
		if (Sound)
		{
			SliderInts("Size##soud", SoundPointSize, 2, 50);
			DComboBox("Style##soud", SoundPointStyle, PointStyleItem);
			DColorEdit("Color##soud", SoundColor);
		}
*/

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DCheckBox("Trace", Trace);

		if (Trace)
		{
			SliderInts("Lenght##trace", TraceLenght, 2, 300);
			DComboBox("Style##trace", TraceStyle, RadTraceStyleItem);
		}

		tahaGUI().Spacing();
		tahaGUI().Separator();
		tahaGUI().Spacing();

		DCheckBox("Name", Name);
		if (Name)
		{
			SliderInts("Text size##name", TextNameSize, 9, MAX_FONT_SIZE);

			DColorEdit("Color##name", NameColor);
		}

	}
}



























































