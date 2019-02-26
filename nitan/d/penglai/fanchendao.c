inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "凡塵道");
        set("long",@LONG
由於仙界有規定，島中仙人均不可隨意離島，需要進行外出遊
歷時即入了凡塵，凡是需要出島進入凡塵的仙者均需要由此處出島，
經過彩石沙灘洗盡身上仙氣才能進入塵世間，而洗掉仙氣同時，出
島仙者的法力也大大減弱。
LONG);

        set("exits", ([
                "southeast"   : __DIR__"pantaoyuan2",
                "southwest"   : __DIR__"pantaoyuan3",
                "north"       : __DIR__"caishishatan",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島

        set("no_clean_up", 1); 

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