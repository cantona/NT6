// fake-biaotou.c
#include <ansi.h>;
inherit NPC;
#include "finit.h"

void create()
{
        string weapon;
        int i;

        set_name("陌生鏢頭", ({ "fake biaotou" }) );
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"鏢頭"NOR);
        set("gender", random(2)>0 ? "女性" : "男性" );
        set("age", 30 + random(20) );
        set("long","一個普通的人，放在人羣中沒有一點突出之處。\n");

        weapon = weapon_msg[random(sizeof(weapon_msg))];
        set("combat_exp",100000 +random(50000));
        set("max_qi",1200+random(300));
        set("max_jing",400+random(200));
        set("str", 20 + random(11));    // 膂力
        set("per", 20 + random(11));    // 容貌
        set("int", 20 + random(11));    // 悟性
        set("con", 20 + random(11));    // 根骨
        set("dex", 100 + random(11));   // 身法
        set("kar", 20 + random(11));    // 福緣
        setup();
        carry_object(weapon);
        carry_object("/clone/misc/cloth")->wear();
}
