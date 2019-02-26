// Last Modified by winder on Sep. 12 2001
// zhang.c 章進

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("章進", ({ "zhang jin", "zhang","jin" }));
        set("title", HIR"紅花會"HIG"十當家"NOR);
        set("nickname", HIM"石敢當"NOR);
        set("long", 
"他是個駝子，最是直性子。他天生殘疾，可是神力驚人，練
就了一身外家的硬功夫。他身有缺陷，最惱別人取笑他的駝
背，他和人説話時自稱“章駝子”，那是好端端地，然而別
人若是在他面前提到個“駝”字，甚至衝着他的駝背一笑，
這人算是惹上了禍啦。笑他之人如是常人也還罷了，如會武
藝，往往就被他結結實實的打上一頓。他在紅花會中最聽駱
冰的話，因他脾氣古怪，旁人都忌他三分，駱冰卻憐他殘廢，
衣着飲食，時加細心照料，當他是小兄弟一般。衣服極為光
鮮。相貌卻頗為醜陋。\n");
        set("gender", "男性");
        set("class", "fighter");
        set("age", 24);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 12);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 1200);
        set("max_jing", 700);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 120000);

        set_skill("force", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("hand", 70);
        set_skill("cuff", 70);
        set_skill("honghua-shengong", 70);
        set_skill("youlong-shenfa", 150);
        set_skill("baihua-cuoquan", 150);
        set_skill("benlei-shou", 150);

        map_skill("dodge", "youlong-shenfa");
        map_skill("force", "honghua-shengong");
        map_skill("hand", "benlei-shou");
        map_skill("cuff", "baihua-cuoquan");
        map_skill("parry", "baihua-cuoquan");
        prepare_skill("hand", "benlei-shou");
        prepare_skill("cuff", "baihua-cuoquan");

        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({        
                (: perform_action, "cuff.cuo" :),
                (: perform_action, "hand.yunkai" :),                        
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );
        create_family("紅花會", 2, "弟子");

         setup();
        carry_object(WEAPON_DIR"gangzhang");
        carry_object(CLOTH_DIR"jinpao")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
}
