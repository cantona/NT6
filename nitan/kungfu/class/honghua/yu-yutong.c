#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("餘魚同", ({ "yu yutong", "yu","yutong" }));
        set("title", "紅花會十四當家");
        set("nickname", HIY "金笛秀才" NOR);
        set("long", "一個長身玉立，眉清目秀，風流英俊的書生。\n"
                    "餘魚同乃江南望族子弟，中過秀才。他父親\n"
                    "因和一家豪門爭一塊墳地，官司打得傾家蕩\n"
                    "產，又被豪門藉故陷害，瘐死獄中。餘魚同\n"
                    "一氣出走，得遇機緣，拜馬真為師，棄文習\n"
                    "武，回來把士豪刺死，從此亡命江湖，後來\n"
                    "入了紅花會。他為人機警靈巧，多識各地鄉\n"
                    "談，在會中任聯絡四方、刺探訊息之職。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 20);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 27);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 2800);
        set("max_qi", 2800);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 120);
        set("combat_exp", 1000000);
        set("score", 10000);

        set_skill("force", 140);
        set_skill("taiji-shengong", 140);
        set_skill("unarmed", 140);
        set_skill("xuangong-quan", 140);
        set_skill("dodge", 140);
        set_skill("tiyunzong", 140);
        set_skill("sword", 140);
        set_skill("rouyun-jian", 140);
        set_skill("parry", 140);
        set_skill("throwing", 140);
        set_skill("furong-jinzhen", 140);
        set_skill("martial-cognize", 100);
        set_skill("literate", 200);

        map_skill("force"  , "taiji-shengong");
        map_skill("sword"  , "rouyun-jian");
        map_skill("unarmed" , "xuangong-quan");
        map_skill("dodge"  , "tiyunzong");
        map_skill("parry"  , "rouyun-jian");
        map_skill("throwing"  , "furong-jinzhen");

        prepare_skill("unarmed", "xuangong-quan");

        set("coagents", ({
                ([ "startroom" : "/d/kaifeng/road4",
                   "id"        : "lu feiqing" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "閣下請留步，那裏下去不得。" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "居然揹人下去，到底是什麼意思？" NOR,
        ]));

        create_family("紅花會", 4, "當家");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.xuan" :),
                (: perform_action, "sword.tao" :),
                (: perform_action, "throwing.xian" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        setup();
        carry_object("/kungfu/class/ouyang/obj/baipao")->wear();
        carry_object(__DIR__"obj/yaodai")->wear();
        carry_object(WEAPON_DIR"changjian")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("en");
        command("say 我不收徒，你找其餘幾位當家的好了。");
}
