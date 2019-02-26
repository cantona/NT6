// /feature/business.c
// buy Find.

class business
{
        string name;    /* 名稱 */
        string id;      /* ID */
        string unit;    /* 單位 */
        int amount;     /* 數量 */
        int buy;        /* 收購單價 */
        string from;    /* 收購地點 */
        string now;     /* 貨物當前所在地 */
        string to;      /* 貨物當前正在前往的地點 */
        int time;       /* 預計到達的時間 */
}

int trade_amount = 0; /* 共進行過的交易次數 */
int profit = 0; /* 共賺取的利潤(silver) */
int query_profit() { return profit; }

class business *all = ({});

mapping query_business()
{
        mapping data = ([]);

        data["all"] = all;
        data["trade_amount"] = trade_amount;
        data["profit"] = profit;
        return data;
}

int set_business(mapping data)
{
        if( !mapp(data) )
                return 0;

        all = data["all"];
        trade_amount = data["trade_amount"];
        profit =  data["profit"];
        return 1;
}

protected void get_fasong_number(string num,object me,class business *have);
protected void get_fasong_where(string num,object me,string *ds,class business ware);

// 返回值 0 此人在本地沒有這種貨物, -1 數量不夠.
nomask int sell_out(string id,int amount,int value)
{
        string domain;
        int n,i,have;

        if(!previous_object()
        || !sscanf(file_name(previous_object()),"/d/%s/business",domain))
                return 0;

        if(member_array(domain,BUSINESS_D->query_valid_domains()) == -1)
                return 0;

        if(!all || !(n=sizeof(all)))
                return 0;

        for(i=0;i<n;i++)
                if((all[i]->now == domain) && (all[i]->id == id))
                        have += all[i]->amount;

        if( !have )
                return 0;

        if(have < amount)
                return -1;

        for(i=0;i<n;i++)
        {
                if(!amount)
                        break;

                if(all[i]->now != domain || all[i]->id != id)
                        continue;
                if(all[i]->amount <= amount)
                {
                        profit += (value - all[i]->buy)*amount;
                        amount -= all[i]->amount;
                        all[i] = 0;
                }

                else
                {
                        profit += (value - all[i]->buy)*amount;
                        all[i]->amount -= amount;
                        break;
                }
        }

        all -= ({ 0 });
        trade_amount++;
        this_object()->save();
        return 1;
}

nomask int buy_in(string name,string id,string unit,int amount,int value)
{
        string domain;
        class business item;

        if(!previous_object()
        || !sscanf(file_name(previous_object()),"/d/%s/business",domain))
                return 0;

        if(member_array(domain,BUSINESS_D->query_valid_domains()) == -1)
                return 0;

        if(!stringp(name)
        || !stringp(id)
        || !stringp(unit)
        || amount <= 0
        || value <= 0)
                return 0;

        item = new(class business);

        item->name = name;
        item->id = id;
        item->unit = unit;
        item->amount = amount;
        item->buy = value;
        item->from = domain;
        item->now = domain;

        if(!all)
                all = ({});
        all += ({ item });
        this_object()->save();
        return 1;
}

nomask string query_business_status()
{
        string output = "\n";
        int n;

        if(!n  = sizeof(all))
                output += "你目前手頭沒有任何貨物。\n";
        else
        {
                output += "你目前手頭的貨物有：\n";
                output += sprintf("%-22s%-12s%-12s%-12s%s\n",
                        "貨物名稱","貨物數量","收購地點","收購價格","狀態");
                output += "----------------------------------------------------------------------\n";
                for(int i=0;i<n;i++)
                {
                        string status;

                        if(!all[i]->to)
                                status = sprintf("貨物在%s",to_chinese(all[i]->now));
                        else if(time() <=  all[i]->time)
                                status = sprintf("正在運往%s的途中剩餘%s天左右到達",to_chinese(all[i]->to),
                                                 chinese_number((all[i]->time - time()) / 1440));
                        else
                                status = sprintf("已運抵%s",to_chinese(all[i]->to));

                        output += sprintf("%-22s%-12s%-12s%-12s%s\n",
                                sprintf("%s(%s)",all[i]->name,all[i]->id),
                                sprintf("%d%s",all[i]->amount,all[i]->unit),
                                to_chinese(all[i]->from),
                                sprintf("%d銀/%s",all[i]->buy,all[i]->unit),
                                status
                                );
                }
        }

        if(!trade_amount)
                output += "\n你還沒有從事過貿易活動。\n\n";
        else
                output += sprintf("\n你共進行過%s次貿易。\n\n",chinese_number(trade_amount));

        if(!profit)
                output += "你還沒有通過貿易賺取過利潤。\n\n";
        else if(profit < 0)
                output += sprintf("你在從事貿易中共虧損了 %d 兩白銀。\n\n",abs(profit));
        else
                output += sprintf("你在從事貿易中共賺取了 %d 兩白銀。\n\n",profit);

        return output;
}

