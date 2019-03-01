// Room: /d/songshan/chufang.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這是嵩山派的廚房，一位油光滿面的伙夫正在燒火做飯。房間裡散
發著飯菜的香味。廚房裡放著幾張小桌椅，你可以向伙夫要(serve) 些
吃的喝的。
LONG);
        set("exits",([
                "east" : __DIR__"westting",
        ]));
        set("no_clean_up", 0);
        set("ricewater", 5);
        set("no_fight","1");
        set("coor/x", -50);
        set("coor/y", 900);
        set("coor/z", 90);
        setup();
}
int valid_leave(object me, string dir)
{
        if ( present("soup", me) || present("rice", me))
                return notify_fail("你一轉身，發現門口貼著張告示：“飲食不外帶”。\n");
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
        if( query("family/family_name", me) != "嵩山派" )
                return notify_fail("伙夫把手一攤：“你不是嵩山派弟子，不能拿取食物。”\n");
        if(present("rice",this_player()) ) 
                return notify_fail("伙夫一瞪牛眼：“吃完了再拿，別浪費食物！”\n");
        if(present("rice",this_object()) ) 
                return notify_fail("伙夫看了看桌上，道：“吃完了再拿，別浪費食物。”\n");
        if (query("ricewater")>0)
        {
                message_vision("伙夫連聲答應，給$N一碗黃米飯和一碗鮮菇湯。\n",me);
                food=new("/d/huashan/obj/rice");
                water=new("/d/huashan/obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater",-1);
        }
        else 
                message_vision("伙夫對$N歉聲道：“嗨，吃的喝的都沒了。”\n",me);
        return 1; 
}