// Room: /d/xiangyang/westgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "白虎外門");
        set("long", @LONG
這裡是襄陽城的西城門，只見城門上方刻著『白虎門』三個大字。
城門高三丈，寬約二丈有余，尺許厚的城門上鑲滿了拳頭般大小的柳
釘。門洞長約四丈，大約每隔兩個時辰就換官兵把守。近年來蒙古屢
次侵犯襄陽城，故這兒把守相當嚴密，城內一些官兵們正在盤查要離
襄陽城的人。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"  : __DIR__"westgate1",
                "west"  : "/d/city2/yidao1",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7870);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

int valid_leave(object me,string dir)
{
       if( dir == "west" && !userp(me) 
            && !query_temp("warquest", me) )
                return notify_fail("軍營重地，閒雜人等，不得入內！\n");

       return ::valid_leave(me,dir);
}