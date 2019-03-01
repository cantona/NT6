// Room: /d/village/temple1.c

inherit ROOM;

void create()
{
        set("short", "玄壇廟");
        set("long", @LONG
這是一間十分破舊的小廟，廟裡供的神像是趙玄壇，神像已經很
殘破了，神案上也積了很多塵土，看來已有很久沒人來上香進供了。
大概村民貧困的太久，已不再寄望於財神爺降福給他們了。神像後面
的牆上有個半人多高的洞(hole)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "southwest" : __DIR__"nwroad1",
        ]));
        set("item_desc", ([
                "hole": "看來這個大洞被人鑿開不久，洞那邊好象有個小棚子。\n"
        ]));

        setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;

        me = this_player();

        if (! arg || arg == "") return 0;
        if (arg == "hole")
        {
                if( query_temp("marks/王", me) )
                {
                        message("vision", me->name() + "一彎腰往洞裡走了進去。\n",
                                environment(me), ({me}));
                        me->move("/d/village/temple2");
                        message("vision", me->name() + "從洞裡走了進來。\n",
                                environment(me), ({me}) );
                        return 1;
                } else
                {
                        write("你沒事那麼愛鑽洞啊?!\n");
                        return 1;
                }
        }
}        