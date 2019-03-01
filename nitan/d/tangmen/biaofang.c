//biaofang.c                四川唐門─鏢房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗器房");
        set("long",
"這裡是唐門的暗器房。一踏進屋門便感到一股熱浪迎面撲來，屋子正\n"
"中的幾個巨大風箱格外奪目，幾個漢子正賣力的拉動著，將火燄激起丈于\n"
"高，唐門的制鏢高手唐鏢正在全神貫注的打造著什麼。\n"
);
        set("exits", ([
                        "southeast" : __DIR__"houroad3",
        ]));
        set("objects", ([
                __DIR__"npc/tangbiao" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}