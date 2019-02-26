// suoha.c 梭哈，只支持兩人, Written by LLM
#define DIAN(x)     (x-1)/4
#define HUA(x)     x%4
#include <ansi.h>
inherit ROOM;

object *player=({});//玩家
int *cards = ({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
20,21,22,23,24,25,26,27,28});//所有的牌
int yazhu=0;//可以押注的標記
int chouma=0;//桌面已經押上的籌碼
int yazhu_chouma=0;//別人押的讓你跟的籌碼數
int wait_time=0;//等待最後讀秒記號
int quansuo=0;//全梭
mapping *suoha_cards=({
([
"anpai":0,
"mingpai":({}),
]),//莊家的牌
([
"anpai":0,
"mingpai":({}),
]),//對家的牌
});
string *all_card=({"８","９","⒑","Ｊ","Ｑ","Ｋ","Ａ" });
string *all_sort=({HIB"黑桃",HIR"方片",HIC"草花",HIR"紅桃",});
string *all_pai=({"散牌","一對","兩對","三條","順子","同花","飛機","炸彈","同花順"});

void suoha_init();
void deal_an_card();
void deal_ming_card();
int check_player(object);
int do_yazhu(string);
int do_gen();
object gen_ob(object);
void ob_win(object);
void game_over();
int do_buya();
int do_leave();
int do_quansuo();
string look_pai();
string type_paiju(object);
int check_chouma();
string query_obs();

string type_card(int x)//單張表述
{
    return sprintf("%s%s%s"NOR,all_sort[HUA(x)],HIW,all_card[DIAN(x)]);
}

string type_cards(mapping pai)//多張表述
{
    switch(pai["lv"])
    {
    case 2:
       return sprintf("%s大對加%s小對，兩對子",type_card(pai["ddui"]),type_card(pai["xdui"]));
    case 3:
    case 6:
    case 7:
        return sprintf(HIW"%s%s%s",all_card[DIAN(pai["max"])],NOR,all_pai[pai["lv"]]);
    default:
    return sprintf("%s%s",type_card(pai["max"]),all_pai[pai["lv"]]);
    }
}

