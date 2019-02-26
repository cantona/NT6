// This program is a part of NT MudLIB
// weishi.c

inherit NPC;

#include <ansi.h>
#include "/kungfu/class/wudang/auto_perform.h"

int auto_perform();

#define CANPIAN "/kungfu/class/wudang/obj/canpian"

string do_huqi();

void create()
{
        object zhenwu;

        set_name("武士", ({ "wu shi", "shi" }));
        set("long","這是位武士，身披鋼甲，手執長劍，雙目精光炯炯，警惕地巡視着四周的情形。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "heroism");
        set("shen_type", 0);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 1123);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("max_jingli", 3000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);
        set("combat_exp", 6400000);

        set_skill("force", 200);
        set_skill("taiji-shengong", 200);
        set_skill("dodge", 200);
        set_skill("tiyunzong", 200);
        set_skill("cuff", 200);
        set_skill("taiji-quan", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("taiji-jian", 200);
        set_skill("taoism", 200);
        set_skill("literate", 200);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");

        prepare_skill("cuff", "taiji-quan");

        create_family("武當派", 2, "");

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: auto_perform :),
        }) );

        set("inquiry", ([
                "護旗": (: do_huqi :),
                "huqi": (: do_huqi :),
        ]));


        setup();
        if( clonep() )
        {
                carry_object("/d/city/obj/gangjian")->wield();
                carry_object("/d/city/obj/tiejia")->wear();
        }
}


void attempt_apprentice(object ob)
{
        return;
}

int accept_kill(object obj)
{
        object me = this_object();
        mapping skill_status;
        string *sname;
        int i, max = 200;

        command("say "+RANK_D->query_rude(obj)+"居然還想殺死我！看招！");

        if( !objectp(query_temp("weapon", obj)) || !objectp(query_temp("weapon", me)) )
        {
                command("unwield sword");
                command("enable parry taiji-quan");
        }
        else if( objectp(query_temp("weapon", obj)) )
        {
                command("wield sword");
                command("enable parry taiji-jian");
        }
        command("exert taiji");
        return 1;
}

string do_huqi()
{
        object ob = this_player();
        object me = this_object();

        if( query_temp("battle/team_name", ob) != query_temp("battle/team_name") )
        {
                me->kill_ob(ob);
                return RANK_D->query_rude(this_player()) + "非本隊人馬，莫非想來誑我？看招！\n";
        }

        if( !query("flag", environment(me)) )
        {
                message_vision(HIG"$N疑惑地四下望望，説道：“可是這裏沒有旗可護！”\n"NOR,me);
                return "別搞錯了！";
        }
        else
        {
                message_vision(HIG"$N看了看$n，痛快地説道：“好吧！我就留下來護旗。”\n"NOR,me,ob);
                command("halt");
                command("follow none");
        }

        return "大家加油幹！";
}

varargs void die(object killer)
{
        object me;
        int i;

        me = this_object();

        if( !killer ) killer = me->query_last_damage_from();
        if( objectp(killer) &&
            userp(killer) &&
            query_temp("battle/team_name", killer) != query_temp("battle/team_name", me) )
        {
                BATTLEFIELD_D->add_killnpc_score(killer, 1);
        }

        ::die(killer);
}

void unconcious()
{
        die(query_last_damage_from());
}
