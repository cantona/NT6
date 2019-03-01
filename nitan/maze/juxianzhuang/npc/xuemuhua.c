// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

int ask_me();

void create()
{
        set_name("薛慕華", ({ "xue muhua", "xue", "muhua" }));
        set("long", "他就是號稱閻王敵的神醫薛慕華，據說他\n"
                    "精通醫理，可以起死回生。\n");
        set("gender", "男性");
        set("title", "逍遙派函谷八友");
        set("nickname", HIM "閻王敵" NOR);
        set("age", 50);
        set("class", "shaman");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 27);
        set("con", 25);
        set("dex", 25);

        set("inquiry", ([
                "療傷" : (:ask_me:),
        ]) );

        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 100);
        set("level", 10);
        set("combat_exp", 1000000);

        set_skill("force", 160);
        set_skill("xiaowuxiang", 160);
        set_skill("dodge", 140);
        set_skill("feiyan-zoubi", 140);
        set_skill("strike", 160);
        set_skill("liuyang-zhang", 160);
        set_skill("hand", 160);
        set_skill("qingyun-shou", 160);
        set_skill("parry", 160);
        set_skill("blade", 140);
        set_skill("ruyi-dao", 140);
        set_skill("xiaoyao-qixue", 220);
        set_skill("medical", 220);
        set_skill("literate", 120);
        set_skill("martial-cognize", 140);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "liuyang-zhang");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("逍遙派", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_me()
{
        object ob=this_player();
        object me = this_object();
        object azhu;
        string dir;
        string quest, userid;

        dir = base_name(environment(me));
        if (sscanf(dir,"/f/%s/%s/maze",quest,userid)!=2) {
                command("say 我現在沒空！");
                return 1;
        }

        azhu = present("a zhu", environment(me));
        if(me->is_fighting() || me->query_temp("busy"))
        {
                command("say 我現在沒空！");
                return 1;
        }

        if((int)ob->query_temp("juxianzhuang_step") != 14)
        {
                command("say 我為何要為你們療傷！");
                return 1;
        }
        if(!objectp(azhu))
        {
                command("say 你沒有受任何傷啊？");
                return 1;
        }
        else
        {
                message_vision("薛慕華喂$N服下一顆藥丸，然後盤膝坐下，雙掌貼著$N的背心。\n", azhu);

                ob->delete_temp("juxianzhuang_step");
                FUBEN_D->delay_clear_fuben(quest, userid);
                return 1;
        }
}

