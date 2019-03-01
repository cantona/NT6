#include <ansi.h>

#include <weapon.h>

inherit CLUB;

void create()
{
        set_name(HIR"方天畫戟" NOR, ({ "fangtian huaji","huaji","ji" }));
        set_weight(15000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("value", 500000);
                set("material", "steel");
                set("long", "一桿玄鐵打制的方天畫戟，傳說是三國名將呂布所用過的武器。\n");
                set("wield_msg", "$N提起$n握在手中，威風凜凜。\n");
        }
        init_club(75);
        setup();
}

