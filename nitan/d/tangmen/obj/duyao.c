// poison.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(50);
        set_name(HIG "唐門奇毒" NOR, ({"tangmen qidu", "du yao", "poison"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "這是一粒由唐門特殊祕方配置而成的毒藥，只要一丁點就可以置人於死地！\n");
                set("value", 50);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 1100,
                        "id"    : "tang du",
                        "name"  : "唐門奇毒",
                        "duration": 40,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，把唐門奇毒全部倒入了嘴中。\n",
                       me);
        set_temp("die_reason", "吃了唐門奇毒暴斃身亡了", me);
        me->die();
        destruct(this_object());
        return 1;
}
