//neiyuan.c                四川唐門─內院

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "內院");
        set("long",
"這裡是蓮雲閣內院。從這裡向北就是唐門的核心唐老太太的寢室據聞\n"
"外人要見到唐老太太勢比登天還難，從這裡向東是一間柴房，向西是通向\n"
"後院的小路。\n"
);
        set("exits", ([
                        "south" : __DIR__"nzlang1",
                        "north" : __DIR__"nzlangn1",
        ]));
        set("objects", ([
                __DIR__"npc/tangsi" : 1,
        ]));
        set("area", "tangmen");
        setup();
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "唐門世家") && 
                !wizardp(me) && (objectp( present("tang si", environment(me)) ) ))
                return notify_fail("唐思一伸手，說道：“你不是唐門中人，不能再向前走了！”\n");
        else
                return ::valid_leave(me, dir);
}