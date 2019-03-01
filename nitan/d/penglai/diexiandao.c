inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "蝶仙道");
        set("long",@LONG
來到此處猶如進入了夢幻般的世界，周圍零星一只五彩斑斕的
蝴蝶圍繞在你身體周圍，前方光彩閃耀，一條大道直通山谷之中。       
LONG);

        set("exits", ([
                "west"     : __DIR__"tianxiandao3",
                "east"     : __DIR__"diexiangu1",                        
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
                set("penglai", 1);           // 表示在蓬萊島

                set("objects", ([ 
                        "/clone/npc/walker": 1,
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