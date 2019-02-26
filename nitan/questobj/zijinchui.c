// bishuijian.c
// for 嶽靈珊

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(HIM"紫金錘"NOR, ({ "zijin chui", "chui", "hammer" }));
        set_weight(20000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long","這是一枚由海底金母鑄造而成的大錘，看上去紫\n光盈盈，顯得極是沉重。\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N振臂一揮, 掄出一枚沉重的$n。\n");
                set("unwield_msg", "$N將手中的$n慢慢收回。\n");
        }
        setup();
}
