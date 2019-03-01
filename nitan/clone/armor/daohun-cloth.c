
#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIW "噬魂戰衣" NOR, ({ "shihun zhanyi"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIW "一件奇異的戰衣，通體透明，飄忽不定，似乎不屬于人間。\n" NOR);
                set("material", "steel");
                set("value", 1);
                set("armor_prop/armor", 100);
                set("armor_prop/str", 5);
                set("armor_prop/con", 5);
        }
        setup();
}

