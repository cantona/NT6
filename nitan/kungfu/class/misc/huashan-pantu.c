// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
	set_name(HIC "華山叛徒" NOR, ({ "huashan pantu", "huashan", "pantu" }) );
	set("title", HIY "華山派" NOR);
	set("gender", "男性");
	set("age", 28);
	set("long", @LONG
此人乃華山派弟子，由於偷學紫霞神功觸犯了門規，被華山派逐出師門。
LONG );
	set("combat_exp", 600000);
	set("shen_type", 0);
        set("max_neili", 3000);
        set("neili", 3000);
        set("max_jing", 5000);
        set("jing", 5000);
        set("max_qi", 100000);
	set("eff_qi", 100000);
        set("qi", 100000);
        set("jingli", 5000);
        set("max_jingli", 5000);
        set("level", 20);

	set("no_clean_up", 1);

	//set("no_nuoyi", 1); // 不被挪移影響

        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

	set_skill("unarmed", 100);
	set_skill("sword", 100);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	set_skill("force", 100);
	set_skill("cuff", 100);

	set_skill("huashan-neigong", 100);
	set_skill("huashan-sword", 100);
	set_skill("huashan-quan", 100);
	set_skill("huashan-shenfa", 100);

	map_skill("sword", "huashan-sword");
	map_skill("cuff", "huashan-quan");
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "huashan-jian");
	map_skill("force", "huashan-neigong");

	prepare_skill("cuff", "huashan-quan");

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.song" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :)
        }) );

        set("jiali", 10);

        set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 10000,
                "pot"   : 3000,
                "mar"   : 150,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM10"    :       100,   // 低級普通裝備
                "RA&RANDOM20"    :       40,    // 低級普通裝備
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/armor/fenghuang-chai"        :       30,
	        "FI&/clone/armor/haizhi-xin"            :       30,
	        "FI&/clone/armor/jinsi-beixin"          :       20,
		"FI&/clone/armor/longshen-toukui"       :       20,
                "FI&/clone/tessera/rune01"  :   1,
        ]));

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
	set_temp("born_time", time());
        if (clonep()) keep_heart_beat();
}

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(3 + random(6));
	me->receive_wound("qi", 100 + random(100), ob);
        return HIY "$N" HIY "大喝一聲，拼命反抗，竟逼得$n" HIY "手忙腳亂。\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(100) == 1)
		set("neili", query("max_neili"));

	::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N急急忙忙的走了。\n", this_object());

                CHANNEL_D->channel_broadcast("mess", env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")一帶出現的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("chat 不想我竟不容於天下武林，今日遭此一劫，悔恨終身 ...");
	CHANNEL_D->channel_broadcast("rumor", "聽説" + name() + HIM "被江湖人士所殺。" NOR);
}

varargs void die(object killer) 
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if( time() < query_temp("end_time") ) // 時間沒有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "大喝一聲，運用祕法，氣血有所回升！\n\n" NOR, this_object());
                return;
        }

        if (! objectp(killer))
                killer = query_last_damage_from();

        if( objectp(killer) && query("family/family_name", killer) == "華山派")
                set("rewards/gongxian", 300);

        return ::die();
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}
