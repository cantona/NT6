#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name( WHT"玄鐵"NOR+HIW"匕首"NOR,  ({ "bi shou", "sword", "jian" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄玄鐵鑄造的匕首，鋒利無比。\n");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set("no_put", "這樣東西不能放在那兒。\n");
                set("no_steal", "這樣東西不能離開那兒。\n");
                set("no_beg", "這樣東西不能離開那兒。\n");
                set("no_sell", "凡人哪裡知道這神劍的厲害。\n");
                set("value", 100000);
                set("material", "gold");
                set("wield_msg", HIR"$N抽出一柄寒氣逼人的"NOR+WHT"玄鐵"NOR+HIW"匕首"NOR+HIR"拿在手中，只感到一陣"NOR+HIW"寒氣"NOR+HIR"撲面而來。\n"NOR);
                set("unwield_msg", HIR"$N將手中的"NOR+WHT"玄鐵"NOR+HIW"匕首"NOR+HIR"插回靴中。\n"NOR);
        }
        init_sword(200);
        setup();
}
