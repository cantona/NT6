#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這是一家價錢低廉的客棧，生意很是清淡。外地遊客偶爾選擇這
裏落腳，你在這裏住可要小心，聽説荊州有黑店。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五十兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"majiu",
                "west" : __DIR__"beidajie1",
                "up" : __DIR__"kedian2",
        ]));
        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail(CYN "店小二一下擋在樓梯前，白眼一"
                                   "翻：怎麼着，想白住啊！\n" NOR);

        return ::valid_leave(me, dir);
}