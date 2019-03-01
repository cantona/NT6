inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "麒麟崖底");
        set("long",@LONG
到得此處，舉頭一望，原來麒麟崖竟如此挺拔，直沖雲霄，令
人驚嘆。崖底風景秀麗，綠樹蔥鬱，生機勃勃。幾只不只名的飛鳥
在你頭頂盤旋，不遠處有一塊圓形的石頭，走近一看，猶如鏡面一
般將天際處的光芒匯聚于此，投射到四周。不遠處有一根樹籐，可
以順著爬（pa）上麒麟崖。
LONG);

        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 0);
                
        setup();
}

void init ()
{        
        add_action("do_pa", "pa");
        
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

int do_pa(string arg)
{
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正在忙著呢。\n");
        
        message_vision(HIY "$N" HIY "施展輕功，順著樹籐及仙氣的浮力，輕鬆地爬上麒麟崖 ……\n", me);
        
        me->move(__DIR__"qilinya");
        
        return 1;
                
}