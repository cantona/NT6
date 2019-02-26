inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "麒麟崖");
        set("long",@LONG       
麒麟乃傳説中瑞獸之一，古代傳説中麒麟與龍、鳳、龜合為四
靈，乃毛類動物之王。麒麟很少在人間出沒，所以凡間也也少有人
見過麒麟。這裏是一處絕壁，向南望去是寬闊的大海，向北俯瞰飛
龍谷，谷中飛龍也不過巴掌般大小。偶然，可見絕壁之上有身影晃
動，不知是不是傳説中的麒麟獸。谷底一片煙霧纏繞，縷縷金光從
谷底射在崖壁之上，閃耀着眩目的光彩，據説，這谷底藏着一隻千
年仙鼠，恐怕已修成人形了吧。你突然覺得渾身輕飄飄的，有一種
想從這裏跳（tiao）下去的衝動。
LONG);

        set("exits", ([
                "northdown"     : __DIR__"feilonggu2",                                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 600 + random(180)); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/jinseqilin");
        
        setup();
}

void init ()
{
        add_action("do_tiao", "tiao");

        if (! this_player()->query_temp("apply/xianshu-lingwei"))
        {
                if (! this_player()->query("penglai/go_quest/ok"))
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "你到了此處，四周仙氣繚繞令你一時間難以辨別方向。\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "你到了此處，四周仙氣繚繞令你一時間難以辨別方向。\n" NOR);                
                        }
                }
        }                
}

int do_tiao(string arg)
{
        object me = this_player();

        message_vision(HIW "\n$N" HIW "深吸一口氣，縱身跳下麒麟崖 ……\n", me);
        
        if (random(2))
        {
                tell_object(me, HIG "突然間，你只覺得渾身飄忽，被一陣仙氣捲走 ……\n" NOR);
                me->move(__DIR__"bianqueju");
                return 1;
        }
        tell_object(me, HIY "如你所料，這裏的仙氣能夠支撐起你自身的重量，慢慢的飄落到谷底 ……\n\n" NOR);
        
        me->move(__DIR__"gudi");

        return 1;         
}