// beihai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("北海謫龍", ({ "king of dragon", "dragon" }) );
        set("title", HIC "龍族" NOR);
        set("gender", "男性");
        set("age", 23);
        set("long", @LONG
這是一個老人，眉目之間透出一股憂傷。
LONG );
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 20000);
        set("neili", 20000);
        set("max_jing", 20000);
        set("jing", 20000);
        set("max_qi", 25000);
        set("qi", 25000);
        set("jingli", 20000);
        set("max_jingli", 20000);

        set("str", 100);
        set("int", 30);
        set("con", 100);
        set("dex", 100);

        set_skill("unarmed", 1200);
        set_skill("sword", 1200);
        set_skill("parry", 1200);
        set_skill("dodge", 1200);
        set_skill("force", 1200);

        set("jiali", 200);

        set_temp("apply/attack", 300);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 1000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIC "$N" HIC "大怒，一聲暴喝，四周"
                       "登時雪花飄飄。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N似乎沒有聽見$n在説什麼。\n",
                       this_object(), ob);
        return 0;
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
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIC "$N" HIC "“哈”的一聲吐出一口寒氣，登時令$n"
               HIC "四肢幾乎凍僵。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        object ob;

        ob = new("/clone/tessera/rune11");
        command("chat 天哪！這年頭，看來是沒有我立足的地方了！");
        message_sort(HIC "$N" HIC "身子一旋，一陣冰雹忽然打來，待你睜眼，只聽叮玲玲一聲"
                     "輕響，掉下來一"+query("unit", ob)+
                     ob->name() + HIC "。\n" NOR, this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->channel_broadcast("rumor",
                        "聽説" + name() + HIM "在人間反省自新，遇"
                        "赦免返回天界。" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
