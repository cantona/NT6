// xiezi.c

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("蠍子", ({ "scorpion" }));
        set("long", "一隻蠍子正虎視眈眈地盯著你。\n");

        set("race", "昆蟲");
        set("subrace", "爬蟲");
        set("age", 3);
        set("attitude", "peaceful");

        set("max_ging", 80);
        set("max_qi", 80);
        set("str", 10);
        set("cor", 50);

        set_temp("apply/attack", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        set("combat_exp", 1000);
        setup();
}

void init()
{
        object me,ob;
        ::init();
        if (interactive(me = this_player()))
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, me);
        }
}

int hit_ob(object me, object ob, int damage)
{
        if( query("combat_exp", ob)>10000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && 
                (int)ob->query_condition("scorpion_poison") < 10 )
        {
                ob->apply_condition("scorpion_poison", 20);
                tell_object(ob, HIG "你開始感到身體變得冰涼。！\n" NOR );
        }
}
