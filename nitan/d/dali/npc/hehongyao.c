// hehongyao.c

inherit BUNCHER;

void create()
{
        set_name("何紅藥",({ "he hongyao", "he" }) );
        set("gender", "女性" );
        set("age", 47);
        set("long", "這女人就象個老乞婆，蓬頭垢面，頭髮亂得象雞窩，十指尤如
雞爪。滿臉都是奇怪的傷痕，好像是被蟲蛇撕咬所致，傷痕青
黑不堪入目。\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 70000);
        set("shen_type", -1);
        set("per", 12);
        set("str", 34);
        set("dex", 35);
        set("con", 36);
        set("int", 35);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);
        set("attitude", "friendly");
        setup();
}
