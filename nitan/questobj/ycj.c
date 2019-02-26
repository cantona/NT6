// Last Modified by winder on Nov. 17 2000

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
void create()
{
        set_name(HIC"魚腸劍"NOR, ({"yuchang jian","jian"}) );
        set_weight(10000);
        set("taskobj", 1);
        set("unit", "柄");
        set("long", "這就是傳説中的魚腸劍。劍身細長，看上去異常鋒利。\n");
        set("value",0);
        set("material", "steel");
        set("wield_msg", HIB "嗤地一聲，$n"HIB"已在$N手中，周遭頓時瀰漫冷冷的殺氣。\n" NOR);
        set("unwield_msg", HIG "$N一揚手，$n"HIG"已入鞘。無聲無息，卻暗藏殺機。\n" NOR);
        setup();
}
