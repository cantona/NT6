// gudi.c 谷底
#include <ansi.h>
inherit ROOM;

int do_climb(string arg);
int do_swim(string arg);
int do_mai(string arg);
void create()
{
        set("short", "谷底");
        set("long", @LONG
這就是懸崖谷底了，三面是高聳的山峯，一面是大海，四周沒有
出口，谷底的煙霧很大，走着走着，你隱隱約約見到前面盤膝坐着一
位老者(Oldman)。
LONG );
        set("outdoors", "xiakedao");
        set("item_desc",([
                "feng"     : "看什麼呀? 這麼高的山你是爬不上去的。\n",
                "shanfeng" : "看什麼呀? 這麼高的山你是爬不上去的。\n",
                "oldman"   : "你仔細一看，這位老者已經仙去很多年了，留下的只是他的遺骨(gu)，好可憐呀!\n",
                "sea"      : "看什麼呀? 你難道想游泳嗎? \n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -4000);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();
}
void init()
{
        add_action("do_climb","climb");
        add_action("do_mai","bury");
        add_action("do_mai","mai");
        add_action("do_swim","swim");

}
int do_mai(string arg)
{
        int n;

        n=query("neili", this_player());
        if( !arg || arg != "gu")
        {
                write("什麼? \n");
                return 1;
        }
        message_vision("$N找了一塊鬆軟的地面，用力挖了起來。\n", this_player());
        if (n > 100)
        {
                message_vision("大約過了半個時辰，$N恭恭敬敬的把老者的遺骨放了進去，埋了起來。突然東面
出現了一個石門。\n", this_player());
                set("exits/east",__DIR__"midao6");
                addn("neili", -100, this_player());
                remove_call_out("close");
                call_out("close",5, this_object());
        }
        else
        {
                message_vision("$N的氣力不足，挖了幾下就幹不動了。\n", this_player());
                set("neili", 0, this_player());
        }
        return 1;
}

void close(object room)
{
        message("vision","石門自動的合上了。\n", room);
        delete("exits/east", room);
}

int do_swim(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg!="sea")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        message_vision("$N深吸了一口氣，跳進海里，奮力的遊了起來。\n", me);
        if( random(query("kar", me))>9 )
        {
                message_vision("海上的風浪太大，$N逐漸的失去了知覺。\n", me);
                me->receive_damage("qi", 50);
                me->receive_wound("qi", 50);
                me->move(__DIR__"haitan");
                tell_object(me,HIR"你醒來發現你渾身疼痛，還受了幾處傷。\n" NOR);
                message("vision",HIR"只見"+query("name", me)+"被海浪衝到海灘上。\n"NOR,environment(me),me);
        }
        else
        {
                message_vision("海上的風浪太大，$N不得不退了回來。\n", me);
                me->receive_damage("qi",10);
                me->receive_wound("qi",10);
        }
        return 1;
}

int do_climb(string arg)
{
        int n;
        n = this_player()->query_skill("dodge",1);
        if ( !arg || arg!="shan")
        {
                write("你要爬什麼呀? \n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢的向上爬。\n", this_player());
        if(n >40)
        {
                message_vision("$N爬了半天，突然發現了一個洞口，$N不顧一切鑽了進去。\n", this_player());
                this_player()->move(__DIR__"midao8");
        }
        else
        {
                message_vision("$N爬了一會，太累了，不小心滑了下來。\n", this_player());
                this_player()->receive_damage("qi",10);
                this_player()->receive_wound("qi",10);
        }
        return 1;
}