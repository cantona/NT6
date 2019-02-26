inherit DEMONROOM;

#include <ansi.h>

void setup()
{

        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("binghuo", 1);           // 表示在冰火島
        set("no_die", 1);
        set("outdoors", "battle4");

        ::setup();
}

void init ()
{
        if (! userp(this_player()))return;
        
        if (! wizardp(this_player()))
        {
                this_player()->start_busy(1+ random(2));
                tell_object(this_player(), NOR + WHT "你來到這裏，突然間迷失了方向。\n" NOR);
        }
        
        // 非幫戰期間，清理所有非天下第一幫的成員
        if( !BUNCH_D->is_battle_start() && !BUNCH_D->is_top_bunch(this_player()) )
        {
                this_player()->move(__DIR__"haitan");
        }
        // 幫戰期間，上屆天下第一幫成員不能進入
        if( (BUNCH_D->is_battle_start() || BUNCH_D->is_battle_open()) && BUNCH_D->query_bunch_topten(1) == query("bunch/bunch_name", this_player()) )
        {
                this_player()->move(__DIR__"haitan");
        }
}
