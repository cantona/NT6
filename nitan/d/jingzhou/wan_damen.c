// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "大門");
        set ("long", @LONG
走到這裡，一座富麗堂皇的大宅院出現在你的眼前，兩頭高大的
石獅子鎮住了大門兩側，朱漆大門足足有三寸厚。門上掛著兩個燈籠，
寫著「荊州萬府」四個金漆大字。只見兩個衣衫華麗的青年站在大門
兩側，警惕地注視著行人。
LONG);
        set("outdoors", "jingzhou");
        set("region", "jingzhou");
        set("exits", ([
                "north"  : __DIR__"wan_dating",
                "south"  : __DIR__"xidajie1",
        ]));

        set("objects", ([
                "/d/shaolin/npc/shang2" : 2,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( dir == "north" &&
           objectp(present("jia ding", environment(me))) )
                return notify_fail(CYN "家丁攔住你罵道：什麼東西，居然連萬"
                                   "老爺的府邸都敢亂闖！\n" NOR);
        return ::valid_leave(me, dir);
}