//jiuhuawan.c
#include <ansi.h>
inherit ITEM;
void setup()
{}
void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}
void create()
{
        set_name(HIG"九花玉露丸"NOR, ({"jiuhuayulu wan", "jiuhua wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("vegetable", 54);
                set("nostrum", 38);
                set("level", 120);
                set("long", "這是一顆晶瑩碧綠的九花玉露丸，經桃花島主精心練制，
有起死回生之功。\n");
                set("value", 50000);
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int fw;
        object me = this_player();

        if (!id(arg))  return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");
        if (me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) )
        {
                write("沒傷沒病的，別浪費這麼珍貴的藥啦。\n");
                return 1;
        }

        fw = (int)me->max_food_capacity();
//        me->set("food", fw);
        fw = (int)me->max_water_capacity();
//        me->set("water", fw);
         set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        set("tili",query("max_tili",  me), me);
        message_vision(HIG "$N吃下一顆九花玉露丸，一股清新涼爽從丹田升起，向全身擴散！\n"NOR,me);
        me->start_busy(1);
        destruct(this_object());
        return 1;
}
