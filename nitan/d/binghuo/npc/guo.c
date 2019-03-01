// mai.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>;
void create()
{
        set_name("過三拳", ({ "guo sanquan", "guo", "sanquan" }));
        set("title", HIY"神拳門掌門"NOR);
        set("long", 
"過三拳這名字的由來，乃因他拳力極猛，一拳可斃牯牛，尋常武師萬
萬擋不住他三拳的轟擊，江湖上傳揚開來，他本來的名字反而沒人知
道了。\n");
        set("gender", "男性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 600);
        set("max_jing", 600);
        set("neili", 600);
        set("max_neili", 600);
        set("combat_exp", 70000);
        set_skill("parry", 70);
        set_skill("unarmed", 70);
        set_skill("changquan", 70);
        map_skill("parry", "changquan");
        map_skill("unarmed", "changquan");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
