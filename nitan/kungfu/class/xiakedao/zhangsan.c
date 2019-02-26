// zhangsan.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("張三", ({ "zhang san", "zhang", "san" }));
        set("title", HIY "俠客島賞善使者" NOR);
        set("gender", "男性");
        set("age", 37);
        set("long",
              "這是個看起來三十來歲的漢子，身材肥胖，臉色紅潤。\n"
        );

        set("str", 1000);
        set("int", 1000);
        set("con", 1000);
        set("dex", 500);

        set_temp("apply/attack", 2000);
        set_temp("apply/armor", 1500);
        set_temp("apply/damage", 800);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/dodge", 600);
        set_temp("apply/parry", 600);

        set("qi", 900000);
        set("max_qi", 900000);
        set("jing", 2000000);
        set("max_jing", 2000000);
        set("neili", 1500000);
        set("max_neili", 1500000);
        set("jiali", 2500);
        set("combat_exp", 500000000);
        set("score", 20000000);

        set_skill("force", 1000);
        set_skill("taixuan-gong", 1000);
        set_skill("dodge", 1000);
        set_skill("taixuan-gong", 1000);
        set_skill("unarmed", 1000);
        set_skill("taixuan-gong", 1000);
        set_skill("parry", 1000);
        set_skill("martial-cognize", 5000);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        map_skill("parry", "taixuan-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "unarmed.taixuan" :),
        }) );
        create_family("俠客島", 0, "賞善使者");
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void start_punish(object ob, string msg)
{
        set_temp("punish_ob", ob);
        move(environment(ob));
        message_vision("$N走了過來，冷冷的盯着$n。\n", this_object(), ob);
        command("chat " + ob->name() + "，你" + msg);
        command("chat " + "今天我" + name() + "要為武林除去此害！");
        command("follow"+query("id", ob));

        if( query("no_fight", environment(ob)) )
        {
                tell_object(ob, "你看着" + name() + "的眼神，心中不禁一寒，轉身逃走。\n");
                message("vision", ob->name() + "看到" + name() + "，臉色忽變，轉身逃走。\n" +
                        name() + "冷笑一聲，緊隨其後而走。\n",
                        environment(ob), ({ ob }));
                ob->move("/d/city/guangchang");
                move("/d/city/guangchang");
                tell_object(ob, HIR "...這...這是哪裏？好熟悉啊？"
                            "你心底一橫，轉過身來，索性不再走了。\n" NOR);
                message("vision", ob->name() + "慌慌張張的跑了過來，只見有一人"
                        "緊隨其後而來。\n", environment(ob), ({ ob }));
        }

        kill_ob(ob);
        command("yun powerup");
        tell_object(ob,"你突然天旋地轉，冥冥中似乎有股力量在操縱你的命運!\n");
        ob->unconcious();
}

void killed_enemy(object victim)
{
        command("chat 嘿嘿，你也有這一天，這就叫善有善報、惡有惡報，不是不報，時辰未到。");
        delete("combat/need_punish", victim);
}

varargs int receive_damage(string type, int damage, object who)
{
        return ::receive_damage(type, damage / 100, who);
}

varargs int receive_wound(string type, int wound, object who)
{
        return ::receive_wound(type, wound / 100, who);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 1000 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "輕吐一口氣，掌力襲來，震得$n"
               HIR "接連退後幾步，悶哼一聲。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        object ob;

        ob = query_temp("punish_ob");
        if (objectp(ob) && ob == query_last_damage_from())
                delete("combat/need_punish", ob);

        command("chat 天哪！想不到我" + name() + "除害不成...反被害除...先回去練功去！");
        message_vision(HIM "$N" HIM "狂吐幾口鮮血，扔下一個煙霧彈，"
                       HIM "趁着混亂逃走了。\n", this_object());
        destruct(this_object());
}

void scan()
{
        object ob;

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        if (! objectp(ob = query_temp("punish_ob")) ||
            environment(ob) != environment() ||
            query("no_fight", environment(ob)) )
        {
                command("chat 今天我先走了，改日再來玩玩兒！");
                message_vision("$N哈哈大笑，飄然而去。\n", this_object());
                destruct(this_object());
                return;
        }

        if (! is_fighting(ob))
                kill_ob(ob);

        ::scan();
}
