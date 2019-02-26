// yuanziyi.c 袁紫衣

#include <command.h>
#include <ansi.h>

inherit NPC;
void create()
{
        set_name("袁紫衣", ({ "yuan ziyi","ziyi","yuan"}));
        set("long",
                "她是峨嵋派一個輩份極高的老尼的關門徒弟。\n"
                "一張臉秀麗絕俗。身着一身淡紫衣裳。\n"
                "這一路上去京師她奪了好幾家掌門。\n");
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("title", RED"九家半門派"HIG"總掌門"NOR);
        set("class", "bonze");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
        }) );
        set("inquiry",([
                "胡斐"    : "我和胡大哥畢竟沒有緣份的。",
                "掌門"    : "我就喜歡搶掌門！",
        ]));
        set("str", 30);
        set("per", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3500);
        set("max_jing", 1000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jingli", 1000);
        set("max_jingli", 1000);

        set("combat_exp", 1500000);
        set("score", 1000);
        set_skill("persuading", 80);
        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("finger", 150);
        set_skill("parry", 150);
        set_skill("unarmed", 150);
        set_skill("strike", 150);
        set_skill("sword", 150);
        set_skill("claw", 150);
        set_skill("literate", 150);
        set_skill("mahayana", 150);
        set_skill("jinding-zhang", 150);
        set_skill("jiuyin-baiguzhao", 150);
        set_skill("tiangang-zhi", 150);
        set_skill("huifeng-jian", 150);
        set_skill("zhutian-bu", 150);
        set_skill("linji-zhuang", 150);
        map_skill("force","linji-zhuang");
        map_skill("claw","jiuyin-baiguzhao");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/emei/obj/ycloth.c")->wear();
}
