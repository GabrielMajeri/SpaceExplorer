project('Space Explorer', 'cpp')

sfml_dep = dependency('sfml-all')
incdir = include_directories('Include')

sources = [
    'Source/Main.cpp',
    'Source/Game.cpp',
    'Source/Gameplay/Entity.cpp',
    'Source/Gameplay/Galaxy.cpp',
    'Source/Gameplay/Orbiter.cpp',
    'Source/Gameplay/Spaceship.cpp',
    'Source/Gameplay/System.cpp',
    'Source/Graphics/AnimatedSphere.cpp',
    'Source/Graphics/AnimatedSprite.cpp',
    'Source/Graphics/Starfield.cpp',
    'Source/State/Paused.cpp',
    'Source/State/Running.cpp',
    'Source/State/State.cpp',
    'Source/State/StateManager.cpp',
    'Source/State/TitleScreen.cpp',
    'Source/Utility/OptionsManager.cpp',
    'Source/Utility/Parser.cpp',
    'Source/Utility/Tools.cpp',
]

executable('SpaceExplorer', sources, dependencies : [sfml_dep], include_directories : incdir)
