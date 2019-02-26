// longbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name("長弓", ({ "long bow", "bow", "chang gong", "gong" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", "一張長弓，打造得頗為精緻，具有相當好的準確度。\n");
                set("value", 80000);
                set("power", 180000);   // 攻擊威力
                set("accuracy", 150);   // 準確度150%
        }
        setup();
}