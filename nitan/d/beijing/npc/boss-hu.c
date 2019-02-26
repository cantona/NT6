// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "bjw"     //揚州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任務的反省時間



mapping bunch_bad = ([
        "bunch_name" : "修羅門",
        "id"   : "xlm",
        "place": "bjw",
        "boss" : "胡媚娘",
        "place_name": "北京西城",
        "type" : "bad",
]);

void create()
{
        set_name("胡媚娘", ({ "hu meiniang", "hu","meiniang" }));
        set("gender", "女性");
        set("age", 26);
        set("long", "她裝扮的妖豔無比，一雙眼睛能攝人魂魄。\n");
        set("title",HIB"修羅門北京壇主"NOR);
        set("per",29);
        set("combat_exp", 1000000);
        set("shen_type", -1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}
#include <boss_bad.h>

