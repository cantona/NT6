// Code of ShenZhou
// hulipi.c 狐貍皮

#include <ansi.h>

inherit ITEM;

int cure_ob(string);

void init();

void create()
{
        set_name("狐貍皮", ({ "huli pi", "pi" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張毛長寸許，柔軟光滑的狐貍皮。\n");
                set("value", 3000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        addn("food", 30, me);

        if ( (int)me->query_condition("bonze_drug" ) > 0 ){
                addn("max_jingli", -1, me);
                addn("eff_jingli", -1, me);
                set("jingli", 0, me);
                me->apply_condition("bonze_drug", 30);
                message_vision(HIR "$N吃下一張狐貍皮，只覺得肝腸寸斷，五臟欲裂，原來服食太多藥物，藥效適得其反！\n" NOR, this_player());
               // this_object()->move("/u/aln/workroom");
                call_out("destroy", 31);
                return 1;
        }

        if( !query_temp("cbs/hulipi", me)){
                addn_temp("apply/dex", 3, me);
                set_temp("cbs/hulipi", 1, me);
                me->start_call_out((:call_other,__FILE__,"remove_effect",me:),query("con", me));
        }

        addn("jingli", 300, me);
        me->apply_condition("bonze_drug", 
        me->query_condition("bonze_drug")+30);
        message_vision(HIY "$N吃下一張狐貍皮，只覺全身的精力都恢復了。\n" NOR, me);
        call_out("destroy", 31);
        return 1;
}

void remove_effect(object me)
{
        addn_temp("apply/dex", -3, me);
        delete_temp("cbs/hulipi", me);
}

void destroy()
{
        destruct(this_object());
}