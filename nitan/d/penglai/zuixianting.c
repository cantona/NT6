inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "醉仙亭");
        set("long",@LONG
傳説醉仙亭中常有仙者在此飲酒作樂，撫琴高歌，順着那梵音
一路尋來。但見一中年男子坐於亭中，撫琴彈奏，琴音陣陣，猶如
天外梵音，令人心境舒泰無比。片刻那男子於彈奏間不斷取出腰間
酒壺，小酌數口，自娛自樂，完全沒有注意到外人的到來。
LONG);

        set("exits", ([
                "south"     : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);

        set("objects", ([
                __DIR__"npc/jiujianxian" : 1,
        ]));
                
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