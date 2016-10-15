#include <stdio.h>
#include <dshow.h>

void main() {
	// 필터 그래프 매니져 포인터 변수
	IGraphBuilder *pGraph = NULL;

	// 미디어 컨트롤 포인터 변수
	IMediaControl *pControl = NULL;

	// 미디어 이벤트 포인터 변수
	IMediaEvent *pEvent = NULL;

	// COM(Component Object Model) 라이브러리를 생성 (DirectShow는 COM 라이브러리 기반)
	HRESULT hr = CoInitialize(NULL);

	// COM 라이브러리가 생성되지 못한 경우
	if (FAILED(hr)) {
		// 에러 메세지 출력 및 프로그램 종료 
		printf("ERROR - Could not initialize COM library.\n");
		return;
	}

	// 필터 그래프 매니져 인스턴스 생성
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);

	// 필터 그래프 매니져가 생성되지 못한 경우
	if (FAILED(hr)) {
		// 에러 메세지 출력 및 프로그램 종료
		printf("ERROR - Could not create the Filter Graph Manager.\n");
		return;
	}

	// 필터 그래프 매니져를 통해 미디어 컨트롤 인스턴스를 가져옴
	// (미디어 컨트롤의 역할 : 미디어 스트림 제어 ex. 시작, 정지, 일시정지)
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);

	// 필터 그래프 매니져를 통해 미디어 이벤트 인스턴스를 가져옴
	// (미디어 이벤트의 역할 : 필터 그래프 매니져의 이벤트를 수신 ex. 재생 완료)
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	// 필터 그래프 매니져로 해당 미디어 파일의 필터 그래프를 생성
	hr = pGraph->RenderFile(L"C:\\Users\\devetude\\Downloads\\passat.mpg", NULL);

	// 미디어 파일의 필터 그래프를 생성했을 경우
	if (SUCCEEDED(hr)) {
		// 미디어 컨트롤을 통해 스트림 재생
		hr = pControl->Run();

		// 스트림 재생이 된 경우
		if (SUCCEEDED(hr)) {
			long evCode;

			// 미디어 이벤트를 통해 재생 완료까지 대기
			pEvent->WaitForCompletion(INFINITE, &evCode);
		}
	}

	// 미디어 파일의 필터 그래프를 생성하지 못한 경우
	else {
		// 에러 메세지 출력
		printf("ERROR - Could not find the media fila.\n");
	}

	// 사용했던 자원들을 반납
	pControl->Release();
	pEvent->Release();
	pGraph->Release();

	// COM 라이브러리를 닫음
	CoUninitialize();
}