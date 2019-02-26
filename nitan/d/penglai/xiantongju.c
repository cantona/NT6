inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "仙童居");
        set("long",@LONG
對於仙童相信大家已經很熟悉了，仙童在此恭候多時了。
這裏可以進行倉庫物品的存取。但見四周金光閃耀，仙氣繚
繞，似乎要比揚州倉庫增色不少。
LONG);

        set("exits", ([
                "southwest"    : __DIR__"caiyunjian2",        
                "northeast"    : __DIR__"changshengmeilin1",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);

        set("objects", ([
                "/d/city/npc/xiantong" : 1,
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