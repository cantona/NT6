// Code of ShenZhou
// yangxin.c 養心丸

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
        set_name("養心丸", ({"yangxin wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆暗紅發亮的養心丸。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        message_vision(HIR "$N吃下一棵養心丹，只覺得頭重腳輕，火氣翻騰，原來服食過猛，藥效適得其反！\n" NOR, this_player());
        addn("jingli", -200, this_player());
        this_player()->apply_condition("bonze_drug", 
                this_player()->query_condition("bonze_drug")+10);
        destruct(this_object());
        return 1;
}

void init()
{
//        worn = 0;
 //       call_out("wear", 1200, 1);
        add_action("do_pour", "drop");
}



void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", "這是一粒擱了很長時間的養心丸。\n");
                call_out("wear", 300, phase+1);
                break;
        case 2:
                set("long", "這是一粒已經不太成形的養心丸，快被風化了。\n");
                call_out("wear", 100, phase+1);
                break;
        case 3:
                destruct(this_object());
                break;
        }
}
int effect_in_liquid(object ob)
{
        if( query("liquid/type", ob) == "alcohol"){
        tell_object(this_player(), HIG"你只覺得一股熱氣自丹田冒出，混身上下有説不出的通泰。\n"NOR);
        addn("jingli", random(10)+10*query("liquid/drunk_apply", ob), this_player());
        if( query("neili", this_player())>query("max_neili", this_player())*2 )
        set("neili",query("max_neili",  this_player())*2-1, this_player());
        }
        return 0;
}