inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "蟠桃園");
        set("long",@LONG
這裏是蓬萊仙島的蟠桃園，蟠桃樹一百年開花，再過一百年才
結果，每逢蟠桃出現的時候羣仙便會會聚在此舉行蟠桃大會。雖然
同居一島，但是每過兩百年羣仙才會藉着蟠桃大會聚會一次，共享
蟠桃美酒。
LONG);

        set("exits", ([
                "northwest"   : __DIR__"fanchendao",
                "southwest"   : __DIR__"pantaoyuan1",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 30); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/mihou");
        
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