// /d/yixing/npc/fengliang.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit F_UNIQUE;
inherit NPC;

void create()
{
        set_name("風良", ({ "feng liang", "feng"}));
        set("title", HIG "青龍門掌門人" NOR);
        set("long", "他是個高大的中年漢子，腰裏纏九節鞭。\n");
        set("gender", "男性");
        set("age", 41);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 22);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);
        
        set("max_qi", 1000);
        set("max_jing", 200);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);

        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("whip", 50);
        set_skill("riyue-bian", 50);
        set_skill("lingxu-bu",50);
        map_skill("dodge", "lingxu-bu");
        map_skill("parry", "riyue-bian");
        map_skill("whip", "riyue-bian");

        set_temp("apply/attack", 25);
        set_temp("apply/attack", 25);
        set_temp("apply/damage", 25);
        set("chat_chance", 10);
        set("chat_msg", ({
                "風良説道：丁不四這老賊不許別人使九節鞭，便是和老子過不去！\n",
                "風良説道：長樂幫的司徒大哥與俺們有過命的交情，真想去拜訪他老人家。\n",
        }) );

        set("inquiry",([
                "丁不四" : "這老賊竟然把我的九節鞭奪走了。",
                "長樂幫" : "我也正要到長樂幫拜山。",
                "司徒大哥" : "司徒大哥的事就是兄弟我的事。",
                "司徒橫" : "聽説長樂幫的奸賊作亂飯上害死了他。",
                "九節鞭" : "九節鞭是找不回來了，得另外弄根鞭子當武器用。",
        ]));

        setup();
        carry_object(__DIR__"obj/jiujiebian")->wield();
        carry_object(CLOTH_DIR"cloth")->wear();
}
