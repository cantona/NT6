// hanshasheying.c 含沙射影

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name("含沙射影", ({ "han sha she ying", "hssy" }) );
        set_weight(500);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是五毒教的奇門暗器「含沙射影」，樣子象一條腰帶，可以束在腰間。\n帶中間有一個扁扁的小鐵盒。\n") ;
                set("unit", "個");
                set("value", 0);
                set("material", "iron");
                set("armor_prop/armor", 3);
        }
        setup();
}

void init()
{
}