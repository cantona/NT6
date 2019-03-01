inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "長生道");
        set("long",@LONG
長生道象征著長生不老，傳說，這島上不但居住著仙者， 
還居住著凡間之人，至于這些人從何而來便不得而知。只知
道他們長年居住在長生村中。也有傳說，凡是踏過長生道的
人便可以獲得永生。不知道這裡為什麼也叫長生道，據說這
裡長生村的居民原本打算在這裡定居，後來谷中出現飛龍後
全村的人便搬離了這裡。
LONG);

        set("exits", ([
                "north"         : __DIR__"wolongdao",        
                "south"         : __DIR__"feilonggu1",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);

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