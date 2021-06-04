def can_build(env, platform):
    return True


def configure(env):
    pass


def get_doc_classes():
<<<<<<< HEAD
    return ["WebRTCPeerConnection", "WebRTCDataChannel", "WebRTCMultiplayer"]

=======
    return [
        "WebRTCPeerConnection",
        "WebRTCDataChannel",
        "WebRTCMultiplayer",
    ]
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45


def get_doc_path():
    return "doc_classes"
