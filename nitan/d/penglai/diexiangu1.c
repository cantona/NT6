inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "蝴蝶谷");
        set("long",@LONG
進入蝴蝶谷，成群的彩蝶飛繞在你四周，而陣陣花香撲鼻而來，
五彩的光環由天際投射而來，將這裡照射得分外美麗。令你覺得置
身如此美景，所有凡塵瑣事都已拋之腦後。    
LONG);

        set("exits", ([
                "west"     : __DIR__"diexiandao",
                "east"     : __DIR__"diexiangu2",        
                "north"    : __DIR__"bianqueju",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("n_time", 45); 
        set("n_npc", 1); 
        set("n_max_npc", 7);
        set("s_npc", __DIR__"npc/xiaodiexian");
        
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