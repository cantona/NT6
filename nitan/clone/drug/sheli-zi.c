// Code of ShenZhou
// sheli-zii.c 舍利子

#include <ansi.h>

inherit ITEM;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name("舍利子", ({"sheli zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆活佛坐化的舍利子，小指尖大小，色泛灰白，隱隱有寶光流動。\n");
                set("no_drop","這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        int add_skill, improve, add;

        add = 10+random(20);
        
        if ( (int)me->query_condition("bonze_drug" ) > 0 ){
                addn("max_jingli", -add, me);
                addn("eff_jingli", -add, me);
                me->apply_condition("bonze_drug", 80);
        message_vision(HIR "$N吃下一顆舍利子，只覺得肝腸寸斷，五臟欲裂，原來服食太多藥物，藥效適得其反！\n" NOR, this_player());
        me->unconcious();
        destruct(this_object());
        }
        else {
                message_vision(HIY "$N吃下一顆舍利子，油然間只覺腦袋裏注進了一縷清新之氣...\n" NOR, this_player());
                addn("max_jingli", add, me);
                addn("eff_jingli", add, me);
                me->apply_condition("bonze_drug", 80);
        }
        me->unconcious();
        destruct(this_object());
        return 1;
}
