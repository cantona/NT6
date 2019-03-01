// Room: /heizhao/houxiang.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "後廂");
        set("long", @LONG
這裡是桃源寺的廚房，一個老和尚正在灶邊忙來忙去，看來他
就是這裡的大師傅了。如果你的肚子餓了，就趕快要 (serve)些吃
的吧。
LONG );
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/laoheshang" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"chanyuan",
        ]));
        set("ricewater", 5);
        set("coor/x", -5020);
        set("coor/y", -1190);
        set("coor/z", 50);
        setup();
}

void init()
{
        add_action("do_serve","serve");
}

int do_serve()
{
        object food, water, me = this_player(), ob = this_object();

        if( query("family/family_name", me) != "大理段家" )
return notify_fail("老和尚道：阿彌陀佛，你非本派弟子，不能拿取食物。\n");
        if(present("mifang", me) || present("qingtang", me)) 
return notify_fail("老和尚道：阿彌陀佛，吃完了再拿，別浪費食物。\n");
        if(present("mifang", ob) || present("qingtang", ob)) 
return notify_fail("老和尚道：吃完了再拿，別浪費食物。\n");
        if (query("ricewater")>0)
        {
                message_vision("老和尚連聲答應，給$N一碗清湯和一碗米飯。\n",me);
                food=new(__DIR__"obj/mifang");
                water=new(__DIR__"obj/qingtang");
                food->move(me);
                water->move(me);
                addn("ricewater",-1);
        }
        else 
                message_vision("老和尚對$N歉聲道: 嗨，吃的喝的都沒了。\n",me);
        return 1; 
}
int valid_leave(object me,string dir)
{
        if(dir=="south" && (present("mifang", me) || present("qingtang", me))) 
             return notify_fail("老和尚說道：吃了就別帶走。\n");
        return ::valid_leave(me,dir);
}