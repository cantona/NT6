// Room: /lingzhou/yipingate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "一品堂大門");
        set("long", @LONG
這裏是西夏一品堂的所在地，座落在西大街的北面，是一座高大的
石頭建築，看上去堅固之極。門口有兩個武士站着，既不高大也不彪悍，
和皇宮門口的守衞差遠啦，就是和衙門口的衙役比也頗有不如，但從他
們陰鷲的眼神裏你不難看出他們是身懷絕技的高手，誰不知西夏一品堂
廣招天下高手為皇上效命。
LONG );
        set("exits", ([
                "north"  : __DIR__"yipindayuan",
                "south"  : __DIR__"xidajie",
        ]));
        set("objects", ([
                __DIR__"npc/yipinwushi" : 2,
        ]));
        set("coor/x", -6295);
        set("coor/y", 2945);
        set("coor/z", 0);
        setup();
        create_door("north" , "銅皮大門", "south" , DOOR_CLOSED);
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && 
            !query("yipin/joined", me) && 
            objectp(present("wu shi", environment(me))))
           return notify_fail("一品堂武士攔住你的去路。\n");

        return ::valid_leave(me, dir);
}