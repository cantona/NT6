#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void sp_attack();
void create()
{
        string *names = ({"骷髏武士"});

        ::create();
        set_name( names[random(sizeof(names))], ({ "skeleton fighter","skeleton", "fighter" }));
        set("long", "這是一隻骨頭架子。\n");
        set("title", HIB "(鬼氣)" NOR);

        set("str", 50);
        set("con", 120);
        set("dex", 22);
        set("int", 50);
        set("max_qi", 800000);
        set("max_jing", 500000);
        set("neili", 450000);
        set("max_neili", 450000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        /*
        set("chat_chance", 1);
        set("chat_msg", ({
                "骷髏空洞的眼眶裏閃爍着可怕的熒光。\n"
        }) );
        */
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: sp_attack :),
        }));

        set("combat_exp", 150000000);
        set("jiali", 5000);
        set("rewards", ([
                "exp" : 300,
                "pot" : 100,
                "mar" : 10,
        ]));
        //set("level", 20 );
        set("death_msg",BLU"\n$N散成了一堆碎骨頭。\n\n"NOR);
        set_temp("apply/attack", 2000+random(1000));
        set_temp("apply/unarmed_damage",2000+random(1000));
        set_temp("apply/armor", 2000+random(1000));
        set_temp("apply/reduce_damage", 60);
        setup();
        carry_object("/clone/weapon/changjian");
}

void set_from_me(object me)
{
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        set("jiali", query_skill("force") / 2);
}

void sp_attack()
{
        object *enemies, enemy;
        object weapon, ob;
        string msg;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies) == 0 )
                return;
        enemy = enemies[random(sizeof(enemies))];
        weapon = query_temp("weapon");
        if( objectp(weapon) ) weapon->unequip();
        if( objectp(ob = present("long sword", this_object())) ) {
                ob->wield();
                msg = HIB"$N雙眼突然發出強烈的藍光，令$n睜不開眼，$n感到一陣具痛。\n片刻後光芒散去，$n赫然發現$N的手中長劍正在滴血，\n"
                 "$n被$N使出一套失傳已久的古代劍法所傷！\n"NOR;
                message_vision(append_color(msg, HIB),this_object(),enemy);
                enemy->receive_damage("qi",2000+random(2000),this_object());
                COMBAT_D->report_status(enemy);
                ob->unequip();
                if( !enemy->is_busy() && random(2) )
                        enemy->start_busy(1);
        }
        if( objectp(weapon) ) weapon->wield();
        return;
}
