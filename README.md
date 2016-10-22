# SimpleMediaPlayer
3학년 2학기 멀티미디어 프로그래밍 (차광호 교수) 1번 예제 프로젝트

> 1. DirectShow 프로그래밍을 위해서는 다음과 같은 **라이브러리**가 우선 포함되어야 합니다.
> **strmiids.lib**와 **quartz.lib** 라이브러리를 **의존성 목록**에 추가해줍니다.
![](https://github.com/devetude/SimpleMediaPlayer/blob/master/SettingImages/set_project_properties.png?raw=true)
> 2. DirectShow 프로그래밍에서는 또한 다음과 같은 **헤더 파일**을 포함되어야 합니다.
> **dshow.h**(DirectShow 헤더 파일)와 **stdio.h**(표준 입출력 헤더 파일)를 **Main.cpp** 파일 내의 **최상단**에 다음과 같이 **include**합니다.
 ```c++
 #include <stdio.h>
 #include <dshow.h>
```
