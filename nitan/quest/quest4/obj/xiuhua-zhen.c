#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW"繡花針"NOR, ({ "xiuhua zhen", "zhen" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", "這是一枚繡花針，千金小姐們手中的尋常之物。\n");
                set("value", 100);
                set("rigidity", 100); 
                set("material", "steel");
                set("wield_msg", "$N嫵媚的從隨身荷包中取出一枚$n捏在手指間。\n");
                set("unwield_msg", "$N將手中的$n收回腰間荷包中。\n");
        }
        init_sword(40);
        setup();
}                

