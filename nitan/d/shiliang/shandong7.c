// Feb. 6, 1999 by Winder
inherit ROOM;
int do_use(string arg);
int do_zuan(string arg);
void create()
{
        set("short", "山洞盡頭");
        set("long", @LONG
你繼續往裏面走去，這裏越發地黑起來，伸手不見五指，許
多蝙蝠在你耳邊不停地怪笑，真令人毛骨悚然，你茫然不知道如
何是好。這裏已經山洞盡頭了，無路可走。
LONG
        );
        set("exits", ([
                "north" : __DIR__"shandong6",
        ]));
        set("coor/x", 1600);
        set("coor/y", -1970);
        set("coor/z", 20);
        setup();
}
void init()
{
        add_action("do_use", "use");
        add_action("do_zuan", "zuan");
}
int do_use(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(
             "你點燃了火折，發現山洞右邊有一道裂縫，似乎可以鑽(zuan)出去。\n"
             );
             set_temp("marks/鑽1", 1, this_player());
             return 1;
       }
}
int do_zuan(string arg)
{
        object me;
        me = this_player();
        if( query_temp("marks/鑽1", me)){
            message("vision", me->name() + "突然一腳踩空，身體直往下墜！\n",
                    environment(me), ({me}) );
            me->move(__DIR__"midao");
            me->unconcious();
            message("vision", me->name() + "從山洞裏掉了下來。\n",
                    environment(me), ({me}) );
            delete_temp("marks/鑽1", this_player());
            return 1;
        }
        else {
            write("你想往哪兒鑽?!\n");
            return 1;
        }
}