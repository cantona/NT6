// paper.c
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"華山論劍"HIR"英雄帖"NOR, ({"yingxiong tie", "tie"}));
        set_weight(100);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"這是武林盟主邀約公平子參加華山論劍比武大會，充任比武裁判的請帖。\n");
                set("material", "paper");
        }
}
