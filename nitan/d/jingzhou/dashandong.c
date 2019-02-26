//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "大山洞");
        set("long", @LONG
這是西山上一個大山洞，裏面黑乎乎的，什麼也沒有。你睜眼仔細
觀察，發現洞中有一叢叢齊肩的長草(cao)。
LONG );
        set("exits", ([
                "out"  : __DIR__"tulu4",
        ]));
        set("item_desc", ([
            "cao" : "長草密集厚實，好像遮蓋住了什麼，你實在看不清楚。\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7131);
	set("coor/y", -2181);
	set("coor/z", 19);
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
        if( arg=="fire" )
        {
                write("你點燃了火折，發現草後面好像還有個洞，似乎可以鑽(zuan)進去。\n");
                set_temp("marks/dashandong", 1, me);
                return 1;
        }
}

int do_zuan(string arg)
{
        object me = this_player();

        if( query_temp("marks/dashandong", me)){
                message("vision", me->name() + "往草叢中滋溜一鑽就不見了。\n", environment(me), ({me}) );
                me->move(__DIR__"shandong");
                message("vision", me->name() + "從草叢中鑽了過來。\n", environment(me), ({me}) );
                delete_temp("marks/dashandong", me);
                return 1;
        }
        else {
                write("你想往哪兒鑽？！\n");
                return 1;
        }
}