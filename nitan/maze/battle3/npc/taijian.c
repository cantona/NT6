#include <ansi.h>
inherit NPC;
void create()
{
        set_name("太監", ({ "tai jian", "gonggong"}));
        set("gender", "無性");
        set("age", random(20) + 20);

        set("long","這是一個京城皇宮中的一名太監，負責為皇帝傳送奏本。\n");
        set("combat_exp", 80000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili",2000);
        set("neili",1000);

        setup();
        carry_object("clone/misc/cloth")->wear();
}            