mapping juesuan(int *ob_allcard)//決算出牌的類型
{
    mapping pai;
    int i,x,flag,*L;

    flag=0;
    x=sizeof(ob_allcard);
    L=sort_array(ob_allcard,1);//排序
    switch(x)
    {
    case 1:
        pai=([
            "lv": 0,
            "max" : L[0],
            ]);
        break;
    case 2:
        if(DIAN(L[0])==DIAN(L[1]))//點數相同是對子
            pai=([
                "lv": 1,
                "max" : L[1],//取對子的大牌
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[1],
            ]);
        break;
    case 3:
        if(DIAN(L[0])==DIAN(L[2]))//第一與第三點數相同是三隻
            pai=([
                "lv": 3,
                "max" : L[2],//隨便取一牌
            ]);
        else if(DIAN(L[0])==DIAN(L[1]))//只有一二點數相同 對子
            pai=([
                "lv": 1,
                "max" : L[1],//取大牌
            ]);
        else if(DIAN(L[1])==DIAN(L[2]))//只有二三點數相同 對子
            pai=([
                "lv": 1,
                "max" : L[2],//取大牌
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[2],//取最大牌
            ]);
        break;
    case 4:
        if(DIAN(L[0])+1==DIAN(L[1])&&DIAN(L[1])+1==DIAN(L[2])&&DIAN(L[2])+1==DIAN(L[3]))
            flag=1;
        if(HUA(L[0])==HUA(L[1])&&HUA(L[2])==HUA(L[3])&&HUA(L[1])==HUA(L[2]))//同花，再看是否順子
        {
            if(!flag)//同花
                pai=([
                "lv": 5,
                "max" : L[3],
                ]);
            else//同花順
                pai=([
                "lv": 8,
                "max" : L[3],
                ]);
        }
        else if(flag)//順子
            pai=([
            "lv": 4,
            "max" : L[3],
            ]);
        else if(DIAN(L[0])==DIAN(L[3]))//一四點數相同是炸彈
            pai=([
                "lv": 7,
                "max" : L[0],//隨便取一牌
            ]);
        else if(DIAN(L[0])==DIAN(L[2])||DIAN(L[1])==DIAN(L[3]))//一三或二四點數相同是三條
            pai=([
                "lv": 3,
                "max" : L[2],//隨便取一中間牌
            ]);
        else if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[2])==DIAN(L[3]))//一二且三四點數相同是兩對
            pai=([
                "lv": 2,
                "xdui":L[1],
                "ddui":L[3],
                "max":L[3],//取最大的牌
            ]);
        else
        {
            if(DIAN(L[0])==DIAN(L[1])) flag=1;
            else if(DIAN(L[1])==DIAN(L[2])) flag=2;
            else if(DIAN(L[2])==DIAN(L[3])) flag=3;
        if(flag)
            pai=([
                "lv": 1,
                "max" : L[flag],//取對子的大牌
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[3],//取最大的牌
            ]);
        }
        break;
    case 5:
        if(DIAN(L[0])+1==DIAN(L[1])&&DIAN(L[1])+1==DIAN(L[2])&&DIAN(L[2])+1==DIAN(L[3])&&DIAN(L[3])+1==DIAN(L[4]))
            flag=1;
        if(HUA(L[0])==HUA(L[1])&&HUA(L[1])==HUA(L[2])&&HUA(L[2])==HUA(L[3])
            &&HUA(L[3])==HUA(L[4]))//是同花，只有是否順子兩個可能
        {
            if(!flag)//同花
                pai=([
                "lv": 5,
                "max" : L[4],
                ]);
            else//同花順
                pai=([
                "lv": 8,
                "max" : L[4],
                ]);
        }
        else if(flag)//順子
            pai=([
            "lv": 4,
            "max" : L[4],
            ]);
        else if(DIAN(L[0])==DIAN(L[3])||DIAN(L[1])==DIAN(L[4]))//1,4或2,5相同，則為炸彈，取第四張
        {
            pai=([
            "lv": 7,
            "max" : L[4],//花色無關緊要，炸彈只要判斷點數
            ]);
        }
        else if(DIAN(L[0])==DIAN(L[2])||DIAN(L[2])==DIAN(L[4])||DIAN(L[1])==DIAN(L[3]))//三張一樣
        {
            if((DIAN(L[0])==DIAN(L[2])&&DIAN(L[3])==DIAN(L[4]))
                ||(DIAN(L[2])==DIAN(L[4])&&DIAN(L[0])==DIAN(L[1])) )//所剩兩張是對子
            {
                pai=([
                "lv": 6,
                "max" : L[2],//取中間那張，花色無關緊要
                ]);
            }
            else
                pai=([
                "lv":3,
                "max" : L[2],//取中間那張，花色無關緊要
                ]);
        }
        else
        {
        flag=0;
        if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[2])==DIAN(L[3])) flag=3;
        if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[3])==DIAN(L[4])) flag=4;
        if(DIAN(L[1])==DIAN(L[2])&&DIAN(L[3])==DIAN(L[4])) flag=4;
        if(flag)//小對子肯定有1，大對子肯定有3
        {
            pai=([
                "lv": 2,
                "xdui":L[1],
                "ddui":L[3],
                "max" : L[flag],//取大對子的大牌
            ]);
        }
        else
        {
        for(i=0;i<4;i++)
            if(DIAN(L[i])==DIAN(L[i+1])) flag=(i+1);
        if(flag)
            pai=([
            "lv": 1,
            "max" : L[flag],//取對子的大牌
            ]);
        else
            pai=([
            "lv": 0,
            "max" : L[4],//取最大的牌
            ]);
        }
        }
        break;
    }
    return pai;
}

