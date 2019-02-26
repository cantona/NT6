#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(RED"聖火令"NOR, ({ "shenghuo ling", "ling" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", 
                BLK"這是一枚聖火令，看起來黑黑的毫不起眼，上面密密麻麻刻滿了波斯文字。\n"NOR);
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N從懷裏掏出一枚$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n收回懷中。\n");
        }
        init_sword(100,2);
        setup();
}

