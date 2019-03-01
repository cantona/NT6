// Room: /yangzhou/banting.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "寒竹風鬆");
        set("long", @LONG
小南海西面的二角半亭，板瓦頂，置美人靠。亭上懸掛孫龍父所書
“寒竹風鬆”匾，外柱懸掛田原所書楹聯(lian)。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIG"
        江        日
        秋        瘦
        逼        抱
        山        鬆
        翠        寒
\n"NOR
        ]));
        set("exits", ([
                "east"   : __DIR__"guanyindian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}