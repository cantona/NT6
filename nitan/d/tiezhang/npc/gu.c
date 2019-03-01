// gu.c 顧炎武
// by pishou and zqb :)

inherit NPC;
//inherit F_SKILL;
int ask_wumu();
int ask_yishu();
int ask_jiannan();
void create()
{
    set_name("顧炎武", ({ "gu yanwu", "gu" }));
    set("long", "顧先生名炎武，字亭林，江蘇昆山人士。\n" "顧先生是當世大儒，明亡之後，心傷國變，隱居不仕。\n" "他又高又瘦，面目黝黑。\n");
        set("gender", "男性");
    set("age", 55);

    set_skill("literate", 200);

    set_temp("apply/attack", 10);
    set_temp("apply/defense", 10);
    set_temp("apply/damage", 5);

    set("combat_exp", 500);
        set("shen_type", 1);
        setup();

        set("inquiry", ([
                "畫" : "這是二瞻先生的丹青。",
              "二瞻" : "他乃是當今一位大畫家。",
            "查士標" : "二瞻先生有位本家伊璜先生牽連在這場‘明史’大案中。",
              "伊璜" : "查伊璜, 也就是查繼佐, 因大力將軍所助, 免罪不究。", 
              "大力" : "大力將軍乃廣東提督吳六奇將軍。",
            "吳六奇" : "吳六奇將軍身在曹營心在漢, 實際上是天地會洪順堂香主。",
            "天地會" : "天地會是台灣國姓爺延平郡王鄭成功手下謀主陳永華所創。",
            "陳永華" : "陳先生暗中聯絡老兄弟，胸口所刺八字便是會裡的口號。",
              "口號" : "天地父母，反清復明。",
          "反清復明" : "你也要學一學當年岳武穆盡忠報國, 刺字以決你心? ",
          "岳武穆" : (: ask_wumu :),
          "武穆遺書" : (: ask_yishu :),
          "上官劍南" : (: ask_jiannan :),
        ]) );
        set("chat_chance", 3);
        set("chat_msg", ({
        "顧炎武高聲呤道：清風雖細難吹我，明月何嘗不照人？ 真是絕唱！ \n",
        "顧炎武道：如此江山，淪于夷狄。我輩忍氣吞聲。偷生其間，實令人悲憤填膺。\n",
        "顧炎武道：終有一日驅除胡虜，還我大漢河山，比之徒抒悲憤，更加令人氣壯。\n",
        "顧炎武道：當今之世，便真有桃源樂土，咱們也不能獨善其身，去躲了起來。\n",
        }) );
}

int ask_wumu()
{
command("say 岳武穆名飛字鵬舉，乃抗金的名將，一生用兵如神。據說他死後留下了一部\n"
"武穆遺書，其中記載著他一生戎馬生涯的兵法要訣。\n");
return 1;
}

int ask_yishu()
{
command("say 這部遺書最早收藏在皇宮之中，後聽說鐵掌幫幫主上官劍南率幫中高手，將\n"
"此書偷走，不知是真是假。\n");
return 1;
}

int ask_jiannan()
{
        object zitie, me, ob;

        me = this_object();
        ob = this_player();
        
        zitie = new("/d/tiezhang/obj/zitie");
        if ( present("zitie", ob) )
        {
                command("say 我不是已經告訴你了麼，怎麼還問？\n");
                return 1;
        }

command("say 這位上官幫主乃是一位俠義之士，鐵掌幫自他接任後，力加整頓，多行俠\n"
"義之事，不過數年聲勢大振，在江湖上侵尋已可以與北方的丐幫分庭抗禮了。只是後來忽\n"
"然消聲匿跡，不知所蹤了。看來想找到武穆遺書，必先找到上官幫主才行！\n");
command("look"+query("id", ob));
command("say 看來" + RANK_D->query_respect(ob) + "也是我輩中人，老朽這裡有一幅字帖送給你，希望你\n"
"能不忘驅除胡虜，還我河山的志向！");
zitie->move(ob);
message_vision("$N交給$n一幅字帖。\n", me, ob);
return 1;
}

int recognize_apprentice(object ob)
{
        int money=50, level = ob->query_skill("literate", 1);

        if (level>29) money=100;
        if (level>59) money=500;
        if (level>89) money=1000;
        if (level>119) money=5000;

    delete_temp("mark/顧", ob);
        switch(MONEY_D->player_pay(ob, money)) {
                case 0:
                case 2:
                        write("你現在的學費是每次" + MONEY_D->money_str(money) + "，請備好零錢。\n");
                        return 1;
        }
    set_temp("mark/顧", 1, ob);
        return 1;
}
/*
int accept_object(object who, object ob)
{
        int money=25, level = who->query_skill("literate", 1);

        while (level >= 0) {
                money += money;
                level -= 30;
        }

        if( query("money_id", ob)){
                if (ob->value() >= money) {
            if( query_temp("mark/顧", who)<1 )
                set_temp("mark/顧", 1, who);
            message_vision("顧炎武同意指點$N一些四書五經的問題。\n", who);
            addn_temp("mark/顧", ob->value()/money, who);
                        return 1;
                }
                return notify_fail("你現在的學費是每次" + MONEY_D->money_str(money) + "。\n");
        }
        return 0;
}
*/