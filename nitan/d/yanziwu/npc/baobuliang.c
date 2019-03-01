// bao.c
inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("包不靚", ({ "bao buliang","bao","buliang" }) );
        set("gender", "女性" );
        set("age", 6);
        set("long",
"她年方六歲，眼睛一大一小，鼻孔朝天，耳朵招風，包三先生有何吩
咐，此人決計不聽，叫她哭必笑，叫她笑必哭，哭起來兩個時辰不停，
乃是包三先生的寶貝女兒包不靚。\n");
        set("shen_type", 1);
        set("combat_exp", 100);
        set("str", 20);
        set("dex", 18);
        set("con", 19);
        set("int", 20);
        set("attitude", "friendly");
        create_family("姑蘇慕容", 34, "弟子");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
