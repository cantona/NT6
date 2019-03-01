// This program is a part of NITAN MudLIB
// Xianglu.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "青銅鼎香爐" NOR, ({ "xiang lu"}) );
        set_weight(500);
        set_max_encumbrance(800000);
        set("no_get", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("prep", "in");
                set("unit", "只");
                set("long", HIR "一只青銅鼎香爐，燒香祭祀用的，常年香火不滅。\n" NOR);
                set("value", 1);
        }
}

int is_container() { return 1; }
