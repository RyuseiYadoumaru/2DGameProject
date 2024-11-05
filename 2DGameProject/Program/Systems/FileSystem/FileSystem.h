#pragma once
#include "../Typedef/Typedef.h"


/**
 * データの形式.
 */
namespace data
{
	enum class Type
	{
		File = 0,
		Folder = 1
	};
}

namespace mySystem
{
	class FileSystem
	{
	public:

		/**
		 * ファイル名パスからファイルパスを取得する
		 * 第二引数をfalseにすることで拡張子を削除することが可能.
		 */
		static string GetFileName(string_view filePath, bool isExt = true) noexcept;

		/**
		 * ファイル拡張子取得.
		 */
		static string GetFileExt(string_view filePath) noexcept;

		/**
		 * フォルダかファイルかを返す.
		 */
		static data::Type JudgeFolderOrFile(string_view dataName) noexcept;


		/**
		 * フォルダから拡張子を探索し、全てのファイルパスをリストにして返す.
		 */
		static vector<string> GetAllFileFromFolder(string_view folderPath, string_view extName);

		/**
		 * ファイルが存在するディレクトリを返す.
		*/
		static string GetDirectryPathFromFilePath(string_view filePath);

	private:
		constexpr static char m_slash = '/';
		constexpr static char m_dot = '.';

	};
}