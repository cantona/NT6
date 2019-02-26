//chufang.c
inherit ROOM;
void create()
{
        set("short","廚房");
        set("long", @LONG
這是華山派的廚房，一位華山小師妹正在燒飯。整個房間瀰漫着
飯菜香。你可以向小師妹要(serve) 些吃的喝的。牆上貼着一張啟事
(note)。
LONG );
        set("exits",([
                "east" : __DIR__"garden",
        ]));
        set("item_desc",([
                "note" : "一粥一飯，當思來之不易。\n",
        ]));
        set("objects",([
                __DIR__"npc/girldizi" : 1,
        ]));
        set("resource/water", 1);
        set("ricewater", 5);
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("soup", me) || present("rice", me))
        return notify_fail("小師妹瞪了你一眼: 吃不了要兜着走啊? \n");
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
        if( query("family/family_name", me) != "華山派" )
                return notify_fail("小師妹道：你不是華山派弟子，不能拿取食物。\n");
        if(present("rice",this_player()) ) 
                return notify_fail("小師妹道：吃完了再拿，別浪費食物。\n");
        if(present("rice",this_object()) ) 
                return notify_fail("小師妹道：吃完了再拿，別浪費食物。\n");
        if (query("ricewater")>0)
        {
                message_vision("小師妹連聲答應，給$N一碗黃米飯和一碗鮮菇湯。\n",me);
                food=new(__DIR__"obj/rice");
                water=new(__DIR__"obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater",-1);
        }
        else 
                message_vision("小師妹對$N歉聲道: 嗨，吃的喝的都沒了。\n",me);
        return 1; 
}

void reset()
{
        ::reset();
        set("ricewater", 5);
}
