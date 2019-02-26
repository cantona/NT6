#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name(NOR + MAG "紫蛟鱗甲" NOR, ({ "zijiao linjia", "zijiao", "linjia" }));
        set_weight(9000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", NOR + MAG "\n一副充滿着神奇力量的鱗甲，散發着攝人心魄的寒芒。\n" NOR
                            HIC "有效招架修正：+ 50        有效輕功修正：+ 30\n" NOR
                            HIC "抗毒效果修正：+ 30%       防禦效果等級： 200\n" NOR
                            HIC "抗毒迴避修正：+ 15%\n" NOR);

                set("material", "dragon");
                set("material_name", "紫蛟須、紫蛟皮革、紫蛟筋、地脈血泉");
                set("can_summon", 1);
                set("summon_id", "zijiaojia");
                set("ctype", "護甲");
                set("summon_wear_msg", NOR + MAG "剎那間，天地變色，雷聲大作，紫氣大盛，瀰漫四周。\n"
                                       "轉眼間，紫氣漸漸化作一條蛟龍，與$N" NOR + MAG "合為一體。\n" NOR);
                set("summon_remove_msg", NOR + MAG "雷聲漸息，紫氣漸散，天地恢復了平靜。\n" NOR);

                set("value", 3000000);
                set("armor_prop/armor", 200);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 30);
                set("armor_prop/avoid_poison", 15);
                set("avoid_msg", NOR + MAG "一道寒芒閃過，紫蛟鱗甲將毒質全部吸收。\n" NOR);
                set("reduce_msg", HIR "一道寒芒劃過，紫蛟鱗甲吸收了部分毒質。" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}