// niutou.c

#include <ansi.h>
#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"

inherit NPC;

void create()
{
        set_name("魔君", ({ "mo jun", "fiend", "mo", "jun" }) );
        set("title", HIY "魔族" NOR);
        set("gender", "男性");
        set("age", 58);
        set("long", @LONG
這是一個滿臉殺氣的惡魔，兩眼直露兇光。
LONG );
        set("combat_exp", 500000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 1000000);
        set("neili", 1000000);
        set("max_jing", 1000000);
        set("jing", 1000000);
        set("max_qi", 20000000);
        set("qi", 20000000);
        set("jingli", 10000000);
        set("max_jingli", 10000000);
        set("jiali", 10000);

        set("str", 500);
        set("int", 100);
        set("con", 500);
        set("dex", 500);

        set_skill("unarmed", 2000);
        set_skill("sword", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("force", 2000);
        
        set_temp("apply/attack", 2000);
        set_temp("apply/unarmed_damage", 2000);
        set_temp("apply/armor", 5000);

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIR "$N" HIR "怒吼一聲，兩眼中"
                       "兇光畢露。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N一陣狂叫，猛然撲了上來。\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 10000 + random(10000), me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "身上騰起一股火燄，登時逼得$n"
               HIR "退後幾步，悶哼一聲。\n" NOR;
}

varargs void die(object killer)
{
        object me;
        int i;

        me = this_object();

        if( !killer ) killer = me->query_last_damage_from();
        if( objectp(killer) )
        {
                BATTLEFIELD2_D->add_killnpc_score(killer, 1);
        }

        ::die(killer);
}

