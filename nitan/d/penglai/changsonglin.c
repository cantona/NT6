inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "長松林");
        set("long",@LONG
蓬萊仙島的長松林中生長着許多高大的松樹，每當有仙氣湧向
這裏的時候，松樹上的松鼠便會不停地搖動樹枝，松葉也紛紛落下，
將地上鋪得軟軟的。
LONG);

        set("exits", ([
                "north"     : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 20); 
        set("n_npc", 2); 
        set("n_max_npc", 10);
        set("s_npc", __DIR__"npc/songshu");
                
        if (random(3) == 1)
        {
                set("objects", ([
                        __DIR__"obj/songye" : 1 + random(10),
                ]));
        }
                        
        setup();
}

void init ()
{
        if (! playerp(this_player()))return;
        
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