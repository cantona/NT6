// Room: /d/xiangyang/juyichufang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這兒是聚義館的廚房，一般只有白天有幾個燒飯師傅在燒火做飯，
供應（serve）伙食，到了晚上就看你的運氣了。
LONG );
        set("exits", ([
                "north" : __DIR__"juyihuayuan",
        ]));
        set("objects", ([
                __DIR__"npc/shaofanshifu"   : 1,
        ]));
        set("no_fight", 0);
        set("ricewater", 30);
        set("coor/x", -7840);
	set("coor/y", -810);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if ( present("soup", me) || present("rice", me))
        return notify_fail("燒飯師傅瞪着一雙怪眼：吃不了要兜着走啊？\n");
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_serve","serve");
}

int do_serve()
{
        object me;
        object food;
        object water;
        me=this_player();
        if(present("rice",this_player()) ) 
                return notify_fail("燒飯師傅道：吃完了再拿，別浪費食物。\n");
        if(present("rice",this_object()) ) 
                return notify_fail("燒飯師傅道：吃完了再拿，別浪費食物。\n");
        if (query("ricewater")>0)
        {
                message_vision("燒飯師傅給$N一碗高粱米飯和一碗野菜湯。\n",me);
                food=new(__DIR__"obj/rice");
                water=new(__DIR__"obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater",-1);
        }
        else 
                message_vision("燒飯師傅對$N歉聲道: 嗨，吃的喝的都沒了。\n",me);
        return 1; 
}
void reset()
{
        ::reset();
        set("ricewater",1);
}