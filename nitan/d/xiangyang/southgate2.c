// Room: /d/xiangyang/southgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "朱雀外門");
        set("long", @LONG
這裏是襄陽城的南城門，只見城門上方刻着『朱雀門』三個大字。
城門高三丈，寬約二丈有餘，尺許厚的城門上鑲滿了拳頭般大小的柳
釘。門洞長約四丈，大約每隔兩個時辰就換官兵把守。近年來蒙古屢
次侵犯襄陽城，故這兒把守相當嚴密，城內一些官兵們正在盤查要離
襄陽城的人。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"   : __DIR__"caodi4",
                "west"   : __DIR__"caodi5",
                "south"  : __DIR__"caodi6",
                "north"  : __DIR__"southgate1",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7820);
	set("coor/y", -820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}