inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "竹林");
        set("long",@LONG
這是蓬萊仙島中的竹林，四周霧氣茫茫，梵音了了，真乃仙境。
不知這裡的仙氣是從何而來，竟覺得越來越多。
LONG);

        set("exits", ([
                "north"   : __DIR__"zhulin1",
                "east"    : __DIR__"xianqimen",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        if (random(2) == 1)
        {
                set("objects", ([
                        __DIR__"obj/zhuye" : 1 + random(4),
                ]));
        }
        
        setup();
}

void init ()
{
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