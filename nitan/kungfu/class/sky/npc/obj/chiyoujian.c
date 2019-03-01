#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name( WHT "玄蚩神劍" NOR,  ({ "chiyou jian", "sword", "jian" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄玄鐵鑄造的長劍，劍柄上雕有蚩尤的頭像。\n");
                set("value", 100000);
                set("material", "gold");
                set("wield_msg", HIR "$N" HIR "抽出玄蚩神劍揮舞了個劍花，只感到一陣"
                                 NOR + HIW "寒氣" NOR + HIR "撲面而來。\n" NOR);
        }
        init_sword(200);
        setup();
}
