// Room: /d/xingxiu/obj/red.c
// Last Modified by winder on Apr. 25 2001

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"紅貨"NOR, ({"prize"}));
        set("unit", "包");
        seteuid(getuid());
        set("long","一包從來往商隊那裡搶來的紅貨，拿給黯然子應該就可以得到獎勵了。\n");
        set("value", 0);
        setup();
}