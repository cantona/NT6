#include <ansi.h>

inherit NPC;

#define PLACE "hz"     //長安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任務的反省時間

mapping bunch_good = ([
        "bunch_name" : "無極幫",
        "id"   : "wjb",
        "place": "hz",
        "boss" : "萬劍愁",
        "place_name" : "杭州",
        "type" : "good",
]);

void create()
{
        set_name("萬劍愁", ({ "wan jianchou", "wan" }));
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是人人敬仰的萬大俠。\n");
        set("nickname",HIY"江南大俠"NOR);
        set("title","無極幫杭州分舵");
        set("per",28);
        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}

#include <boss_good.h>
