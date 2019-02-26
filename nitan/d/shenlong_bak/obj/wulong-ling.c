// lingpai.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(RED"令牌"NOR, ({ "lingpai", "pai" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("value", 50);
                set("material", "wood");
                set("long", "這是一支木令牌，上面用朱漆寫着一個「神龍」兩字。\n");
        }
        setup();
}