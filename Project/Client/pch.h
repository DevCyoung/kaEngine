// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include <Windows.h>
#include <string>
#include <assert.h>
#include <vector> // 배열
#include <list> //링크드리스트 
#include <map> // 2진트리
#include <unordered_map> // hash map
#include <bitset> // 비트 배열 편하게 사용해주는 라이브러리
#include <set> // 해시 테이블
#include <functional> // 함수 포인터
#include <cmath> //수학
#include <algorithm> //정렬 알고리즘
#include <limits> //부동 소수점 표현 및 반올림과 관련된 클래스 템플릿 numeric_limits 및 두 개의 열거형을 정의합니다.
#include <memory> //메모리 관련된 라이브러리
#include <filesystem> // 파일입출력 편하게 도와주는 라이브러리

#endif //PCH_H
