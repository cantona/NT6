

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIR "錦" HIC "鑭" HIM "袈裟" NOR, ({ "jinlan jiasha", "jinlan", "jiasha" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIR "此乃傳說中唐僧所穿戴的錦鑭袈裟，只見金光閃耀，令人睜不開眼，猶如佛光普照般祥和。\n"
                            HIC "仔細看去，袈裟上隱約出現幾個大字：" HIG "不墜地獄，不入輪回\n" NOR);
                set("value", 800000);
                set("armor_prop/armor", 800);
                set("armor_prop/str", 7);
                set("armor_prop/dex", 7);
                set("armor_prop/int", 7);                                
                set("armor_prop/con", 7);
                set("limit", ([
                        "exp"  :   100000000,
                        "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
