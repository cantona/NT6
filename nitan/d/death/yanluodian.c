// regiser: yanluodian.c
// by Doing

#include <ansi.h>

inherit ROOM;


void create()
{
        set("short", HIR "閻羅殿" NOR);
        set("long", HIB @LONG
這裏陰深恐怖，讓人感覺到一陣陣的寒意，兩旁列着牛頭馬面，冥
府獄卒，各個威嚴肅穆。十殿閻羅，盡皆在此，地藏王正坐在大堂之上，
不怒自威，你的腿腳不禁都有些軟了。
    大殿角落有一個石頭砌成的池子，其中水清澈卻不見底，不知道它
究竟有多深。
LONG NOR
);
        set("no_fight", 1);
        
        set("exits", ([
                "east"  : __DIR__"jimiesi",        
                "south" : __DIR__"youmingdian",
                "west"  : __DIR__"yinyangta1",
                "north" : __DIR__"xuechi1",
        ]));
        
        set("objects", ([
                __DIR__"npc/dizangwang"    : 1,
        ]));

        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();
        if (dir != "south")
        {
                if (objectp(present("dizang", environment(me))) 
                 && !query("hell_quest/鎖陽丹", me) )
                        return notify_fail(CYN "地藏王看了你一眼，喝道：你還不滾"
                                           "回去還陽，來這裏湊什麼熱鬧！\n" NOR);
        }
        return ::valid_leave(me, dir);
}
       