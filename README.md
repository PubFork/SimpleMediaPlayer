# SimpleMediaPlayer
3학년 2학기 멀티미디어 프로그래밍 (차광호 교수) 1번 예제 프로젝트

다음과 같은 간단한 미디어 플레이어를 DirectShow를 이용하여 만들어봅니다.

<p align="center">
  <img src="https://github.com/devetude/SimpleMediaPlayer/blob/master/RunImages/run_screenshot.gif?raw=true" width="500"/>
</p>

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
> DirectShow 프로그래밍에서 여러가지 필터 객체 인스턴스를 생성하기 위해서 Microsoft의 **COM** 라이브러리를 사용합니다. COM 라이브러리의 **생성**과 **반납**은 아래 코드와 같습니다.
> ```c++
> // COM 라이브러리 생성
> CoInitialize(NULL);
> 
> // COM 라이브러리 반납
> CoUninitialize();
> ```

#* Filter Graph Manager 인스턴스 생성과 반납
> DirectShow 프로그래밍에서 직접 필터 객체와 핀 객체 연결할 때 대리자 역할인 **Filter Graph Manager**를 통해서 위와 같은 과정들을 진행하게 됩니다. COM 객체를 이용하여 Filter Graph Manager 객체 인스턴스를 **생성**하고 **반납**하는 방법은 아래 코드와 같습니다.
> ```c++
> // Filter Graph Manager 객체를 저장 할 포인터 변수
> IGraphBuilder *pGraphBuilder = NULL;
> 
> // COM 객체를 이용하여 Filter Graph Manager 객체 인스턴스 생성
> CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPOC_SERVER, IID_IGraphBuilder, (void **)&pGraphBuilder);
>  
> // Filter Graph Manager 객체 인스턴스 반납
> pGraphBuilder->Release();
>  ```

#* IMediaControl, IMediaEvent 인스턴스 생성과 반납
> 생성되어있는 Filter Graph Manager 객체 인스턴스를 가지고 미디어 스트림의 재생과 정지 등을 관리하는 **IMediaControl**과 다양한 미디어 스트림의 이벤트를 처리하는 **IMediaEvent**를 **생성**하고 **반납**하는 코드는 아래와 같습니다.
> ```c++
> // IMediaControl, IMediaEvent 객체를 저장 할 포인터 변수
> IMediaControl *pMediaControl = NULL;
> IMediaEvent * pMediaEvent = NULL;
> 
> // IMediaControl, IMediaEvent 객체 인스턴스 생성
> pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
> pGraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&pMediaEvent);
>  
>  // IMediaControl, IMediaEvent 객체 인스턴스 반납
>  pMediaControl->Release();
>  pMediaEvent->Release();

#* 미디어 파일을 읽어와서 필터 그래프를 랜더링
> Filter Graph Manager 객체 인스턴스의 **RenderFile** 메소드를 이용하여 미디어 파일을 읽어온 후 필터 그래프를 랜더링을 할 수 있습니다. 또한 IMediaGraph를 이용하여 가져온 미디어 파일을 재생(**Run**)하거나, 정지(**Stop**) 할 수 있습니다. 마지막으로 IMediaEvent를 이용하여 이벤트를 수신하여 처리(**WaitForCompletion**) 할 수도 있습니다.
> ```c++
> // Filter Graph Manager로 미디어 파일을 읽어와서 랜더링
> pGraphBuilder->RenderFile(L"미디어 파일의 경로를 입력");
> 
> // IMediaControl로 미디어 파일을 재생하고 정지
> pMediaControl->Run();
> pMediaControl->Stop();
> 
> // IMediaEvent로 미디어 파일의 이벤트를 수신(재생이 끝날 때 까지 기다림)
> long eventCode = 0;
> pMediaEvent->WaitForCompletion(INFINITE, &eventCode);
> ```

#* 라이센스
본 프로젝트는 Apache 2.0 License를 따릅니다. http://www.apache.org/licenses/LICENSE-2.0

#* 문의사항
기타 문의사항이 있으실 경우 아래의 **문의 수단**으로 연락해주세요.
> **문의 수단:**
> - 메일 : **devetude@naver.com** 또는 **devetude@gmail.com**
> - github : **https://github.com/devetude/SimpleMediaPlayer/issues**
