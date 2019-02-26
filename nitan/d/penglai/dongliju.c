inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "東籬居");
        set("long",@LONG
這裏似乎是一處居所，不遠處有一處茅屋，四周用籬笆圍住。  
放眼遠望，山影起伏，霧氣陣陣，令人無限遐思。     
LONG);

        set("exits", ([
                "northwest"        : __DIR__"caijuyuan2",
                "southwest"        : __DIR__"caijuyuan3",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        if (random(2) == 1)
        {
                set("objects", ([
                        __DIR__"obj/juhua" : 3 + random(5),
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