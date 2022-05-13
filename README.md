# Wurst Autobuild Json Generator
A simple GUI application to generate Wurst compatible autobuild json files.

Popular Minecraft Java Hacked Client [Wurst](https://www.wurstclient.net) introduced it's [AutoBuild](https://wiki.wurstclient.net/autobuild) feature ages ago.
And for some odd reason I always loved this feature. That's why I introduced a Wurst compatible Autobuild feature to my private Minecraft Bedrock Edition client and made this program.

## Features:
- Duplicate layers function
- Displays total blocks
- Select blocks by draging
- Adjustable grid
- responsive GUI

## Screenshot:
![Screenshot of program](https://github.com/fligger/WurstAutobuildGen/blob/master/Screenshot.png?raw=true)

## Troubleshooting:
VCRUNTIME140_1.dll not found:
1. Go to https://support.microsoft.com/en-us/help/2977003
2. Scroll down and download the x64: vc_redist.x64.exe
3. Run the exe and install it
4. Fate Injector should open now

#### This project uses wxWidgets [version 3.1.4](https://wxwidgets.org/news/2020/07/wxwidgets-3.1.4-released/).
