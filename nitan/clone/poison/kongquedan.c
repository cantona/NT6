#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(100);
        set_name(GRN "孔雀膽" NOR, ({"kongque dan", "kongque", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "瓶");
                set("long", GRN "這是一瓶碧綠色的劇毒粉末，可殺人於無形。\n" NOR);
                set("value", 50);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                        "id"    : "he tieshou",
                        "name"  : "孔雀膽劇毒",
                        "duration": 15,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將孔雀膽倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了孔雀膽去見黑白無常了", me);
        me->die();
        destruct(this_object());
        return 1;
}