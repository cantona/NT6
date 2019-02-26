// npc: /d/city/npc/jiangong.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL "監工" NOR, ({"jian gong", "jian"}));
        set("title", "漕運碼頭");
        set("age", 33);
        set("gender", "男性");
        set("str", 26);
        set("dex", 25);
        set("long", "監工面無表情的站在碼頭邊上，手裏握着一根鞭子。\n");
        set("max_jing", 500);
        set("max_qi", 500);
        set("attitude", "heroism");
        set("combat_exp", 20000);

        set_skill("force", 50);
        set_skill("whip", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        setup();
        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        carry_object(__DIR__"obj/douli")->wear();
}