int bi_daxiao(mapping card1,mapping card2)//比大小,card1大就是0，card2大就是1
{
    if(card1["lv"]==card2["lv"])//同類相比
    {
        if(card1["lv"]== 2)//兩對子
        {
            if(DIAN(card1["ddui"])>DIAN(card2["ddui"]))
                return 0;
            else if(DIAN(card1["ddui"])==DIAN(card2["ddui"]))
            {
                if(DIAN(card1["xdui"])>DIAN(card2["xdui"])
                    ||(DIAN(card1["xdui"])==DIAN(card2["xdui"])
                    &&card1["max"]>card2["max"]))
                    return 0;
                else return 1;
            }
            else return 1;
        }
        else if(card1["max"]>card2["max"]) return 0;
        else return 1;
    }
    else if(card1["lv"]>card2["lv"]) return 0;
    else return 1;
}

int do_sit()
{
        object me;
        int i;
        me = this_player();

    if( query_temp("suoha/being", me) )
                return notify_fail("你已經坐上桌了！\n");
    if( query_temp("duchang_chouma", me)<200 )
        return notify_fail("你的籌碼太少了！\n");
    i=sizeof(player);
        if (i<2)//還有空位
        {
        set_temp("suoha/being", 1, me);
                player+=({me});
                addn_temp("duchang_chouma", -5, me);//押５個
                yazhu_chouma+=5;//籌碼
        i=sizeof(player);
        message_vision("$N拿出5個籌碼押出去，坐上了座位！\n",me);
        if (i == 2)//滿2人自動開始
                {
               tell_room(this_object(), HIM"    好，可以開始發牌了！\n"NOR);
                        suoha_init();
                }
                return 1;
        }
        else
                return notify_fail("這裏已經滿人了！\n");
}

void suoha_init()
{
    chouma+=yazhu_chouma;
    yazhu_chouma=0;//清零
    deal_an_card();
}

void deal_an_card()//發暗牌
{
        int i, j;

    i=random(sizeof(cards));//隨機取一張
    suoha_cards[0]["anpai"]=cards[i];//發到手中暗牌
    message_vision("\n$N拿到了一張暗牌，看了一眼後，迅速地蓋在桌上！\n",player[0]);
    tell_object(player[0],"這張暗牌是："+type_card(cards[i])+"！\n");
    cards-=({cards[i]});//桌上這張牌被髮掉

    i=random(sizeof(cards));//從剩下來的牌中隨機再取一張
    suoha_cards[1]["anpai"]=cards[i];//發到手中暗牌
    message_vision("\n$N拿到了一張暗牌，看了一眼後，迅速地蓋在桌上！\n",player[1]);
    tell_object(player[1],"這張暗牌是："+type_card(cards[i])+"！\n");
    cards-=({cards[i]});//桌上這張牌被髮掉
    tell_room(this_object(), HIM"    現在開始給每個人發明牌了！\n"NOR);
        remove_call_out("deal_ming_card");//一秒後發第二張
        call_out("deal_ming_card",1);//一秒後發第二張
}

void deal_ming_card()//發明牌
{
    int i,j;
    string arg;
    mapping card1,card2;

    i=random(sizeof(cards));//隨機取一張
    suoha_cards[0]["mingpai"]+=({cards[i]});//發到手中的明牌
    message_vision("\n$N拿到了一張：" +type_card(cards[i])+"！\n",player[0]);
    cards-=({cards[i]});//桌上這張牌被髮掉
    i=random(sizeof(cards));//剩下的牌中隨機取一張
    suoha_cards[1]["mingpai"]+=({cards[i]});//發到手中第一張明牌
    message_vision("\n$N拿到了一張：" +type_card(cards[i])+"！\n",player[1]);
    cards-=({cards[i]});//桌上這張牌被髮掉

    card1=juesuan(suoha_cards[0]["mingpai"]);//決算出牌型
    card2=juesuan(suoha_cards[1]["mingpai"]);//決算出牌型
    j=bi_daxiao(card1,card2);//比出大牌
    tell_object(player[0],type_paiju(player[0]));
    tell_object(player[1],type_paiju(player[1]));
    if(j) arg=type_cards(card2);
    else arg=type_cards(card1);
    message_vision(HIY"\n　　$N的"+arg+HIY"説話！\n"NOR,player[j]);
    set_temp("suoha/shuohua", 1, player[j]);
    tell_object(player[j],"\n　想押就ya <籌碼數>,不押(buya)就認輸！\n");
        yazhu=1;//可以押注了
        call_out("check_player",60,player[j]);//一分鐘後檢查
    return;
}

