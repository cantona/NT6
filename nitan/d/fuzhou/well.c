// room: well.c

inherit ROOM;

int do_use(string arg);
int do_zuan(string arg);

void create()
{
        set("short", "井中");
        set("long", @LONG
這是在一口枯井中。光線極暗，什麼也看不清。
LONG );
        set("exits", ([
                "up" : __DIR__"houyuan",
                "down" : __DIR__"well1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6310);
        set("coor/z", -10);
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
             "你點燃了火折，發現井壁上有一道裂縫，似乎可以鑽(zuan)出去。\n"
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
            message("vision", me->name() + "滋溜一下不見了。\n",
                    environment(me), ({me}) );
            me->move(__DIR__"midao");
            message("vision", me->name() + "從井裡鑽了出來。\n",
                    environment(me), ({me}) );
            delete_temp("marks/鑽1", this_player());

            return 1;
        }
        else {
            write("你想往哪兒鑽?!\n");
            return 1;
        }
}