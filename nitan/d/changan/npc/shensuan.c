// This program is a part of NT MudLIB

inherit NPC;
int look_ob();
int ask_letter();
int do_suan(string str);
int ask_suanming();
string ask_mimi();
void create()
{
        set_name("賽神仙", ({ "shensuan zi", "shensuan" }) );
        set("nickname", "神算子");
        set("gender", "男性");
        set("age", 66);
        set("long",
                "神算子正坐在板凳頭趴在桌子上睡覺，唾液一直流到了桌子底下。\n");
        set("attitude", "peaceful");
        set_skill("taoism", 300);
        set_skill("force",200);
        set("max_neili",5000);
        set("max_jingli",3000);
        set("letter", 1);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 20);
        set("combat_exp", 500000);
        set("shen_type", 1);

        set("inquiry", ([
                "算命": (: ask_suanming :),
                "秘密": (: ask_mimi :),
                "信": (: ask_letter :),
        ]));

        setup();
        carry_object("/clone/cloth/changpao")->wear();
}
void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("look_ob");
                call_out("look_ob", 6, ob);
        }
}

int look_ob()
{
        foreach (object player in all_inventory(environment()) )
                command("look "+query("id", player));
        return 1;
}

int ask_suanming()
{
        if( query_temp("knock", this_player())){
                command("whisper "+query("id", this_player())+"沒點誠意，老夫恕難從命！\n");
                set_temp("knock", 0, this_player());
                return 1;
        }
        return 0;
}

string ask_mimi()
{
        object me=this_player();
        if( !query_temp("mimi", me))return "這個嘛，我不知道也！";
        delete_temp("mimi", me);
        set_temp("letter", 1, me);
        return "很多年前，我的爺爺的爺爺給我留下一封信，我知道信中隱藏著一個大秘密。";
}

int ask_letter()
{
        object ob,me=this_player();
        int p1;
        if (query("letter") < 1)
                say("神算子很遺憾的說道：這樣東西我已經給人了。\n");
        if( query("passwd1", me) )
        {
                say("神算子很不耐煩的說道：我把我知道的都告訴你了，還問什麼嘛！\n");
        }else
        if( query_temp("letter", me) )
        {
                say("神算子嘿嘿的姦笑了幾聲，道：你想要這封手信嗎？\n");
                write("神算子歪頭想了會，說道：好吧！\n");
                p1=random(6)+1;
                set("passwd1", p1, me);
                write("這封信的後面已經看不到了，但我隱約記得曾多次提到"+CHINESE_D->chinese_number(p1)+"樣什麼東西的。\n");
                write("現在我就把這封信交給你了，我對這封信已經失去興趣了，唉，你要保重啊！！\n");
                delete_temp("letter", me);
                addn("letter", -1);
                ob=present("letter",this_object());
                if (!ob)
                        ob=new("/d/changan/obj/letter.c");
                ob->move(me);
        } else {
                message("vision","神算子不知道你在說什麼也！！\n", me);
        }
        return 1;
}

int accept_object(object me, object ob)
{
        command("smile");
        command("say 嘿嘿，多謝這位" + RANK_D->query_respect(me) + " ！");
        if( query("money_id", ob) && query("class", me) != "bonze" )
        {
                if(ob->value() < 1000000)
                {
                        command("say 唉，近來生意難做啊，是不是能再給點...");
                        return 1;
                }else{
                        // command("smile shensuan");
                        command("say 告訴我，" + RANK_D->query_respect(me) + "，你要算(suan)自己，還是算誰。");
                        add_action("do_suan","suan");
                        set_temp("give_money", 1, me);
                        return 1;
                }
        }
        return 1;
}

int do_suan(string arg)
{
        object ob, me = this_player();
        string name;
        int str, ntg, dex, per, con, kar,str1, ntg1, dex1, per1, con1, kar1;

        if(!arg || sscanf(arg, "%s", name)!= 1 )   return 0;
        if( !query_temp("give_money", me))return 0;
        if(!objectp(ob = find_player(name)) )   return 0;
        if( !ob || wizardp(ob)) {
                command("tell "+query("id", me)+" 噓，小聲點，神仙我怎麼敢算啊。");
                return 1;
        }

        delete_temp("give_money", me);
        str=query("str", ob);
        ntg=query("int", ob);
        dex=query("dex", ob);
        per=query("per", ob);
        con=query("con", ob);
        kar=query("kar", ob);
        str1 = ob->query_str();
        ntg1 = ob->query_int();
        dex1 = ob->query_dex();
        per1 = ob->query_per();
        con1 = ob->query_per();
        kar1 = ob->query_kar();


        switch(random(6)) {
                case 0 :
                if( str1+ntg1+dex1+per1+con1+kar1>(query("age", ob)+6)*6){
                        command("nod");
                        command("say 不錯，"+ob->name()+"也還算修練有方。");
                } else {
                        command("sigh");
                        command("say "+ob->name()+"還要在基本功上多下點功夫！");
                }
                break;
                case 1 :
                if(kar > 22) {
                        command("smile");
                        command("say "+ob->name()+"福緣深厚，吉人自有天相。");
                }else {
                        command("hmm");
                        command("say "+ob->name()+"這一生看來是注定要多歷磨難了。");
                }
                break;
                case 2 :
                if( ntg>25 || ntg1>40+query("age", ob)){
                        command("nod");
                        command("say "+ob->name()+"天資過人，若能多加努力，必定能出人頭地。");
                } else {
                        command("shake");
                        command("say "+ob->name()+"如果知道〝笨鳥先飛〝的道理，還是有機會的。");
                }
                break;
                case 3 :
                if(str > 25)
                        command("say "+ob->name()+"如果有意鑽研，倒也不難成為一代大俠。");
                else    command("say "+ob->name()+"應該專精幾門武功，不可以貪多。");
                break;
                case 4 :
                if(per > 23 ) {
                        command("nod");
                        command("say "+ob->name()+"天生美貌，若能繼續保養，必定能長命百歲");
                }else {
                        command("shake");
                        command("say "+ob->name()+"相貌雖然如此，若能尋些仙緣，還是可以美容的。");
                }
                break;
                case 5 :
                if( dex1>(query("age", ob)+60)){
                        command("nod");
                        command("say "+ob->name()+"身輕如燕，已達一葦渡江的能力，再下苦功，定成大器");
                }else {
                        command("shake");
                        command("say "+ob->name()+"步伐沉重，在江湖中逃命才是重要的，練錯功了啊!");
                }
                break;
        }
        set_temp("mimi", 1, me);
        return 1;
}
