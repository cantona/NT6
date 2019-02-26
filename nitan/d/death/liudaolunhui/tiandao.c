#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "\n\n                天        極        道" NOR);
        set("long", HIW "\n"
"茫茫雲海，渺無邊際。四周金光散佈，祥雲朵朵，遠處有鳳凰\n"
"盤繞，麒麟逐戲。耳邊傳來陣陣梵音，令你茫然不知所措。天\n"
"道眾生遍及欲界、色界及無色界三界。欲界有六慾天，色界有\n"
"四禪十八天，無色界四天，共有二十八天。\n\n" NOR);

        set("objects", ([
                __DIR__"npc/tiandaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}