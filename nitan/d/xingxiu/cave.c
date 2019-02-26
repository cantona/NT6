// Room: /d/xingxiu/cave.c
// Last Modified by Winder on Apr. 25 2001

inherit ROOM;
void create()
{
        set("short", "山洞");
        set("long", @LONG
黑黝黝的山洞裏，有一股腥臭味。等眼睛適應了這裏的弱光後，才
發現地上有一條色彩斑斕的巨蟒。巨蟒旁有許多白慘慘的骨駭，令人膽
寒。想必都是探險之人，誤入山洞，為巨蟒所害。
LONG
        );
        set("exits", ([
                "out" : __DIR__"shanshi",
        ]));
        set("objects", ([
                __DIR__"npc/jumang" : 1,
                __DIR__"npc/snake" : 1,
        ]));
        set("coor/x", -50400);
        set("coor/y", 20400);
        set("coor/z", 200);
        setup();
}
void init()
{
        add_action("do_use", "use");
        add_action("do_zuan", "zuan");
}

int do_use(string arg)
{
        object me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if(arg=="fire")
        {
                write("你點燃了火折，發現西面石壁上有一道裂縫，似乎可以鑽(zuan)出去。\n");
                set_temp("marks/鑽", 1, me);
                me->start_busy(2);
                return 1;
        }
}

int do_zuan(string arg)
{
        object me = this_player();

        if( query_temp("marks/鑽", me) )
        {
                message("vision", me->name() + "滋溜一下不知從什麼地方鑽出去了。\n", environment(me), ({me}) );
                me->move(__DIR__"cave2");
                message("vision", me->name() + "從石縫裏鑽了進來。\n", environment(me), ({me}) );
                set_temp("marks/鑽", 0, me);
                return 1;
        }
        else {
                write("你想往哪兒鑽?!\n");
                return 1;
        }
}
