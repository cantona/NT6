// This program is a part of NITAN MudLIB
// killer.c

#include <ansi.h>
inherit CLASS_D("generate") + "/chinese";

void create()
{

        mapping my;

        ::create();
        set("gender", "男性" );
        set("age", 30 + random(30));
        set_name(BLU "蒙面人" NOR, ({"figure", "mengmian ren", "ren"}));
        set("long", "這個人頭上戴著蒙面頭罩，八成準備幹什麼壞事。\n");
        set("attitude", "friendly");
        set("scale", 150);
        set("chat_chance_combat", 120);
        set_temp("apply/armor", 300);
        set_temp("apply/damage", 200);
        add_money("silver", 10 + random(20));

        if (clonep()) keep_heart_beat();
}

void set_from_me(object me, int scal)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();

        exp=query("combat_exp", me)*12/10;

        if (exp > query("combat_exp"))
                set("combat_exp", exp);

        my["jiali"] = query_skill("force") / 2;
}

void init()
{
        object me = this_player();

        ::init();
        if (interactive(me) && visible(me) &&
            ! is_fighting())
        {
                // NPC_D->set_from_me(killer, me, 100);
                kill_ob(me);
        }
}

int accept_fight(object me)
{
        return 0;
}

void kill_ob(object ob)
{
        if (! is_busy())
                exert_function("powerup");

        message_vision(HIB "$n對$N，喝道: “什麼人如此大膽，"+
                           "竟敢擅闖柳綠山莊？！\n" NOR, ob, this_object());
        ::kill_ob(ob);
}

void unconcious()
{
        message_vision(HIR "$N大叫一聲：好厲害！然後地板突然翻起，$N鑽了進去不見了。\n",
                       this_object());
        destruct(this_object());
        return ;
}

