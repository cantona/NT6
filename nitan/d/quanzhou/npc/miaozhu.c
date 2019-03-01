// miaozhu.c
// Last Modified by winder on May. 29 2001

inherit NPC;

void create()
{
        set_name("廟祝", ({ "miao zhu", "zhu", "miaozhu" }));
        set("class", "taoist");
        set("gender", "男性");
        set("age", 65);
        set("long", "這是一位年老的廟祝，在此已幾十年了，對此地一切都十分熟悉。\n");
        set("combat_exp", 800);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
}
