// Room: /heizhao/chanyuan.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "禪院");
        set("long", @LONG
你步入殿內，只見大殿上佛前供著一盞油燈，映照著佛像寶相
莊嚴。一個小沙彌正跪倒在蒲團上暗暗禱祝。左右兩壁立著四大天
王塑像，舉劍執蛇，神情甚是靈動。
LONG );
        set("no_clean_up", 0);
        set("valid_startroom", 1);
        set("objects", ([
                __DIR__"npc/xiaoshami" : 1,
        ]));
        set("exits", ([
                "east"       : __DIR__"dongxiang",
                "west"       : __DIR__"xixiang",
                "southdown"  : __DIR__"yideng9",
                "north"      : __DIR__"houxiang",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1200);
        set("coor/z", 50);
        setup();
        "/clone/board/yideng_b"->foo();
}