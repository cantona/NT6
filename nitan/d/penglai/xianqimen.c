inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "仙氣門");
        set("long",@LONG
到了這裏，四周盡是白茫茫的仙氣，猶如置身在夢境之中，感
覺自己隨着仙氣繚繚升起，就快成了神仙。不遠處隱約可見一塊碑
石，上書「仙氣門」三個大字。似乎島上的霧氣都是從這裏湧出來
的。陣陣梵音又漸漸傳來，似乎越來越近了。
LONG);

        set("exits", ([
                "west"   : __DIR__"zhulin2",
                "east"    : __DIR__"wuchi",
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