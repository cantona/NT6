#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";
void do_swing();
void create()
{
        string *names = ({"屍煞"}); 
        // set_name( names[random(sizeof(names))], ({ "power zombie","zombie"}));
        set_name( names[random(sizeof(names))], ({ "power zombie" }));
        set("vendetta_mark","zombie");
        set("long", "這是一個腐爛的僵屍。\n");
        set("title", HIB "(鬼氣)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 50); 
        set("int", 50);
        set("max_qi", 80000);
        set("max_jing", 85000);
        set("neili", 350000);
        set("max_neili", 350000);
        set("max_jingli", 80000);
        set("attitude", "peaceful");
        //set("chat_chance", 2);
        //set("chat_msg", ({
        //                "骷髏空洞的眼眶裡閃爍著可怕的熒光。\n"
        //}) ); 

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: do_swing() :),
        }) ); 

        set("combat_exp", 150000000);
        set("bellicosity", 5 );
        set("death_msg",RED"\n$N化作了一灘血水。\n\n"NOR);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("unarmed", 120);
        set_skill("parry", 120);    
        set_temp("apply/attack", 1500);
        set_temp("apply/parry", 1500);
        set_temp("apply/unarmed_damage", 1600);
/*
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));
*/

        setup();
        //carry_object(__DIR__"obj/bone_finger");
} 

int is_undead() {
        return 1;
}

/*
int is_zombie() {
        return 1;
}
*/



void do_swing() {
        object *enemies,enemy;
        string msg;

        enemies = query_enemy();

        if(!enemies || sizeof(enemies)==0)
                return;

        msg = RED"$N一聲嚎叫，身子旋風般轉動起來！！\n"NOR;        
        message_vision(msg,this_object());
        addn_temp("apply/damage",400);
        addn_temp("apply/attack",400);
        foreach(enemy in enemies) {
                if(!enemy)
                        return;
                if(!present(enemy, environment(this_object())))
                return; 
                msg = RED"一道爪影襲向$n！"NOR;
                message_vision(msg,this_object(), enemy);
                COMBAT_D->do_attack(this_object(),enemy); 
        }
        addn_temp("apply/damage",-400);
        addn_temp("apply/attack",-400);
        
        if (this_object()->is_busy())
                this_object()->start_busy(2);
}
