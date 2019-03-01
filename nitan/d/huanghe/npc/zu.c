// zu.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
string ask_me();

void create()
{
        set_name("祖千秋", ({ "zu qianqiu", "zu", "qianqiu" }) );
        set("nickname", "黃河老祖");
        set("gender", "男性" );
        set("age", 52);
        set("long", "一個衣衫襤褸的落魄書生。焦黃臉皮，一個酒糟鼻，疏疏落落的
幾根胡子，兩眼無神。衣衫上一片油光，右手拿了一把破折扇。\n");
        set("combat_exp", 400000);
        set("attitude", "friendly");

        set("max_jing",500);
        set("max_qi",500);
        set("per", 17);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 30);
        set("no_get", 1);

        set_skill("literate", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("unarmed", 100);
        set("inquiry", ([
//          "續命八丸" : (: ask_me :),
//           "8wan"     : (: ask_me :),
        ]));

        set("book_count", 1);
        setup();
        add_money("gold", 1);
        carry_object("d/city/obj/cloth")->wear();
}
/*
string ask_me()
{
        object ob;

        if (uptime() < 1000)
                return "這位"+RANK_D->query_respect(this_player()) +
                "，續命八丸還在老頭子那裡，我怎麼給你？";
        if (random(10) < 3)
                return "這位"+RANK_D->query_respect(this_player()) +
                "，續命八丸給令狐公子吃掉了，我拿什麼給你？";
        if (random(10) < 6)
                return "這位"+RANK_D->query_respect(this_player()) +
                "，吃了續命八丸就要給老不死賢侄女放血治病，你能成麼？";
        if (random(10) < 9)
                return "這位"+RANK_D->query_respect(this_player()) +
                "，給了你續命八丸，豈不傷了我和老頭子的黃河老祖的義氣？";
        ob = new("/clone/medicine/nostrum/xuming8wan");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到續命八丸了啦。\n");
        return "好吧，看在聖姑份上就給你嘗嘗續命八丸的味道吧。";
}

*/