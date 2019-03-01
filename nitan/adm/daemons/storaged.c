// leagued.c
/*
每個人一個mapping
每個人一個計數器，計算他曾經存放過多少個物品
存放物品都會有一個序列號
根據此序列號取出物品
原生物件不能存放
按月租用
租用代價要易于修改

*/
#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

void create()
{
        mapping m;
        seteuid(getuid());
        restore();
        m=query_entire_dbase();
        if(!mapp(m)||undefinedp(m["data"]))
        {
                set("data",([]));
                save();
        }
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

public string query_save_file() { return DATA_DIR "storage"; }

//=================具體實現部分=======================

int DoMonFee(object me,int mon)
{
        mixed res;
        int onl,fee,j;
        string arg,sql;
        arg=query("id", me);
        res=DATABASE_D->do_sql("select on_time,fee_time from users where id="+DB_STR(arg));
        if(!res)
        {
                write("查詢出錯，請詢問遊戲管理員。\n");
                return 0;
        }
        else
        {
                sscanf(res[0]+"0","%d",onl);
                sscanf(res[1]+"0","%d",fee);
                onl/=10;fee/=10;

                if(wizardp(this_player())) write("你目前的遊戲點可用數"+(fee-onl/3600)+"\n");
                
                if(fee - onl/3600 > (mon*150)+50  )
                {
                        sql="update users set fee_time=fee_time-"+150*mon+",endrgt=now() where id="+DB_STR(arg);
                        if ((DATABASE_D->do_sqlexec(sql))<1)
                        {
                                write("扣除點數失敗，請盡快聯系遊戲管理員查明原因。\n");
                                return 0;
                        }
                        else
                        {
                                //扣除點數成功                                
                                me->save();
                                //重新從數據庫取，以驗証是否真的已經改變
                                       res=DATABASE_D->do_sql("select fee_time from users where id="+DB_STR(arg));
                                       sscanf(res[0]+"0","%d",j);
                                sql=sprintf("insert into reg_log (id,add_hours,new_fee_time,time) values (%s,%d,%d,now())",DB_STR(arg),-150*mon,j/10);
                                if(DATABASE_D->do_sqlexec(sql) < 1)
                                        log_file("mysql.log",ctime(time())+":"+sql);
                                write("你的遊戲點已經扣除了"+mon*150+"點！\n");
                        }
                }
                else
                {
                        write("你的遊戲點已經不夠用于開通（或續費）儲物櫃了（你得有至少"+(mon*150+50)+"點才可以），請趕快匯款購卡吧。\n");
                        return 0;
                }
        }
        return 1;
}

int ExpireDate(string id)
{
        return query("data/"+id+"/expiredate");
}

int AccountOk(string id)
{
        return (ExpireDate(id)>=time());
}

int ExistAccount(string id)
{
        mapping m=query_entire_dbase();
        if(undefinedp(m["data"]))
        {
                set("data",([]));
                return 0;
        }
        return !undefinedp(m["data"][id]);
}

int CancelAccount(object me)
{
        mapping m;
        m=query("data/"+query("id", me));
        if(!mapp(m))
        {
                write("你還沒有開過戶呀！\n");
        }
        else 
        {
                if( query_temp("sure_cancel", me) != 1 )
                {
                    write("帳戶取消我們也不會退回租費的喲！\n如果你還沒想好，可以先把東西都取走。\n(請注意，再次輸入取消命令將不再提示本信息)\n");
                    set_temp("sure_cancel", 1, me);
                    return 1;
                }
                m=query("data/"+query("id", me)+"/objects");
                if(sizeof(m)==0)
                {
                        m=query("data/"+query("id", me));
                        if(!mapp(m))
                        {
                            write("你的帳戶未能成功取消，請聯系管理員。\n");
                            return 1;
                        }
                        log_file("storage.log","cancel:"+query("name", me)+"("+query("id", me)+")取消了帳戶！類型："+m["typ"]+"\n");
                        delete("data/"+query("id", me));
                        write("你的帳戶已經成功取消！\n");
                }
                else
                {
                        write("取消帳戶前，請先將你的物品全部取出來！\n");
                }
        }
        return 1;
}
        
int OpenAccount(object me,string arg)
{
        mapping m;
        string id;
        int i,j,k,obcount;
        id=query("id", me);
        if(ExistAccount(id))
        {
            write("你已經開過戶了！請使用cw fee <幾個月> 續租！\n");
            return 1;
        }
        if(sscanf(arg,"%d",i)!=1)
            i=0;
        if( query_temp("yes_i_know", me) != 1 )
        {
            set_temp("yes_i_know", 1, me);
            write("儲物櫃每月租費為：\n類型0\t需要100兩黃金\n類型1\t需要200兩黃金\n類型2\t需要花150個遊戲點\n"
                "請確認你已經知道以上資費情況，再次輸入開戶命令將不再提示直接開戶！\n");
            return 1;
        }
        switch(i)
        {
                case 0:
                        k=me->pay_money(1000000);
                        obcount=35;
                        break;
                case 1:
                        k=me->pay_money(2000000);
                        obcount=80;
                        break;
                case 2:
                        //具體的扣點
                        if(k=DoMonFee(me,1))
                                obcount=500;
                        break;
                default:
                        k=0;
                        obcount=0;
        }
        if(k)
        {
                j=time()+86400*30;
                //初始化一些參數
                m=([
                        "cnt":0,
                        "typ":i,
                        "expiredate":j,
                        "max_obs":obcount,
                        ]);
                set("data/"+query("id", me),m);
                log_file("storage.log","open:"+query("name", me)+"("+query("id", me)+")開設了第"+i+"類帳戶！\n");
                write("恭喜你，你的開戶已經成功。你的儲物櫃可以儲藏"+obcount+"件物品，你可以用到"+CHINESE_D->cctime(j)+"為止。\n");
                save();
                return 1;
        }
        else
        {
                if(i!=2)
                        write("對不起，你的錢未帶夠！請帶上足夠的錢然後使用cw open 0 或cw open 1來開戶！\n"+i+" "+k);
                else
                        write("對不起，你的遊戲點不夠，請先續上足夠的遊戲點然後使用cw open 2來開戶！\n");
        }
        return 1;
}

void ListObject(object me)
{
        string k,res="你的儲物櫃裡有：\n";
        mapping m,om;
        int i,j;
        string id;
        id=query("id", me);
        if(!ExistAccount(id))
        {
                write("請先開戶！\n");
                return ;
        }
        if(!AccountOk(id))
        {
                write("請先續費！\n");
                return ;
        }
        i=wizardp(me);
        m=query("data/"+id+"/objects");
        if(!mapp(m)||sizeof(m)<1)
        {
                write("你還沒有儲存過什麼物品。\n");
                return ;
        }
        j=0;
        foreach(k in keys(m))
        {
                om=m[k];
                j++;
                res+=sprintf("第%d個物品 編號%5s ： %20s(%10s) 數量：%d %s\n",j,k,om["name"],om["id"],om["num"],(i?om["file"]:""));
        }
        me->start_more(res);
}

void PutObject(object me,string arg)
{
        object ob;
        string file,id,key,str;
        mapping m;
        int i,j;
        id=query("id", me);
        if(!ExistAccount(id))
        {
                write("請先開戶！\n");
                return ;
        }
        if(!AccountOk(id))
        {
                write("請先續費！\n");
                return ;
        }
         ob=present(arg,me);
        if(!objectp(ob))
        {
                write("沒有發現物品"+arg+"！\n");
                return ;
        }
        file=file_name(ob);
        //什麼樣的物品不能存呢？
        if(strsrch(file,"#")==-1 || ob->is_character() || living(ob))
        {
                write("對不起，該物品不可以儲存！\n");
                return ;
        }
        if( query("task_ob", ob) || query("unique", ob) || 
            query("no_store", ob) || query("maze_item", ob) || 
            query("bindable", ob) || query("set_data", ob) )
        {
                write("對不起，該物品不可以儲存！\n");
                return ;
        }
        if( query("money_id", ob) )
        {
                write("對不起，金錢不可以被儲存！\n");
                return ;
        }
        //如何判定食物呢？
        if(mapp(m=ob->query_entire_dbase()))
        {
                if(!undefinedp(m["food_remaining"])||!undefinedp(m["food_supply"]))
                {
                        write("對不起，食物不可以儲存！\n");
                        return ;
                }
        }

        key="data/"+id+"/";
        if(sizeof(query(key+"objects"))>=query(key+"max_obs"))
        {
            write("對不起。你已經存儲了"+query(key+"cnt")+"件物品了。不能再存儲更多的東西了。\n");
            return ;
        }
        
        str=query("unit", ob);
        if(!str) str="個";
        j=ob->query_amount();
        if(j<1) j=1;
        m=([
                "file":file,
                "name":query("name", ob),
                "id":query("id", ob),
                "unit":str,
                "num":j,
                ]);
        i=query(key+"cnt");
        i++;
        set(key+"cnt",i);
        set(key+"objects/"+i,m);
        destruct(ob);
        if(objectp(ob))
        {
                write("錯誤！儲存失敗，請聯系管理員。\n");
                set(key+"cnt",i-1);
                delete(key+"objects/"+i);
        }
        else
                write(m["name"]+"已經儲存好了！編號："+i+" 。\n");
        //也許應該用心跳來控制
        save();
        return ;
}

void GetObject(object me,string arg)
{
        string kid,*ks,id;
        string res="";
        object ob;
        mapping m;
        int i,ok=0;
        id=query("id", me);
        if(!ExistAccount(id))
        {
                write("請先開戶！\n");
                return ;
        }
        if(!AccountOk(id))
        {
                write("請先續費！\n");
                return ;
        }
         if(!arg||arg=="")
        {
                write("你要取走什麼物品？\n");
                return ;
        }
        arg=lower_case(arg);
        kid="data/"+id+"/objects";
        m=query(kid);
        if(sizeof(m)<1)
        {
                write("你什麼物品都沒有儲存著，還想拿走什麼？\n");
                return ;
        }
        ks=keys(m);
        for(i=0;i<sizeof(ks);i++)
        {
                if(ks[i]==arg || m[ks[i]]["id"]==arg)
                {
                        m=m[ks[i]];
                        ok=1;
                        break;
                }
        }
        if(ok)
        {
                res=m["file"];
                sscanf(res,"%s#%*s",res);
                ob=new(res);
                if(objectp(ob))
                {
                        ob->set_amount(m["num"]); 
                        if(ob->move(me))
                        {
                                write("你從儲物櫃取出了"+m["name"]+"("+m["id"]+") 。\n");
                                //write("你從儲物櫃取出了"+ob->query("name")+"("+ob->query("id")+")。\n");
                                delete(kid+"/"+ks[i]);
                                //也許應該用心跳來控制
                                save();
                                return;
                        }
                        else
                        {
                                write("你身上已有物品負荷過重，無法取出該物品。\n");
                                return;
                        }
                }
        }
        write("取出物品，請輸入cw get <物品編號>，編號可用cw list指令查看。\n");
        return ;
}

int DoFee(object me,string arg)
{
    int mon,k,i;
    string id=query("id", me);
    mon=1;
    if(!ExistAccount(id))
    {
            write("請先開戶！\n");
            return 1;
    }
    if(AccountOk(id))
    {
            write("你還沒必要續費！你的到期時間是"+CHINESE_D->cctime(query("data/"+id+"/expiredate"))+"\n");
            return 1;
    }
    if(arg)
        sscanf(arg,"%d",mon);
    if(mon<1) mon=1;
    if(mon>3)
    {
        write("對不起，一次最多續三個月！\n");
        return 1;
    }
    switch(i=query("data/"+id+"/typ"))
    {
            case 0:
                    k=me->pay_money(1000000*mon);
                    break;
            case 1:
                    k=me->pay_money(2000000*mon);
                    break;
            case 2:
                    //具體的扣點
                    k=DoMonFee(me,mon);
                    break;
            default:
                    k=0;
    }
    if(k)
    {
            int expiredate=query("data/"+id+"/expiredate");
            expiredate+=86400*30*mon;
            set("data/"+id+"/expiredate",expiredate);
            log_file("storage.log","open:"+query("name", me)+"("+query("id", me)+")為第"+i+"類帳戶續了"+mon+"個月！\n");
            write("恭喜你，你的續費已經成功。你可以用到"+CHINESE_D->cctime(expiredate)+"為止。\n");
            save();
            return 1;
    }
    else
    {
            if(i!=2)
                    write("對不起，你的錢未帶夠！請帶上足夠的錢然後使用cw fee <幾個月> 命令來續費！\n"+i+" "+k);
            else
                    write("對不起，你的遊戲點不夠，請先續上足夠的遊戲點然後使用cw fee <幾個月> 來續費！\n");
    }
    return 1;
}

int ShowHelp(object me)
{
        string helpstr=
        "help              獲取本幫助信息\n"
        "fee <租期>        為儲物櫃續費，如果欠費則會先補欠費。租期為月數。\n"
        "open <0-2>        開設儲物櫃帳戶，在該命令後的參數0-2分別代表三種不同的租用方式\n"
        "cancel            取消自己的儲物櫃帳戶。你必須先將裡面的物品全部取出來後才可取消\n"
        "list              列出自己的儲物櫃裡都有些什麼物品\n"
        "put <物品ID>      將身上的某個物品放到儲物櫃裡（不是什麼都可以存放的）\n"
        "get <編號|物品ID> 將儲物櫃裡某個編號的物品取出來\n"
        ;
        write(helpstr);
        MYGIFT_D->check_mygift(this_player(1), "newbie_mygift/cangku"); 
        return 1;
}
