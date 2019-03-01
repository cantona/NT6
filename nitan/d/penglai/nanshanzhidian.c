inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "南山之顛");
        set("long",@LONG
南山之顛乃南山最高峰，不少仙者常來這裡吸收天地的靈氣以
促進仙法的修煉。你站在高峰之上，遠眺蓬萊仙島，其景美不勝收，
實在難以用人間任何語言來描述。俯瞰南山，依然是如此神秘，若
隱若現，時高時低。翹首東望麒麟崖，更是令人充滿無盡的遐思。
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 600 + random(180)); 
        set("n_npc", 1); 
        set("n_max_npc", 8);
        set("s_npc", __DIR__"npc/dacaishen");
        
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
        
        if (playerp(this_player()) && ! this_player()->query("penglai/nanshan_quest/ok"))
        {
                tell_object(this_player(), HIG "\n你被一陣仙氣卷下山去 ……！。\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // 第一次南山之顛獲取一些獎勵
        {
                if (! this_player()->query("penglai/nanshanzhidian_quest/ok"))
                {
                        tell_object(this_player(), HIR "\n你找到南山之顛峰並吸收了這裡的天地靈氣，獲得了5萬點潛能及10萬點實戰體會獎勵。\n\n" NOR);
                        this_player()->add("potential", 50000);
                        this_player()->add("experience", 100000);
                        this_player()->set("penglai/nanshanzhidian_quest/ok", 1);
                        this_player()->save();
                }                
        }
}
