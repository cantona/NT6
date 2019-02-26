//eting.c                四川唐門—東偏廳

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "東偏廳");
        set("long",
"這裏是蓮雲閣東側的偏廳。一些唐門弟子喜歡到這裏海闊天空，聚首\n"
"閒談。廳內擺設了器具桌椅，廳外溪流潺潺，草木葱葱。一陣夾帶着泥土\n"
"氣息的涼風飄進來，你感到精神為之一爽。\n"
);
        set("exits", ([
             "west" : __DIR__"lianyunge",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangque" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}