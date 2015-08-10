
#include "SoundManager.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//=========================================================================
// 1. 함수명: CGSoundManager(HWND hWnd = NULL )
// 2. 기   능: 생성자
// 3. 입력인수: HWND 핸들
// 4. 반환값: 없음
//=========================================================================
CGSoundManager::CGSoundManager(HWND hWnd)
	: m_SoundBufferIndex(0)
{
	m_hWnd = hWnd; // 핸들값초기화
	memset(m_ArrlpDSBuf, 0, sizeof(int) * SOUNDBUFFER_SIZE);    // 버퍼초기화
}

//=========================================================================
// 1. 함수명: ~CGSoundManager
// 2. 기   능: 소멸자
// 3. 입력인수: 없음
// 4. 반환값: 없음
//=========================================================================
CGSoundManager::~CGSoundManager(void)
{
	AllStop();
	for (int i = 0; i < SOUNDBUFFER_SIZE; i++)
	{
		if (m_ArrlpDSBuf[i] != NULL)
		{
			m_ArrlpDSBuf[i]->Release();
			m_ArrlpDSBuf[i] = NULL;
		}
	}
}

//=========================================================================
// 1. 함수명: SoundManagerInit
// 2. 기   능: SoundManager를사용하기위한초기화
// 3. 입력인수: 없음
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::DirectSoundInit(HWND hWnd)
{
	if (m_hWnd == NULL)
		m_hWnd = hWnd;

	// 다이렉트사운드객체생성
	HRESULT dsrval = ::DirectSoundCreate(NULL, &m_lpDS, NULL);
	if (dsrval != DS_OK)
	{
		DirectSoundError(L"객체생성실패");
		return;
	}
	// 다이렉트사운드사용환경을지정한다.
	dsrval = m_lpDS->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY);

	if (dsrval != DS_OK) DirectSoundError(L"모드설정실패");
}


//=========================================================================
// 1. 함수명: DirectSoundError
// 2. 기   능: 에러메세지출력
// 3. 입력인수: char* 에러메세지
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::DirectSoundError(TCHAR *errorString)
{
	exit(1);
}


//=========================================================================
// 1. 함수명: AddSoundBuffer
// 2. 기   능: SoundBuffer 배열에추가한다
// 3. 입력인수: LPSoundManagerBUFFER 사운드버퍼구조체
// 4. 반환값: 배열의index 위치반환
//=========================================================================
int  CGSoundManager::AddSoundBuffer(LPDIRECTSOUNDBUFFER buffer)
{
	if (m_SoundBufferIndex < SOUNDBUFFER_SIZE - 1)
	{
		m_ArrlpDSBuf[m_SoundBufferIndex] = buffer;
	}
	return m_SoundBufferIndex++;
}

//=========================================================================
// 1. 함수명: DeleteSoundBuffer
// 2. 기   능: 사운드버퍼배열의해당index 삭제
// 3. 입력인수: int iDel_index
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::DeleteSoundBuffer(int iDel_index)
{

	if (m_ArrlpDSBuf[iDel_index] == NULL)  return;

	m_ArrlpDSBuf[iDel_index]->Release();
	m_SoundBufferIndex--;

	for (int i = iDel_index; i < m_SoundBufferIndex; i++)
	{
		m_ArrlpDSBuf[i] = m_ArrlpDSBuf[i + 1];
	}
	m_ArrlpDSBuf[m_SoundBufferIndex] = NULL;
}

