#include <ansi.h>
#include <armor.h>

inherit ARMOR;

// 組合物品，通過特殊故事殺死特殊npc後獲得
// 龍須2個 + 龍鱗10個 + 龍角2個 + 龍筋1根 + 赤龍之瞳2個 = 炎龍聖甲

void create()
{
        set_name(HIY "炎龍聖甲" NOR, ({ "yanlong shengjia", "yanlong", "shengjia" }));
        set_weight(6000);
        if (clonep())set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", HIY "\n一副充滿着神奇力量的聖甲，散發着奇異的光芒。\n" NOR
                            HIG "有效招架修正：+ 50        有效輕功修正：+ 30\n" NOR
                            HIG "抗毒效果修正：+ 25%       防禦效果等級： 180\n" NOR
                            HIG "抗毒迴避修正：+ 20%\n" NOR);
                set("value", 2000000);
                set("material", "dragon");

                set("material_name", "龍須、龍鱗、龍角、龍筋、赤龍之瞳");
                set("can_summon", 1);
                set("summon_id", "yanlongjia");
                set("ctype", "護甲");
                set("summon_wear_msg", HIY "剎那間，天空忽暗，風聲大作，一條炎龍騰空而來，\n"
                                "漸漸地化為一陣青煙，與$N" HIY 
                                "合為一體。\n" NOR);
                set("summon_remove_msg", HIY "風雨漸息，一條炎龍疼空而起，消失在天際。\n" NOR);
                set("armor_prop/armor", 180);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 25); // 提高30%抗毒效果
                set("armor_prop/avoid_poison", 20); // 提高20%迴避效果
                set("avoid_msg", HIG "剎那間，" HIY "炎龍聖甲" HIG "散發出"
                                             "一道奇異的光芒，將毒質全部吸收。\n" NOR);
                set("reduce_msg", HIR "剎那間，" HIY "炎龍聖甲" HIR "散發出"
                                             "一道奇異的光芒，吸收了部分毒質。\n" NOR);

        }
        setup();
}

int query_autoload()
{
        return 1;
}