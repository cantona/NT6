// Room: /city/zhujuan.c
// YZC 1995/12/04 

#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "豬圈");
        set("long", @LONG
這裡是一個臭烘烘的豬圈，欄上掛著一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "大家一起發呆，把泥潭變成豬的世界。\n",
        ]));
        set("exits", ([
                "up"   : "/d/city/kedian",
        ]));

        setup();
}
