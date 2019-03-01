inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "迎仙道");
        set("long",@LONG
仙者在出島時法力會受到彩石沙灘的影響而減弱，當再次回到
島上後需要在距離這裡不遠處的修真池中進行修煉以幫助恢復法力。
此路便是為迎接從修真池中修煉出來的仙者而設，意為歡迎其回到
蓬萊仙島。
LONG);

        set("exits", ([
                "east"     : __DIR__"nanshandao2",
                "west"     : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
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