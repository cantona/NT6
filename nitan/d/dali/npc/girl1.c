// girl1.c

inherit NPC;

void create()
{
        set_name("南國姑娘",({ "girl" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long", "南國的大姑娘頗帶有當地優美秀麗山水的風韻，甜甜的笑，又有
天真的浪漫。她穿着白色上衣，藍色的寬褲，外面套着黑絲絨領褂，
頭上纏着彩色的頭巾。\n");
         set_temp("apply/defense", 15);
        set("combat_exp", 2000);
        set("shen_type", 1);
        set("per", 25);
        set("str", 24);
        set("dex", 25);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/whitecloth1")->wear();
}
