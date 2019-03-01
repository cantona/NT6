#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(100);
        set_name(HIW "五聖散" NOR, ({"wusheng san", "wusheng", "san"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", HIW "這便是五毒教的獨門秘藥五聖散，可置人于死地。\n" NOR);
                set("value", 50);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 250,
                        "id"    : "he tieshou",
                        "name"  : "五聖散劇毒",
                        "duration": 20,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將五聖散倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了五聖散去見黑白無常了", me);
        me->die();
        destruct(this_object());
        return 1;
}