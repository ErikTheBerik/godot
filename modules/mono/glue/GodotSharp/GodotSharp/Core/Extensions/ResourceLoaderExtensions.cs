namespace Godot
{
    public static partial class ResourceLoader
    {
<<<<<<< HEAD
        public static T Load<T>(string path, string typeHint = null, bool noCache = false) where T : class
=======
        public static T Load<T>(string path, string typeHint = null, CacheMode noCache = CacheMode.Reuse) where T : class
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
        {
            return (T)(object)Load(path, typeHint, noCache);
        }
    }
}