//=========================================================================
// 1. 함수명: LoadWav
// 2. 기   능: 사운드버퍼배열의해당index 삭제
// 3. 입력인수: char* wav (파일명& path) , int Flag( 옵션)
// 4. 반환값: LPSoundManagerBUFFER 사운드버퍼구조체
//=========================================================================
LPDIRECTSOUNDBUFFER CGSoundManager::LoadWav(TCHAR * wav)
{
	int ret;
	WORD                    wExtraAlloc;
	UINT                    i, DataIn;
	LPDIRECTSOUNDBUFFER     lpDSTemp;
	HMMIO                   hmmioIn;
	MMIOINFO                mmioinfoIn;
	MMCKINFO                ckInfo, ckInfoRIFF;
	LPWAVEFORMATEX          lpWaveFormat = 0;
	PCMWAVEFORMAT           pcmWaveFormat;
	LPBYTE                  lpData;
	LPVOID                  lpWrapPtr;
	DWORD                   dwBSize, dwWavSize, dwDataSize, dwWrapBSize;
	DSBUFFERDESC            dsbd;

	// 화일을연다
	hmmioIn = mmioOpen(wav, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (!hmmioIn) DirectSoundError(L"WAV 화일을읽을수없음");
	// 열린화일이RIFF WAVE화일인지확인한다   
	ckInfoRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(hmmioIn, &ckInfoRIFF, NULL, MMIO_FINDRIFF) != 0)
	{
		DirectSoundError(L"RIFF WAVE 화일이아닙니다");
	}
	// 'fmt' Chunk인지확인한다
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmioIn, &ckInfo, &ckInfoRIFF, MMIO_FINDCHUNK) != 0)
	{
		DirectSoundError(L"화일이fmt Chunk가아닙니다");
	}
	// 열린화일을읽는다
	ret = mmioRead(hmmioIn, (HPSTR)&pcmWaveFormat, (long) sizeof(pcmWaveFormat));
	if (ret != (long) sizeof(pcmWaveFormat))
	{
		DirectSoundError(L"화일읽기실패");
	}
	// 읽은화일이PCM형식인지확인한다
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		wExtraAlloc = 0;
	else
	{
		ret = mmioRead(hmmioIn, (LPSTR)&wExtraAlloc, (long) sizeof(wExtraAlloc));
		if (ret != (long) sizeof(wExtraAlloc))
		{
			DirectSoundError(L"화일읽기실패");
		}
	}

	lpWaveFormat = (LPWAVEFORMATEX)malloc(sizeof(WAVEFORMATEX) + wExtraAlloc);
	memcpy(lpWaveFormat, &pcmWaveFormat, sizeof(pcmWaveFormat));
	lpWaveFormat->cbSize = wExtraAlloc;
	if (wExtraAlloc != 0)
	{
		ret = mmioRead(hmmioIn,
			(LPSTR)(((BYTE*)&(lpWaveFormat->cbSize)) + sizeof(wExtraAlloc)),
			(long)(wExtraAlloc));
		if (ret != (long) sizeof(wExtraAlloc))
		{
			DirectSoundError(L"화일읽기실패");
		}
	}

	if (mmioAscend(hmmioIn, &ckInfo, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError(L"오류");
	}


	if (mmioSeek(hmmioIn, ckInfoRIFF.dwDataOffset + sizeof(FOURCC), SEEK_SET) == -1)
	{
		DirectSoundError(L"오류");
	}
	// 'data' Chunk를찾는다
	MMCKINFO    pckIn;
	pckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmioIn, &pckIn, &ckInfoRIFF, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		DirectSoundError(L"Data Chunk가아닙니다");
	}
	dwDataSize = pckIn.cksize;
	lpData = NULL;

	// 스태틱2차버퍼를만들기위해구조체를생성한다.
	// 사운드버퍼의제어는볼륨, 좌우밸런스, 주파수조절이가능하도록한다
	memset(&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
	dsbd.dwBufferBytes = dwDataSize;
	dwWavSize = lpWaveFormat->cbSize + sizeof(WAVEFORMATEX);

	dsbd.lpwfxFormat = (LPWAVEFORMATEX)malloc(dwWavSize);
	memcpy(dsbd.lpwfxFormat, lpWaveFormat, dwWavSize);
	free(lpWaveFormat);

	// 2차사운드버퍼를생성한다.
	if (m_lpDS->CreateSoundBuffer(&dsbd, &lpDSTemp, NULL) != DS_OK)
	{
		DirectSoundError(L"사운드버퍼생성실패");
	}

	free(dsbd.lpwfxFormat);
	// 생성된버퍼에기입한다
	ret = lpDSTemp->Lock(0, dwDataSize, (void**)&lpData, &dwBSize,
		&lpWrapPtr, &dwWrapBSize, 0L);
	if (ret != DS_OK)
	{
		DirectSoundError(L"오류");
	}
	dwDataSize = dwBSize;
	// 열린화일의상태(진행상황)을알아온다
	if (mmioGetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError(L"오류");
	}

	DataIn = dwDataSize;
	if (DataIn > pckIn.cksize) DataIn = pckIn.cksize;
	pckIn.cksize -= DataIn;

	for (i = 0; i < DataIn; i++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			ret = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ);
			if (ret != MMSYSERR_NOERROR) DirectSoundError(L"오류");
		}
		*((BYTE*)lpData + i) = *((BYTE*)mmioinfoIn.pchNext++);
	}
	if (mmioSetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError(L"오류");
	}
	lpDSTemp->Unlock(lpData, dwBSize, lpWrapPtr, dwWrapBSize);
	return lpDSTemp;
}


