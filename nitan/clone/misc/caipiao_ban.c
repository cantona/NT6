// 彩票投注系統 made by 葉雨飛(sunyc)@kync 2001/1/26
// remodify by Sunyc@kync 2002/7/24
// remodify By Sunyc@kync.tomud.com 5555 2002/11/24
// 更換獎金，可以累計，也不只是gold了
// 改為30選7

#include <ansi.h>
#include <localtime.h>
inherit ITEM;
inherit F_SAVE;

mixed *all_biao;
nosave string *touzhu;

int do_read(string);
int do_ya(string);
void enough_rest();
string show_player();
void auto_post(string title, string body);

string query_save_file()
{
        return DATA_DIR + "caipiao";
}

void create()
{
        set_name(HIG "彩票投注板" NOR, ({ "touzhu ban", "touzhu", "ban"}) );
        set("long",
                "這是全體玩家的彩票投注板。\n"
                "如何購買彩票請read rules，\n");
        set_weight(900000000);
        seteuid(getuid());
        set("unit", "塊");
        set("no_put", 1);
        set("no_get", 1);

        set("times", 1);
        restore();
}

void init()
{
        add_action("do_read", "read");
        add_action("do_ya", "touzhu");
        add_action("do_duijiang", "duijiang");
}

void enough_rest()
{
        delete_temp("busy");
}

int do_ya(int arg)
{
        object me, ob, caipiao;
        mapping biao;
        string str;
        int i;

        me = this_player();
        str = "";

        if( query("balance", me)/10000<10 )
                return notify_fail("錢莊至少要有十兩黃金才能投注。\n");

        if( query("end_ya") || query("duijiang") )
                return notify_fail("截止時間已過，等下次再來買吧......\n");

        if( query_temp("busy") )
                return notify_fail("請稍候幾秒鐘再試...\n");

        if( !intp(arg) || !arg ) {
                tell_object(me, "請選7個30以內的號碼，用逗號隔開。\n");
                tell_object(me,"例如：2,3,4,5,6,7,8\n");
                tell_object(me,"或者輸入-1進行機選。\n");
                tell_object(me,"請輸入您的選擇：");
                input_to("touzhu_1",me);
                return 1;
        } else {
                message_vision("$N把投票單寫好後，扔進了投票板。天上突然掉下了一張彩票，$N連忙揣了起來。\n",me);
                addn("balance", -100000, me);
                tell_object(me,"錢莊已經扣除了你十兩黃金。請在"+query("kaijiang_cdate")+"來等待結果吧！\n");
                tell_object(me,HIR"ＧＯＯＤ　ＬＵＣＫ 祝您好運！\n"NOR);
                caipiao=new("/clone/misc/caipiao.c");
                set("kaijiang_date", query("kaijiang_cdate"), caipiao);
                // 獲得一個連續字符串
                for(i=0;i<sizeof(query_temp("z_num", me));i++)
                        str+=query_temp("z_num", me)[i]+"";
                set("z_num", str, caipiao);
                set("times", query("times"), caipiao);
                caipiao->move(me);
                set("crypt", oldcrypt(str,0), caipiao);
                biao = ([
                        "id":query("id", me),
                        "name"  :me->name(1),
                        "z_num" :str,
                        "z_num_all":query_temp("z_num",me),
                        "jieguo":"未開獎",
                ]);
                delete_temp("z_num", me);
                if( !pointerp(all_biao) ) all_biao = ({biao});
                else all_biao += ({biao});
                save();
                remove_call_out("enough_rest");
                call_out("enough_rest", 1);
                return 1;
        }
        return 1;
}

