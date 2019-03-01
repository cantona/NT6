#include <ansi.h>
inherit NPC;
string *first_name = ({ "沙", "塵"});
string *first_id = ({ "sha", "ash"});
string *name_words = ({ "蠍", "魔"});
string *id_words = ({ "xie", "mo"});
int combatpower();

void create()
{
        string name;
        int i, j;

        i = random(sizeof(first_name));
        name = first_name[i];
        j = random(sizeof(name_words));
        name += name_words[j];

        set_name(name, ({ first_id[i]+" "+id_words[j] }) );
        // random_name_color(this_object());

        set("age", 20);
        set("vrm_guard", 1);
        set("attitude", "aggressive");

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 25000000);
        set("level", 25);
        set("qi", 500000);
        set("max_qi", 500000);
        set("jing", 250000);
        set("max_jing", 250000);
        set("neili", 1000000);
        set("max_neili", 1000000);
        set("jiali", 5000);

        set_skill("unarmed", 2500);
        set_skill("dodge", 2500);
        set_skill("parry", 2500);
        set_skill("force", 2500);


        set_temp("apply/attack", 2500+random(2500));
        set_temp("apply/unarmed_damage",2500+random(2500));
        set_temp("apply/armor", 2500+random(2500));

        set("drops", ([
                "RA&RANDOM20"    :       100,   // 低級普通裝備
                "RA&RANDOM30"    :       30,    // 中級普通裝備
                "MO&A1000"       :       1,
                "MO&A1001"       :       1,
                "MO&A1002"       :       1,
                "MO&A1003"       :       1,
                "MO&A1004"       :       1,
                "MO&A1005"       :       1,
        ]));

        //set_weight(500000);
        setup();

}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;

        damage = 400 + random(400);
        damage-=query_temp("apply/reduce_cold", ob);
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIC "$N" HIC "“呼”的一聲吹出一陣黃沙，登時令$n"
               HIC "猶如千針加身。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}

