#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void do_swing();
void set_from_me(object me);
void create()
{
        string *names = ({ "青銅狻猊" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "bronze ni", "bronze", "ni" }));
        set("long", @LONG
這是一個沉睡在皇陵青銅機關獸，身長丈許，肋生雙翅，爪利牙尖，更有飛天遁地之
能，道法神通均為獸族翹楚。在東方仙術的作用下，它的行動奇快，進退如風，再加
上毛皮刀槍不入，利爪快如刀刃，端的是極難對付。
LONG);
        set("title", HIR"機關獸" NOR);
        set("str", 150);
        set("con", 150);
        set("dex", 150);
        set("int", 150);
        set("max_qi", 2500000);
        set("max_jing", 1500000);
        set("neili", 2500000);
        set("max_neili", 2500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: do_swing :),
        }) );

        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N散落成一堆青銅。\n\n"NOR);

        set("rewards", ([
                "exp" : 500,
                "pot" : 120,
                "mar" : 20,
        ]));
        set_temp("apply/attack", 15000);
        set_temp("apply/parry", 15000);
        set_temp("apply/damage", 15000);
        set_temp("apply/unarmed_damage", 15000);
        set_temp("apply/armor", 20000);
        setup();
}

void init()
{
        object me;

        ::init();
        if( !interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
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

void do_swing()
{
        object *enemies,enemy;
        string msg;

        enemies = query_enemy();

        if( !enemies || sizeof(enemies)==0 )
                return;

        msg = HIW"$N口中突然多了件物事，似是一塊透明的布疋，若有若無，不知是什麼東西,向眾人吐去！\n"NOR;
        message_vision(msg,this_object());
        foreach( enemy in enemies ) {
                msg = HIW"$n突然間腳下一滑，撲地倒了，跟着身子便變成了一團。\n"NOR;
                message_vision(msg,this_object(), enemy);
                enemy->receive_damage("qi",10000+random(10000),this_object());
                COMBAT_D->report_status(enemy);
                if( !enemy->is_busy() && random(2) )
                        enemy->start_busy(2);
        }
}
