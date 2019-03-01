// cq.c

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIW "蒼穹神劍" NOR, ({ "cang qiong" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄沒有劍頭的長劍\n");
                set("value", 50000);
                set("rigidity",2000);        
                set("material", "steel");
                set("max_enchant",7);
                set("for_create_weapon",1);
        }
        init_sword(50);
        setup();
}