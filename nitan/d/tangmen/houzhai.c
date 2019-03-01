//houzhai.c                唐門世家─走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後宅");
        set("long",
"這裡是蓮雲閣後宅。從這裡向北就是唐門的代表唐老太太的寢室據聞\n"
"外人要見到唐老太太勢比登天還難，從這裡向東是一間柴房，向西是通向\n"
"後院的小路。\n"
);
        set("exits", ([
                        "north" : __DIR__"nzlang2",
                        "south" : __DIR__"dating",
                        "southwest" : __DIR__"chaifang",
        ]));
        create_door("southwest","木門","northeast",DOOR_CLOSED);
        set("objects", ([
                __DIR__"npc/tangkan" : 1,
        ]));
        set("area", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "唐門世家") )
                return notify_fail("你不是唐門中人，不能再向前走了！\n");

        return ::valid_leave(me, dir);
}