#include <ansi.h>
#include <combat.h>
inherit "/maze/necropolis/necropolis_npc";
void create()
{
        string *names = ({"骷髏武士"}); 
        // set_name( names[random(sizeof(names))], ({ "skeleton fighter","skeleton"}));
        set_name( names[random(sizeof(names))], ({ "skeleton fighter" }));
        set("vendetta_mark","skeleton");
        set("long", "這是一只骨頭架子。\n");
        set("title", HIB "(鬼氣)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("max_qi", 80000);
        set("max_jing", 85000);
        set("neili", 450000);
        set("max_neili", 450000);
        set("max_jingli", 50000);
        set("attitude", "peaceful");
        //set("shen_type", -1);        
/*
        set("chat_chance", 1);
        set("chat_msg", ({
                "骷髏空洞的眼眶裡閃爍著可怕的熒光。\n"
        }) ); 
*/

        set("combat_exp", 150000000);
        set("bellicosity", 5 );
               set("death_msg",BLU"\n$N散成了一堆碎骨頭。\n\n"NOR); 
        set_skill("force", 60);
        set_skill("dodge", 60);
        set_skill("unarmed", 60);
        set_skill("sword", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 1000);
        set_temp("apply/parry", 500);
        set_temp("apply/damage", 500);
/*
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));
*/
        setup();
        carry_object(__DIR__"obj/bone_sword")->wield();
} 

int is_undead() {
        return 1;
}
