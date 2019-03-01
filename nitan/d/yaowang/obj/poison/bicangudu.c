// gudu.c

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + WHT "碧蠶蠱毒" NOR, ({ "bican gudu", "bican", "gudu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "這是一粒集百毒之精華煉制而成的毒藥，毒性猛烈之極。經過孔雀膽、鶴頂紅練制後無色無味，唯見效較緩!\n" NOR);
                set("base_unit", "粒");
                set("base_value", 200000);
                set("base_weight", 10);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 350,
                        "id"    : "yaowang",
                        "name"  : "碧蠶蠱毒",
                        "duration" : 22,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        message_vision("$N一仰脖，把碧蠶蠱毒全部倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了碧蠶蠱毒暴斃身亡了", me);
        me->die();

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

