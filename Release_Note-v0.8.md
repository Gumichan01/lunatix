# LunatiX Engine v0.8 - Release note #

## Important changes ##

 - Text input
 - Log messages
 - Window creation
 - New namespace : LX_Win

## Details ##

> **Text Input**

*LX_TextInput* is a class that handles text input. The text input is activated
at class intantiation and unactivated at class destruction.
This class can handle Unicode string in UTF-8 thanks to
[UTF8string](https://github.com/Gumichan01/utf8_string).

The API provides a callback (*LX_RedrawCallback*) function defined as a function object.
This callback was designed to redraw the current window that displays
the user-typed text at each user input.
It is not necessary to handle text input events, because *LX_TextInput* does that properly.

So, in order to use LX_TextInput, you need to:
- Define a class as a subclass of the pure virtuel class *LX_RedrawCallback*.
- Define the operator **()** provided by *LX_RedrawCallback*.
- Declare an object of type *LX_TextInput*.
- Call the function **eventLoop** of this object giving the callback function in argument.

Example of code :

    // Define and implement a subclass of LX_RedrawCallback
    class FuncDraw : public LX_RedrawCallback
    {
    public:

        ...
        void operator ()(UTF8String& u8str)
        {
            // Do something
        }
        ...
    }

    ...

    // In a function that uses the callback
    ...
    void textInput()
    {
        FuncDraw callbck;
        LX_TextInput input;
        input.eventLoop(callbck);
    }

*LX\_TextInput* also supports clipboard handling.

> **Log messages**

The log module has a new formatted message based on the following syntax:

    <logtype>: [date] <message>

***logtype*** is one of these following words:

 - INFO
 - DEBUG
 - WARN
 - ERROR
 - CRITICAL

The date between the brackets is in ISO-8601 format ([%Y-%m-%d %H:%M:%S]).

Example of log entries:

    DEBUG:    [2016-06-25 11:19:19] Start the input.
    INFO:     [2016-06-25 11:19:20] Got new message: hello.
    DEBUG:    [2016-06-25 11:19:22] End of input.


> **Window creation**

① Constructor

A new signature of the constructor (LX_Window) has been added
in order to simplify the creation of a window.

A window can be created using *LX_WindowInfo* that defines a structure.
This structure contains information about the window that will be created by
the user.
It is possible to give default information to the strucure using one of these
following functions :

 - LX\_initWindowInfo	: it defines the default values of the window.
 - LX\_loadWindowConfig	: it defines some values from the configuration file.

② Get information about a window

Now it is possible to get information about a window.
It is also possible to get information about a window freshly created
by *LX_Window*. The constructor updates data about the window.
So the user is able to know information about it.

③ Fixed a performance issue.

The private function *create_window()* took an std::string in argument.
It was a problem because every constructors of *LX_Window*
send an std::string into this function instead of a C-style string.

So, in order to avoid a copy between the public functions and *create_window()*,
The string itself was replaced by a reference to the string in order to
avoid a useless copy and optimize the function call.


## Other changes ##

> UTF8 string

In addition with the text input, the engine can support utf-8 encoded strings.
See [UTF8string](https://github.com/Gumichan01/utf8_string).

> **Information about dependencies**

LX\_Version provides information about the dependencies of the engine.
It is possible to get the version of the engine and also the version of the different
libraries used by the engine.

> **MP3 and Flac support**

Two audio formats have been added in order to be handled by the engine.
So, these are the following audio formats that are supported:

 - OGG Vorbis
 - WAV
 - MP3
 - FLAC

> (Linux version) Makefile refactored

The Makefile has been refactored in order to use the external libraries installed in
the system. That is to say SDL2 is not provided anymore by the engine.
It should be installed in the system.

The Lua library is still provided. But the engine will not depend on the library
for the configuration loading in the next version.

## FIXES

> LX_Device::gamepadToString(): [Segmentation fault][].

[Segmentation fault]: https://github.com/Gumichan01/lunatix-engine/commit/87e069
