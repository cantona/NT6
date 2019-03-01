inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "天仙道");
        set("long",@LONG
走在這根道上猶如踏上雲層的感覺一般，輕飄飄的，從未試過
這種感覺，陽光照射在仙氣上折射出的各種光圈，五彩斑斕，美麗
非常。
LONG);

        set("exits", ([
                "west"     : __DIR__"tianxiandao2",
                "east"     : __DIR__"diexiandao",        
                "north"    : __DIR__"caiyunjian1",        
                "south"    : __DIR__"lancaodi2",                
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