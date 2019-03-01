inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "飛馬崖");
        set("long",@LONG
飛馬乃島中仙者的主要坐騎，這裡便是飛馬生長的地方。據說，
每過幾年仙者便回來這裡挑選新的飛馬。傳說，這飛馬與尋常之馬
不同，其主要飼料來源于金色沙灘的金沙，只有喂實金沙飛馬才能
生長。放眼望去，懸崖四周一群飛馬正飛行，追逐嬉戲。
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 180); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/feima");
        
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
        
        if (userp(this_player()) && ! this_player()->query("penglai/nanshan_quest/ok"))
        {
                tell_object(this_player(), HIG "\n你被一陣仙氣卷下山去 ……！。\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // 第一次飛馬崖增加ridding 5LV
        {
                if (! this_player()->query("penglai/feimaya_quest/ok"))
                {
                        tell_object(this_player(), HIR "\n你仔細觀察飛馬的一舉一動，對騎術有了新的理解。\n" NOR);
                        tell_object(this_player(), HIC "你的「騎術」進步了！\n\n" NOR);
                        this_player()->set_skill("riding", this_player()->query_skill("riding", 1) + 5);
                        this_player()->set("penglai/feimaya_quest/ok", 1);
                        this_player()->save();
                }
        }
}
