#include <stdio.h>
#include <dshow.h>

void main() {
	// ���� �׷��� �Ŵ��� ������ ����
	IGraphBuilder *pGraph = NULL;

	// �̵�� ��Ʈ�� ������ ����
	IMediaControl *pControl = NULL;

	// �̵�� �̺�Ʈ ������ ����
	IMediaEvent *pEvent = NULL;

	// COM(Component Object Model) ���̺귯���� ���� (DirectShow�� COM ���̺귯�� ���)
	HRESULT hr = CoInitialize(NULL);

	// COM ���̺귯���� �������� ���� ���
	if (FAILED(hr)) {
		// ���� �޼��� ��� �� ���α׷� ���� 
		printf("ERROR - Could not initialize COM library.\n");
		return;
	}

	// ���� �׷��� �Ŵ��� �ν��Ͻ� ����
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);

	// ���� �׷��� �Ŵ����� �������� ���� ���
	if (FAILED(hr)) {
		// ���� �޼��� ��� �� ���α׷� ����
		printf("ERROR - Could not create the Filter Graph Manager.\n");
		return;
	}

	// ���� �׷��� �Ŵ����� ���� �̵�� ��Ʈ�� �ν��Ͻ��� ������
	// (�̵�� ��Ʈ���� ���� : �̵�� ��Ʈ�� ���� ex. ����, ����, �Ͻ�����)
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);

	// ���� �׷��� �Ŵ����� ���� �̵�� �̺�Ʈ �ν��Ͻ��� ������
	// (�̵�� �̺�Ʈ�� ���� : ���� �׷��� �Ŵ����� �̺�Ʈ�� ���� ex. ��� �Ϸ�)
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	// ���� �׷��� �Ŵ����� �ش� �̵�� ������ ���� �׷����� ����
	hr = pGraph->RenderFile(L"C:\\Users\\devetude\\Downloads\\passat.mpg", NULL);

	// �̵�� ������ ���� �׷����� �������� ���
	if (SUCCEEDED(hr)) {
		// �̵�� ��Ʈ���� ���� ��Ʈ�� ���
		hr = pControl->Run();

		// ��Ʈ�� ����� �� ���
		if (SUCCEEDED(hr)) {
			long evCode;

			// �̵�� �̺�Ʈ�� ���� ��� �Ϸ���� ���
			pEvent->WaitForCompletion(INFINITE, &evCode);
		}
	}

	// �̵�� ������ ���� �׷����� �������� ���� ���
	else {
		// ���� �޼��� ���
		printf("ERROR - Could not find the media fila.\n");
	}

	// ����ߴ� �ڿ����� �ݳ�
	pControl->Release();
	pEvent->Release();
	pGraph->Release();

	// COM ���̺귯���� ����
	CoUninitialize();
}