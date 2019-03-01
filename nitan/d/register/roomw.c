// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
        set("short", "桃源石屋");
        set("long", @LONG
這裡是一間小石屋，看不出有什麼特別，屋中立著一位正氣凜然的
大漢，正盯著你看。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/hua" : 1,
        ]));
        set("exits", ([
                "east"  : __DIR__"entry",
                "out"   : __DIR__"yanluodian",
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("hua tiegan", this_object())))
        {
                ob = new(__DIR__"npc/hua");
                ob->move(this_object());
        }

        ob->check_leave(me, dir);
        return ::valid_leave(me, dir);
}