// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "bje"     //揚州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任務的反省時間



mapping bunch_bad = ([
        "bunch_name" : "黑白道",
        "id"   : "hbd",
        "place": "bje",
        "boss" : "黑白郎君",
        "place_name": "北京城東",
        "type" : "bad",
]);

void create()
{
        set_name("黑白郎君", ({ "heibai langjun", "heibai","langjun" }));
        set("gender", "男性");
        set("age", 32);
        set("long", "他是一個很奇怪的男子，整個身體明顯的分為黑白兩半，真不愧是" + bunch_bad["bunch_name"] + "的首領。\n");
        set("title",HIB"黑"WHT"白"NOR"道總首領"NOR);
        set("per",25);
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

