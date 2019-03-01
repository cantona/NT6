// Room: /d/guiyun/rivere.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

int do_jump(string arg);

void create()
{
        set("short", "小河東岸");
        set("long", @LONG
這裡是一條小河之濱，四下都是亂墳。往周圍看去，並無橋樑可以
過河(he)。
LONG );
        set("exits", ([
                "east" : __DIR__"road1",
        ]));
        set("item_desc", ([
                "river" : "小河很寬，河水下面隱隱約約有什麼東西。你看不清。\n",
                "he"    : "小河很寬，河水下面隱隱約約有什麼東西。你看不清。\n",
        ]) );

          set("outdoors", "guiyun");
        set("coor/x", 320);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
}

void init()
{
        if (!present("old man", this_object()))
                new(__DIR__"npc/qianzhang")->move(this_object());
        add_action("do_jump", "jump");
        add_action("do_jump", "yue");
}

int do_jump(string arg)
{
        object me = this_player();

        if (arg == "river" || arg == "he")
        {
                if( query_temp("guiyun_river", me) )
                {
                        message("vision", me->name() + "飛身躍在水面，身形穩凝，河水只及小腿，一步步走過了河。\n", environment(me), ({me}) );
                        write("你踩著水底的暗樁，慢慢的走過了小河。\n");
                        me->move(__DIR__"riverw");
                        message("vision", "只見河面上人影閃動，" + me->name() +  "如飄在水面一般，直走過來。\n", environment(me), ({me}) );
                        write("你踩著暗樁慢慢地走過了小河。\n");
                        delete_temp("guiyun_river", me);
                        return 1;
                }
                else {
                        write("你試了試，發覺河面很寬，你絕對跳不過去。\n");
                        return 1;
                }
        }
        return 0;
}