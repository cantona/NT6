inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "蝶仙居");
        set("long",@LONG
一來到這裏，花香襲來，仔細一看，才知道這居所竟是用各種
花瓣堆砌而成，紅橙粉蘭，各種顏色縱橫交匯，芬芳豔麗。房間中
央，一名年親貌美的仙子正在將死去的蝴蝶製作成標本。想必這便
是傳説中的蝶仙了。
LONG);

        set("exits", ([        
                "north"    : __DIR__"diexiangu2",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/diexian" : 1,
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