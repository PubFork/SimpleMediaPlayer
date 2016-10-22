# SimpleMediaPlayer
3학년 2학기 멀티미디어 프로그래밍 (차광호 교수) 1번 예제 프로젝트

#* 프로젝트를 시작하기 전에...
본 프로젝트는 **Microsoft Visual Studio Community 2013** IDE를 사용하였습니다. 프로젝트의 형태는 **Win32 Console Application**이며 프로젝트 파일을 생성하는 부분의 설명은 생략하겠습니다.
> 1. DirectShow 프로그래밍을 위해서는 다음과 같은 **라이브러리**가 우선 포함되어야 합니다.
> **strmiids.lib**와 **quartz.lib** 라이브러리를 **의존성 목록**에 추가해줍니다.
> <p align="center">
  <img src="https://github.com/devetude/SimpleMediaPlayer/blob/master/SettingImages/set_project_properties.png?raw=true" width="500"/>
</p>
> <p align="center">
  <img src="https://github.com/devetude/SimpleMediaPlayer/blob/master/SettingImages/set_linker_options.png?raw=true" width="500"/>
</p>
> 2. 본 프로젝트는 **Multi-Bytes Character Set**을 사용합니다.
> <p align="center">
  <img src="https://github.com/devetude/SimpleMediaPlayer/blob/master/SettingImages/set_general_string.png?raw=true" width="500"/>
</p>
> 3. **strcpy** 메소드를 사용 할 때 Visual Studio 2013에서 **unsafe warning**으로 인해서 컴파일이 안되는 경우를 해결하기 위해 다음과 같이 설정합니다.
> <p align="center">
  <img src="https://github.com/devetude/SimpleMediaPlayer/blob/master/SettingImages/set_preprocessor.png?raw=true" width="500"/>
</p>
> 4. 마지막으로 DirectShow 프로그래밍에서는 또한 다음과 같은 **헤더 파일**을 포함해야 합니다. **dshow.h**(DirectShow 헤더 파일)와 **stdio.h**(표준 입출력 헤더 파일)를 **Main.cpp** 파일 내의 **최상단**에 다음과 같이 **include**합니다.
> ```c++
> #include <stdio.h>
> #include <dshow.h>
> ```

#* COM(Component Object Model) 생성과 반납
> DirectShow 프로그래밍에서 여러가지 필터 객체 인스턴스를 생성하기 위해서 Microsoft의 COM 라이브러리를 사용합니다. COM 라이브러리의 생성과 반납은 아래 코드와 같습니다.
> ```c++
> // COM 라이브러리 생성
> CoInitialize(NULL);
> 
> // COM 라이브러리 반납
> CoUninitialize();
> ```
