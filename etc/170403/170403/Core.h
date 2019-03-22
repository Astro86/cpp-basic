
#pragma once

// 사용자정의 헤더파일을 include 할때는 <>가 아니라 ""을 사용한다.
#include "value.h"

// core 헤더에는 이 프로그램을 구동시킬 핵심 core부분들의 함수들을
// 만들어둔다.
// 일반적으로 헤더파일에는 함수의 선언부분을 만들어두고
// cpp 파일에 함수의 구현부분을 만들어두게 된다.
void Run(PSTUDENT pStudentArr, int iStudentCount);