
cxx_binary(
    name = "cg",
    srcs = [
		"src/canvas.cpp",
        "src/main.cpp",
        "src/trace_ray.cpp",
    ],
	headers = [
  		"src/canvas.hpp",
        "src/color.hpp",
        "src/common.hpp",
        "src/scene_object.hpp",
        "src/sphere.hpp",
        "src/viewport.hpp",
        "src/trace_ray.cpp",
    ],
    deps = [
        "//lib/boost_1_78_0:boost",
        "//lib/libbmp:libbmp",
    ],
    preprocessor_flags = [
        "-std=c++17",
    ]
)
