inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "夢幻琉璃");
        set("long",@LONG
這是一條用各種顏色的琉璃鋪成的路，琉璃的光彩透仙氣折射
出各種不同的色彩，照耀着整條道路，顯得猶如夢境般奇幻。令人
匪夷所思。
LONG);

        set("exits", ([
                "north"    : __DIR__"tianxiandao1",
                "south"    : __DIR__"nanshandao1",        
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

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