nomask void fasong_ware()
{
        class business *have = ({});
        int i,n;
        string out,from;

        if(!previous_object()
        || !sscanf(file_name(previous_object()),"/d/%s/business",from))
                return;

        if(member_array(from,BUSINESS_D->query_valid_domains()) == -1)
                return;

        if( !(n = sizeof(all)) )
        {
                write("你現在手裏沒有任何貨物。\n");
                return;
        }

        for(i=0;i<sizeof(all);i++)
                if(all[i]->now == from)
                        have += ({ all[i] });

        if( !(n = sizeof(have)) )
        {
                write(sprintf("你在%s沒有任何貨物。\n",to_chinese(from)));
                return;
        }

        if(n > 1)
        {
                out = sprintf("你目前在%s共有%s筆貨物：\n",to_chinese(from),chinese_number(n));
                for(i=0;i<n;i++)
                        out += sprintf("%2d. %s %d %s。\n",(i+1),
                                have[i]->name,have[i]->amount,have[i]->unit);
                out += "請選擇你要發送的貨物：\n";
                write(out);
                input_to( (: get_fasong_number :),this_player(),have );
                return;
        }

        get_fasong_number(sprintf("%d",1),this_player(),have);
}

protected void get_fasong_number(string num,object me,class business *have)
{
        int n,l,bk,s,i;
        string *v_domains,*ds,out;

        if(!objectp(me) || (num[0] == 'q'))
                return;

        if(!sscanf(num,"%d",n))
        {
                write("請選擇你要發送的貨物：\n");
                input_to((: get_fasong_number :),me,have);
                return;
        }

        n--;
        if( (n < 0 ) || (n > sizeof(have)) )
        {
                write("請選擇你要發送的貨物：\n");
                input_to((: get_fasong_number :),me,have);
                return;
        }

        ds = BUSINESS_D->query_valid_domains()-({have[n]->now});
        v_domains = map_array(ds,(: to_chinese($1) :));

        s = sizeof(v_domains);

        for(i=0;i<s;i++)
                if(strlen(v_domains[i]) > l)
                        l = strlen(v_domains[i]);

        out = "目前可以發往的地點有：\n";
        bk = to_int(50/(l+5));
        l++;
        for(i=0;i<s;i++)
                out += sprintf("%-3d%-"+(string)l+"s  %s",(i+1),v_domains[i],(i%bk==(bk-1))||i==n-1?"\n":"" );

        out += "請選擇你要發往的地點：\n";
        write(out);
        input_to((: get_fasong_where :),me,ds,have[n]);
}

protected void get_fasong_where(string num,object me,string *ds,class business ware)
{
        int n,time,fs_fee,plus;

        if(!objectp(me) || (num[0] == 'q'))
                return;

        if(!sscanf(num,"%d",n))
        {
                write("請選擇你要發往的地點：\n");
                input_to((: get_fasong_where :),me,ds,ware);
                return;
        }

        n--;
        if( (n < 0 ) || (n >= sizeof(ds)) )
        {
                write("請選擇你要發往的地點：\n");
                input_to((: get_fasong_where :),me,ds,ware);
                return;
        }

        time = BUSINESS_D->count_fasong_time(ware->now,ds[n],ware->buy*ware->amount/100);
        if(!time)
        {
                write("發送失敗！！！！\n");
                return;
        }

        fs_fee = ware->buy*ware->amount/100;
        plus = time/10;
        if(plus > 1)
                fs_fee *= plus;

        if(fs_fee < 20) // 1000 兩白銀。每次運費最少為 20 silver。
                fs_fee = 20;

        if(query("balance", me) < fs_fee*100)
        {
                write(sprintf("發送 %d %s%s去%s須繳納運費 %d 兩白銀，你銀行存款不夠。\n",
                        ware->amount,ware->unit,ware->name,to_chinese(ds[n]),fs_fee ));
                return;
        }

        addn("balance", -fs_fee*100, me);
        write(sprintf("發送 %d %s%s去%s的運費 %d 兩白銀已直接從你的銀行存款中轉帳。\n",
                        ware->amount,ware->unit,ware->name,to_chinese(ds[n]),fs_fee ));
        ware->now = 0;
        ware->to = ds[n];
        ware->time = time()+time*1440;
        this_object()->save();
        write(sprintf("%s已發往%s,路上大約需要%s天。\n",
                ware->name,to_chinese(ds[n]),chinese_number(time)));
}

int delete_all_wares()
{
        all = ({});
        this_object()->save();
        return 1;
}

protected void random_happen(class business w)
{
        string reason,cl;
        int n,loss;

        // 損失率 1-5%，30% 可能性發生損失。

        if(random(100) >= 30)
                return;

        n = random(100);

        if(n < 10)      // 5%
                loss = w->amount*5/100;
        else if(n < 20)
                loss = w->amount*4/100;
        else if(n < 30)
                loss = w->amount*3/100;
        else if(n < 40)
                loss = w->amount*2/100;
        else if(n < 50)
                loss = w->amount*1/100;
        else
                return;

        if(!loss)
                return;

        cl = BUSINESS_D->query_ware_class(w->id);
        if(!cl)
                return;

        if( (cl == "穀物") || (cl == "土特產") )
                reason = "爛掉";
        else
        {
                if(random(2))
                        reason = "被偷";
                else
                        reason = "被搶";
        }

        w->amount -= loss;

        tell_object(this_object(),sprintf("你的%s在運輸途中%s了 %d %s。\n",
                w->name,reason,loss,w->unit ));
}

nomask void update_all_wares()
{
        int n,i,t,flag = 0;

        if(!n = sizeof(all))
                return;

        t = time();

        for(i=0;i<n;i++)
        {
                if(!all[i]->to)
                        continue;
                if( t <= all[i]->time )
                        continue;
                random_happen(all[i]);
                all[i]->now = all[i]->to;
                all[i]->to = 0;
                all[i]->time = 0;
                flag++;
        }

        if(flag)
                this_object()->save();

}
