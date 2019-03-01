// /d/guiyun/ouyangfeng.c
// Last Modified by Sir 03/05/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("歐陽鋒", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "他是白駝山莊主，號稱“西毒”的歐陽鋒。\n"
                +"由于習練「九陰真經」走火入魔，已變得精\n"
                +"神錯亂，整日披頭散發。\n");
        set("title", "白駝山莊主");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIY "西毒" NOR);
        set("shen_type",-1);
        set("shen", -150000);
        set("attitude", "peaceful");
        set("no_get",1);

        set("str", 30);
        set("int", 29);
        set("con", 30);
        set("dex", 28);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 900);
        set("max_jing", 900);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 50);

        set("combat_exp", 3000000);
        set("score", 200000);

        set_skill("force", 200);
        set_skill("cuff", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set_skill("hand",200);
        set_skill("strike",200);
        set_skill("staff", 200);
        set_skill("training",200);
        set_skill("literate", 100);
        set_skill("xidu-poison", 150);
        set_skill("hamagong", 200);
        set_skill("chanchu-bufa", 300);
        set_skill("shexing-diaoshou", 300);
        set_skill("lingshe-zhangfa", 300);
        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("strike", "hamagong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        prepare_skill("strike", "hamagong");
        prepare_skill("hand", "shexing-diaoshou");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "staff.shoot" :),
                (: perform_action, "staff.saoye" :),
                (: perform_action, "strike.hama" :),
                (: exert_function, "powerup" :),
                (: exert_function, "reserve" :),
                (: exert_function, "recover" :),
        }) );

        create_family("白駝山派",1, "開山祖師");
        set("chat_chance",2);
        set("chat_msg",({
                "歐陽鋒自言自語道：何日白駝山派才能重霸江湖呢…\n",
                "歐陽鋒道：我兒歐陽克必能夠重振白駝山派雄風！\n",
                "歐陽鋒道：江湖險惡，困難重重哪！\n",
        }));

        set("inquiry", ([
                "name":   "名字，我...我沒有名字，我...我是誰?",
                "名字":   "名字，我...我沒有名字，我...我是誰?",
        ]));
        setup();
//        carry_object(WEAPON_DIR"treasure/lingshezhang")->wield();
        carry_object("/d/baituo/obj/shezhang")->wield();
        carry_object(__DIR__"obj/baipao")->wear();
        add_money("silver",50);
}

