#include <localtime.h>
#include <ansi.h>

inherit F_DBASE;

mixed festivals = ([]);
mixed now_festivals = ({});
string now_string = "";
void setup();
void check_festival();
void create()
{
        seteuid(getuid());
        set("channel_id", "節日獎勵精靈");   
        setup();
        check_festival();
}

void setup()
{
        // /adm/etc/festival
        // 英文名:中文名:開始時間:結束時間:節日日期:節日中文名:經驗限制:獎勵
        // 獎勵：類型|數量,類型|數量
        string sen;
        mixed fess;
        mixed tmp,tmp2;
        int i,sz,j,sz2;
        int y,m,d;
        string reward;
        int rewardcount;
        sen = read_file("/adm/etc/festival");
        fess = explode(sen,"\n");
        sz = sizeof(fess);
        for(i=0;i<sz;i++) {
                tmp = explode(fess[i],":");
                //log_file("fes",sprintf("%O\n",tmp));
                festivals[tmp[0]] = ([]);
                festivals[tmp[0]]["cname"] = tmp[1];
                festivals[tmp[0]]["fname"] = tmp[5];
                festivals[tmp[0]]["fdate"] = tmp[4];
                festivals[tmp[0]]["stime"] = tmp[2];
                festivals[tmp[0]]["etime"] = tmp[3];
                festivals[tmp[0]]["type"] = atoi(tmp[6]);//0表示領取一次，1表示每日領取
                festivals[tmp[0]]["explimit"] = atoi(tmp[7]);
                festivals[tmp[0]]["reward"] = ([]);
                tmp2 = explode(tmp[8],",");
                sz2 = sizeof(tmp2);
                for(j=0;j<sz2;j++) {
                        sscanf(tmp2[j],"%s|%d",reward,rewardcount);
                        festivals[tmp[0]]["reward"][reward] = rewardcount;
                }
                sscanf(tmp[2],"%d-%d-%d",y,m,d);
                festivals[tmp[0]]["stimey"] = y;
                festivals[tmp[0]]["stimem"] = m;
                festivals[tmp[0]]["stimed"] = d;
                sscanf(tmp[3],"%d-%d-%d",y,m,d);
                festivals[tmp[0]]["etimey"] = y;
                festivals[tmp[0]]["etimem"] = m;        
                festivals[tmp[0]]["etimed"] = d;        
        }
}

string set_festival_string()
{
        string ret;
        mixed tmp;
        int i,sz,j,sz2;
        if(!(sz=sizeof(now_festivals))) {
                ret = HIY + "當前沒有正在進行的節日活動。\n"+NOR;
        } else {
                ret = HIY+"當前正在進行中的節日活動有：\n";
                for(i=0;i<sz;i++) {
                        ret += HIY+"\t活動名稱："+HIG+festivals[now_festivals[i]]["cname"]+"\n";
                        ret += HIY+"\t英文標識："+HIG+now_festivals[i]+"\n";
                        ret += HIY+"\t起始時間："+HIG+festivals[now_festivals[i]]["stime"]+"\n";
                        ret += HIY+"\t結束時間："+HIG+festivals[now_festivals[i]]["etime"]+"\n";
                        ret += HIY+"\t經驗限制："+HIG+festivals[now_festivals[i]]["explimit"]+"\n";
                        ret += HIY+"\t獎勵內容："+HIG;
                        tmp = keys(festivals[now_festivals[i]]["reward"]);
                        sz2 = sizeof(tmp);
                        for(j=0;j<sz2;j++) {
                                switch(tmp[j]) {
                                case "exp":
                                        ret += "經驗";
                                        break;
                                case "pot":
                                        ret += "潛能";
                                        break;
                                case "mar":
                                        ret += "體會";
                                        break;
                                case "neili":
                                        ret += "內力";
                                        break;
                                case "jingli":
                                        ret += "精力";
                                        break;
                                case "weiwang":
                                        ret += "威望";
                                        break;
                                case "score":
                                        ret += "閲歷";
                                        break;
                                case "gongxian":
                                        ret += "貢獻";
                                        break;
                                case "gold":
                                        ret += "黃金";
                                        break;
                                default ://發道具的簡單接口
                                        ret+=query("name", get_object(tmp[j]));
                                        break;
                                }
                                ret += ":"+festivals[now_festivals[i]]["reward"][tmp[j]]+"，";
                        }
                        ret += "\n";
                        ret += HIY+"\t獎勵類型："+HIG+((festivals[now_festivals[i]]["type"])?"每日領取":"限領一次")+"\n";
                        ret += HIY+"\t所屬節日："+HIG+festivals[now_festivals[i]]["fname"]+"("+festivals[now_festivals[i]]["fdate"]+")\n\n";

                }
        }       
        ret += NOR;
        return ret;
}

