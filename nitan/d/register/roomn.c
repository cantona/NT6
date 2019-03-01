// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
        set("short", "桃源茅屋");
        set("long", @LONG
這裡是一間小茅屋，屋內一位大漢坦胸露乳，正大碗酒、大塊肉落
肚，看見你進來，只是略略一點頭。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/li" : 1,
        ]));
        set("exits", ([
                "south"  : __DIR__"entry",
                "out"   : __DIR__"yanluodian",
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("li zicheng", this_object())))
        {
                ob = new(__DIR__"npc/li");
                ob->move(this_object());
        }

        ob->check_leave(me, dir);
        return ::valid_leave(me, dir);
}