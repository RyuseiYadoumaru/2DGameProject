#include "FileSystem.h"


string mySystem::FileSystem::GetFileName(string_view filePath, bool isExt) noexcept
{
    string fileName;
    size_t index = filePath.find_last_of(m_slash);
    size_t dotIndex = filePath.find_last_of(m_dot);

    /** 拡張子あり */
    if (isExt == true) fileName = filePath.substr(index + 1);

    /** 拡張子なし */
    else
    {
        unsigned int nameLength = dotIndex - (index + 1);
        fileName = filePath.substr(index + 1, nameLength);
    }

    return fileName;
}



string mySystem::FileSystem::GetFileExt(string_view filePath) noexcept
{
    string extName;
    size_t dotIndex = filePath.find_last_of(m_dot);

    /** 拡張子を抽出する */
    extName = filePath.substr(dotIndex + 1, filePath.size() - dotIndex);
    return extName;
}



data::Type mySystem::FileSystem::JudgeFolderOrFile(string_view dataName) noexcept
{
    size_t index = 0;
    index = dataName.find(m_dot);
    if (index != -1) return data::Type::File;
    return data::Type::Folder;
}



vector<string> mySystem::FileSystem::GetAllFileFromFolder(string_view folderPath, string_view extName)
{
    vector<string> filePathList;

    HANDLE hFind;
    WIN32_FIND_DATA win32fd;

    /** 探索用仮パス */
    string path;
    string ext;
    path = folderPath;
    ext = extName;
    string searchPath = path + "*." + ext;

    /*
     * 探索開始
     * フォルダ内にデータがない時はAssertで無理やり止める.
    */
    hFind = FindFirstFile(searchPath.c_str(), &win32fd);
    if (INVALID_HANDLE_VALUE == hFind)
    {
        cout << "Not FileData" + searchPath << endl;
    }

    /** 探索 */
    do
    {
        if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}

        else
        {
            filePathList.push_back(path + win32fd.cFileName);
        }

    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return filePathList;
}


string mySystem::FileSystem::GetDirectryPathFromFilePath(string_view filePath)
{
    string directryPath;
    /** 最後のスラッシュのインデックスを保存 */
    size_t index = filePath.find_last_of(m_slash);
    directryPath = filePath.substr(0, index + 1);
    return directryPath;
}