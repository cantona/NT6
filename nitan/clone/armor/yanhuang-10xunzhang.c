
#include <armor.h>
#include <ansi.h>

inherit MEDAL3;

void create()
{
        set_name(HIY "炎黃風雨十年紀念勛章" NOR, ({ "yhhero year10", "yhhero", "year10" }));
        set("long", HIY "為紀念炎黃運營十周年，“風雨十年”活動特別限量發行的紀念勛章！\n" NOR);
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/year10", 1);
                set("armor_prop/damage", 4000);
                set("armor_prop/armor", 4000);
                set("armor_prop/force", 200);
                set("armor_prop/add_yanjiu_times", 100);
                set("special/desc", HIR "佩帶後可增加神龍島殺怪經驗及潛能獎勵5%\n"
                                        "                  額外提升100次研究次數\n"
                                        "                  有效內功提升200級" NOR);
                set("armor_prop/con", 40);
                set("armor_prop/dex", 40);
                set("armor_prop/str", 40);
                set("armor_prop/int", 40);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}