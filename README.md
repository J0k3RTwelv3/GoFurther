# GoFurther

Go further is a flexible line generation program, that can be easily extended with new level formats and line generation algorithms.

# Implementing level format support
In order to implemenet support for your desired level format, you need to create a new class, which inherits from ```LevelWriter``` class. Then implement all pure virtual functions and finally, you can pass new instance of your class to ```LevelGenerator``` constructor. ```WriteForegroundLines``` and ```WriteBackgroundLines``` are optional and you can just override them with empty function body if you don't have to write those values to the file. **REMEMBER TO ALWAYS OVERRIDE THOSE METHODS REGARDLESS TO NOT MAKE YOUR CLASS ABSTRACT**

# Implementing new line generation algorithm
Implementing new level generation algorithm follows the same principle except you need to inherit from ```LevelGenerationAlgorithm``` class. When generating lines, please use ```LineStyleFactory``` for ```LineStyle*``` struct member to optimize RAM usage.

# Other things

```ClassicLevelWriter``` is for the level file format used by the game Draw Rider v 9.4

This program will recive occasional updates in case I want to include really cool line generation algorithms or some optimizations. You can always request those in issues or pull requests and I'll take a look into it.

Yeah and that's it.
