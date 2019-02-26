
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIM "十週年·端午·鳳戒" NOR, ({ "duanwu fengjie", "fengjie" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", HIM "這是由炎黃十週年暨端午節發放的戒指，紅光微微，其絢奪目，猶如一條鳳凰起舞。\n" NOR);
                set("value", 100);
                set("material", "gold");
                set("armor_prop/dex", 10);
                set("armor_prop/str", 10);
                set("armor_prop/int", 10);
                set("armor_prop/con", 10);
                set("armor_prop/damage", 500);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
