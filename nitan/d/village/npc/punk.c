// punk.c

inherit NPC;

int ask_me();

void create()
{
        set_name("小流氓", ({"punk"}) );
        set("gender", "男性" );
        set("age", 18);
        set("long", "這是一個遊手好閒的小流氓。\n");

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set("combat_exp", 500);
//        set("shen", -100);
        set("shen_type", -1);
        set("str", 25);
        set("dex", 20);
        set("con", 18);
        set("int", 15);
        set("attitude","heroism");
        set("inquiry", ([
                "王小二" : (: ask_me :),
                "翠花" : 
                "翠花是個小寡婦，她家就在打谷場西邊。",
                "雞" : "雞是王小二弄來的，味道還真不錯。",
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
"流氓罵罵咧咧的說道：這真他媽的邪唬，老子手裡一對天牌，王\n"
"小二這雜種居然就摸出一對至尊來。\n",
"流氓靠著牆角打起瞌睡來了，睡夢中也不知想到了什麼，嘴裡哼\n"
"哼道：我看見你哪雪白的大腿，我就起～了～壞～心～嘍。\n",
"流氓摸了摸自己的口袋，嘆了口氣說道：唉，錢都讓王小二騙去\n"
"了，不能去找翠花了。\n",
"流氓嘴角露出一絲邪笑，說道：翠花這娘兒們真夠勁兒，真她奶\n"
"奶的夠～勁～兒!\n",
        }) );
        carry_object(__DIR__"obj/cloth")->wear();
}

int ask_me()
{
        if( query_temp("marks/王", this_player())){
            say("流氓說道：你還有完沒完? 問話不要錢啊?\n");
        }
        else {
                say(
"流氓說道：王小二啊，他不是本村的人，幾個月前來才我們這兒。\n" 
"    跟王小二賭錢總是輸，我看他有搗鬼。這小子拳腳挺厲害的。\n"
                );
                write(
"流氓悄聲跟你說：你要找王小二的麻煩吧? 他就住在財神廟後面，\n"
"    他在那兒搭了個小棚子。\n");
set_temp("marks/王", 1,                 this_player());
        }
        return 1;
}