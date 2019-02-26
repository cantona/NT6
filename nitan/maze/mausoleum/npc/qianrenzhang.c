#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void set_from_me(object me);
void create()
{
        string *names = ({ "陶俑千人長" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "qian renzhang", "qian" }));
        set("long", @LONG
這是一個沉睡在皇陵千年陶俑千人長，身高七尺有餘，由陶土燒製而成，看起來十分
堅硬。他手持一柄青銅巨錘，神情頗為威武。在機關消息的作用下，他的四肢可以活
動，攻守進退也有模有樣，但總歸不算非常靈活。
LONG);
        set("title", YEL"皇陵四品護衞" NOR);

        set("str", 80);
        set("con", 80);
        set("dex", 80);
        set("int", 80);
        set("max_qi", 1000000);
        set("max_jing", 500000);
        set("neili", 500000);
        set("max_neili", 500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);

        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N化成了一堆黃土。\n\n"NOR);

        set("rewards", ([
                "exp" : 250,
                "pot" : 70,
                "mar" : 10,
        ]));
        set_temp("apply/attack", 5000);
        set_temp("apply/parry", 5000);
        set_temp("apply/damage", 5000);
        set_temp("apply/unarmed_damage", 5000);
        set_temp("apply/armor", 5000);
        setup();
}

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) ||
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
