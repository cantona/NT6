#include <ansi.h>
#include <armor.h>

inherit ARMOR;

// 組合物品，通過特殊故事殺死特殊npc後獲得
// □須2個 + □鱗10個 + □角2個 + □筋1根 + 赤□之瞳2個 = 炎□□甲

void create()
{
        set_name(HIY "炎□□甲" NOR, ({ "yanlong shengjia", "yanlong", "shengjia" }));
        set_weight(6000);
        if (clonep())set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", HIY "\n一副充滿著神奇力量的□甲，散發著奇異的光芒。\n" NOR
                            HIG "有效招架修正：+ 50        有效輕功修正：+ 30\n" NOR
                            HIG "抗毒效果修正：+ 25%       防御效果等級： 180\n" NOR
                            HIG "抗毒回避修正：+ 20%\n" NOR);
                set("value", 2000000);
                set("material", "dragon");

                set("material_name", "□須、□鱗、□角、□筋、赤□之瞳");
                set("can_summon", 1);
                set("summon_id", "yanlongjia");
                set("ctype", "護甲");
                set("summon_wear_msg", HIY "剎那間，天空忽暗，風聲大作，一條炎□騰空而來，\n"
                                "漸漸地化為一陣青煙，與$N" HIY 
                                "合為一體。\n" NOR);
                set("summon_remove_msg", HIY "風雨漸息，一條炎□疼空而起，消失在天際。\n" NOR);
                set("armor_prop/armor", 180);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 25); // 提高30%抗毒效果
                set("armor_prop/avoid_poison", 20); // 提高20%回避效果
                set("avoid_msg", HIG "剎那間，" HIY "炎□□甲" HIG "散發出"
                                             "一道奇異的光芒，將毒質全部吸收。\n" NOR);
                set("reduce_msg", HIR "剎那間，" HIY "炎□□甲" HIR "散發出"
                                             "一道奇異的光芒，吸收了部分毒質。\n" NOR);

        }
        setup();
}

int query_autoload()
{
        return 1;
}