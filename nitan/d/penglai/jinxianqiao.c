inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "金仙橋");
        set("long",@LONG
金仙橋乃是連接臥龍谷與金色沙灘的一座橋樑，橋下流水潺潺，
泛著金光。據說，原本這裡的流水清澈無比，後來海水主講將金色
沙灘的金沙沖到金仙橋下，這流水便成了金色。這裡的水經過金色
沙灘的凈化和仙氣的洗滌變成了可以引用的淡水，如果有容器可以
在這裡裝一壺（fill）嘗嘗。
LONG);

        set("exits", ([
                "west"     : __DIR__"wolongdao",
                "east"     : __DIR__"jinseshatan",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("resource/water", 1);    // 可以加水

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