// zhongxiaoer.c

inherit NPC;

void create()
{
        set_name("鐘小二",({ "zhong xiaoer", "zhong", "xiaoer" }) );
        set("gender", "男性" );
        set("age", 3);
        set("long", "他是鐘阿四的二兒子，幾只狼狗在追著撕咬他。\n");
        set("combat_exp", 50);
//        set("shen", 50);
        set("shen_type", 1);
        set("str", 11);
        set("dex", 11);
        set("con", 11);
        set("int", 11);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
