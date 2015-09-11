#include "PreCompiled.h"
#include <conio.h>

void main(void)
{
	Vdfs Test;
	Timer Measure;
	Measure.Start();
	Test.Init();
	printf("%f\n", Measure.GetElapsedTimeSeconds());
	_getch();
}