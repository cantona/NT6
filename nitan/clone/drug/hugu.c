// Code of ShenZhou
// hugu.c 虎骨

#include <ansi.h>

inherit ITEM;

int cure_ob(string);

void init();

void create()
{
        set_name("虎骨", ({ "hu gu", "gu" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "這是一支老虎的脛骨，乃是極為珍貴的藥材。\n");
                set("value", 10000);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if( query("food", me) >= me->max_food_capacity() )
          return notify_fail("你已經吃太飽了，再也塞不下任何東西了。\n");
        else
 
        addn("food", 40, me);

        if ( (int)me->query_condition("bonze_drug" ) > 0 ){
                addn("max_jingli", -1, me);
                addn("eff_jingli", -1, me);
                set("jingli", 0, me);
                me->apply_condition("bonze_drug", 30);
                message_vision(HIR "$N吃下一支虎骨，只覺得肝腸寸斷，五臟欲裂，原來服食太多藥物，藥效適得其反！\n" NOR, this_player());
              //  this_object()->move("/u/aln/workroom");
                call_out("destroy", 31);
                return 1;
        }

        if( !query_temp("cbs/hugu", me)){
                addn_temp("apply/str", 3, me);
                set_temp("cbs/hugu", 1, me);
                me->start_call_out((:call_other,__FILE__,"remove_effect",me:),query("con", me));
        }

        me->receive_curing("qi", 200);
        set("qi",query("max_qi",  me), me);

        me->apply_condition("bonze_drug", 
        me->query_condition("bonze_drug")+30);
        message_vision(HIY "$N吃下一支虎骨，只覺得全身冒汗，爽快淋漓。\n" NOR, me);
        //this_object()->move("/u/aln/workroom");
        call_out("destroy", 31);
        return 1;
}

void remove_effect(object me)
{
        addn_temp("apply/str", -3, me);
        delete_temp("cbs/hugu", me);
}

void destroy()
{
        destruct(this_object());
}