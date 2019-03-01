// Room: /d/huanggong/qianqingmen.c
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "乾清門");
        set("long", @LONG
這是皇宮後廷的正門. 門中有一個寶座, 有些時候, 皇上為表示親
政, 就在這聽取各衙門主管依次奏事, 這叫御門聽政.
LONG
        );
        set("outdoors", "huanggong");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"rijing",
                "west"      : __DIR__"yuehua",
                "south"     : __DIR__"baohedian",
                "north"     : __DIR__"qianqinggong",
                "northeast" : __DIR__"jiuqingfang",
                "northwest" : __DIR__"junjichu",
                "southeast" : __DIR__"jingyunmen",
                "southwest" : __DIR__"longzongmen",
        ]));
        set("objects", ([
                __DIR__"npc/duolong" : 1,
        ]));
	set("coor/x", -2810);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if ((dir=="north") &&
        objectp(present("duo long", environment(me))))
                return notify_fail("多隆攔住你說：此處禁地，請止步。\n");

        return ::valid_leave(me, dir);
}