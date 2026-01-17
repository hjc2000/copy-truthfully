# 编译目标
add_executable(${ProjectName})
target_import_src(${ProjectName})

target_import_base(${ProjectName} PUBLIC)
target_import_cli11(${ProjectName} PUBLIC)
target_import_base_filesystem(${ProjectName} PUBLIC)
