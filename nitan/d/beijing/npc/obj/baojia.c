#include <ansi.h>
#include <armor.h>
inherit ARMOR;
void create()
{
        set_name( CYN"真絲"NOR+HIY"寶甲"NOR,  ({ "bao jia", "jia", "armor" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "一見黑黝黝的甲，毫不起眼。\n");
                /*
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set("no_put", "這樣東西不能放在那兒。\n");
                set("no_steal", "這樣東西不能離開那兒。\n");
                set("no_beg", "這樣東西不能離開那兒。\n");
                */
                set("no_sell", "這樣東西不能賣。\n");
                set("value", 100000);
                set("material", "cloth");
                set("armor_prop/armor", 200);
        }
        setup();
}

