// sheerkou.c 蛇兒口
#include <ansi.h>
inherit ITEM;

#define max_poison 24
#define least_poison 8

void init()
{
}

void create()
{
        set_name(HIM"蛇兒口"NOR, ({ "sheer kou", "sk" }) );
        set_weight(600);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("value", 0);
                set("material", "steel");
                set("long", "這是傳説中古老而神祕的暗器--蛇兒口。\n");
        }
        setup();
}