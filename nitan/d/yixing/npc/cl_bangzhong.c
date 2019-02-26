// /d/yixing/npc/cl_bangzhong.c 幫眾
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("幫眾", ({ "changle bangzhong", "bangzhong" }));
        set("party/party_name", HIC"長樂幫"NOR);
        set("party/rank", "虎猛堂");
        set("long", "這是一個慣於為非作歹的長樂幫眾。\n他眼珠亂轉，似乎正在想什麼壞主意。\n");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 23);
        set("int", 20);
        set("con", 20);
        set("dex", 23);

        set("max_qi", 300);
        set("max_jing", 200);
        set("max_neili", 100);
        set("neili", 100);
        set("combat_exp", 20000);
        set("score", 1000);

        set_skill("force", 50);
        set_skill("dodge", 40);
        set_skill("cuff", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "長樂幫" : "這裏就是長樂幫總舵所在地。",
                "司徒橫" : "我對我們幫主老人家的景仰之情，有如滔滔江水連綿不絕。",
                "虎猛堂" : "虎猛堂自從邱香主上任後，一日千里！",
                "邱香主" : "他在外面接待客人。",
                "邱山風" : "他在外面接待客人。",
                "香主" : "各位香主的任命由幫主老人家説了算。",
                "貝海石" : "貝大夫在弊幫勞苦功高，頗得幫主信任。",
                "幫主" : "我家幫主司徒大爺乃威鎮江南的“東霸天”也。",
        ]));

        setup();

         carry_object("/clone/weapon/changjian")->wield();
}
