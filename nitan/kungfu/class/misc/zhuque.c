// nanhai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIR "朱雀" NOR, ({ "fire phoenix", "phoenix", "fenghuang" }) );
        set("title", HIR "鳳族" NOR);
        set("gender", "女性");
        set("age", 20);
        set("long", @LONG
這是一隻巨大的火鳳凰，渾身燃燒着熊熊的烈火，不時發出一兩聲撕心裂肺的怪叫。
LONG );
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 220000);
        set("neili", 220000);
        set("max_jing", 180000);
        set("jing", 180000);
        set("max_qi", 100000);
        set("qi", 100000);
        set("jingli", 120000);
        set("max_jingli", 120000);

        set("str", 60);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set_skill("unarmed", 1000);
        set_skill("sword", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);

        set("jiali", 400);

        set_temp("apply/attack", 800);
        set_temp("apply/unarmed_damage", 600);
        set_temp("apply/armor", 300);

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

        message_vision(HIR "$N一聲長嘶，渾身火焰四射，"
                       "令人心膽聚裂。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N一聲長嘶，撲了上來。\n",
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
        ob->receive_wound("qi", 160 + random(170), me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "周圍火焰爆漲，電光四射，登時令$n"
               HIR "痛苦不堪，難以忍受。\n" NOR;
}

void unconcious()
{
        die();
}

varargs void die(object killer)
{
        object ob;
        string str;
        string* prize = ({
                "/clone/fam/etc/zhuquejiao",
                "/clone/fam/etc/zhuquejiao",
                "/clone/fam/etc/zhuquejin",
                "/clone/fam/etc/yumao",
        });

        // 鳳凰重生
        if( !query("is_die", this_object()) )
        {
                message_vision(HIR "\n$N" HIR "一聲長嘶，地動山搖，猛然間，周身火焰沖天，$N"
                         HIR "騰空而起，在半空中盤旋着，隨即又回到了原地。\n" NOR, this_object());

                this_object()->start_busy(2 + random(5));

                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + name() + HIM "衝出地獄，獲得了重生。\n" NOR);

                set("max_neili", 220000);
                set("neili", 220000);
                set("max_jing", 180000);
                set("jing", 180000);
                set("eff_jing", 180000);
                set("max_qi", 340000);
                set("qi", 340000);
                set("eff_qi", 340000);
                set("jingli", 120000);
                set("max_jingli", 120000);

                set("str", 100);
                set("int", 100);
                set("con", 100);
                set("dex", 200);

                set_skill("unarmed", 1800);
                set_skill("sword", 1800);
                set_skill("parry", 1800);
                set_skill("dodge", 1800);
                set_skill("force", 1800);

                addn("is_die", 1);
                return ;
        }

        str = prize[random(sizeof(prize))];
        ob = new(str);
        command("chat 啊呀！人間居然有人能打敗我，待我回到火焰山再修煉千年再説！");
        message_sort(HIR "$N" HIR "身子一扭，鑽入地心，"
                     "只聽叮玲玲的一聲，從$N" HIR "身上掉下了一" +
                     query("unit", ob)+ob->name()+
                     HIR "。\n" NOR, this_object());

        if (objectp(killer)) set("who_get", ([ "id"    : query("id", killer),
                                               "time"  : time() + 60]), ob); // 60秒內只允許殺死我的ID揀
        ob->move(environment());

        // 帝王符圖
        // 編號34
        if (random(10) == 1)
        {
                int n_tt;
                object ob_tt;
                n_tt = 34;
                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                if (ob_tt)
                {
                        write(HIG "叮~~一張帝王符圖碎片落在地上。\n" NOR);
                        ob_tt->move(environment());
                }
        }

        // 1/600機率掉出無名銅人
        if (random(600) < 1)
        {
                object ob_tongren;
                ob_tongren = new("/clone/tongren/tongren" + (1 + random(2)));
                message_vision(HIR "當~~一聲，從$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time() + 30, ob_tongren); // 30秒內都不能撿取
                ob_tongren->move(environment(this_object()));
        }
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 2400)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->channel_broadcast("rumor",
                        "聽説" + name() + HIM "覺得人間氣候惡劣，水土不服，終於又回到了火焰山。" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
