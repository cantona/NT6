inherit ROOM;

void create()
{
          set("short", "花園");
        set("long", @LONG
你的眼前出現了一個美麗的花園，花園裏種着一些花，花從中隱
約可見飄渺的倩影，那是宮中的姐妹們在玩耍。花園中央有一座假山
(jiashan) 。花園的東西兩頭是長廊，北邊有一條小道通向天山童姥
修練之處。
LONG );
          set("exits",([
                      "west" : __DIR__"changl1",
                      "north" : __DIR__"xiaodao1",
                      "east" : __DIR__"changl2",
                      "south" : __DIR__"changl15",
          ]));
          set("outdoors", "lingjiu");
        set("item_desc", ([
                "jiashan" : "這座假山看起來不算太大，你應該可以搬動(move)它.\n",
        ]));
          set("objects", ([
                      "/clone/quarry/lu" : 1,
                      "/clone/quarry/zhang" : 1,
          ]));
          setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_enter", "enter");
}

int do_move(string arg)
{      
        object me = this_player();
        
        if (! arg || arg != "jiashan")
                return notify_fail("你要移動什麼？\n");
        if ((int)me->query_str() > 28)
        {
                message_vision("$N使出吃奶的力氣把假山挪開,只見下面露出一個大洞，似乎可以進去(enter)。\n", 
                        this_player());
                set("move_jiashan", 1);
        }
        else
                message_vision("$N使出吃奶的力氣也挪不動假山，只好悻悻地放棄了。\n", this_player());        
        return 1;        
}

int do_enter(object me)
{
        object room;
        object where;
        
        me = this_player();
        where = environment(me);
        
        if( !query("move_jiashan", where) )
                return notify_fail("你要進哪去？\n");
                
        if (! (room = find_object(__DIR__"midao1")))
                room = load_object(__DIR__"midao1");
                
        message_vision("$N“咕咚”一聲，跳進洞中。\n", me);
        me->move(room);
        set("move_jiashan", 0);
        return 1;
}