void touzhu_1(string num,object me)
{
    int i,z,j=0;
    int h,k,p=0;
    int *jieguo=({});
    string str,*tmp=({});
    if(!num || num=="")
    {
        tell_object(me,"請選7個1-30中的號碼，用逗號隔開。\n");
        tell_object(me,"例如：2,3,4,5,6,7,8\n");
        tell_object(me,"或者輸入-1進行機選。\n");
        tell_object(me,"請輸入您的選擇：");
        input_to("touzhu_1", me);
        return;
    }
    if(atoi(num)==-1)
    {
        i=0;
        z=0;
        str="";
        while(p!=7)
        {
            i=random(30)+1;
            if(member_array(i,jieguo)!=-1) continue;
            else
            {
                jieguo+=({i});
                p++;
                continue;
            }
        }
        for(i=0;i<sizeof(jieguo);i++)
            str+=jieguo[i]+" ";
        set_temp("z_num", jieguo, me);
        write("\n您的投注號碼為"HIR+str+NOR"，您確定麼?[y/n]：");
        input_to("yn",me);
        return;
    }
    touzhu=explode(num,",");
    str="";
    for(i=0;i<sizeof(touzhu);i++)
    {
        if(!intp(z=atoi(touzhu[i])) || z<1 || z>30 || sizeof(touzhu)!=7) {j=1;break;}
        if(member_array(z,tmp)==-1)
            tmp+=({z});
        str+=" "+z;
    }
    if(sizeof(tmp)!=7) j=1;
    if(j)
    {
        tell_object(me,"請選7個1-30中的號碼，用逗號隔開。\n");
        tell_object(me,"例如：2,3,4,5,6,7,8\n");
        tell_object(me,"或者輸入-1進行機選。\n");
        tell_object(me,"請輸入您的選擇：");
        input_to("touzhu_1", me);
        return;
    }
    set_temp("z_num", touzhu, me);
    write("\n您的投注號碼為"HIR+str+NOR"，您確定麼?[y/n]：");
    input_to("yn",me);
    return;
}
void yn(string yn,object me)
{
    if( (yn[0]!='y' && yn[0]!='Y') ) {
        delete_temp("z_num", me);
        write("\n好吧，請重新投注。");
        tell_object(me,"請選7個1-30中的號碼，用逗號隔開。\n");
        tell_object(me,"例如：2,3,4,5,6,7,8\n");
        tell_object(me,"請輸入您的選擇：");
        input_to("touzhu_1", me);
        return;
    }
    else {
        write("\n儲存數據中...\n");
        do_ya(1);
        return;
    }
}

//void check(string yn,object me)
void check(object me)
{
    int money=0;
    int i;
 /*query_temp("check", if( oldcrypt(me),yn) != yn){
        write("對不起，您輸入的校驗碼有誤，不能給您發獎。\n");
        delete_temp("check", me);
        return;
    }
    else {   */
        write("\n恭喜您中了本期大獎...\n");
        delete_temp("check", me);
        write("ok...開始發獎\n");
        switch (all_biao[query_temp("num",me)]["jieguo"])
        {
        case "特等獎":money=query("last_gold");
            break;
        case "一等獎":money=query("last_gold")/5;
            break;
        case "二等獎":money=query("last_gold")/10;
            break;
        case "三等獎":money=query("last_gold")/100;
            break;
        case "四等獎":money=query("last_gold")/1000;
            break;
        }
        for(i=0;i<money;i++)
        {
            addn("money", 10000, me);
        }
        write(HIR"你中了"+chinese_number(money)+"兩黃金,已經撥入你的賬户！\n");
        message("system",HIW"〖泥潭福彩〗："+HIC" "+query("name",me)+HIW" 中了"+HIY" "+chinese_number(money)+HIW" 兩黃金，已經撥入帳户！\n"NOR,users());
        all_biao[query_temp("num",me)]["jieguo"]="已兑獎";
        //all_biao-=({query_temp("num", all_biao[me)]});
        save();//存盤
        restore();
        delete_temp("num", me);
        delete_temp("check", me);
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);
        return;
 //   }
}

