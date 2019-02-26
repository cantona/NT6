// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
        set("short", "仙人洞");
        set("long", @LONG
這個洞高七尺，裏面光線暗淡，你看不清是否洞裏有任何器物，
只有洞口堆着半尺來高的山羊糞。
LONG );
        set("exits", ([
                "down" : "/d/xingxiu/xrdong",
        ]));
        set("cost", 2);
        
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

"你點燃了火折，發現西面石壁上有一道裂縫，似乎可以鑽(zuan)出去。\n");
        set_temp("marks/鑽", 1, this_player());
             return 1;
       }
}

int do_zuan(string arg)
{
        object me = this_player();
        
        if( query_temp("marks/鑽", me)){

        message("vision", me->name() +
"滋溜一下不知從什麼地方鑽出去了。\n",
                    environment(me), ({me}) );
            me->move("/d/xingxiu/icecave1");
            message("vision", me->name() + "從石縫裏鑽了出來。\n",
                    environment(me), ({me}) );
            delete_temp("marks/鑽", this_player());
        return 1;
        }
        else {
            write("你想往哪兒鑽?!\n");
            return 1;
        }
}