int check_player(object me)
{
    object ob;

    if(!wait_time)
    {
        wait_time=1;
        call_out("check_player",10,me);//最後十秒;
        tell_object(me,"你還有十秒鐘時間，超時就表示認輸！\n");
        return 1;
    }
    yazhu=0;
    wait_time=0;
    message_vision("$N超時放棄了，大家亮底牌！\n");
    ob=gen_ob(me);
    call_out("juesheng",0,ob,1);//決勝
    return 1;
}

int do_yazhu(string arg)
{
    int i;
    string str;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("現在不是下注的時候！\n");
    if( !query_temp("suoha/shuohua", me))//是否為説話的方向
        return notify_fail("現在不是你説話！\n");
     if(!arg||sscanf(arg,"%d",i)!=1||(i!=5&&i!=10&&i!=20))
        return notify_fail("你要押多少籌碼？可選5個,10個,20個籌碼。\n");
    remove_call_out("check_player");//清除延時呼叫
    addn_temp("duchang_chouma", -i, me);
    yazhu_chouma=i;
    message_vision("$N哼了一聲，推上去一些籌碼説：“我押 "+i+" 個！敢跟嗎？”\n",me);
    ob=gen_ob(me);
    tell_object(ob,"你要跟(gen)的話，就是再上"+i+"個籌碼，不押(buya)就是認輸！\n");
    delete_temp("suoha/shuohua", me);
    set_temp("suoha/genhua", 1, ob);
    call_out("check_player",60,ob);
    return 1;
}

int do_gen()
{
    int i;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("現在不是跟注的時候！\n");
    if( !query_temp("suoha/genhua", me) )
        return notify_fail("現在不是你説話！\n");
    remove_call_out("check_player");//清除延時呼叫
    i=yazhu_chouma;//前面人押下的籌碼數
    addn_temp("duchang_chouma", -i, me);
    chouma+=(i*2);//兩個人的籌碼都加進去
    yazhu_chouma=0;//清零
    message_vision("$N微微一笑，也推了一些籌碼上去，説：“我跟 ！”\n",me);
    delete_temp("suoha/genhua", me);
    if(sizeof(suoha_cards[0]["mingpai"])==4)//牌發完了
    {
        yazhu=0;
        message_vision("\n牌已發完，大家亮底牌！\n",me);
        call_out("juesheng",1,me,0);//決勝
    }
    else//否則再發牌
    {
        remove_call_out("deal_ming_card");
            call_out("deal_ming_card",1);
        }
    return 1;
}
//跟牌的人
object gen_ob(object ob)
{
   if(sizeof(player)<2) return 0;
    if(player[0]==ob)
        return player[1];
    else
        return player[0];
}

