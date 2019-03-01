inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "南山道");
        set("long",@LONG
這是通往蓬萊島南山的必經之路，傳說南山乃仙人修煉仙法的
地方，屬于禁地。雖無人看守，但若沒有仙人的指引外人是無論如
何也無法進入的。四周植物蔥鬱，仙氣圍繞，景致甚是迷人。而那
陣陣梵音之聲越來越近。
LONG);

        set("exits", ([
                "north"    : __DIR__"nanshandao1",
                "south"    : __DIR__"xianrenzhilu",        
                "west"     : __DIR__"yingxiandao",
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