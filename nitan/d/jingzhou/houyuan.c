// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "衙門後院");
        set("long", @LONG
這裡是衙門的後院，打掃得非常幹凈，四周是過人的圍牆，院子
裡種了不少的各種奇花異草，尤以各色菊花為多。院西是丫鬟的房間，
東側有一扇門(men)。
LONG );
        set("region", "jingzhou");
        set("item_desc", ([
                "men" : "這扇門後便是凌小姐的閨房。\n",
        ]));

        set("exits", ([ /* sizeof() == 2 */
                "west"  : __DIR__"xixiang",
                "north" : __DIR__"ymzhengting",
                "east"  : __DIR__"dongxiang",
                "south" : __DIR__"huayuan",
        ]));

        set("objects", ([
                __DIR__"npc/guanjia" : 1,
        ]));

        set("no_clean_up", 0);

        set("coor/x", -7110);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        // replace_program(ROOM);
}

void init()
{
        add_action("do_unlock", "unlock");
        if (present("guan jia", environment(this_player())))
                delete("exits/east");
}

int do_unlock(string arg)
{
        object ob;
        if (query("exits/east"))
                return notify_fail("這扇門已經是打開的。\n");
        if (!arg || (arg != "men" && arg != "east"))
                return notify_fail("你要打開什麼？\n");
        if (!(ob = present("guifang key", this_player())))
                return notify_fail("你不會撬鎖。\n");
        set("exits/east", __DIR__"dongxiang");
        message_vision("$N用一把鑰匙打開房門，可是鑰匙卻斷了。\n", this_player());
        destruct(ob);
        return 1;
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("guan jia", environment(me))) &&
                (dir == "west" || dir =="east"))
                return notify_fail("管家擋住了你：請勿入內宅。\n");
        return ::valid_leave(me, dir);
}