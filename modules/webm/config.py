def can_build(env, platform):
<<<<<<< HEAD
    return platform not in ["iphone"]
=======
    if platform in ["iphone"]:
        return False

    return env.module_check_dependencies("webm", ["ogg", "opus", "vorbis"])
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45


def configure(env):
    pass


def get_doc_classes():
    return [
        "VideoStreamWebm",
    ]


def get_doc_path():
    return "doc_classes"