//=========================================================================
// 1. 함수명: Stop
// 2. 기   능: 스톱
// 3. 입력인수: int index 사운드버퍼의인덱스
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::Stop(int index)
{
	m_ArrlpDSBuf[index]->Stop();
}

//=========================================================================
// 1. 함수명: AllStop
// 2. 기   능: 스톱
// 3. 입력인수: 없음
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::AllStop()
{
	for (int i = 0; i < GetBufferSize(); i++)
	{
		m_ArrlpDSBuf[i]->Stop();
	}
}


//=========================================================================
// 1. 함수명: IsPlaying
// 2. 기   능: 현재재생중인가를판단
// 3. 입력인수: int index 사운드버퍼의인덱스
// 4. 반환값: BOOL   TRUE = 재생중일때  FALSE = 재생중이아닐때
//=========================================================================
BOOL CGSoundManager::IsPlaying(int index)
{
	DWORD   dwPlayCursol;
	DWORD   dwWriteCursol;

	m_ArrlpDSBuf[index]->GetCurrentPosition(&dwPlayCursol, &dwWriteCursol);

	if (dwPlayCursol != 0) return TRUE;

	return FALSE;
}


//=========================================================================
// 1. 함수명: Play
// 2. 기   능: 사운드재생
// 3. 입력인수: int index 사운드버퍼의인덱스, LOOP ( TRUE : 반복재생   FALSE(기본값) : 1번반복
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::Play(int index, BOOL Loop)
{
	if (IsPlaying(index) == TRUE) return;
	if (IsBufIndex(index))
	{
		if (IsPlaying(index))
		{
			Stop(index);
		}
		m_ArrlpDSBuf[index]->SetCurrentPosition(0);
		m_ArrlpDSBuf[index]->Play(0, 0, (Loop == TRUE) ? 1 : 0);
	}
}

//=========================================================================
// 1. 함수명: IsBufIndex
// 2. 기   능: 버퍼가Empty상태인지확인
// 3. 입력인수: 사운드버퍼의인덱스
// 4. 반환값: TRUE : NULL이아닐경우  FALSE : NULL일경우
//=========================================================================
BOOL CGSoundManager::IsBufIndex(int index)
{
	if (m_ArrlpDSBuf[index] == NULL)
		return FALSE;
	return TRUE;
}


//=========================================================================
// 1. 함수명: SetPan
// 2. 기   능: 좌우밸런스조절
// 3. 입력인수: 사운드버퍼의인덱스, 밸런스값(-10000~10000)
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::SetPan(int index, long pan)
{
	if (m_lpDS == NULL)return;
	if (IsBufIndex(index))
		m_ArrlpDSBuf[index]->SetPan(pan);
}

//=========================================================================
// 1. 함수명: SetVol
// 2. 기   능: 볼륨조절
// 3. 입력인수: 사운드버퍼의인덱스, 볼륨값(-10000~10000)
// 4. 반환값: 없음
//=========================================================================
void CGSoundManager::SetVol(int index, long vol)
{
	if (m_lpDS == NULL)return;
	if (vol<-10000)  vol = -10000;
	if (vol>10000)   vol = 10000;
	if (IsBufIndex(index)) m_ArrlpDSBuf[index]->SetVolume(vol);
}
