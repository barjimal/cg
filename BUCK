
cxx_binary(
    name = "cg",
    srcs = [
		"src/canvas.cpp",
        "src/main.cpp",
        "src/scene.cpp",
        "src/trace_ray.cpp",
    ],
	headers = [
  		"src/canvas.hpp",
        "src/color.hpp",
        "src/common.hpp",
        "src/scene.hpp",
        "src/scene_object.hpp",
        "src/sphere.hpp",
        "src/trace_ray.hpp",
        "src/viewport.hpp",
        "src/scene_light.hpp",
    ],
    deps = [
        "//lib/boost_1_78_0:boost",
        "//lib/libbmp:libbmp",
    ],
    preprocessor_flags = [
        "-std=c++17",
    ]
)
