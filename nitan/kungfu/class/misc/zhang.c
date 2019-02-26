// zhang.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("張召重", ({ "zhang zhaozhong", "zhang", "zhaozhong" }) );
        set("title", "御林軍驍騎營佐領");
        set("nickname", HIR "火手判官" NOR);
        set("gender", "男性");
        set("age", 43);
        set("long", @LONG
張召重人稱“火手判官”，身材魁梧，留一叢短鬍子。江湖盛言“寧
挨一槍，莫遇一張”就是指他了。他熱衷功名利祿，投身朝廷，此人
辦事賣力，這些年來更是青雲直上。
LONG );
        set("combat_exp", 1800000);
        set("shen_type", -1);
        set("attitude", "heroism");
        set("max_neili", 5500);
        set("neili", 5500);
        set("max_jing", 250000);
        set("jing", 250000);
        set("max_qi", 50000);
        set("qi", 50000);

        set("str", 35);
        set("int", 32);
        set("con", 33);
        set("dex", 31);

        set_skill("unarmed", 2000);
        set_skill("sword", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("force", 2000);
        set_skill("taiji-shengong", 2000);
        set_skill("taiji-jian", 2000);
        set_skill("taiji-quan", 2000);
        set_skill("tiyunzong", 2000);
        set_skill("martial-cognize", 1000);
        set_skill("yinyang-shiertian", 2000);
        map_skill("dodge", "yinyang-shiertian");
        map_skill("force", "yinyang-shiertian");
        map_skill("sword", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");

        create_family("武當派", 13, "弟子");
        setup();

        set_max_encumbrance(2000000000);
        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 1000);
        set_temp("apply/damage", 1500);
        set_temp("apply/armor", 1500);

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/d/city/obj/tiejia")->wear();
}

void init()
{
        add_action("do_halt", "halt");
}

int do_halt()
{
        object me;

        if (this_player() == query_temp("catch_ob"))
        {
                write(name() + "喝道：“你還想在我面前逃走嗎？"
                      "乖乖的束手就擒吧！”\n");
                return 1;
        }

        return 0;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        if (ob != query_temp("catch_ob"))
        {
                message_vision("$N對$n大喝道：大膽！居然敢攻擊官差？找死麼？\n",
                               this_object(), ob);
                if (! ob->is_busy())
                        ob->start_busy(2);
        }

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N冷冷的對$n道：“我有公幹，你少來惹事！”。\n",
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

void start_catch(object ob)
{
        set_temp("catch_ob", ob);
        move(environment(ob));
        message_vision("$N走了過來，看到$n，冷笑了一聲。\n", this_object(), ob);
        command("chat " + ob->name(1) + "你為非作歹，官府已經下"
                "了海捕文書，你就乖乖的跟我回去吧！");
        command("follow"+query("id", ob));

        if( query("no_fight", environment(ob)) )
        {
                tell_object(ob, "你看到" + name() + "，不由大吃一驚，慌忙轉身逃走。\n");
                message("vision", ob->name() + "看到" + name() +
                        "，臉色大變，慌里慌張的轉身逃走。\n" +
                        name() + "冷笑一聲，喝道：“那裏走？”，緊隨其後追了上去。\n",
                        environment(ob), ({ ob }));
                ob->move("/d/city/guangchang");
                move("/d/city/guangchang");
                tell_object(ob, HIR "...這...這是哪裏？好熟悉啊？"
                            "你心底一橫，轉過身來，喝道：“不是魚死，就是網破，來吧！”。\n" NOR);
                message("vision", ob->name() + "慌慌張張的跑了過來，只見有一人"
                        "緊隨其後而來。\n", environment(ob), ({ ob }));
        }

        command("yun powerup");
        kill_ob(ob);
}

void catch_ob(object ob)
{
        remove_enemy(ob);
        message_vision("$N伸手把$n提拎了起來，喝道：“走吧！”\n",
                       this_object(), ob);
        ob->move(this_object());
        if (is_fighting())
        {
                // Am I in fighting now ?
                message_vision("$N冷冷道：“今天我要先回去交"
                               "差，你們幾個我改日再收拾！”\n",
                               this_object());
        }
        message_vision("$N拎着$n轉身離去。\n", this_object(), ob);

        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" +
                            ob->name(1) + HIM "因為妄殺無辜，現已被"
                            "火手判官張召重緝拿歸案，押入大牢。");
        ob->get_into_prison(0, "/d/changan/prison", 30);
        delete("combat/need_catch", ob);
        ob->clear_condition("killer");
        destruct(this_object());
        return;
}

int attack()
{
        object ob;

        if (objectp(ob = query_temp("catch_ob")) &&
            ! living(ob) &&
            environment(ob) == environment())
        {
                catch_ob(ob);
                return 1;
        } else
                return ::attack();
}

void unconcious()
{
        die();
}

void die()
{
        command("chat 天哪！我" + name() + "忠心耿耿，可是...不是我沒用，而是敵人太強大了。");
        message_vision(HIM "$N" HIM "狂吐幾口鮮血，扔下一個煙霧彈，"
                       HIM "藉着混亂逃走了。\n", this_object());
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

        if (! objectp(ob = query_temp("catch_ob")) ||
            environment(ob) != environment() ||
            query("no_fight", environment(ob)) )
        {
                message_vision("$N收住招式，悻悻道：“哼”，隨即轉身離去。\n",
                               this_object());
                destruct(this_object());
                return;
        }

        if (! living(ob))
        {
                catch_ob(ob);
                return;
        }

        if (! is_fighting(ob))
                fight_ob(ob);

        ::scan();
}
