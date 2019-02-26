// cunfu.c
// by star
inherit NPC;
string *first_name = ({"張", "趙", "錢", "孫","李"});
string *name_words = ({"寡婦","大媽","大姐","二嫂","三姐"});


void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];


        set_name(name,({"cun fu"}));
        set("gender", "女性" );
        set("age", 32);
        set("long", "這是個普普通通的農家婦女，臉上擦着厚厚的白粉。\n");

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