
#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIR "聖武士披風" NOR, ({ "wushi pifeng", "wushi", "pifeng" }) );
        set_weight(200);
        set("long", HIR "傳説中聖潔的武士才能穿戴此披風，乃神聖的象徵。\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIR "聖武士所穿戴的披風，藴藏着神奇的力量！\n" NOR);
                set("material", "steel");
                set("value", 3000000);
                set("armor_prop/armor", 400);
                set("armor_prop/con", 1); // 後天根骨+1
                set("armor_prop/str", 1); // 後天臂力+1
        }
        setup();
}

int query_autoload()
{
        return 1;
}
