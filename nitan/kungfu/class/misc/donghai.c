// donghai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("東海三太子", ({ "prince of dragon", "dragon", "san taizi" }) );
        set("title", HIG "龍族" NOR);
        set("gender", "男性");
        set("age", 23);
        set("long", @LONG
這是一個神採奕奕的年輕人，風度翩翩，氣宇軒昂。
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

        message_vision(HIW "$N" HIW "冷哼一聲，一股雲氣自身後"
                       "升起，似真似幻。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N掃了$n一眼，沒有理$n。\n",
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
        return HIY "$N" HIY "身上閃過一道電光，登時令$n"
               HIY "渾身麻木，手腳酸軟。\n" NOR;
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
                "/clone/fam/etc/longjiao",
                "/clone/fam/etc/longjin",
                "/clone/fam/etc/longlin",
                "/clone/fam/etc/longxu",
        });
        str = prize[random(sizeof(prize))];
        ob = new(str);
        command("chat 呀！想不到凡人也有如此厲害的！");
        message_sort(HIR "$N" HIR "吐一口鮮血，駕雲而去。只聽叮玲玲一聲"
                     "輕響，$N"HIR"\n掉下了一"+query("unit", ob)+
                     ob->name() + HIR "。\n", this_object());

        if (objectp(killer)) set("who_get", ([ "id"    : query("id", killer),
                                               "time"  : time() + 60]), ob); // 60秒內只允許殺死我的ID揀

        ob->move(environment());
        // 帝王符圖
        // 編號32
        if (random(10) == 1)
        {
                int n_tt;
                object ob_tt;
                n_tt = 32;
                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                if (ob_tt)
                {
                        write(HIG "叮~~一張帝王符圖碎片落在地上。\n" NOR);
                        ob_tt->move(environment());
                }
        }

        // 1/600幾率掉出無名銅人
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
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->channel_broadcast("rumor",
                        "聽說" + name() + HIM "修煉良久，元氣恢復，"
                        "已經安然返回神界。" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