string query_festival_string()
{
        return now_string;
}

int compare_date(mixed a,mixed b)
{
        //小於等於是1
        //大於是0
        if(a[0]<b[0]) {
                return 1;
        } else if(a[0]>b[0]) {
                return 0;
        } else {
                if(a[1] < b[1]) {
                        return 1;
                } else if(a[1]>b[1]) {
                        return 0;
                } else {
                        if(a[2] < b[2]) {
                                return 1;
                        } else if(a[2]>b[2]) {
                                return 0;
                        } else {
                                return 1;
                        }
                }
        }       
}

int is_festival(string arg)
{
        mixed lc;
        int y,m,d;

        lc = localtime(time());
        y = lc[LT_YEAR];
        m = lc[LT_MON] + 1;
        d = lc[LT_MDAY];

        if(!arg || undefinedp(festivals[arg]))
                return 0;

        if(compare_date(({festivals[arg]["stimey"],festivals[arg]["stimem"],festivals[arg]["stimed"]}),({y,m,d})) && compare_date(({y,m,d}),({festivals[arg]["etimey"],festivals[arg]["etimem"],festivals[arg]["etimed"]})) )
                return 1;
        return 0;
}
void check_festival()
{
        //使用節日的中文名來進行判定
        
        // 先判斷是否有舊的活動過期
        int i,sz;
        mixed tmp_fes;
        mixed feskeys;
        tmp_fes = copy(now_festivals);
        if(sz = sizeof(tmp_fes)) {
                //一個一個判斷
                for(i=0;i<sz;i++) {
                        if(!is_festival(tmp_fes[i])) {
                                now_festivals -= ({tmp_fes[i]});
                                CHANNEL_D->channel_broadcast("mess","節日精靈：節日活動 "+festivals[tmp_fes[i]]["cname"]+" 結束了。");
                        }
                }
        }
        feskeys = keys(festivals);
        sz = sizeof(feskeys);
        for(i=0;i<sz;i++) {
                if(member_array(feskeys[i],now_festivals)>=0)
                        continue;
                if(is_festival(feskeys[i])) {
                        now_festivals += ({feskeys[i]});
                        CHANNEL_D->channel_broadcast("mess", "節日精靈：節日活動 "+festivals[feskeys[i]]["cname"]+" 開始了。");
                }
        }       
        now_string = set_festival_string();
        call_out("check_festival",60);
}

