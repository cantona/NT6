// niutou.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("牛頭怪", ({ "niutou guai", "niutou" }) );
        set("title", HIY "魔族" NOR);
        set("gender", "男性");
        set("age", 58);
        set("long", @LONG
這是一個滿臉殺氣的惡漢，兩眼直露兇光。
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

        message_vision(HIR "$N" HIR "口中呵呵作響，兩眼中"
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
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "身上騰起一股火燄，登時逼得$n"
               HIR "退後幾步，悶哼一聲。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        object ob;

        ob = new("/clone/tessera/rune09");
        command("chat 呀！想不到凡人也有如此厲害的！");
        message_sort(HIR "$N" HIR "吐一口鮮血，身邊湧現出一股黑煙，只聽叮玲玲一聲"
                     "輕響，$N"HIR"掉下了一"+query("unit", ob)+
                     ob->name() + HIR "。\n", this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->channel_broadcast("rumor",
                        "聽說" + name() + HIM "找上花果山水簾洞，慘"
                        "遭猴兵戲辱，已經逃回火燄山。" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
