#include "base/filesystem/filesystem.h"
#include "base/filesystem/Path.h"
#include "CLI/CLI.hpp"
#include <iostream>
#include <string>
#include <windows.h>

namespace
{
	void create_symlink_a(std::string const &target,
						  std::string const &link_path,
						  bool is_directory)
	{
		DWORD flags = is_directory ? SYMBOLIC_LINK_FLAG_DIRECTORY : 0;
		flags |= SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;

		if (!CreateSymbolicLinkA(link_path.c_str(),
								 target.c_str(),
								 flags))
		{
			throw std::runtime_error("CreateSymbolicLinkA failed");
		}
	}

	class Parser
	{
	private:
		base::Path _src_path{};
		base::Path _dst_path{};

	public:
		Parser(int argc, char **argv)
		{
			CLI::App app{"如实地拷贝目录或文件。对于目录，会递归拷贝，其中的符号链接会仍然保持为符号链接。"};

			std::string src_path_string{};
			std::string dst_path_string{};

			{
				CLI::Option *src_path_option = app.add_option("--src",
															  src_path_string,
															  "源路径");

				src_path_option->required();
			}

			{
				CLI::Option *dst_path_option = app.add_option("--dst",
															  dst_path_string,
															  "目标路径");

				dst_path_option->required();
			}

			app.parse(argc, argv);

			_src_path = src_path_string;
			_src_path = base::filesystem::ToAbsolutePath(_src_path);

			_dst_path = dst_path_string;
			_dst_path = base::filesystem::ToAbsolutePath(_dst_path);
		}

		base::Path const &SrcPath() const
		{
			return _src_path;
		}

		base::Path const &DstPath() const
		{
			return _dst_path;
		}
	};

} // namespace

int main(int argc, char **argv)
{
	Parser parser{argc, argv};

	std::cout << "源路径：" << parser.SrcPath() << std::endl;
	std::cout << "目标路径：" << parser.DstPath() << std::endl;

	if (base::filesystem::IsSymbolicLink(parser.SrcPath()))
	{
		std::cout << "源路径是符号链接" << std::endl;
		std::cout << base::filesystem::ReadSymboliclink(parser.SrcPath()) << std::endl;
	}

	// base::filesystem::Copy(parser.SrcPath(),
	// 					   parser.DstPath(),
	// 					   base::filesystem::OverwriteOption::Overwrite);

	return 0;
}
