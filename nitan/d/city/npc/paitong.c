// paitong.c 牌童

# include <ansi.h>
inherit NPC;
int pieqian(object me);
int pieshuang(object me);
int do_deal();
int do_turn();
int yesorno();
string cstr(int i);

//全程變量
int sumi,summ;
int thecash;
int m1,m2,m3,i1,i2,i3,j1,j2,j3,k1,k2,k3;

void create()
{
        set_name("牌童", ({ "pai tong", "paitong", "kid" }));
        set("gender", "男性");
        set("long",
                "這是一個牌場小廝。\n"
        );
        set("age", 32);
        set("no_get", 1);
        set("immortal",1);

        set("inquiry", ([
                "賭"   : "要賭就賭，和我羅嗦？沒空沒空。\n",
                "押牌" : "快押快押，先給錢再押。別磨蹭。\n",
        ]) );
        set("book_count",1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_deal","deal");
        add_action("do_turn","turn");
}

int accept_object(object who, object ob)
{
        object obj;
        object me=this_player();

        if (me->is_busy())
                return notify_fail("你還在忙著呢，等一會吧。");
        me->start_busy(5);
        if (query("book_count"))
        {
                if( query("money_id", ob) )
                {
                        if( query_temp("tmark/押", ob) )
                        {
                                message_vision( HIG"牌童詫異地對$N說：你已經下過注了呀！\n"NOR,who);
                                return 0;
                        }
                        if (ob->value()<100)
                        {
                                message_vision( HIR"牌童不屑一顧地看著$N，說道：要下注至少一兩銀子！\n"NOR,who);
                                return 0;
                        }
                        if (ob->value()>20000)
                        {
                                message_vision( HIR"牌童搖了搖頭，對$N說道：這裡不歡迎孤注一擲，最多下二兩黃金。\n"NOR,who);
                                return 0;
                        }
                        addn("book_count",-1);
                        thecash = ob->value();
                        set_temp("tmark/押", 1, who);
                        sumi=summ=0;
                        i1=i2=i3=m1=m2=m3=j1=j2=j3=k1=k1=k3=0;
                        message_vision( HIY"牌童吆喝道：$N下注完成，發牌了。\n"NOR,who);
                        i1 = 1+random(13);
                        i2 = 1+random(13);
                        message_vision( WHT"莊家的牌是:    ？   和   "HIG+cstr(i1)+"\n"NOR,who);
                        if (i1>10) j1=10; else j1=i1;
                        if (i2>10) j2=10; else j2=i2;
                        sumi = j1 + j2;

                        m1 = 1+random(13);
                        m2 = 1+random(13);
                        message_vision( WHT"\n你的牌是:    "HIR+cstr(m1)+WHT"   和   "HIR+cstr(m2)+"\n"NOR,who);
                        if (m1>10) k1=10; else k1=m1;
                        if (m2>10) k2=10; else k2=m2;
                        summ = k1+k2;
                        if ((summ == 21) || ((summ==11) && (m1==1 || m2==1)) )
                        {
                                message_vision(HIG"啊！BLACKJACK，你真厲害，還得賠你雙倍！我呸！\n"NOR,who);
                                remove_call_out("destroying");
                                call_out("destroying", 0, me, ob);
                                pieshuang(who);
                                set("book_count",1);
                        }
                        else
                        {
                                message("vision", HIW"如果還要牌，請鍵入 deal,否則請鍵入 turn。\n"NOR,who);
                        }

                        remove_call_out("destroying");
                        call_out("destroying", 0, me, ob);
                        return 1;
                }
        }
        else
        {
                message_vision("已經有人在牌童對賭了，看來$N得等下一撥了。\n",who);
                return 0;
        }
}

int do_deal()
{
        object me=this_player();
        int m3;

        if( !query_temp("tmark/押", me) )
        {
                message_vision( MAG"牌童不耐煩地推了$N一把：去去去，注還沒下呢，押什麼牌啊！\n"NOR,me);
                return 1;
        }
        m3 = 1+random(13);
        message("vision", HIM"你還要一張啊，好吧，給你這張牌:   "HIR+cstr(m3)+"\n"NOR,me);
        if (m3>10) k3=10; else k3=m3;
        summ = summ+k3;
        if(m1==1 || m2==1 || m3==1)
                if(summ<12) summ=summ+10;

        if (summ>21)
        {
                message_vision( WHT"牌童笑嘻嘻地說：不好意思，你的牌漲爆了，我又贏了。\n"NOR,me);
        }
        else
        {
                if (summ==21)
                {
                        message_vision( HIW"牌童面如土色：又是２１點？你奶奶的，害老子賠雙倍！\n"NOR,me);
                        pieshuang(me);
                }
                else
                {
                        sumi = yesorno();
                        if(i1==1 || i2==1 || i3==1)
                        {
                                if(sumi<12) sumi=sumi+10;
                                if(sumi>21) sumi=sumi-10;
                        }

                        if (sumi>21 || sumi<summ)
                        {
                                if (sumi>21)
                                        message_vision( HIY"牌童喪氣地說：我的"HIG+cstr(i1)+cstr(i2)+cstr(i3)+HIY"漲爆了，天災人禍，賠你！\n"NOR,me);
                                else
                                        message_vision( HIY"牌童氣得一把把牌扔在桌上：我"HIG+cstr(i1)+cstr(i2)+cstr(i3)+HIY"，你點大，給你錢！撐死你！\n"NOR,me);
                                pieqian(me);
                        }
                        else
                        {
                                if (sumi == summ)
                                {
                                        message("vision", HIG"牌童賊兮兮的道：不好意思，我是"HIR+cstr(i1)+cstr(i2)+cstr(i3)+HIG"，同點莊家吃了。\n"NOR,me);
                                }
                                else
                                {
                                        message_vision( HIG"牌童笑嘻嘻地說：我的牌是"HIR+cstr(i1)+cstr(i2)+cstr(i3)+"\n"NOR,me);
                                        message_vision( HIG"牌童滿臉遺憾的表情：大家這麼熟的朋友了，怎麼能老贏你的錢呢？怪不好意思！\n"NOR,me);
                                }
                        }
                }
        }

        set_temp("tmark/押", 0, me);
        set("book_count",1);
        return 1;
}

int do_turn()
{
        object me = this_player();
        if( !query_temp("tmark/押", me) )
        {
                message_vision( HIY"牌童不耐煩地推了$N一把：去去去，注還沒下呢，押什麼牌啊！\n"NOR,me);
                return 1;
        }

        summ = summ+k3;
        if(m1==1 || m2==1 || m3==1)
                if(summ<12) summ=summ+10;

        sumi = yesorno();
        if(i1==1 || i2==1 || i3==1)
        {
                if(sumi<12) sumi=sumi+10;
                if(sumi>21) sumi=sumi-10;
        }

        if (sumi>21 || sumi<summ)
        {
                if (sumi>21)
                        message_vision( HIY"牌童喪氣地說：我的牌"HIG+cstr(i1)+cstr(i2)+cstr(i3)+HIY"漲爆了，虧大了人家我，賠你！\n"NOR,me);
                else
                        message_vision( HIY"牌童氣得一把把牌扔在桌上：我是"HIG+cstr(i1)+cstr(i2)+cstr(i3)+HIY"，算你走運！\n"NOR,me);
                pieqian(me);
        }
        else
        {
                if (sumi == summ)
                {
                        message_vision( HIG"牌童賊兮兮的道：不好意思，我是"HIR+cstr(i1)+cstr(i2)+cstr(i3)+HIG"，同點莊家吃了。嘿嘿嘿...\n"NOR,me);
                }
                else
                {
                        message_vision( HIG"牌童笑嘻嘻地說：我的牌是"HIR+cstr(i1)+cstr(i2)+cstr(i3)+"\n"NOR,me);
                        message_vision( HIG"牌童滿臉遺憾的表情：大家這麼熟的朋友了，贏你的錢別不開心了！\n"NOR,me);
                }
        }

        set_temp("tmark/押", 0, me);
        set("book_count",1);
        return 1;
}

int pieqian(object me)
{
        object ob,ob1;

        if(thecash<10000)
        {
                ob = new("/clone/money/silver");
                ob->set_amount(thecash/100*2);
                ob->move(me);
        }
        else
        {
                ob = new("/clone/money/gold");
                ob->set_amount(thecash/10000*2);
                ob->move(me);
                if((thecash % 10000)!=0)
                {
                        ob1 = new("/clone/money/silver");
                        ob1->set_amount((thecash-((thecash/10000*10000)))/100*2);
                        ob1->move(me);
                }
        }
        set_temp("tmark/押", 0, me);
        return 1;
}

int pieshuang(object me)
{
        object ob,ob1;

        if(thecash<10000)
        {
                ob = new("/clone/money/silver");
                ob->set_amount(thecash/100*3);
                ob->move(me);
        }
        else
        {
                ob = new("/clone/money/gold");
                ob->set_amount(thecash/10000*3);
                ob->move(me);
                if((thecash % 10000)!=0)
                {
                        ob1 = new("/clone/money/silver");
                        ob1->set_amount((thecash-((thecash/10000)*10000))/100*3);
                        ob1->move(me);
                }
        }
        set_temp("tmark/押", 0, me);
        return 1;
}

int yesorno()
{
        object me=this_player();

        if (i1==1 || i2==1)
                if(sumi<12) sumi=sumi+10;

        if (sumi>17) return sumi;
        else
        {
/* 似乎這個概率不太對 by xmmy

是關于押牌房(就是賭21點)的一個大bug。
在賭21點的時候，系統是設置讓牌童在拿到的牌在小于15點的時候就繼續要牌，
大于等于15點的話：
                如果玩家兩張牌的點數大于牌童的點數，還是繼續要牌，
                如果玩家的點數比牌童的點數小，牌童就直接攤牌。
這個算法其實並不是最優策略。
通過計算可以發現（具體計算太復雜，因為要考慮A既可以算1點，也可以算11點
的情況，我是先不考慮A可以算11點的情況，算出有問題，再通過實踐來驗証的），
在大于等于16點的時候才攤牌是最佳的選擇。呵呵，具體的計算過程我就不發過來了，

如果你要的話，我再打給你（因為我是在紙上算的）。
附上我實踐的一些數據：
   我的機器人是設置成如果我的牌小于16點就繼續要牌，大于等于16點就攤派。
   長安、揚州兩處押牌房一起掛，從晚上12點到早上7點，一般可以賺七萬到八萬gold。
   我掛機紀錄的數據：win=39655,lost=37310,
   win就是贏的次數(如果剛好21點贏雙份的話我是算贏兩次的)， lost就是輸的次數。
建議吧押牌的程序改成牌童在大于等于16點的時候才攤牌，這樣子就不會再有bug了。
btw:呵呵，我的bug沒有讓別人知道的，所以不用擔心會出現舊站的時候cash滿天飛的情
況。
    我的錢現在有二三十萬吧（因為我只用過幾次，賺太多了也沒意思），我會注意控
制我的錢的，
     不會引起mud系統的金錢混亂。
     xixi,那為什麼我要把bug交出來呢？是因為上次做bug的時候被其他玩家看見了，
為了避免出現舊站的混亂，我就忍痛來報告了。當然啦，還是那句話，我是不要獎勵的。
        作為xkx100的一個老玩家，能為xkx100做點貢獻我認為很欣慰，總算沒白跳進
泥潭一場!
                if (sumi<14)

*/
                if (sumi<15)
                {
                        i3 = 1+random(13);
                        if (i3>10) j3=10; else j3=i3;
                        return sumi+j3;
                }
                else
                {
                        if(random(21)>10)
                        {
                                i3 = 1+random(13);
                                if (i3>10) j3=10; else j3=i3;
                                return sumi+j3;
                        }
                        else return sumi;
                }
        }
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

string cstr(int i)
{
        switch(i) {
                case 1:
                        return "Ａ";
                case 2:
                        return "２";
                case 3:
                        return "３";
                case 4:
                        return "４";
                case 5:
                        return "５";
                case 6:
                        return "６";
                case 7:
                        return "７";
                case 8:
                        return "８";
                case 9:
                        return "９";
                case 10:
                        return "Ｔ";
                case 11:
                        return "Ｊ";
                case 12:
                        return "Ｑ";
                case 13:
                        return "Ｋ";
                default:
                        return "";
        }
}