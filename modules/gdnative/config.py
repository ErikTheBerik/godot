def can_build(env, platform):
    return True


def configure(env):
    pass



def get_doc_classes():
    return [
<<<<<<< HEAD
        "ARVRInterfaceGDNative",
=======
        "XRInterfaceGDNative",
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
        "GDNative",
        "GDNativeLibrary",
        "MultiplayerPeerGDNative",
        "NativeScript",
        "PacketPeerGDNative",
        "PluginScript",
        "StreamPeerGDNative",
        "VideoStreamGDNative",
        "WebRTCPeerConnectionGDNative",
        "WebRTCDataChannelGDNative",
    ]


def get_doc_path():
    return "doc_classes"
