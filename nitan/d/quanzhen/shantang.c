// shantang.c
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "膳堂");
        set("long", @LONG
這裡是全真教的膳堂，是弟子們用餐的地方。這個堂很大，
整齊地擺放著一排一排的桌椅。現在桌椅上三三兩兩地坐著全真
弟子，有的正在用餐，有的低頭談笑。看著可口的飯菜，你忍不
住也想叫(order)一份。
LONG
        );
        set("exits",([
                "north" : __DIR__"xiuxishi",
                "east" : __DIR__"chufang",
                "northwest" : __DIR__"wuchang2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2740);
        set("coor/y", 80);
        set("coor/z", 170);
        setup();
}

void init()
{
        add_action("do_order","order");
}

int do_order(string arg)
{
        object me=this_player();
        object food;
        object water;

        if (arg)  return notify_fail("這樣東西這裡沒有啊。\n");
        if( query("family/family_name", me) != "全真教" )
        {
              message_vision("火工道人沖出來，瞪了$N一眼：“你哪裡來的！敢來混飯吃！”\n",me);
              return 1;
        }

        if ((present("bowl",this_player()) || present("rice",this_player())))
              message_vision("火工道人沖出來，瞪了$N一眼：“還沒吃完又想要！”\n",me);
        else
        {
              message_vision("火工道人連忙從廚房出來，把一碗米飯和一碗水拿了給$N。\n",me);
              food=new(__DIR__"obj/rice");
              water=new(__DIR__"obj/bowl");
              food->move(me);
              water->move(me);
        }
        return 1;
}

int valid_leave(object me,string dir)
{
        me=this_player();
        if(( dir=="north" || dir=="northwest")
        && (present("bowl",this_player()) || present("rice",this_player())))
             return notify_fail("火工道人說道：食物和飲水不能帶出膳堂去。\n");
        return ::valid_leave(me,dir);
}