int juesheng(object ob,int flag)//flag為真,則不管結果都是ob勝
{
    mapping card1,card2;
    int i,*pai1,*pai2;

    pai1=suoha_cards[0]["mingpai"];
    pai1+=({suoha_cards[0]["anpai"]});
    card1=juesuan(pai1);

    pai2=suoha_cards[1]["mingpai"];
    pai2+=({suoha_cards[1]["anpai"]});
    card2=juesuan(pai2);

    i=bi_daxiao(card1,card2);

    message_vision("\n$N的牌是『"+type_cards(card1)+"』\n"
    "\n$n的牌是『"+type_cards(card2)+"』\n",player[0],player[1]);
    if(!flag)
        ob=player[i];
    else
    {
        if(ob!=player[i])
            message_vision("$N懊悔地拍拍後腦勺：“早知道我就......！”\n",player[i]);
        else
            message_vision("$N得意地點點頭道：也虧你有自知之明啊！\n",player[i]);
    }
    message_vision("\n恭喜$N勝出，桌上籌碼全收！\n",ob);
    ob_win(ob);
    return 1;
}

void ob_win(object ob)
{
    addn_temp("duchang_chouma", chouma, ob);
    message_vision("\n這一局，$N一共贏了"+chouma+"個籌碼！\n",ob);
    game_over();
}

void game_over()
{
    if(sizeof(player))
    {
        delete_temp("suoha", player[0]);
        message_vision("$N站了起來。\n",player[0]);
    }
    if(sizeof(player)>1)
    {
        delete_temp("suoha", player[1]);
        message_vision("$N站了起來。\n",player[1]);
    }
    player=({});
    chouma=0;
    yazhu_chouma=0;
    suoha_cards=({
    ([
        "anpai":0,
        "mingpai":({}),
    ]),//莊家的牌
    ([
        "anpai":0,
        "mingpai":({}),
    ]),//對家的牌
    });
    wait_time=0;
    quansuo=0;
    cards =({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28});//所有的牌
//--------end---------
}

int do_buya()
{
    int i;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("現在不是跟注的時候！\n");
    if( !query_temp("suoha/shuohua", me) && !query_temp("suoha/genhua", me))//是否為説話的方向
        return notify_fail("現在不是你説話！\n");
    remove_call_out("check_player");//清除延時呼叫

    chouma+=yazhu_chouma;//加進前面人押下的籌碼數
    yazhu_chouma=0;//清零
    message_vision("$N皺了皺眉，突然一笑，説：“我不跟了 ！”\n",me);
    yazhu=0;
    message_vision("$N放棄跟牌，大家亮底牌！\n",me);
    ob=gen_ob(me);
    call_out("juesheng",1,ob,1);//決勝
    return 1;
}

int do_leave()
{
    object me,ob;
    me = this_player();

    if( !query_temp("suoha/being", me) )
                return notify_fail("你現在沒有在玩梭哈！想走就直接出大門。\n");
    ob=gen_ob(me);
    if(ob)//已經有兩個人
    {
        if(!yazhu)//還未發明牌
            return notify_fail("你現在不能離開!\n");
        yazhu=0;
        remove_call_out("check_player");//清除延時呼叫
        message_vision("$N不想再玩了！\n",me);
        chouma+=yazhu_chouma;//加進前面人押下的籌碼數
        call_out("juesheng",0,ob,1);//決勝
    }
    else//只有一個人，就是還沒開局
    {
        addn_temp("duchang_chouma", yazhu_chouma, me);//將剛剛押的返還
        yazhu=0;
        remove_call_out("check_player");//清除延時呼叫
        message_vision("$N不想再玩了！\n",me);
        chouma+=yazhu_chouma;//加進前面人押下的籌碼數
        call_out("game_over",0);//結束
    }
    return 1;
}

