// heisuo.c  黑索□
#include <ansi.h>
#include <weapon.h>
inherit WHIP;

void create()
{
        set_name(BLK"黑索"NOR, ({ "heisuo", "bian" }));
        set_weight(500);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根長索，通體黝黑無光，舞動之時瞧不見半點影子。\n");
                set("value", 0);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一條$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n卷回腰間。\n");
        }
        setup();
}