// 絕地末日﹒NPC: /d/suzhou/npc/xi-laifu.c  辦喜宴出現的喜來福老板
// llm 99/07/09 修改2000.09

#include <ansi.h>

inherit BUNCHER;
int ask_party();
void start_party(object,object);
int do_start();
int do_serve();
void finish_party(object,object);
int give_money(object,object);
int do_kill(string);
int do_exert();
int do_steal(string);
int kick(object);

void create()
{
        set_name("喜來福",({"xi laifu","xi","laifu" }));
   set("title", "迎賓樓老板");
   set("age", 42);
   set("gender", "男性");
   set("attitude", "friendly");
   set("combat_exp", 50000);
   set_skill("unarmed", 100);
   set_skill("dodge", 100);
   set_skill("parry", 100);
   set("per", 20);

        set("inquiry", ([
                "name": "喜來福呵呵笑道：“小可名字有點福氣，姓喜名來福，就是這裡的老板。\n",
                "here": "喜來福搖頭晃腦地說：“我們迎賓樓可是方圓幾十裡的名樓，辦喜宴還得要來我們這裡。”\n",
                "宴" : (: ask_party :),
                "喜宴" : (: ask_party :),
                "席" : (: ask_party :),
                "酒席" : (: ask_party :),
                "喜酒" : (: ask_party :),
                "酒宴" : (: ask_party :),
                "party" : (: ask_party :),
                "送禮":"喜來福呵呵笑道：“新人的禮金交給我好了，我來轉交給他們！”\n",
                "禮":"喜來福呵呵笑道：“新人的禮金交給我好了，我來轉交給他們！”\n",
                ]) );
   setup();
   carry_object("/d/beijing/npc/obj/hupi")->wear();
}

void init()
{
        object me=this_player();
        ::init();
        if( !query("no_fight", environment()) )
                set("no_fight", 1, environment());//將此地設為不能戰鬥
        if( interactive(me) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("do_serve", "kaixi");
        add_action("do_finish", "jieshu");
        add_action("do_start", "kaishi");
        add_action("do_kill", ({"kill","fight","hit","perform","yong","ge","touxi"}));
        add_action("do_steal", "steal");
        add_action("do_exert", ({"exert","yun"}));
}

int greeting(object me)
{
        if( !me || environment(me) != environment() ) return 0;
        if( query_temp("married_party", me))//新人
                write("喜老板對你拱手道：“喜宴布置得差不多了，等客人來齊了您問我喜宴就行了！”\n");
        else if( query_temp("kick", me))//被踢的人
                write("喜來福沖你哼了一聲：“不想嘗嘗老夫的佛山無影腿就老實點。”\n");
        else if(!query_temp("party_finish"))//喜宴未結束，吃喜酒的人
                write("喜老板點點頭：“喲！您來吃喜酒呀！新人的禮金由我代收，交給我就行。”\n");
        else
                write("喜老板一拱手：“您吃好，慢走！”\n");
        return 1;
}

int accept_object(object me, object ob)
{
        int i;
        if(!query("name1")||!query("name2"))
                return notify_fail("喜來福迷惑地看看你：“我們現在沒給誰辦喜酒呀！你送誰的禮？”\n");
        if(query_temp("party_finish"))
                return notify_fail("喜老板呵呵一笑：“您來遲了，喜宴已經結束了，您還是直接給新人吧！”\n");
        if( !query("money_id", ob) )
             return notify_fail("喜老板皺了皺眉頭：“如今早就不時興送東西了，喝喜酒還是給現金的好！”\n");
        if( query_temp("married_party", me))//新人
                return notify_fail("喜老板一愣，又笑道：“自己給自己送禮？也沒有這樣吃飽了撐著的事吧！”\n");
        i = ob->value();
        if( !query_temp("songli", me))//防止玩家反復送禮騷擾頻道
        {
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf("%s恭賀%s和%s新婚大喜，送上賀禮"+MONEY_D->price_str(i)+"！\n",me->name(),query("name1"),query("name2")));
                set_temp("songli", 1, me);
        }
        if( query_temp("songli", me)>10 && i<100000 )
        {
                addn_temp("songli", -1, me);
                call_out("kick",0,me);
        }
        else if( query_temp("songli", me)>7 && i<100000 )
        {
                write("喜來福不悅道：“我警告你啊！你這送禮就到此為止吧，再下去我不客氣了！”\n");
                addn_temp("songli", 1, me);
        }
        else if( query_temp("songli", me)>4 && i<100000 )
        {
                write("喜來福收起笑臉道：“你是不是來搗亂的？要送禮就一筆頭送完算了！”\n");
                addn_temp("songli", 1, me);
        }
    else
        addn_temp("songli", 1, me);
        addn("money",i);//記錄送來的禮金數
        return 1;
}

