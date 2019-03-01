// /d/yixing/npc/cl_qiu.c 邱山風
// Last Modified by winder on Jul. 12 2002

#define TUCHAN "/d/yixing/obj/cl_tuchan"

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("邱山風", ({ "qiu shanfeng", "qiu" }));
        set("party/party_name", HIC"長樂幫"NOR);
        set("party/rank", "虎猛堂香主");
        set("long", "他是一位三十多歲的彪形大漢。\n");
        set("gender", "男性");
        set("age", 32);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 25);
        set("int", 20);
        set("con", 28);
        set("dex", 25);

        set("max_qi", 700);
        set("max_jing", 400);
        set("max_neili", 600);
        set("neili", 600);
        set("jiali", 30);
        set("combat_exp", 150000);
        set("score", 7000);
/*
        set_skill("force", 90);
        set_skill("dodge", 90);
        set_skill("parry", 90);
        set_skill("cuff",  90);
        set_skill("club",  100);

        set_skill("ding-force", 90);
        set_skill("wuxingbu", 90);
        set_skill("wuxing-quan", 90);
        set_skill("wuhu-gun", 100);

        map_skill("force", "ding-force");
        map_skill("dodge", "wuxingbu");
        map_skill("cuff", "wuxing-quan");
        map_skill("parry", "wuhu-gun");
        map_skill("club", "wuhu-gun");

        prepare_skill("cuff", "wuxing-quan");
*/
        set("inquiry", ([
                "長樂幫" : "這裡就是長樂幫總舵所在地。",
                "司徒橫" : "我對我們幫主老人家的景仰之情，有如滔滔江水連綿不絕。",
                "虎猛堂" : "虎猛堂自從我當香主後，一日千裡，哈！哈！哈！",
                "香主" : "各位香主的任命由幫主老人家說了算。",
                "貝海石" : "貝大夫在弊幫勞苦功高，頗得幫主信任。",
                "幫主" : "我家幫主司徒大爺乃威鎮江南的“東霸天”也。",
        ]));

        setup();
        carry_object(WEAPON_DIR"sword/panguanbi")->wield();
}

int accept_object(object who, object ob)
{
        if( base_name(ob) != TUCHAN )
                return notify_fail(name() + "擺了擺手，說道：你還是自個兒留著用吧。\n");

        command("joythank"+query("id", who));
        set_temp("changle", 1, who);
        call_out("do_destroy", 1, ob);
        return 1;
}

void do_destroy(object ob)
{
        if( ob ) destruct(ob);
}
