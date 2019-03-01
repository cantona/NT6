// Code of ShenZhou
// guiyuan.c 歸元丹
// Ryu
// Modified by xQin to forbid the abuse of gyd

inherit PILL;
#include <ansi.h>
void setup()
{}
void init();
void wear(int);

int worn;

int cure_ob(string);
void create()
{
        set_name("歸元丹", ({"guiyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆瑩白溜圓的歸元丹。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        addn("neili", -200, this_player());
        message_vision(HIR "$N吃下一棵歸元丹，只覺得頭重腳輕，火氣翻騰，原來服食過猛，藥效適得其反！\n" NOR, this_player());
        this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);
        destruct(this_object());
        return 1;
}

void init()
{
        worn = 0;
        call_out("wear", 1200, 1);

        add_action("do_pour", "drop");
}



void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", "這是一粒擱了很長時間的歸元丹。\n");
                call_out("wear", 300, phase+1);
                break;
        case 2:
                set("long", "這是一粒已經不太成形的歸元丹，快被風化了。\n");
                call_out("wear", 100, phase+1);
                break;
        case 3:
                destruct(this_object());
                break;
        }
}
int effect_in_liquid(object ob)
{
        object me = this_player();
        if (this_player()->query_condition("bonze_drug" ) > 0 )
        {        
        addn("neili", -50, me);
        message_vision(HIR "$N喝下一口藥酒，發現原來體內藥性過猛，適得其反。\n" NOR, this_player());
        this_player()->apply_condition("bonze_drug",
        this_player()->query_condition("bonze_drug")+10);
        return 1;
        }
        
        if( query("neili", this_player())>query("max_neili", this_player())*2 )
        set("neili",query("max_neili",  this_player())*2-1, this_player());
        if( query("liquid/type", ob) == "alcohol" && !query("zuixian", ob)){
        tell_object(this_player(), HIG"你只覺得體內真力源源滋生，不絕如縷。\n"NOR);
        addn("neili", random(10)+10*query("liquid/drunk_apply", ob), this_player());
        me->apply_condition("bonze_drug", 30);
        return 1;
        }
}