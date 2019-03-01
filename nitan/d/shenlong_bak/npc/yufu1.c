// yufu1.c 漁夫
// Last Modified by winder on Jul. 12 2002

inherit NPC;
string ask_shenlong();

void create()
{
        set_name("漁夫", ({ "yu fu","fu" }) );
        set("gender", "男性");
        set("age", 35);
        set("long", "島上以打魚為生的漁夫。\n");
        set("combat_exp", 8800);
        set("shen_type", 0);
        set("attitude", "friendly");

        set("apply/attack", 50);
        set("apply/defense", 50);

        set("inquiry",([
                "神龍島" : (: ask_shenlong :),
                "神龍教" : (: ask_shenlong :),
        ]));

        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("coin", 50);
}

string ask_shenlong()
{
        mapping fam;
        object ob;
        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "神龍教")
        {
                set_temp("marks/shenlong", 1, this_player());
                write("漁夫對你說：神龍島可是個好去處，你想去就喊小人一聲。\n");
                return "快上船，走吧。\n";
        }
        else
        {
                command("nod");
                return "既是本教弟子，喊一聲就行了。";
        }
}
