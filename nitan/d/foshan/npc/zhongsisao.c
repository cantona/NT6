// zhongsisao.c

inherit NPC;

void create()
{
        set_name("鍾四嫂", ({ "zhong sisao","zhong","sisao" }) );
        set("gender", "女性");
        set("age", 35);
        set("long",
"她就是鍾阿四的老婆。鳳老爺後院中養了十隻肥鵝，忽然不見了一隻。家丁\n"
"説是鍾家的小二子、小三子兄弟倆偷了，到巡檢衙門去告了一狀，差役便來\n"
"將鍾阿四鎖了去整治得奄奄一息。鍾四嫂心裏一急，便橫了心。她趕回家裏，\n"
"一手拖了小三子，一手拿了柄菜刀，叫了左右鄉鄰，一齊上祖廟去。\n"
"鍾四嫂在北帝爺爺座前磕了幾個響頭，説道：‘北帝爺爺，我孩子決不能偷\n"
"人家的鵝。他今年還只四歲，刁嘴拗舌，説不清楚，在財主爺面前説什麼吃\n"
"我，吃我！小婦人一家橫遭不白，贓官受了賄，斷事不明，只有請北帝爺爺\n"
"伸冤！’説着提起刀來，一刀便將小三子的肚子剖了。自己也發瘋了。\n");
        set("combat_exp", 20000);
        set("shen_type", 1);
        set("attitude", "aggressive");

        set("apply/attack",  30);
        set("apply/defense", 30);

        set("chat_chance", 5);
        set("chat_msg", ({
                "鍾四嫂嘶啞着嗓子喊：‘不賣地，不賣地！沒有偷，沒有偷。’\n",
                (: random_move :)
        }) );

        set_skill("blade", 30);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);

        setup();
        carry_object(__DIR__"obj/caidao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}