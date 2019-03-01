#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(100);
        set_name(HIM "腐肉膏" NOR, ({"furou gao", "furou", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", HIM "這是一盒五彩斑斕的劇毒藥膏，可殺人于無形。\n" NOR);
                set("value", 50);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                        "id"    : "he tieshou",
                        "name"  : "腐肉膏劇毒",
                        "duration": 15,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將腐肉膏倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了腐肉膏去見黑白無常了", me);
        me->die();
        destruct(this_object());
        return 1;
}