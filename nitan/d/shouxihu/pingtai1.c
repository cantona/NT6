// Room: /yangzhou/pingtai1.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "平台");
        set("long", @LONG
由風亭西行下山，石徑中段有一平台，平台石欄為法海寺遺物。在
此遠眺五亭橋、白塔、釣魚台諸景最佳。出平台，過山澗石樑，即達觀
音殿。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "westdown" : __DIR__"guanyindian",
                "eastup"   : __DIR__"fengting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 20);
        set("coor/y", 120);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}