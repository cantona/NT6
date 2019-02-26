inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "飛龍谷");
        set("long",@LONG
這裏便是居住着飛龍的飛龍谷，不時地有一些飛龍向你飛來發
出震耳欲聾的叫聲，令人毛骨悚然。難怪天界會派巨龍守護峽谷，
不讓這些飛龍出谷危害人間，凡人見之早已經心膽懼烈，哪裏是這、
廝的對手。
LONG);

        set("exits", ([
                "north"     : __DIR__"changshengdao2",        
                "south"     : __DIR__"feilonggu2",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 120); 
        set("n_npc", 1); 
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/feilong");
        
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