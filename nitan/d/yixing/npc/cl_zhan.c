// /d/yixing/npc/zhan.c 展飛
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("展飛", ({ "zhan fei", "zhan" }));
        set("party/party_name", HIC"長樂幫"NOR);
        set("party/rank", "豹捷堂香主");
        set("long", "他是一個身披斑衣的漢子。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 25);
        set("int", 25);
        set("con", 24);
        set("dex", 25);

        set("max_qi", 700);
        set("max_jing", 400);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 30);
        set("combat_exp", 120000);
        set("score", 6000);

        set_skill("force", 90);
        set_skill("dodge", 90);
        set_skill("parry", 90);
        set_skill("strike", 90);
/*
        set_skill("ding-force", 90);
        set_skill("wuxingbu", 90);
        set_skill("cuixin-zhang", 90);

        map_skill("force", "ding-force");
        map_skill("dodge", "wuxingbu");
        map_skill("strike", "cuixin-zhang");
        map_skill("parry", "cuixin-zhang");

        prepare_skill("strike", "cuixin-zhang");
*/
        set("inquiry", ([
                "長樂幫" : "我為長樂幫赴湯蹈火十幾年竟落得這個下場。",
                "司徒橫" : "這賊幫主兇淫毒辣，不知要想什麼新鐐古怪的花樣來折磨我？",
                "幫主"   : "這賊幫主兇淫毒辣，不知要想什麼新鐐古怪的花樣來折磨我？",
                "豹捷堂" : "沒有我的管轄，豹捷堂眼看要垮了。",
                "貝海石" : "貝大夫在弊幫勞苦功高，頗得幫主信任。",
                "香主"   : "各位香主的任命由幫主老人家説了算。",
        ]));

        setup();
}
