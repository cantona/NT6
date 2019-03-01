#include <armor.h>
#include <ansi.h>
inherit CLOTH;


void create()
{
        set_name(BLU "藍布短衫" NOR, ({ "cloth" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一件普普通通的短衫，穿得髒兮兮的。\n");
                set("unit", "套");
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}
