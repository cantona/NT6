#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIG "無名劍" NOR, ({ "wuming jian", "wuming", "jian" }) );
        set_weight(28000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIG "此劍長約四尺，青光閃閃，似是利器。\n乃劍魔獨孤求敗年輕時所持。\n" NOR);
                set("unit", "柄");
                set("value", 8000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIG "$N" NOR + WHT "抽出$n" NOR + WHT"，負手而立，一派宗師風範。\n" NOR);
                set("unwield_msg", HIG "$N" NOR + WHT "清嘯一聲，彈指間，將$n" NOR + WHT "收回。\n" NOR);
                set("stable", 100);
        }
        init_sword(80);
        setup();
}