int ask_party()
{
        object me,ob,wife;
        ob=this_object();
        me=this_player();
        if (! objectp(me)) return 1;
        if( query_temp("host_of_party", me) )
                message_vision("$N對$n說：“您的喜宴不是正在開著嗎？”\n", ob, me);
        if( !query_temp("married_party", me) )
                message_vision("$N翻了翻帳本，對$n遲疑的問道：“媒婆好象沒有在我這裡給您訂喜筵，會不會搞錯了？”\n", ob,me);
        if( query("gender", me) == "女性" )
                message_vision("$N笑著對$n說道：“媒婆是以新郎的名義在這訂酒席，還是叫你的丈夫來問吧！”\n", ob,me);
        if( !query("couple/couple_id", me) )
                message_vision("$N對$n說：新娘子都沒來，這喜宴怎麼開？\n", ob,me);
        if( !objectp(wife=present(query("couple/couple_id", me),environment(me))) )
                return notify_fail("新娘子都沒來，這喜宴怎麼開？\n");
        if( query_temp("ready_to_party", ob) )
                message_vision("$N對$n不好意思的說：我這正開著一席呢，要不您明兒再來吧！\n",ob,me);
        if( query("short", environment(ob)) != "喜福堂" )
                message_vision("$N對$n為難的說：“對不起，等我回店準備了再說吧！”\n",ob,me);
        if( query_temp("ready_to_ask", me) )
                message_vision("$N對$n不耐煩的說道：“不是都說了嗎？你怎麼問個沒完！”\n",ob,me);
        else
        {
                set_temp("ready_to_ask", 1, me);//新郎問過了的記號
                set_temp("ready_to_party", 1, ob);//老板開始記號
                set_temp("host_of_party", 1, me);//新郎的記號
                delete_temp("married_party", me);
                if (objectp(wife))
                delete_temp("married_party", wife);
                message_vision("喜來福對$N點點頭道：“您老盡管吩咐！我馬上給您準備！”\n",me);
                call_out("start_party",1,ob,me);
        }
        return 1;
}

void start_party(object ob,object me)
{
        command("chat* "+name()+"一拱手道：“良宵一刻值千金，酒不醉人人自醉，今日迎賓樓榮幸地為"+query("name1")+
                "和"+query("name2")+"\n大開喜宴，恭迎各位前來捧場！\n\n");
        message_vision("喜老板轉身又對$N小聲問了幾句。\n",me);
        write("您要開始，就輸入 kaishi，如果想開席，就輸入 kaixi，\n"
                "大家吃飽了，喝足了就可以結束了(jieshu)。");
        delete_temp("ready_to_ask", me);
        set_temp("ready_to_party", 1, me);//新郎準備開始記號
}

