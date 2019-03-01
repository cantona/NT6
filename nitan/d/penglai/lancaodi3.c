inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "蘭草地");
        set("long",@LONG
來到這裡，蘭草的香味已經令人心曠神怡，四周飄著淡淡的仙
氣，蘭草在仙氣的籠罩下顯得格外美麗。置身于如此境界，真可謂
夫復何求。
LONG);

        set("exits", ([
                "north"        : __DIR__"lancaodi2",
                "southeast"    : __DIR__"caijuyuan1",        
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        if (random(3) == 1)
        {
                set("objects", ([
                        __DIR__"obj/lancao" : 3,
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