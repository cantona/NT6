// difu1.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIW "酆都地府" NOR);
        set("long",BLU @LONG
你現在來到一座黑色城樓之前，城樓上刻著三個大字：酆都城。往
南不遠處有一座橋，橋上鬼影幢幢，但是卻聽不到半點聲音，再往南就
是鬼門關，可是一旦進了鬼門關，就再也不能出去了；往北走進城樓只
見一片黑漆漆的，只有少許暗紅色的火光若隱若現地閃爍著。再往北是
一個大殿。
LONG NOR );
        set("no_fight", 1);
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"difu2",
                "south" : __FILE__,
        ]));
        set("objects", ([
                __DIR__"npc/niutou": 1,
                __DIR__"npc/mamian": 1,
        ]) );

        setup();
}

int valid_leave(object me, string dir)
{
        if( wizardp(me) || !userp(me) ) return 1;

        if (dir == "south")
        {
                return notify_fail("一個空洞的聲音在你耳邊響起....\n"+
                "沒有回頭路了!\n");
        }
        else return 1;
}