string give_festival_reward(object usr,string arg)
{
        string ret;
        mixed tmp;
        int i,j,sz2;
        object ob;
        ret = "您在節日活動："+festivals[arg]["cname"]+"("+arg+")中獲得瞭如下獎勵：\n";
        tmp = keys(festivals[arg]["reward"]);
                        sz2 = sizeof(tmp);
                        for(j=0;j<sz2;j++) {
                                switch(tmp[j]) {
                                case "exp":
                                        addn("combat_exp", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "經驗";
                                        break;
                                case "pot":
                                        addn("potential", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "潛能";
                                        break;
                                case "mar":
                                        addn("experience", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "體會";
                                        break;
                                case "neili":
                                        addn("max_neili", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "內力";
                                        break;
                                case "jingli":
                                        addn("max_jingli", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "精力";
                                        break;
                                case "weiwang":
                                        addn("weiwang", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "威望";
                                        break;
                                case "score":
                                        addn("score", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "閲歷";
                                        break;
                                case "gongxian":
                                        addn("family/gongji", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "功績";
                                        break;
                                case "gold":
                                        ob = new("/clone/money/gold");
                                        ob->set_amount(festivals[arg]["reward"][tmp[j]]);
                                        ob->move(usr);
                                        ret += "黃金";
                                        break;
                                default ://發道具的簡單接口
                                        for(i=0;i<festivals[arg]["reward"][tmp[j]];i++)  {
                                                ob = new(tmp[j]);
                                                ob->move(usr);
                                        }
                                        ret+=query("name", get_object(tmp[j]));
                                        break;
                                }
                                ret += ":"+festivals[arg]["reward"][tmp[j]]+"，";
                        }

                        ret += "\n";
        return ret;
}

string get_reward(object usr)
{
        int i,sz;
        mixed fes_record;
        string today,ret;
        int y,m,d,ty,tm,td;
        mixed lc;

        if(!(sz=sizeof(now_festivals)))
                return "目前沒有正在進行中的節日，因此沒有可以領取的獎勵。";    
        ret = "";       
        lc = localtime(time());
        ty = lc[LT_YEAR];
        tm = lc[LT_MON] + 1;
        td = lc[LT_MDAY];

        today = lc[LT_YEAR]+"-"+sprintf("%.2d",lc[LT_MON] + 1)+"-"+sprintf("%.2d",lc[LT_MDAY]);
        fes_record=query("festival_record", usr);
        if(!mapp(fes_record))
                fes_record = ([]);
        for(i=0;i<sz;i++) {
                //每個fes的判定和獎勵。。。。
                if(undefinedp(fes_record[now_festivals[i]])) { //無記錄，可領獎
                        //給獎勵
                        if( query("combat_exp", usr)<festivals[now_festivals[i]]["explimit"]){
                                ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")要求經驗至少為"+festivals[now_festivals[i]]["explimit"]+"，您當前經驗不足，無法領取獎勵。\n";
                        } else {
                                ret += give_festival_reward(usr,now_festivals[i]);
                                //加record
                                fes_record[now_festivals[i]] = today;
                        }
                } else {//有記錄
                        sscanf(fes_record[now_festivals[i]],"%d-%d-%d",y,m,d);
                        if(compare_date(({festivals[now_festivals[i]]["stimey"],festivals[now_festivals[i]]["stimem"],festivals[now_festivals[i]]["stimed"]}),({y,m,d}))==0) {//獎勵記錄比開啟更早，説明是上次節日獲得，可領獎(開啟時間大於獎勵記錄 0)
                                //給獎勵
                                if( query("combat_exp", usr)<festivals[now_festivals[i]]["explimit"]){
                                         ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")要求經驗至少為"+festivals[now_festivals[i]]["explimit"]+"，您當前經驗不足，無法領取獎勵。\n";
                                } else {
                                        ret += give_festival_reward(usr,now_festivals[i]);
                                        //加record
                                        fes_record[now_festivals[i]] = today;
                                }
                        } else { //這次領過獎了。。。
                                if(festivals[now_festivals[i]]["type"]==0) { //類型是限領一次，不給獎勵
                                        ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")只能領取一次獎勵，您於"+fes_record[now_festivals[i]]+"已領取過，不能再次領取。\n";
                                } else { //每日領取的
                                        if(compare_date(({ty,tm,td}),({y,m,d}))==0) { //獎勵記錄比今天早，可領取(今天 大於 獎勵記錄 0)
                                                if( query("combat_exp", usr)<festivals[now_festivals[i]]["explimit"]){
                                                        ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")要求經驗至少為"+festivals[now_festivals[i]]["explimit"]+"，您當前經驗不足，無法領取獎勵。\n";
                                                } else {
                                                        //給獎勵
                                                        ret += give_festival_reward(usr,now_festivals[i]);
                                                        //加record
                                                        fes_record[now_festivals[i]] = today;
                                                }       
                                        } else { //今天已領，不給
                                                ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")在活動期間可每日領取獎勵一次，您今天（"+today+"）已經領取過獎勵，不能再次領取。\n";
                                        }
                                }
                        }
                }
        }
        set("festival_record", fes_record, usr);
        return ret;
}
