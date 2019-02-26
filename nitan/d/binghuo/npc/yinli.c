// yinli.c
#include <ansi.h>

inherit NPC;

string ask_me();
void create()
{
        set_name("殷離", ({ "yin li", "yin", "li"}));
        set("long",
            "她是張無忌的表妹，殷野王的女兒，一張秀麗的臉蛋因為練千蛛萬毒
手的武功，變得浮腫不堪。\n");
        set("gender", "女性");
        set("age", 16);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 12);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 500);
        set("max_jing", 200);
        set("max_neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("qianzhu-wandushou", 70);
        set_skill("qingfu-shenfa",50);
        map_skill("dodge", "qingfu-shenfa");
        map_skill("parry", "qianzhu-wandushou");
        map_skill("unarmed", "qianzhu-wandushou");

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
        set("inquiry", ([
            "張無忌" :  "你是問阿牛哥嗎？",
            "阿牛"   :  "這個狠心短命的......",
               "父母": "我親生爹爹不要我，見到我就會殺我。我媽媽是我害死的。\n",
               "蛛兒": "你怎麼知道的?快走開,不然叫你嚐嚐我的千蛛萬毒手的厲害!\n",
                "錦盒":(:ask_me:),
        ]));

        set("book_count", 1);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);
}

string ask_me()
{
        object me,ob;
        ob=this_player(); 

        if (query("book_count") < 1)
                return "你來晚了，錦盒我已經贈送給別入了。";   
        addn("book_count", -1);                  

        message_vision(HIY"殷離從懷裏拿出一個錦盒，交了給$N \n\n"NOR,ob);
        me=new("/clone/book/jinhe");
        me->move(ob);

        return "這個錦盒你要好好保管。\n";
}
