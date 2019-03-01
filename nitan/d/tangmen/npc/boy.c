//boy.c

inherit NPC;

void create()
{
        int i,amun;
        string *order = ({"張", "王", "李", "趙", "孫", "徐", "鄭", "周", "吳",
                "蔣", "沈", "楊", "苗", "尹", "金", "魏", "陶", "俞", "柳", "朱"});
        string *orderr = ({"包包", "寶寶", "乖乖", "小小", "磊磊",
                "雞雞", "鴉鴉", "狗狗", "貓貓"});
        set_name( order[random(20)] + orderr[random(8)], ({ "boy", "kid" }) );
        set("title", "無知男孩");
        set("gender", "男性" );
        set("age", random(5)+4);
        set("long",
                "他很小, 很好欺服.\n");
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );

        set("attitude", "peaceful");
        set("combat_exp", random(1000));
        set("max_qi", 100);
        set("qi", 100);
        set("max_jingli", 100);
        set("jingli", 100);
        set_skill("cuff", 1+random(10));
        setup();
        carry_object("clone/misc/cloth")->wear();
}