int do_start()
{
        object me,ob,obj,*list;
        int i;
        me = this_player();
        ob = this_object();

        if( !query_temp("host_of_party", me) )
        {
                if( !query_temp("married_party", me) )
                        return notify_fail(name()+"對你說：“你又不是新人！喊什麼喊？”\n");
                return notify_fail(name()+"對你說：“你先ask xi about 喜宴，讓我告訴你酒席進行程序！”\n");
        }
        if( !query_temp("ready_to_party", ob) )
                return notify_fail(name()+"對你說：“開始什麼呀，現在又沒人辦婚宴！”\n");
        if( query_temp("party_start_already", me) )
                return notify_fail(name()+"笑呵呵地對你說：“你看這不是已經開始了嘛！”\n");

        message_vision("$N對$n點點頭說：“喜老板，喜宴可以開始了！”\n\n"
                "$n立刻大聲喊著：“給客人上～～喜～～酒～～”\n\n",me,ob);
        set_temp("party_start_already", 1, me);//新郎已經開始記號
        delete_temp("ready_to_party", me);
        tell_room( environment(ob), HIY"喜老板又手一揮，幾個彩衣樂手立刻吹起嗩吶、奏起喜樂。\n"NOR);

        list = all_inventory(environment(me));
        i = sizeof(list);
        while (i--)
        {
       if( obj=new("/d/suzhou/npc/obj/xijiu"))
       obj->move(list[i]);
   }
   tell_room(environment(), "\n從內堂走出一排漂亮的黃衫少女，依次走到每個人面前。\n"
                "黃衫少女遞給你一杯斟滿喜酒的玉盞又走開了去。\n");
   call_out("finish_party", 600, me,ob);//10分鐘後自動結束
   return 1;
}

int do_serve()
{
        object ob,me,food;
        ob=this_object();
        me=this_player();

        if( !query_temp("host_of_party", me) )
                return notify_fail(name()+"斜眼瞪了你一眼道：“主人沒說話，你嚷什麼？！”\n");
        if( !query_temp("party_start_already", me) )
                return notify_fail(name()+"對你笑說：“還沒告訴我開始(kaishi)，我怎麼好開席？”\n");

        message_vision("$N大聲嚷嚷著：上菜，上菜！\n", me);

        tell_room(environment(me), "“來啦！”四五個小伙計從內堂魚貫而出，一盤盤美味佳肴立刻擺上了桌。\n");
        if(food=new("/d/suzhou/npc/obj/jiuyan"))
        food->move(environment(me));
        return 1;
}

int do_finish()
{
        object ob=this_object();
        object me=this_player();

        if( !query_temp("host_of_party", me) )
                return notify_fail(name()+"不滿意地瞪了你一眼：“你吃你的，不關你事不要亂說話！”\n");

        if( !query_temp("party_start_already", me) )
                return notify_fail(name()+"呵呵笑道：“喜筵不是已經結束了嗎！”\n");
        message_vision("$N對$n說道：“客人吃得都不錯，十分感謝喜老板的安排！”\n", me, ob);
        remove_call_out("finish_party");
        call_out("finish_party", 2, me,ob);
        return 1;
}

void finish_party(object me,object ob)
{
        int i;
        object *list,ob1,ob2;

        message_vision(HIC"\n$N大聲說道：“小小薄宴，怠慢諸位，$n的喜宴就此結束，多謝大家光臨！\n"NOR, ob,me);

        if( !me || environment(me) != environment(ob) )
        {
            tell_room(environment(ob), "\n一旁的黃衫少女連忙上來把酒席上的殘羹剩菜收拾幹凈抬下去。\n");
            if(ob1=present("jiuxi", environment(ob)))
            destruct (ob1);
            remove_call_out("give_money");
            call_out("give_money",1,0,ob);
        }

        command("gongxi"+query("id", me));

        set_temp("party_finish", 1, me);
        delete_temp("party_start_already", me);
        delete_temp("host_of_party", me);
        set_temp("party_finish", 1, ob);
        message("vision","\n一旁的黃衫少女連忙上來把酒席上的殘羹剩菜收拾幹凈抬下去。\n",environment(me));
        if(ob1=present("jiuxi", environment(ob)))
            destruct (ob1);
        list = all_inventory(environment(ob));
        i = sizeof(list);
        while (i--)
        {
            ob2=new("/d/suzhou/npc/obj/xitang");
            set("name", me->name()+"和"+query("couple/couple_name", me)+"的喜糖", ob2);
            ob2->move(list[i]);
        }
        tell_room(environment(ob), "\n喜老板吩咐手下的伙計把喜糖一包包地發給每一個人。\n");
        remove_call_out("give_money");
        call_out("give_money",1,me,ob);
}