int do_quansuo()//全梭
{
    int i;
    string str;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("現在不是下注的時候！\n");
    if(sizeof(suoha_cards[0]["mingpai"])!=4)//牌發完了,最後一輪
        return notify_fail("現在不是最後一張，不能showhand！\n");
    if(quansuo)
        return notify_fail("對方已經showhand了，你只要決定跟(gen)還是不跟(buya)！\n");
    if( !query_temp("suoha/shuohua", me) && !query_temp("suoha/genhua", me) )
        return notify_fail("現在不是你説話！\n");
    remove_call_out("check_player");//清除延時呼叫
    quansuo=1;
    if( query_temp("suoha/shuohua", me))//説話方
    {
    i=(200-chouma/2);//最高是200,枱面上有一半
    addn_temp("duchang_chouma", -i, me);
        delete_temp("suoha/shuohua", me);
    yazhu_chouma=i;
    }
    else if( query_temp("suoha/genhua", me))//跟話方
    {
    i=yazhu_chouma;//先跟上前面的人押的注
    addn_temp("duchang_chouma", -i, me);
    chouma+=i*2;
    i=(200-chouma/2);
    addn_temp("duchang_chouma", -i, me);
        delete_temp("suoha/genhua", me);
    yazhu_chouma=i;
    }
    message_vision("$N將面前的籌碼“呼”地一下全推了上去：“我全梭了！敢跟嗎？”\n",me);
    ob=gen_ob(me);
    tell_object(ob,"你要跟(gen)的話，就是再上"+i+"個籌碼，不押(buya)就是認輸！\n");
    set_temp("suoha/genhua", 1, ob);
    call_out("check_player",60,ob);
    return 1;
}

string look_pai()
{
    switch(sizeof(player))
    {
    case 0:
        return "桌上的牌局還沒有開始呢！\n";
    case 1:
        return "現在"+player[0]->name()+"正坐在桌上等候別人的加入！\n";
    case 2:
        return type_paiju(this_player());
    }
}

string type_paiju(object me)
{
    string str,name1,name2,an1,an2;
    int *pai1,*pai2,i,j,k;

    pai1=suoha_cards[0]["mingpai"];
    pai2=suoha_cards[1]["mingpai"];
    i=sizeof(pai1);
    j=sizeof(pai2);
    an1=an2="※※※";//默認
    if(player[0]==me)
    {
        an1= type_card(suoha_cards[0]["anpai"]);
        name1="你";
    }
    else
        name1=player[0]->name();
    if(player[1]==me)
    {
        an2= type_card(suoha_cards[1]["anpai"]);
        name2="你";
    }
    else
        name2=player[1]->name();
    str=sprintf("　　%s的牌：%s%s\n"
"┌───┐┌───┐┌───┐┌───┐┌───┐\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"│%s│",name1,(query_temp("suoha/shuohua", player[0])?HIW"説話"NOR:""),
    (query_temp("suoha/genhua", player[0])?HIW"跟話"NOR:""),an1);
    for(k=0;k<4;k++)
    {
        if(k<i)
            str+=sprintf("│%s│",type_card(pai1[k]));
        else
            str+="│　　　│";
    }
    str+=sprintf("\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"└───┘└───┘└───┘└───┘└───┘\n\n"
"　　%s的牌：%s%s\n"
"┌───┐┌───┐┌───┐┌───┐┌───┐\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"│%s│",name2,(query_temp("suoha/shuohua", player[1])?HIW"説話"NOR:""),
    (query_temp("suoha/genhua", player[1])?HIW"跟話"NOR:""),an2);
    for(k=0;k<4;k++)
    {
        if(k<j)
            str+=sprintf("│%s│",type_card(pai2[k]));
        else
            str+="│　　　│";
    }
    str+="\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"└───┘└───┘└───┘└───┘└───┘\n\n";
    str+=sprintf("　桌面上的籌碼數是%d只，要跟進的籌碼數為%d只。\n\n",chouma,yazhu_chouma);
    return str;
}

int valid_leave(object me, string dir)
{
    if( query_temp("suoha", me) )
        return notify_fail("你正在打牌呢！要想走先離開(leave)牌桌！\n");
    return ::valid_leave(me, dir);
}

int check_chouma()
{
    int i;
    object me=this_player();
    if( !i=query_temp("duchang_chouma", me) )
        return notify_fail("你身上沒有任何籌碼！\n");
    write("目前你身上一共有"+chinese_number(i)+"只籌碼！\n");
    return 1;
}