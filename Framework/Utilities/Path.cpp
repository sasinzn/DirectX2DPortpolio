#include "Framework.h"
#include "Path.h"


// 파일 존재 여부 확인
bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path));
}

bool Path::ExistFile(wstring path)
{
	// 파일이나 폴더의 속성을 알아오는 함수
	// 실패하면 INVALID_FILE_ATTRIBUTES 를 반환

	DWORD fileValue = GetFileAttributes(path.c_str());

	return fileValue != INVALID_FILE_ATTRIBUTES;
}
// 폴더의 존재 여부 확인
bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && attribute & FILE_ATTRIBUTE_DIRECTORY);
	
	return false;
}

string Path::Combine(string path1, string path2)
{
	
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{

	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";

	for (string path : paths)
		temp += path;
	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";

	for (wstring path : paths)
		temp += path;
	return temp;
}

// 입력된 경로에서 폴더 이름을 반환
string Path::GetDirectoryName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');
	
	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}
// 파일의 확장자를 반환
string Path::GetExtension(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

// 파일 이름과 확장자를 반환
string Path::GetFileName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

// 파일 이름만 반환 시켜주는 함수
string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

// 특정 확장자 파일의 필터
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text file\0*.txt";
const WCHAR* Path::TileFilter = L"Tile file\0*.png;*.bmp;*.jpg;*.json;*.data";
const WCHAR* Path::TMapFilter = L"TMap file\0*.tmap";



void Path::OpenFileDialog(wstring defaultFileName, const WCHAR* fileTypeFilter, const wstring defaultFolder, const function<void(wstring)> callback, HWND parentWindowHandle)
{
	WCHAR name[255];
	wcscpy_s(name, defaultFileName.c_str());

	wstring tempFolder = defaultFolder;

	OPENFILENAME ofn;
	Zero(ofn);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parentWindowHandle;					// 부모창 핸들
	ofn.lpstrFilter = fileTypeFilter;					// 파일 유형 필터
	ofn.lpstrFile = name;								// 파일 이름
	ofn.lpstrFileTitle = L"불러오기";					// 대화상자 제목
	ofn.nMaxFile = 255;									// 파일 이름 최대 크기
	ofn.lpstrInitialDir = tempFolder.c_str();			// 기본 폴더 경로
	ofn.Flags = OFN_NOCHANGEDIR;						// 대화 상자 옵션

	if (GetOpenFileName(&ofn) == TRUE)					// 대화 상자 열고 사용자가 파일을 선택하면
	{
		if (callback != NULL)							// 콜백 함수가 존재 한다면
		{
			wstring loadName = name;					// 선택된 파일의 경로를 저장
			String::Replace(&loadName, L"\\", L"/");	// 경로에서 역슬래시를 슬래시로 변환

			callback(loadName);							// 콜백 함수 호출 

		}


	}
}

void Path::SaveFileDialog(wstring defaultFileName, const WCHAR* fileTypeFilter, const wstring defaultFolder, const function<void(wstring)> callback, HWND parentWindowHandle)
{
	WCHAR name[255];
	wcscpy_s(name, defaultFileName.c_str());

	wstring tempFolder = defaultFolder;

	OPENFILENAME ofn;
	Zero(ofn);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parentWindowHandle;					// 부모창 핸들
	ofn.lpstrFilter = fileTypeFilter;					// 파일 유형 필터
	ofn.lpstrFile = name;								// 파일 이름
	ofn.lpstrFileTitle = L"저장하기";					// 대화상자 제목
	ofn.nMaxFile = 255;									// 파일 이름 최대 크기
	ofn.lpstrInitialDir = tempFolder.c_str();			// 기본 폴더 경로
	ofn.Flags = OFN_NOCHANGEDIR;						// 대화 상자 옵션

	if (GetOpenFileName(&ofn) == TRUE)					// 대화 상자 열고 사용자가 파일을 선택하면
	{
		if (callback != NULL)							// 콜백 함수가 존재 한다면
		{
			wstring saveName = name;					// 선택된 파일의 경로를 저장
			String::Replace(&saveName, L"\\", L"/");	// 경로에서 역슬래시를 슬래시로 변환

			callback(saveName);							// 콜백 함수 호출 

		}


	}
}
// 지정된 폴더에서 특정 유형의 파일들을 찾아 반환하는 함수
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);


	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData); // 첫 번째 파일을 검색
	if (handle != INVALID_HANDLE_VALUE) //  파일이 발견 되면
	{
		do
		{
			// 발견된 파일이 디렉토리(폴더)일 경우
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				// 하위 폴더 검색 옵션 활성화 && 발견된 폴더가 '.'으로 시작하지 않는 경우
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					// 발견된 폴더의 전체 경로 설정
					wstring folder = path + wstring(findData.cFileName) + L"/";
					// 재귀적으로 하위 폴더에서 파일을 검색
					GetFiles(files, folder, filter, bFindSubFolder);
				}

			}
			else // 발견된 파일이 디렉토리가 아닌 경우
			{
				// 발견된 파일의 전체 경로 생성
				wstring fileName = path + wstring(findData.cFileName);
				// 벡터에 발견된 파일의 전체 경로 추가
				files->push_back(fileName);
			}

		} while (FindNextFile(handle, &findData)); // 다음 파일 검색
		// 파일 검색 종료
		FindClose(handle);
	}
}

// 주어진 경로에 폴더가 존재하지 않는 경우 생성하는 함수
void Path::CreateFolder(string path)
{
	CreateFolder(String::ToWString(path));
}

void Path::CreateFolder(wstring path)
{
	if (ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), NULL);
}

void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWString(path));
}

void Path::CreateFolders(wstring path)
{
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(&folders, path, L"/");

	wstring temp = L"";

	for (wstring folder : folders)
	{
		temp += folder + L"/";
		CreateFolder(temp);
	}
}
