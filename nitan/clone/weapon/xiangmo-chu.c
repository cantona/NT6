// weapon: xiangmo-chu.c
// Summer. 10/7/96

#include <ansi.h>
#include <weapon.h>
inherit F_UNIQUE;
inherit STAFF;

void create()
{
        set_name(HIY"降魔杵"NOR, ({ "xiangmo chu", "xiangmo","chu" }));
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", HIY"此杵頂呈蓮花狀，杵身長約兩尺，鴨蛋粗細，杵段尖銳鋒厲。是密宗喇嘛降妖伏魔的法器。\n"NOR);
                set("value", 7000);
                set("material", "steel");
                set("rigidity", 4000);
                set("wield_msg", HIY"一道金光在你眼前一閃，$N操出一根降魔杵，舉過頭頂，光茫萬照。\n"NOR);
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_staff(120);
        setup();
}


