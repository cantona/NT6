inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "修真池");
        set("long",@LONG
此處是島中仙者恢復法力的修真池，池中仙氣大盛，置身於此
感覺身心舒泰無比。真是快活似神仙。那熟悉已久的梵音似乎就從
北方傳來，你不禁想去探個究竟。
LONG);

        set("exits", ([
                "west"      : __DIR__"xiuzhenchi3",
                "east"      : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("xiuzhenchi", 1);       // 可以提高冥思獎勵
        set("no_fight", 1);
        set("sleep_room", 1);
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