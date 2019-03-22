
#include "Core.h"

int main()
{
	STUDENTCONTAINER	tStudentContainer = {};

	if (!Init(&tStudentContainer))
		return 0;

	Run(&tStudentContainer);

	Close(&tStudentContainer);

	return 0;
}