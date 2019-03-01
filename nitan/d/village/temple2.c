// Room: /d/village/temple2.c

inherit ROOM;

void create()
{
        set("short", "小棚子");
        set("long", @LONG
這是一個臨時搭起來的小棚子。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west" : __DIR__"temple1",
        ]));
        set("objects", ([
             __DIR__"npc/wang": 1,
        ]) );
        setup();
}

int valid_leave(object me, string dir)
{
        if( query_temp("marks/王", this_player()) )
                set_temp("marks/王", 0, this_player());

        return 1;
}