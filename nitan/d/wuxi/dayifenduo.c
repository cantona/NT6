// Room: /d/wuxi/dayifenduo.c
// Last Modifyed by Winder on Dec. 4 2001
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大義分舵");
        set("long", @LONG
這裏是杏子林中的丐幫大義分舵。分舵羣丐分坐草地上，次序和職
司前後井然。林子邊有一個大草堆(dui) ，看似十分平常，可是你總覺
得有點奇怪。
LONG );
        set("item_desc", ([
                "dui"  : "你仔細一看，發現祕密了：呵呵，草堆下面有個黑乎乎的大洞口！\n",
        ]));
        set("exits", ([
                "south" : __DIR__"xinlin1",
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/jiang" : 1,
                CLASS_D("gaibang") + "/bangzhong" : random(5),
        ]));
        set("coor/x", 1070);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="dui" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision",
                                me->name() + "運起丐幫縮骨功，一彎腰往草堆下的洞裏鑽了進去。\n",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/underwx");
                        message("vision", me->name() + "從洞裏走了進來。\n", environment(me), ({me}) );
                        return 1;
                }
                else 
                        return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}        