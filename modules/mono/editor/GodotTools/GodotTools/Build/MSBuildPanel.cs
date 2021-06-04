using System;
using Godot;
using GodotTools.Internals;
using JetBrains.Annotations;
using static GodotTools.Internals.Globals;
using File = GodotTools.Utils.File;

namespace GodotTools.Build
{
    public class MSBuildPanel : VBoxContainer
    {
        public BuildOutputView BuildOutputView { get; private set; }

        private Button errorsBtn;
        private Button warningsBtn;
        private Button viewLogBtn;

        private void WarningsToggled(bool pressed)
        {
            BuildOutputView.WarningsVisible = pressed;
            BuildOutputView.UpdateIssuesList();
        }

        private void ErrorsToggled(bool pressed)
        {
            BuildOutputView.ErrorsVisible = pressed;
            BuildOutputView.UpdateIssuesList();
        }

        [UsedImplicitly]
        public void BuildSolution()
        {
            if (!File.Exists(GodotSharpDirs.ProjectSlnPath))
                return; // No solution to build

<<<<<<< HEAD
            BuildManager.GenerateEditorScriptMetadata();
=======
            try
            {
                // Make sure our packages are added to the fallback folder
                NuGetUtils.AddBundledPackagesToFallbackFolder(NuGetUtils.GodotFallbackFolderPath);
            }
            catch (Exception e)
            {
                GD.PushError("Failed to setup Godot NuGet Offline Packages: " + e.Message);
            }
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

            if (!BuildManager.BuildProjectBlocking("Debug"))
                return; // Build failed

            // Notify running game for hot-reload
<<<<<<< HEAD
            Internal.ScriptEditorDebuggerReloadScripts();
=======
            Internal.EditorDebuggerNodeReloadScripts();
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

            // Hot-reload in the editor
            GodotSharpEditor.Instance.GetNode<HotReloadAssemblyWatcher>("HotReloadAssemblyWatcher").RestartTimer();

            if (Internal.IsAssembliesReloadingNeeded())
                Internal.ReloadAssemblies(softReload: false);
        }

        [UsedImplicitly]
        private void RebuildSolution()
        {
            if (!File.Exists(GodotSharpDirs.ProjectSlnPath))
                return; // No solution to build

<<<<<<< HEAD
            BuildManager.GenerateEditorScriptMetadata();
=======
            try
            {
                // Make sure our packages are added to the fallback folder
                NuGetUtils.AddBundledPackagesToFallbackFolder(NuGetUtils.GodotFallbackFolderPath);
            }
            catch (Exception e)
            {
                GD.PushError("Failed to setup Godot NuGet Offline Packages: " + e.Message);
            }
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

            if (!BuildManager.BuildProjectBlocking("Debug", targets: new[] {"Rebuild"}))
                return; // Build failed

            // Notify running game for hot-reload
<<<<<<< HEAD
            Internal.ScriptEditorDebuggerReloadScripts();
=======
            Internal.EditorDebuggerNodeReloadScripts();
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

            // Hot-reload in the editor
            GodotSharpEditor.Instance.GetNode<HotReloadAssemblyWatcher>("HotReloadAssemblyWatcher").RestartTimer();

            if (Internal.IsAssembliesReloadingNeeded())
                Internal.ReloadAssemblies(softReload: false);
        }

        [UsedImplicitly]
        private void CleanSolution()
        {
            if (!File.Exists(GodotSharpDirs.ProjectSlnPath))
                return; // No solution to build

            BuildManager.BuildProjectBlocking("Debug", targets: new[] {"Clean"});
        }

        private void ViewLogToggled(bool pressed) => BuildOutputView.LogVisible = pressed;

<<<<<<< HEAD
        private void BuildMenuOptionPressed(BuildMenuOptions id)
        {
            switch (id)
=======
        private void BuildMenuOptionPressed(int id)
        {
            switch ((BuildMenuOptions)id)
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
            {
                case BuildMenuOptions.BuildSolution:
                    BuildSolution();
                    break;
                case BuildMenuOptions.RebuildSolution:
                    RebuildSolution();
                    break;
                case BuildMenuOptions.CleanSolution:
                    CleanSolution();
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(id), id, "Invalid build menu option");
            }
        }

        private enum BuildMenuOptions
        {
            BuildSolution,
            RebuildSolution,
            CleanSolution
        }

        public override void _Ready()
        {
            base._Ready();

            RectMinSize = new Vector2(0, 228) * EditorScale;
            SizeFlagsVertical = (int)SizeFlags.ExpandFill;

            var toolBarHBox = new HBoxContainer {SizeFlagsHorizontal = (int)SizeFlags.ExpandFill};
            AddChild(toolBarHBox);

<<<<<<< HEAD
            var buildMenuBtn = new MenuButton {Text = "Build", Icon = GetIcon("Play", "EditorIcons")};
=======
            var buildMenuBtn = new MenuButton {Text = "Build", Icon = GetThemeIcon("Play", "EditorIcons")};
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
            toolBarHBox.AddChild(buildMenuBtn);

            var buildMenu = buildMenuBtn.GetPopup();
            buildMenu.AddItem("Build Solution".TTR(), (int)BuildMenuOptions.BuildSolution);
            buildMenu.AddItem("Rebuild Solution".TTR(), (int)BuildMenuOptions.RebuildSolution);
            buildMenu.AddItem("Clean Solution".TTR(), (int)BuildMenuOptions.CleanSolution);
<<<<<<< HEAD
            buildMenu.Connect("id_pressed", this, nameof(BuildMenuOptionPressed));
=======
            buildMenu.IdPressed += BuildMenuOptionPressed;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

            errorsBtn = new Button
            {
                HintTooltip = "Show Errors".TTR(),
<<<<<<< HEAD
                Icon = GetIcon("StatusError", "EditorIcons"),
=======
                Icon = GetThemeIcon("StatusError", "EditorIcons"),
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
                ExpandIcon = false,
                ToggleMode = true,
                Pressed = true,
                FocusMode = FocusModeEnum.None
            };
<<<<<<< HEAD
            errorsBtn.Connect("toggled", this, nameof(ErrorsToggled));
=======
            errorsBtn.Toggled += ErrorsToggled;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
            toolBarHBox.AddChild(errorsBtn);

            warningsBtn = new Button
            {
                HintTooltip = "Show Warnings".TTR(),
<<<<<<< HEAD
                Icon = GetIcon("NodeWarning", "EditorIcons"),
=======
                Icon = GetThemeIcon("NodeWarning", "EditorIcons"),
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
                ExpandIcon = false,
                ToggleMode = true,
                Pressed = true,
                FocusMode = FocusModeEnum.None
            };
<<<<<<< HEAD
            warningsBtn.Connect("toggled", this, nameof(WarningsToggled));
=======
            warningsBtn.Toggled += WarningsToggled;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
            toolBarHBox.AddChild(warningsBtn);

            viewLogBtn = new Button
            {
                Text = "Show Output".TTR(),
                ToggleMode = true,
                Pressed = true,
                FocusMode = FocusModeEnum.None
            };
<<<<<<< HEAD
            viewLogBtn.Connect("toggled", this, nameof(ViewLogToggled));
=======
            viewLogBtn.Toggled += ViewLogToggled;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
            toolBarHBox.AddChild(viewLogBtn);

            BuildOutputView = new BuildOutputView();
            AddChild(BuildOutputView);
        }
    }
}
