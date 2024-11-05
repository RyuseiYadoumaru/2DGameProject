#pragma once
#include "../Typedef/Typedef.h"


/**
 * �f�[�^�̌`��.
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
		 * �t�@�C�����p�X����t�@�C���p�X���擾����
		 * ��������false�ɂ��邱�ƂŊg���q���폜���邱�Ƃ��\.
		 */
		static string GetFileName(string_view filePath, bool isExt = true) noexcept;

		/**
		 * �t�@�C���g���q�擾.
		 */
		static string GetFileExt(string_view filePath) noexcept;

		/**
		 * �t�H���_���t�@�C������Ԃ�.
		 */
		static data::Type JudgeFolderOrFile(string_view dataName) noexcept;


		/**
		 * �t�H���_����g���q��T�����A�S�Ẵt�@�C���p�X�����X�g�ɂ��ĕԂ�.
		 */
		static vector<string> GetAllFileFromFolder(string_view folderPath, string_view extName);

		/**
		 * �t�@�C�������݂���f�B���N�g����Ԃ�.
		*/
		static string GetDirectryPathFromFilePath(string_view filePath);

	private:
		constexpr static char m_slash = '/';
		constexpr static char m_dot = '.';

	};
}