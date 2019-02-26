#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + CYN "霜冷寶刀" NOR, ({ "shuangleng dao", "shuangleng", "dao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", NOR + CYN "刀柄上的小篆寫着：亮如霜雪，揮灑之間漫天銀雨。出鞘之時，無血不歸，十步之內，誰與爭鋒！。\n"
                                                      "此刀為炎黃非自造兵器寶刀排名第三位。\n" NOR);
                set("material", "steel");
                set("wield_msg", NOR + CYN "$n寒光一閃，已然出鞘。\n" NOR);
                set("unwield_msg", NOR + CYN "$n回鞘，天地頓時暗淡。\n" NOR);
                                set("value", 100000);
        }
        init_blade(800);
        setup();
}

int query_autoload()
{
        return 1;
}