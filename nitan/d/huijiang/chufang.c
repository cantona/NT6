// Room: /d/huijiang/chufang.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short","廚房");
        set("long",@LONG
這是紅花會的廚房。紅花會數萬會眾歸隱回疆後，這個大廚房就
一直十分忙碌。廚房的大師傅都是來自蘇杭，所以，飲食一如江南。
如果你餓了或渴了，可以向大師傅要(serve) 些吃的喝的。大師傅也
賣些江南的小點，注意留神一下牆上每天的告示(gaoshi)就好了。
LONG );
        set("objects", ([
                __DIR__"npc/shifu"     : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"zoulang3",
        ]));
        set("item_desc", ([
                "gaoshi" : 
"西湖醋魚(Fish)           ：一兩白銀又二十文銅板
龍井蝦仁(Shrimp)         ：五十文銅板
叫化童雞(Chicken)        ：一兩白銀又二十文銅板
桂花鮮慄羹(Guihua geng)  ：一兩白銀又二十文銅板
酒瓶(Jiuping)            ：十六兩白銀\n"
        ]));

        set("ricewater", 8);
        set("no_fight", 1);
        set("coor/x", -50050);
        set("coor/y", 9150);
        set("coor/z", 10);
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("soup", me) || present("baozi", me))
        return notify_fail("大師傅瞪了你一眼: 吃不了要兜着走啊？\n");
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
        if( query("family/family_name", me) != "紅花會" )
                return notify_fail("大師傅道：你不是紅花會弟子，不能拿取食物。\n");
        if(present("baozi",this_player()) ) 
                return notify_fail("大師傅道：吃完了再拿，別浪費食物。\n");
        if(present("baozi",this_object()) ) 
                return notify_fail("大師傅道：吃完了再拿，別浪費食物。\n");
        if (query("ricewater")>0)
        {
                message_vision("大師傅連聲答應，給$N一碟百果油包和一碗荷葉冬筍湯。\n",me);
                food=new("/d/hangzhou/npc/obj/baozi");
                water=new("/d/suzhou/npc/obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater",-1);
        }
        else 
                message_vision("大師傅對$N歉聲道: 嗨，吃的喝的都沒了。\n",me);
        return 1; 
}