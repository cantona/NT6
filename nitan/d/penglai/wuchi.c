inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "霧池");
        set("long",@LONG
這島上的仙氣的源頭竟是這霧池，但見池中不斷湧出白色的霧
氣，然後這些霧氣吸收了島上的靈氣化為仙氣向四周瀰漫。看着陣
陣仙氣飄起，你禁不住想吸（xi）上一口。
LONG);

        set("exits", ([
                "west"   : __DIR__"xianqimen",
                "east"   : __DIR__"tianxiandao1",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
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

int do_xi()
{
        object me = this_player();
        
        if (! me->query("penglai/wuchi_quest/ok"))
        {
                message_vision(HIM "$N" HIM "深深地吸了一口霧池中的仙氣 ……\n" NOR, me);
                tell_object(me, HIG "恭喜你，你的靈慧增加了。\n" NOR);
                me->set("penglai/wuchi_quest/ok", 1);
                me->add("magic_points", 5000);
                me->save();
                return 1;
        }
        tell_object(me, HIC "你吸了一口池中仙氣，覺得舒泰無比。\n" NOR);
        return 1;
}