int do_read(string arg)
{
    int i,j,k;
    object me;
    string name,str,str1,str2;
    mapping biao;

    me = this_player();

    if(arg == "rules")
    {
        write("本彩票系統已經開通，歡迎大家前來購彩。\n");
        write("投注請用touzhu\n");
        write("查詢請用read biao\n");
        write("查詢規則請用read duijiang\n");
        write("請使用duijiang指令，你的獎金將自動進入你帳户。\n");
        return 1;
    }
    if(arg == "biao")
    {
        restore();
        /*if( !pointerp(all_biao) || !sizeof(all_biao) )
        {
            write("\n還沒有人開始投注。\n");
            return 1;
        }*/
        write(show_player());
        return 1;
    }
    if(arg == "duijiang")
    {
        write("兑獎細則：\n");
        write("特等獎：七個數字全部吻合。      ——全部累計獎金.\n");
        write("一等獎：共有六個數字吻合。      ——全部累計獎金/5.\n");
        write("二等獎：共有五個數字吻合        ——全部累計獎金/50.\n");
        write("三等獎：共有四個數字吻合        ——全部累計獎金/100.\n");
        write("四等獎：僅有三個數字吻合        ——全部累計獎金/1000.\n");
        write("祝您玩得痛快!\n");
        return 1;
    }
    else        write("你要看什麼？購買規則請read rules，購買情況請read biao,兑獎規則請read duijiang。\n");
    return 1;
}
string show_player()
{
    int z,j,k,i,h, m;
    string str="";
    int *str_te,*str_1,*str_2,*str_3,*str_4,*str_5,*list, *str_old;
    mapping name;
    restore();
    i=0;
    if(!query("duijiang"))
    {
        h=sizeof(all_biao);
        str+=HIW"本期彩票已有 "HIG+chinese_number(sizeof(all_biao))+HIW" 位玩家投注，投注狀況如下：\n"NOR;
        str+="┏━━━━━━┳━━━━━━━━━━━┳━━━┓\n";
        while (i<h)
        {
            name=all_biao[i];
            /*if (strlen(name["name"])==6)
                str+= sprintf("┃%-28s┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);//刪除name["jieguo"]前(int)name["t_num"]  by wenwu
            else if(strlen(name["name"])==4)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+" "NOR,(int)name["z_num"],name["jieguo"],);
            else if(strlen(name["name"])==8)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==1)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==3)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==5)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==7)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==9)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
            else if(strlen(name["name"])==10)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
            else if(strlen(name["name"])==2)
                str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);*/
                        str+= sprintf("┃%-12s┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
                        i++;
        }
        str+="┗━━━━━━┻━━━━━━━━━━━┻━━━┛\n"NOR;
        if (query("end_cdate")) str+=HIW"本期投注截止時間："HIY+query("end_cdate")+HIW"\n本期彩票開獎時間："HIM+query("kaijiang_cdate")+"\n"NOR;
        else str+=HIR"本期彩票已經截止購買,"HIW"開獎時間："HIG+query("kaijiang_cdate")+HIW"。\n"NOR;
        str+=HIW"本期彩票累計獎金："HIY+query("all_gold")+HIG" 兩黃金。\n"NOR;
        return "/feature/more.c"->start_more(str);
    }
    str_te=str_1=str_2=str_3=str_4=str_5=list=str_old=({});
    str=HIW"第 "HIY+chinese_number(query("times")-1)+ HIW" 期彩票大獎已開出："+HIR+query("last_z_num_str")+NOR+"\n";
    str+=HIW"已有 "HIG+chinese_number(sizeof(all_biao))+HIW" 個玩家投注，中獎玩家如下：\n"NOR;
    i=0;
    h=sizeof(all_biao);
    for(i=0;i<h;i++)
    {
        k=0;
        for(z=0;z<sizeof(query("last_z_num"));z++)
        {
            j=all_biao[i]["z_num_all"][z];
            if(member_array(z,query("last_z_num"))!=-1) k++;
        }

                if ( all_biao[i]["jieguo"] == "已兑獎")
                        str_old+=({i});
                else
                {
        switch (k){
        case 7:
            str_te+=({i});
            all_biao[i]["jieguo"]="特等獎";
            break;
        case 6:
            str_1+=({i});
            all_biao[i]["jieguo"]="一等獎";
            break;
        case 5:
            str_2+=({i});
            all_biao[i]["jieguo"]="二等獎";
            break;
        case 4:
            str_3+=({i});
            all_biao[i]["jieguo"]="三等獎";
            break;
        case 3:
            str_4+=({i});
            all_biao[i]["jieguo"]="四等獎";
            break;
        default:
            str_5+=({i});
            all_biao[i]["jieguo"]="無獎";
            break;
        }
                }
    }
    save();
    list+=str_te+str_1+str_2+str_3+str_4+str_old;
    str_te=str_1=str_2=str_3=str_4=str_5=str_old=({});
    str+="┏━━━━━━┳━━━━━━━━━━━┳━━━┓\n";
    str+= sprintf("┃%-12s┃%-22s┃%-6s┃\n","玩家名","  投   注   號   碼   ","所中獎");
    str+="┣━━━━━━╋━━━━━━━━━━━╋━━━┫\n";
    z=0;
    h=sizeof(list);
    set("zhongjiang_num",h);
        m = 0;
    while (z<h)
    {
        i=list[z];
        name=all_biao[i];
        /*if (strlen(name["name"])==6)
            str+= sprintf("┃%-28s┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==4)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+" "NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==8)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==1)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==2)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==3)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==5)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==7)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==9)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==10)
            str+= sprintf("┃%-27s ┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);*/
                str+= sprintf("┃%-12s┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
                if ( name["jieguo"] != "已兑獎" )
                        m++;
        z++;
    }
    list=({});
    str+="┗━━━━━━┻━━━━━━━━━━━┻━━━┛\n"NOR;
        str+=HIW"本期尚未兑獎注數："HIM+chinese_number(m)+HIW"\n"NOR;
    str+=HIW"下期彩票發行時間："HIG+query("start_cdate")+HIW"\n"NOR;
    str+=HIW"下期彩票預計獎金："HIY+query("all_gold")+HIW" 兩黃金。\n"NOR;
    return "/feature/more.c"->start_more(str);
}
int do_duijiang()//兑獎指令
{
    int i,j,k,m,n,money;
    object me;
    me = this_player();
    restore();
    if(!query("duijiang"))
        return notify_fail("還未到兑獎時間！\n");
    if (query_temp("busy"))
        return notify_fail("稍候........\n");
    set_temp("busy",1);
    j=sizeof(all_biao);
    k=0;
        i=0;
        m = 0;
        n = 0;
    while ( i < j )
    {
        if( all_biao[i]["id"] == query("id", me) && all_biao[i]["name"] == query("name", me) )
        {
                        n = 1;
                        if ( all_biao[i]["jieguo"] != "已兑獎" && all_biao[i]["jieguo"] != "無獎" )
                        {
                                k = i + 1;
                                break;
                        }
                        else if ( all_biao[i]["jieguo"] == "已兑獎" )
                                m = 1;
                        else if ( all_biao[i]["jieguo"] == "無獎" )
                                m = 2;
        }
        i++;
    }
    delete_temp("busy");
    if ( !n || n == 0 ) return notify_fail("你並沒有買彩票呀！\n");
    else if ( k )
    {
        set_temp("check", all_biao[k-1]["z_num"]+""+all_biao[k-1]["t_num"], me);
        set_temp("num", k-1, me);
        write("您的中獎號碼是"+query_temp("check", me)+"。\n");
     //   write("請輸入您的校驗碼:");
        //input_to("check",me);
                check(me);
        return 1;
    }
        else if( m == 1 ) return notify_fail("你已經兑過獎了！\n");
    else if( m == 2 ) return notify_fail("你根本沒中獎，來兑個屁！\n");
}

void auto_post(string title,string body)
{
    mapping note;
    note = allocate_mapping(4);
    note["title"] = title;
    note["author"] ="彩票板";
   // "/cmds/std/news.c"->done_post(this_object(),note,body);暫註釋掉新聞提醒領獎 by wenwu
    return;
}
void clean_data()
{
    all_biao=({});
    save();
    restore();
}
