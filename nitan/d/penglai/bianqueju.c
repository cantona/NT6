inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "扁鵲居");
        set("long",@LONG
據說，凡是在蓬萊仙島的凡人在意外死亡後魂魄都不會離開身
體，而是被島上的仙氣帶來這裡，神醫扁鵲會將這些人起死回生。
四周看起古香古色，桌椅擺設也非常簡單，奇怪的是這裡並沒有任
何醫治病人的藥具。 
LONG);

        set("exits", ([        
                "south"    : __DIR__"diexiangu1",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/bianque" : 1,
        ]));
                
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