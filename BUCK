
cxx_binary(
    name = "cg",
    srcs = [
        "src/main.cpp",
				"src/canvas.cpp",
    ],
		headers = [
  			"src/canvas.hpp",
    ],
    deps = [
        "//lib/libbmp:libbmp",
        "//lib/boost_1_78_0:boost",
    ],
    preprocessor_flags = [
        "-std=c++14"
    ]
)
