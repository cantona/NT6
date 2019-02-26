// Room: /d/shaolin/andao2.c
// Date: YZC 96/02/06

#include <login.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是一個陰暗潮濕的地道，四壁用粗糙的片巖壘垛而成，一顆顆
水珠沿着牆壁滾下來，濺在地上。也許是因為長時間無人通行的緣故，
整個地道瀰漫着一股腐屍般的惡臭。
LONG );
        set("exits", ([
                "up" : __DIR__"gulou1",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{       
        object ob;

        if( interactive(ob = this_player()) 
        && (int)ob->query_condition("bonze_jail") >= 0 )
        {
                message("vision",
                        HIY "只聽水聲嘩啦啦地一響，一個滿臉漆黑，全身泥漿的傢伙爬了過來！\n\n" NOR, 
                        environment(ob), ob);

                tell_object(ob, "你覺得混身輕鬆，總算走出了這個五行迷魂陣，逃出生天了！\n");

                set("startroom", START_ROOM, ob);
                ob->clear_condition("bonze_jail");
               return;
        }
}
