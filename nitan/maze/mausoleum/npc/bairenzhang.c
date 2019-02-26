#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void set_from_me(object me);
void create()
{
        string *names = ({ "陶俑百人長" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "bai renzhang", "bai" }));
        set("long", @LONG
這是一個沉睡在皇陵千年陶俑百人長，身高六尺有餘，由陶土燒製而成，看起來十分
堅硬。他手持一柄青銅長槍，神情頗為威武。在機關消息的作用下，他的四肢可以活
動，攻守進退也有模有樣，但總歸不算非常靈活。
LONG);
        set("title", YEL "皇陵六品護衞" NOR);

        set("str", 50);
        set("con", 50);
        set("dex", 50);
        set("int", 50);
        set("max_qi", 100000);
        set("max_jing", 100000);
        set("neili", 500000);
        set("max_neili", 500000);
        set("max_jingli", 100000);
        set("attitude", "killer");

        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N化成了一堆黃土。\n\n"NOR);

        set("rewards", ([
                "exp" : 200,
                "pot" : 50,
                "mar" : 5,
        ]));

        set_temp("apply/attack", 3000);
        set_temp("apply/parry", 3000);
        set_temp("apply/damage", 2000);
        set_temp("apply/unarmed_damage", 2000);
        set_temp("apply/armor", 3000);
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
