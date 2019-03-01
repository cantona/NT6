// Room: /d/mingjiao/tomen1.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "青石階");
        set("long", @LONG
石級到這裡似乎變得寬闊了些。清新的山風撲面而來，令人精神
頓為一爽。遠處傳來淙淙水聲，漸行漸遠。山壁上掛滿了厚密的籐蘿，
隨風輕輕搖弋。
LONG );
    set("exits", ([
        "west" : __DIR__"shanmen",
        "east" : __DIR__"tomen2",
    ]));

    set("objects", ([
        __DIR__"npc/xiaofan" : 1,
    ]));

    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}
