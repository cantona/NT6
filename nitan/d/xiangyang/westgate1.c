// Room: /d/xiangyang/westgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "白虎內門");
        set("long", @LONG
這裏是襄陽城的西城門的內城門，城門高三丈，寬約二丈有餘，尺許厚的城
門上鑲滿了拳頭般大小的柳釘。門洞長約四丈，大約每隔兩個時辰就換官兵把守。
洞側帖滿了懸賞捉拿之類的官府通諜。門洞西側則是一條上城牆的窄梯。近年來
蒙古屢次侵犯襄陽城，故這兒把守相當嚴密，一些官兵們正在盤查要離襄陽城的
人。兩邊是上城頭的石階，向東進入城區。
                         s________________s         
                        /LLLLLLLLLLLLLLLLLL\        
    []__[]             ^^||======||======||^^             []__[] 
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]      
    []==[]__|__|__|__|__|__|_┃白虎門┃__|__|__|__|__|__|_[]==[]   
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|__/      \|__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__||        |_|__|緝|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__┌┐┌┐_|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|└┘└┘|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|  西門  |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "southup" : __DIR__"wallw2",
                "northup" : __DIR__"wallw1",
                "east"    : __DIR__"westjie3",
                "west"    : __DIR__"westgate2",
        ]));
        set("objects", ([
                "/quest/quest5/job2/pi4"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7860);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}