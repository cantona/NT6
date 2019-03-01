//wting.c                四川唐門─西偏廳

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西偏廳");
        set("long",
"這裡是蓮雲閣西側的偏廳。一些唐門弟子喜歡到這裡海闊天空，聚首\n"
"閒談。廳內擺設了器具桌椅，廳外溪流潺潺，草木蔥蔥。聽說，唐門最漂\n"
"亮的那位女弟子，常在這裡徘徊，默默地思念他那遠方的情郎。\n"
);
        set("exits", ([
                "east" : __DIR__"lianyunge",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangfang" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}