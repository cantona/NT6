// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("狄雲", ({ "di yun", "di","yun" }));
        set("long",
                "他就是"+HIR"血刀門"NOR+"弟子狄雲。\n"
                "他今年看起來倒滿和藹的。\n");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);
        set("level", 40);
        set("combat_exp", 5000000);
        set("score", 60000);

        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("hand", 600);
        set_skill("mizong-neigong", 600);
        set_skill("dashou-yin", 600);
        set_skill("unarmed", 600);
        set_skill("blade", 600);
        set_skill("literate", 600);
        set_skill("xuehai-mogong", 600);
        set_skill("xuedao-daofa", 600);
        set_skill("force", 600);
        set_skill("shenkong-xing", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("liancheng-jianfa", 600);
        set_skill("shenzhaojing", 600);

        map_skill("unarmed", "shenjingzhao");
        map_skill("cuff", "yujiamu-quan");
        map_skill("force", "shenzhaojing");
        map_skill("blade", "xuedao-daofa");
        map_skill("parry", "xuedao-daofa");
        map_skill("dodge", "shenkong-xing");
        map_skill("sword", "liancheng-jianfa");

        create_family("血刀門", 5, "弟子");

        set("master_ob", 3);
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query("shen", ob)<100000 )
        {
                command("sigh");
                command("say 我已經封門不收弟子了，你請回吧。");
                return;
        }
        if ((int)ob->query_skill("xuehai-mogong", 1) < 120) {
                command("say 練血刀刀法最重內功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否還應該在血海魔功上多下點功夫？");
                return;

        }
        if ((int)ob->query_skill("lamaism", 1) < 100) {
                command("say 入我血刀門，修習密宗心法是首要的。");
                command("say 這位" + RANK_D->query_respect(ob) +


                        "是否還應該多多鑽研本門的心法？");
                return;
        }

        command("say 好吧，看你還是個人才，血刀門看來得靠你了。");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "無影神拳" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenzhaojing/ying",
                           "name"    : "無影神拳",
                           "sk1"     : "shenzhaojing",
                           "lv1"     : 100,
                           "sk2"     : "unarmed",
                           "lv2"     : 100,
                           "gongxian": 800, ]));
                break;

        case "無影拳舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenzhaojing/wu",
                           "name"    : "無影拳舞",
                           "sk1"     : "shenzhaojing",
                           "lv1"     : 120,
                           "sk2"     : "unarmed",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "耳光式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liancheng-jianfa/erguang",
                           "name"    : "耳光式",
                           "sk1"     : "liancheng-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 600, ]));
                break;

        case "刺肩式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liancheng-jianfa/cijian",
                           "name"    : "刺肩式",
                           "sk1"     : "liancheng-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "去劍勢" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liancheng-jianfa/qujian",
                           "name"    : "去劍勢",
                           "sk1"     : "liancheng-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 600, ]));
                break;

        default:
                return 0;
        }
}
