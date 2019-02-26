inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "彩雲間");
        set("long",@LONG
這裏是蓬萊仙島彩雲間道，由於陽光折射到這裏的仙氣上產生
彩色的光環，猶如置身與彩雲之間，故此路以此命名。
LONG);

        set("exits", ([
                "northeast"    : __DIR__"xiantongju",        
                "south"        : __DIR__"caiyunjian1",                
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