#include "Framework.h"
#include "Path.h"


// ���� ���� ���� Ȯ��
bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path));
}

bool Path::ExistFile(wstring path)
{
	// �����̳� ������ �Ӽ��� �˾ƿ��� �Լ�
	// �����ϸ� INVALID_FILE_ATTRIBUTES �� ��ȯ

	DWORD fileValue = GetFileAttributes(path.c_str());

	return fileValue != INVALID_FILE_ATTRIBUTES;
}
// ������ ���� ���� Ȯ��
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

// �Էµ� ��ο��� ���� �̸��� ��ȯ
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
// ������ Ȯ���ڸ� ��ȯ
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

// ���� �̸��� Ȯ���ڸ� ��ȯ
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

// ���� �̸��� ��ȯ �����ִ� �Լ�
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

// Ư�� Ȯ���� ������ ����
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
	ofn.hwndOwner = parentWindowHandle;					// �θ�â �ڵ�
	ofn.lpstrFilter = fileTypeFilter;					// ���� ���� ����
	ofn.lpstrFile = name;								// ���� �̸�
	ofn.lpstrFileTitle = L"�ҷ�����";					// ��ȭ���� ����
	ofn.nMaxFile = 255;									// ���� �̸� �ִ� ũ��
	ofn.lpstrInitialDir = tempFolder.c_str();			// �⺻ ���� ���
	ofn.Flags = OFN_NOCHANGEDIR;						// ��ȭ ���� �ɼ�

	if (GetOpenFileName(&ofn) == TRUE)					// ��ȭ ���� ���� ����ڰ� ������ �����ϸ�
	{
		if (callback != NULL)							// �ݹ� �Լ��� ���� �Ѵٸ�
		{
			wstring loadName = name;					// ���õ� ������ ��θ� ����
			String::Replace(&loadName, L"\\", L"/");	// ��ο��� �������ø� �����÷� ��ȯ

			callback(loadName);							// �ݹ� �Լ� ȣ�� 

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
	ofn.hwndOwner = parentWindowHandle;					// �θ�â �ڵ�
	ofn.lpstrFilter = fileTypeFilter;					// ���� ���� ����
	ofn.lpstrFile = name;								// ���� �̸�
	ofn.lpstrFileTitle = L"�����ϱ�";					// ��ȭ���� ����
	ofn.nMaxFile = 255;									// ���� �̸� �ִ� ũ��
	ofn.lpstrInitialDir = tempFolder.c_str();			// �⺻ ���� ���
	ofn.Flags = OFN_NOCHANGEDIR;						// ��ȭ ���� �ɼ�

	if (GetOpenFileName(&ofn) == TRUE)					// ��ȭ ���� ���� ����ڰ� ������ �����ϸ�
	{
		if (callback != NULL)							// �ݹ� �Լ��� ���� �Ѵٸ�
		{
			wstring saveName = name;					// ���õ� ������ ��θ� ����
			String::Replace(&saveName, L"\\", L"/");	// ��ο��� �������ø� �����÷� ��ȯ

			callback(saveName);							// �ݹ� �Լ� ȣ�� 

		}


	}
}
// ������ �������� Ư�� ������ ���ϵ��� ã�� ��ȯ�ϴ� �Լ�
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
	HANDLE handle = FindFirstFile(file.c_str(), &findData); // ù ��° ������ �˻�
	if (handle != INVALID_HANDLE_VALUE) //  ������ �߰� �Ǹ�
	{
		do
		{
			// �߰ߵ� ������ ���丮(����)�� ���
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				// ���� ���� �˻� �ɼ� Ȱ��ȭ && �߰ߵ� ������ '.'���� �������� �ʴ� ���
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					// �߰ߵ� ������ ��ü ��� ����
					wstring folder = path + wstring(findData.cFileName) + L"/";
					// ��������� ���� �������� ������ �˻�
					GetFiles(files, folder, filter, bFindSubFolder);
				}

			}
			else // �߰ߵ� ������ ���丮�� �ƴ� ���
			{
				// �߰ߵ� ������ ��ü ��� ����
				wstring fileName = path + wstring(findData.cFileName);
				// ���Ϳ� �߰ߵ� ������ ��ü ��� �߰�
				files->push_back(fileName);
			}

		} while (FindNextFile(handle, &findData)); // ���� ���� �˻�
		// ���� �˻� ����
		FindClose(handle);
	}
}

// �־��� ��ο� ������ �������� �ʴ� ��� �����ϴ� �Լ�
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
