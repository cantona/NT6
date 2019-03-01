// Room: /d/gaochang/shulin9.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "高昌迷宮");
        set("long", @LONG
這是條黑沈沈的長甬道，甬道前出現了三條岔道。迷宮之內並無足
跡指引，你不知道要往哪條路走。俯身細看，見左首，右首和前方三條
路上都有淡淡的足跡。你似乎迷失了方向，象沒頭蒼蠅般到處亂闖。
LONG
        );

        set("outdoors", "gaochang");
        set("no_drop",1);
        set("exits", ([
                "east" : __DIR__"shulin"+(random(8)+6),
                "west" : __DIR__"shulin"+(random(8)+6),
                "south" : __DIR__"shulin"+(random(8)+6),
                "north" : __DIR__"shulin"+(random(8)+6),
        ]));
        set("coor/x", -38000);
        set("coor/y", 11000);
        set("coor/z", 0);
        setup();
}

void init()
{
        object ob, room;
        mapping fam;

        int i = random(2);
        if( i == 0) return;

        ob = this_player();
        room = this_object();

        if( query("id", ob) == "gui" || !living(ob))return ;

        message_vision(HIR "\n$N一不小心，觸動了迷宮的機關！
$N只聽得頭上一陣巨響，原來是頭上一塊巨石落下。\n\n" NOR, ob);

        message_vision(HIR "\n$N痛得幾乎失去了知覺......\n\n" NOR, ob);

        if( query("qi", ob)<250)ob->die();else ob->unconcious();
}