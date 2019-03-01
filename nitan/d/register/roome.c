// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
        set("short", "桃源竹屋");
        set("long", @LONG
這裡是一間小竹屋，樸素異常，屋中立著一位氣宇軒昂的大漢，正
滿懷笑意的看著你。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/lu" : 1,
        ]));
        set("exits", ([
                "west"  : __DIR__"entry",
                "out"   : __DIR__"yanluodian",
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("lu tianshu", this_object())))
        {
                ob = new(__DIR__"npc/lu");
                ob->move(this_object());
        }

        ob->check_leave(me, dir);
        return ::valid_leave(me, dir);
}