int give_money(object me,object ob)
{
        int money,v;
        
        delete("no_fight", environment());
        if( !me || environment(me) != environment(ob) )
        {
                   message_vision("喜老板突然向四周一看：“咦？人去哪裡了，連代收的禮金都不要了？”一邊\n"
                        "搖著頭一邊向內堂走去，伙計、黃衫少女也一齊走進去，喜福堂一下子空下來了。\n",ob);
                log_file("static/marry_money",sprintf("%s(%s)%s",me->name(),query("id", me),query("money", ob)));
                delete_temp("ready_to_party", ob);
                ob->move("/u/lonely/workroom");//不要直接dest，以備查
           return  1;
        }
        //注：由于實際過程有的玩家會收到大量的喜金，有時會超過負重，造成喜金丟失
        //因此改成進帳戶
        message_vision("\n喜老板笑呵呵地走到$N面前，一揮手，旁邊的小伙計捧過來一本帳本，喜老板說道：\n"
                "“這是小可代二位收下的客人送上的禮金，一共是"+MONEY_D->price_str(query("money", ob))+"\n"
                "我已經托伙計轉進了您的錢莊帳戶，您可去查看查看！”說完然後一齊走進內堂不見了。\n",me);
        money=query("money", ob);
        addn("balance", money, me);
        delete_temp("ready_to_party", ob);
          ob->move("/u/lonely/workroom");//不要直接dest，以備查
        return 1;
}

int do_kill(string arg)
{
        write("喜來福沖著你直搖頭：“這大喜的日子動手幹什麼啊！”\n");
        return 1;
}

int do_exert()
{
   write("你鬼鬼祟祟地一運氣。\n喜來福沖你瞪了一眼：“剛吃過飯，不要亂用內功！”\n");
   return 1;
}

int do_steal(string arg)
{
        object me = this_player();
        object ob = this_object();
        if( query_temp("steal_xiyan", me)<5 )
        {
                message_vision("$N伸出手，想要偷點什麼。\n$n對$N罵道：怎可隨便光天化日施盜行竊！\n",me,ob);
                addn_temp("steal_xiyan", 1, me);
                return 1;
        }
        else if( query_temp("steal_xiyan", me)<8 )
        {
                message_vision("喜來福氣得對$N罵道：“你要還是賊性不改的話，我叫衙門裡的人抓你做牢去！”\n",me);
                addn_temp("steal_xiyan", 1, me);
                return 1;
        }
        message_vision("門外沖進來幾個捕快，指著$N問喜來福：“是這個小偷嗎？”喜老板道：“正是正是！”\n"
        "于是捕快們一擁而上，將$N拷起，拖了出去。\n",me);
        tell_object(me,"你還沒搞清楚是什麼事，就被一群捕快拖著出了迎賓樓......\n");
        set("jianyu/what", "steal", me);//做牢原因
        set("jianyu/where", "suzhou", me);//被捕地點
        me->apply_condition("jianyu",20);//做牢時間
        me->move("/d/changan/prison");//進監獄
        return 1;
}

int kick(object me)
{
        if( !me || environment(me) != environment() ) return 0;
        message_vision("喜老板怒喝一聲：“警告了你還不聽，看腳！”說完，喜來福一抬腿，$N大驚失色，\n"
                "卻怎麼也無法躲得過這一腳。“□！”地一聲，身子從窗戶裡飛了出去。\n"
                "喜老福撣撣身上塵土，呵呵笑道：“沒事了，大家坐！坐！！”\n",me);
        tell_room("/d/suzhou/xiaozheng","突然一個人影從西邊的迎賓樓二樓飛出來，“蓬”地重重摔在地上，細看卻是一個差點摔死的人。\n");
        set_temp("kick", 1, me);
        me->move("/d/suzhou/baodaiqiao");//移到樓下的大街房間裡即可
        tell_object(me,"你只覺屁股一吃痛，身子已飛起來，“蓬”地落在地上，你的五臟六腑似乎全震盪起來了……\n");
        if( query("qi", me)>30)addn("qi", -30, me);
        else me->unconcious();
}
