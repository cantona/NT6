#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name(HIR "鳳凰披風" NOR, ({ "fenghuang pifeng", "fenghuang", "pifeng" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIR"\n一件用鳳凰羽毛織成的披風，乃稀世珍。\n" NOR
                            HIC "有效招架修正：+ 20        有效輕功修正：+ 30\n" NOR
                            HIC "抗毒效果修正：+ 15%       防御效果等級：  70\n" NOR
                            HIC "抗毒回避修正：+ 15%\n" NOR);

                set("material", "phoenix");
                set("material_name", "朱雀羽毛、朱雀之角、朱雀筋、五彩玲瓏珠");
                set("can_summon", 1);
                set("summon_id", "fenghuangjia");
                set("ctype", "披風");
                set("summon_wear_msg", HIR "剎那間，一股火燄從地心騰射而出，直沖天際，\n"
                                       "轉眼間，火燄漸漸化作一只火鳳凰，與$N" HIR "合為一體。\n" NOR);
                set("summon_remove_msg", HIR "只聽得一聲長嘶，一只巨大的火鳳凰消失與天際。\n" NOR);

                set("value", 4500000);
                set("armor_prop/armor", 50);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 20);
                set("armor_prop/reduce_poison", 15);
                set("armor_prop/avoid_poison", 15);
        }
        setup();
}

int query_autoload()
{
        return 1;
}