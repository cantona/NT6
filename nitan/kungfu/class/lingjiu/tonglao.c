// This program is a part of NT MudLIB

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("天山童姥", ({ "tong lao", "tong", "lao" }));
        set("long",
            "她就是"+HIC"「靈鷲宮」"NOR+"的開山祖師.\n"+
            "乍一看似乎是個十七八歲的女子,可神情卻是老氣橫秋.\n"+
            "雙目如電,炯炯有神,向你瞧來時,自有一股凌人的威嚴.\n");
        set("title", HIC"靈鷲宮主人"NOR);
        set("gender", "女性");
        set("per", 20);
        set("age", 96);
        set("nickname", HIR "唯我獨尊" NOR);
        set("shen_type",0);
        set("attitude", "peaceful");

        set("str", 25);
        set("int", 35);
        set("con", 40);
        set("dex", 40);

        set("qi", 8000);
        set("max_qi", 8000);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 5000000);
        set("score", 200000);

        set_skill("force", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("hand", 600);
        set_skill("strike", 600);
        set_skill("sword", 600);

        set_skill("zhemei-shou", 600);
        set_skill("liuyang-zhang", 600);
        set_skill("tianyu-qijian", 600);
        set_skill("yueying-wubu", 600);
        set_skill("bahuang-gong", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
/*
        set_skill("force", 450);
        set_skill("dodge", 450);
        set_skill("parry", 450);
        set_skill("hand", 450);
        set_skill("strike", 450);
        set_skill("sword", 450);

        set_skill("zhemei-shou", 450);
        set_skill("liuyang-zhang", 450);
        set_skill("tianyu-qijian", 480);
        set_skill("yueying-wubu", 450);
        set_skill("bahuang-gong", 450);
        set_skill("literate", 200);
        set_skill("martial-cognize", 320);
*/

        map_skill("force", "bahuang-gong");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("strike","liuyang-zhang");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword","tianyu-qijian");

        prepare_skill("strike", "liuyang-zhang");
        prepare_skill("hand", "zhemei-shou");

        create_family("靈鷲宮", 1, "主人");

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "strike.zhong" :),
                (: perform_action, "hand.duo" :),
                (: perform_action, "sword.san" :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
        }) );

        set("master_ob",5);
        setup();

         carry_object("/clone/weapon/changjian")->wield();
         carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
        carry_object("/clone/food/jiudai");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "女性" )
        {
                command("say 你找死啊!");
                return;
        }
        if ((int)ob->query_skill("bahuang-gong", 1) < 230)
        {
                command("say " + RANK_D->query_respect(ob) + "是否還應該多練練八荒六合唯我獨尊功？");
                return;
        }
        if (ob->query_con() < 30)
        {
                command("say 本門功法極為難練,你的根骨似乎不夠.");
                return;
        }
        command("recruit "+query("id", ob));
        if( query("class", ob) != "dancer" )
                set("class", "dancer", ob);
        return;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {

        case "灰飛煙滅" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/hui",
                           "name"    : "灰飛煙滅",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 150,
                           "sk2"     : "zhemei-shou",
                           "lv2"     : 150,
                           "neili"   : 2000,
                           "gongxian": 900, ]));
                break;

        case "一掌震天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/zhen",
                           "name"    : "一掌震天",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800, ]));
                break;

        case "白虹掌力" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/baihong",
                           "name"    : "白虹掌力",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800, ]));
                break;

        case "九弧破日" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianyu-qijian/pori",
                           "name"    : "九弧破日",
                           "sk1"     : "tianyu-qijian",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 400, ]));
                break;

        case "天女散花" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianyu-qijian/san",
                           "name"    : "天女散花",
                           "sk1"     : "tianyu-qijian",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 400, ]));
                break;

        case "九羽天誅" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianyu-qijian/zhu",
                           "name"    : "九羽天誅",
                           "sk1"     : "tianyu-qijian",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 400, ]));
                break;

        case "化妖功" :
               return MASTER_D->teach_pfm(me, this_object(),
                       ([ "perform" : "can_perform/zhemei-shou/hua",
                          "name"    : "化妖功",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 400, ]));
                break;

        default:
                return 0;
        }
}
