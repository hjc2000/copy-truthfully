#include "CLI/CLI.hpp"
#include <iostream>
#include <string>

namespace
{
	class Parser
	{
	private:
		std::string _src_path{};
		std::string _dst_path{};

	public:
		Parser(int argc, char **argv)
		{
			CLI::App app{"如实地拷贝目录或文件。对于目录，会递归拷贝，其中的符号链接会仍然保持为符号链接。"};

			{
				CLI::Option *src_path_option = app.add_option("--src",
															  _src_path,
															  "源路径");

				src_path_option->required();
			}

			{
				CLI::Option *dst_path_option = app.add_option("--dst",
															  _dst_path,
															  "目标路径");

				dst_path_option->required();
			}

			app.parse(argc, argv);
		}

		std::string const &SrcPath() const
		{
			return _src_path;
		}

		std::string const &DstPath() const
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

	return 0;
}
