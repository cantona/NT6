// cunmin.c
// by star

inherit NPC;
string *first_name = ({"張", "趙", "錢", "孫","李"});
string *name_words = ({"大叔","二伯","大哥","半仙","大傻"});


void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];


        set_name(name,({"cun min"}));
        set("gender", "男性" );
        set("age", 32);
        set("long", "這是個普普通通的鄉下人，紫紅的臉膛，手上長滿了厚厚的老繭。\n");

        set("max_qi", 200);
        set("shen_type", 1);
        set("str", 17);
        set("dex", 20);
        set("con", 18);
        set("int", 19);
        set("combat_exp", 500);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 15);
        set("attitude", "peaceful");
        setup();
        carry_object("/d/city/obj/cloth")->wear();
}