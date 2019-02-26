#include <ansi.h>

inherit NPC;

void create()
{
        set_name("時萬年", ({"shi wannian", "shi", "wannian"}));
        set("gender", "男性");
        set("long", "他是凌霄城第六代弟子時萬年，乃是繼白萬劍、封\n"
                    "萬里後武功最高、劍法最精的弟子。此時他在此守\n"
                    "衞監獄。\n");
        set("age", 24);
        set("attitude", "peaceful");

        set("str", 25);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 1500);
        set("max_jing", 1200);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 120);
        set("combat_exp", 800000);

        set("chat_chance", 8);
        set("chat_msg", ({
                CYN "時萬年恨恨説道：老瘋子不知道又怎麼了，把自己關在裏面弄死不肯出來。\n" NOR,
                       CYN "時萬年把劍一彈，傲然道：有我守在這，誰都別想把老瘋子放出來。\n" NOR,
        }) );

        set_skill("force", 160);
        set_skill("xueshan-neigong", 160);
        set_skill("dodge", 160);
        set_skill("taxue-wuhen", 160);
        set_skill("cuff", 160);
        set_skill("lingxiao-quan", 160);
        set_skill("strike", 160);
        set_skill("piaoxu-zhang", 160);
        set_skill("sword", 180);
        set_skill("hanmei-jian", 180);
        set_skill("yunhe-jian", 180);
        set_skill("parry", 160);
        set_skill("literate", 120);
        set_skill("martial-cognize", 80);

        map_skill("force", "xueshan-neigong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "yunhe-jian");
        map_skill("parry", "hanmei-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 6, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chong" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wear();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒，你去找我其它師兄好了。");
}

void init()
{ 
        object ob;
        ::init();

        ob = this_player();

              if( query("family/family_name", ob) != "凌霄城" )
        {
                command("heng");
                command("say 你居然敢闖入本派禁地，受死吧！\n");
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob); 
        } else
        if( query("family/master_name", ob) == "白自在" )
        {
                command("say 師兄回來了，快去見師祖吧，不過小心點……沒準他又犯病了。");
        } else
        if( query("family/master_name", ob) == "白萬劍" )
        {
                command("say 你是白師哥的弟子吧，老爺子就在裏面，他的病越來越不得了啦。");
        }
}
