#include <ansi.h>;
#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(CYN "鎮岳尚方" NOR, ({ "zhenyue shangfang", "zhenyue", 
                                              "jian", "sword" }));
        set_weight(8000);
        if (clonep())
//                destruct(this_object());
                                                set_default_object(__FILE__);
        else {
                set("long", CYN"
此劍乃周昭王瑕在位五十一年以二年歲次壬午，鑄五劍，各投
五岳，銘曰鎮岳尚方，古文篆書，劍長五尺通體流光。劍脊與
劍柄之上還鑄有無數密密麻麻的古篆，似乎與武學有關。\n" NOR);
                set("unit", "柄");
                set("value", 80000);
                                                                set("no_sell",1);
                set("material", "steel");
                set("wield_msg", CYN "$N" CYN "驀地縱聲長嘯，霎時寒"
                                 "芒一閃，一道金光破空劃過，落于$N"
                                 CYN "掌間。\n" NOR);
                set("unwield_msg", CYN "$N" CYN "一聲輕哼，將手中的"
                                   "寶劍插入劍鞘。\n" NOR);
                set("skill", ([
                        "name"         : "hengshan-sword",
                        "exp_required" : 300000,
                        "jing_cost"    : 40,
                        "difficulty"   : 30,
                        "max_skill"    : 150,
                        "min_skill"    : 50
                ]));

           //     set("stable", 100);
        }
        init_sword(160);
        setup();
}