inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裡是村長家的廚房，平常弟子們餓了可以到這裡要 （輸入指
令 yao）些食物。房中灶火正旺，一個大廚師正忙的滿頭大汗。屋角
放著一個大水缸。  
LONG);

        set("exits", ([
                "east" : __DIR__"cunzhangjia",
        ]));

        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));

        set("ricewater", 1000);
        set("xinshoucun", 1); 
        set("no_fight", 1);
        setup();
}

void init()
{
        add_action("do_yao", "yao");
}

int do_yao()
{
        object me;
        object food;
        object water;
        me = this_player();

        if (present("man tou", this_player())) 
                return notify_fail(CYN "廚師眉頭一皺，說道：吃完了再拿，別浪費食物。\n" NOR);

        if (present("water", this_object())) 
                return notify_fail(CYN "廚師眉頭一皺，說道：吃完了再拿，別浪費食物。\n" NOR);

        if( time()-query_temp("last_yao_food", me)<30 )
                return notify_fail(CYN "廚師眉頭一皺，說道：你剛要過食物了，留點口糧給別人吧！\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "廚師將一個饅頭和一碗清水遞到$N手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new("/d/henshan/obj/mantou");
                water = new("/d/henshan/obj/water");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
                set_temp("last_yao_food", time(),                 me);
        }
        else 
                message_vision(CYN "廚師對$N" CYN "歉聲道：嗨，吃的喝的都"
                               "沒了。\n" NOR,me);
        return 1; 

}
