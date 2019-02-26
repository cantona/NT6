//houroad1.c                四川唐門—青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"這裏是後宅西側的青石小路。隱隱的可以聽到遠處傳來清脆的流水聲\n"
"，展目望去已經可以看見在風中搖擺的片片荷葉。一陣清風吹過帶來一股\n"
"荷花清香。\n"
);
        set("exits", ([
                        "west" : __DIR__"houroad2",
                        "south" : __DIR__"nzlangw1",
                        "north" : __DIR__"yaotian2",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 1,
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if ( ( (dir == "north") || (dir == "west") )&& 
                (query("family/family_name", me) != "唐門世家") && 
                !wizardp(me) && (objectp( present("jia ding", environment(me)) ) ))
                return notify_fail("家丁一伸手，説道：“你不是唐門中人，不能再向前走了！”\n");

        if ( ((dir == "north") || (dir == "west")) && !wizardp(me) && 
                (objectp( present("jia ding", environment(me)) ) ) && 
                !query_temp("tangmen", me) )
                return notify_fail("家丁一恭身，説道：“沒有任務你是不能進入這裏的！”\n");

        if ( (dir == "north") && !wizardp(me) && 
                (objectp( present("jia ding", environment(me)) ) ) && 
                !query_temp("yao", me) )
                return notify_fail("家丁一恭身，説道：“沒有任務你是不能進入藥圃的！”\n");

                return ::valid_leave(me, dir);
}