// Room: /d/mingjiao/mjfengmen1.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "竹林");
        set("long", @LONG
這是竹林中的一間小院，竹影依依，經聲入耳，其南北各有一間
竹舍，乃是明教中釋道和佛家弟子的修煉場所。
LONG );
    set("exits", ([
        "northwest" : __DIR__"mjfengmen",
        "north" : __DIR__"foshe",
        "south" : __DIR__"daoshe",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}
