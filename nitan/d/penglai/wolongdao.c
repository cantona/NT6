inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "卧龍道");
        set("long",@LONG
卧龍道位於蝶仙谷與飛龍谷之間，是連接兩處的要道，傳説仙
界曾派出巨龍守護這裏的道口，為的是防止谷中飛龍出谷，危害人
間。可不想那巨龍偷懶睡熟，讓那飛龍逃出山谷。後來巨龍得到仙
界懲罰，變做化石，卧在此路之上，終身守護飛龍谷，此道便以卧
龍道命名。
LONG);

        set("exits", ([
                "west"     : __DIR__"diexiangu2",
                "east"     : __DIR__"jinxianqiao",        
                "south"    : __DIR__"changshengdao2",                
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("objects", ([ 
                "/clone/npc/walker": 2,
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