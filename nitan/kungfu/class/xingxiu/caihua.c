// Last Modified by Winder on Apr. 25 2001

inherit NPC;

void create()
{
        set_name("採花子", ({ "caihua zi", "caihua", "zi" }) );
        set("gender", "男性" );
        set("nickname", "賽崑崙");
        set("age", 38);
        set("long", 
                "採花子是星宿派的一個小嘍羅，武功雖不好，但生性淫邪，"
                "經常姦淫良家婦女，是官府通緝的犯人，故而星宿派名義上"
                "也不承認有這個弟子。\n");
        set("str", 25);
        set("dex", 30);
        set("con", 17);
        set("int", 15);
        set("shen_type", -1);
        set_skill("unarmed", 20);
        set_skill("force", 50);
        set_skill("dodge", 95);
        set_skill("zhaixinggong", 95);
        map_skill("dodge","zhaixinggong");
        set("combat_exp", 25000);
        set("max_qi", 300);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        create_family("星宿派", 2, "弟子");

        set("attitude", "peaceful");
        set("inquiry", ([
                "name" : "我也記不清我姓甚名誰了，江湖朋友送我雅號採花子。",
                "採花" : "那可是學問，我不能隨便教。",
                "學問" : "嘿嘿，娘兒們閒着，豈不是浪費了？",
        ]) );
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        add_money("silver", 10);
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        mapping myfam;
        myfam=query("family", me);
        if (myfam && myfam["family_name"] == "星宿派" &&
                (query("gender", me) == "男性") )
                command("say 我昨天從山下又捉了個小妞來。水靈極了，就關在我的逍遙洞裏，\n折騰了一夜，大爺我爽夠了，你要不要進去試試？");
        set_temp("marks/花", 0, me);
}

void attempt_apprentice(object ob)
{
        command("hehe");
        command("say 想學我的採花神技？沒門兒！");
        return;
}

int accept_object(object me, object obj)
{
        mapping myfam;
        myfam=query("family", me);

        if (!myfam || myfam["family_name"] != "星宿派") 
                command("say 少跟我套近乎。");
        else {
                if( !query("money_id", obj) )
                {
                        if( query("gender", me) == "女性" )
                        {
                                command("kiss"+query("id", me));
                                command("say 想不到師姐也有這個愛好。");
                        }
                        else
                        {
                                command("bow"+query("id", me));
                                command("say 多謝師兄。");
                        }
                        command("say 對不起，那小妞昨天晚上被不知道哪個混蛋救走了，不過\n你可以進洞睡一覺。");
                        set_temp("marks/花", 1, me);
                }
                else
                {
                        command("thank"+query("id", me));
                        command("say 錢我有的是，你還是給我點別的什麼吧。");
                }
        }
        return 1;
}
