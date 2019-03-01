// hua1.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIW"三生有約"NOR, ({"sansheng youyue", "youyue",}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "一朵潔白的百合花，冠上那麼隆重的名字倒有些造作了。\n");
                set("value", 10000);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n插在鬢間，微微一笑。\n");
                set("unequip_msg", "$N幽幽長嘆，輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}