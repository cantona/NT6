#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "【酆都城門】" NOR);
       set("long", HIR @LONG

                    酆     都     城     門

    你現在來到一座黑色的城樓之前，城樓上雕刻著「酆都城」三個大
字。往南不遠處有一座石橋，橋上鬼影幢幢，但是卻聽不到半點聲音，
往北走進城樓只見一片黑漆漆的，只有少許暗紅色的火光若隱若現地閃
爍著。


LONG NOR );
        set("exits", ([
                "north" : __DIR__"road1",
                "south" : __DIR__"gate",
        ]));
        set("objects", ([
                __DIR__"npc/hei": 1,
        ]) );

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
}

int valid_leave(object me, string dir)
{
        if( wizardp(me) || !userp(me) ) return 1;

        if (dir == "south") {
                return notify_fail(HIW "\n一個空洞的聲音在你耳邊響起……沒有回頭路了……\n" NOR);
        }
        else return 1;
}
