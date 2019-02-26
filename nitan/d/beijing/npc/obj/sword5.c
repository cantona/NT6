#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name( "東廠鑄劍",  ({ "dongchang jian", "dongchang", "jian" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄官府衞兵特用的長劍，劍脊上鑄有“東廠”二字。\n");
                set("value", 2000);
                set("material", "gold");
        }
        init_sword(20);
        setup();
}
