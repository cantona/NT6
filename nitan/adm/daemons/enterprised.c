#include <ansi.h>
#include <dbase.h>

inherit F_DBASE;

#define DATA_PATH       "/data/enterprise.o"
#define MRTGDATA        "/data/stock/"

#define STOCK_MAX_VALUE         1000.0
#define STOCK_MIN_VALUE         1.0
#define STOCK_DEFAULT_VALUE     50.0
#define STOCK_DEFAULT_AMOUNT    5000

mapping enterprises;
mapping special_stockvalue;
mapping serial_number;

int range_random(int i, int j)
{
        return random(i<j?j-i+1:i-j+1)+((i<j)?i:j);
}

string query_serial_number(string key)
{
        if( !stringp(key) )
                return 0;
        
        serial_number[key] = count_add(serial_number[key], 1);
        
        save_object(DATA_PATH);

        return serial_number[key];
}

int enterprise_exists(string id)
{
        return !undefinedp(enterprises[id]);
}

string query_enterprise_color_id(string id)
{
        if( undefinedp(enterprises[id]) ) return 0;

        return enterprises[id]["color_id"];
}


// 回傳在哪個企業體裏
string in_enterprise(string id)
{
        string enterprise_id, member_id;
        mapping enterprise_data, member_data;

        foreach( enterprise_id, enterprise_data in enterprises )
                foreach( member_id, member_data in enterprise_data["member"] )
                        if( id == member_id )
                                return enterprise_id;

        return 0;
}

// 註冊企業成員
void register_member(string enterprise_id, string member_id)
{
        mapping member_data = allocate_mapping(0);

        member_data["jointime"] = time();

        enterprises[enterprise_id]["member"][member_id] = member_data;

        save_object(DATA_PATH);
}

// 註銷企業成員
void unregister_member(string unregister_id)
{
        string enterprise_id, member_id;
        mapping enterprise_data, member_data;

        foreach(enterprise_id, enterprise_data in enterprises)
        {
                foreach(member_id, member_data in enterprise_data["member"])
                {
                        if( unregister_id == member_id )
                                map_delete(enterprises[enterprise_id]["member"], unregister_id);
                }
        }

        save_object(DATA_PATH);
}

// 設定企業資訊
mixed set_enterprise_info(string id, string prop, mixed info)
{
        if( undefinedp(enterprises[id]) ) return 0;

        return enterprises[id][prop] = info;
}

// 查詢企業資訊
varargs mixed query_enterprise_info(string id, string prop)
{
        if( undefinedp(enterprises[id]) ) return 0;

        if( undefinedp(prop) )
                return enterprises[id];

        return enterprises[id][prop];
}

// 刪除企業資訊
void delete_enterprise_info(string id, string prop)
{
        if( undefinedp(enterprises[id]) ) return 0;

        map_delete(enterprises[id], prop);
}

// 註冊企業
void register_enterprise(string id, string color_id, string president)
{
        enterprises[id] = allocate_mapping(0);

        enterprises[id]["president"] = president;
        enterprises[id]["color_id"] = color_id;
        enterprises[id]["member"] = allocate_mapping(0);
        enterprises[id]["registertime"] = time();
        enterprises[id]["stockvalue"] = STOCK_DEFAULT_VALUE;
        enterprises[id]["stockpredictvalue"] = STOCK_DEFAULT_VALUE;
        enterprises[id]["stockamount"] = STOCK_DEFAULT_AMOUNT;
        enterprises[id]["available_stockamount"] = STOCK_DEFAULT_AMOUNT;

        register_member(id, president);

        save_object(DATA_PATH);
}
///////////////////////////////////////////////////////////////////////////////////////////
// 註銷企業
void unregister_enterprise(string enterprise_id)
{
        object member_ob;
        string member_id;
        mapping member_data;

        if( undefinedp(enterprises[enterprise_id]) ) return;

        foreach(member_id, member_data in enterprises[enterprise_id]["member"])
        {
                member_ob = UPDATE_D->global_find_player(member_id);

                if( objectp(member_ob) )
                {
                        delete("enterprise", member_ob);

                        UPDATE_D->global_destruct_player(member_ob, 1); 
                }                
        }

        map_delete(enterprises, enterprise_id);

        save_object(DATA_PATH);
}

// 檢查是否為總裁
int is_president(string enterprise_id, string id)
{
        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        return enterprises[enterprise_id]["president"] == id;
}

string query_president(string enterprise_id)
{
        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        return enterprises[enterprise_id]["president"];
}

// 檢查是否為成員
int is_member(string enterprise_id, string id)
{
        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        return !undefinedp(enterprises[enterprise_id]["member"][id]);
}

// 處理投資
string change_invest(string enterprise_id, string id, mixed money)
{
        string result;

        if( undefinedp(enterprises[enterprise_id]) || 
            undefinedp(enterprises[enterprise_id]["member"][id]) ) return 0;

        result = count_add(enterprises[enterprise_id]["member"][id]["invest"], money);

        enterprises[enterprise_id]["member"][id]["invest"] = result;

        return result;
}

// 處理資產
string change_assets(string enterprise_id, mixed money)
{
        string result;

        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        result = count_add(enterprises[enterprise_id]["assets"], money);

        if( count_lt(result, 0) ) return 0;

        enterprises[enterprise_id]["assets"] = result;

        //if( wizardp(enterprises[enterprise_id]["president"]) )
        //      enterprises[enterprise_id]["assets"] = "0";

        return result;
}

//
// 檢查兩人是否在同一個企業中
int same_enterprise(string member_id1, string member_id2)
{
        if( !member_id1 || !member_id2 )
                return 0;

        foreach(string enterprise_id, mapping enterprise_data in enterprises)
        {
                if( !undefinedp(enterprise_data["member"][member_id1]) &&
                        !undefinedp(enterprise_data["member"][member_id2]) )
                        return 1;
        }

        return 0;
}

string query_money(string enterprise_id)
{
        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        return enterprises[enterprise_id]["assets"];
}

mapping query_enterprises()
{
        return copy(enterprises);
}

string query_enterprise_assets(string enterprise_id)
{
        string totalassets;

        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        // 每小時作一次 cache
        if( enterprises[enterprise_id]["assets_cache_time"] + 3600 < time() )
        {
                enterprises[enterprise_id]["assets_cache"] = query("ENTERPRISE/"+enterprise_id);
                enterprises[enterprise_id]["assets_cache_time"] = time();
        }

        totalassets = count_add(enterprises[enterprise_id]["assets"], enterprises[enterprise_id]["assets_cache"]);

        //foreach(string id, mapping data in enterprises[enterprise_id]["member"])
                //totalassets = count_add(totalassets, MONEY_D->query_lazy_assets(id));

        return totalassets;
}


//
// 回傳所有成員的總資產
/////////////////////////////////////////////////////////////
string query_enterprise_allmembers_assets(string enterprise_id)
{
        string totalassets;

        if( undefinedp(enterprises[enterprise_id]) ) return 0;

        foreach(string id, mapping data in enterprises[enterprise_id]["member"])
                totalassets = count_add(totalassets, MONEY_D->query_lazy_assets(id));

        return totalassets;
}

array query_all_enterprises()
{
        return sort_array(keys(enterprises), (: count_lt(query_enterprise_allmembers_assets($1), 
                                                         query_enterprise_allmembers_assets($2)) ? 1 : -1 :));
}

int save()
{
        return save_object(DATA_PATH);
}

int remove()
{
        return save();
}

void fix_enterprise_database()
{
//      foreach(string enterprise_id, mapping data1 in enterprises)
}

void add_enterprise_to_mrtg(string enterprise_id, int enterprise_id_number, float new_stockvalue)
{
/*
        mapping info = ([
                "Directory":"stock/"+enterprise_id_number,
                "Target":"`cat \""LIBRARY_PATH+MRTGDATA+enterprise_id_number+"\"`",
                "YLegend":"Value",
                "LegendI":"股價",
                "LegendO":"",
                "Legend1":"企業個股走勢",
                "Legend2":"",
                "ShortLegend":"元",
                "MaxBytes":50,
                "MaxAbs":1500,
                "Options":"gauge, growright, nopercent, noinfo",
                "Title": enterprise_id+"企業個股走勢",
                "PageTop":enterprise_id+"企業個股走勢"
        ]);
*/
}


void set_special_stockvalue(string reason, int value)
{
        if( !mapp(special_stockvalue) )
                special_stockvalue = allocate_mapping(0);

        special_stockvalue[reason] = value;
}

void heart_beat()
{
        string enterprise_id;
        mapping enterprise_data;
        float new_stockvalue;
        float stockvalue_change;
        int randomvalue;
        int assets_scale;
        int global_randomvalue;

        global_randomvalue = range_random(-30, 30);

        if( sizeof(special_stockvalue) > 0 )
        {
                foreach(string reason, int svalue in special_stockvalue )
                {
                        CHANNEL_D->do_channel(this_object(), "stock", reason); 
                        global_randomvalue += svalue;
                }
                special_stockvalue = allocate_mapping(0);
        }

        if( global_randomvalue >= 25 )
                CHANNEL_D->do_channel(this_object(), "stock", "股市受到各方"HIR"利"NOR RED"多"NOR HIR"影響，各股普遍呈現攀升走勢。");
        else if( global_randomvalue <= -25 )
                CHANNEL_D->do_channel(this_object(), "stock", "股市受到各方"HIG"利"NOR GRN"空"NOR HIR"影響，各股普遍表現疲弱。");

        foreach(enterprise_id, enterprise_data in enterprises)
        {
                if( undefinedp(enterprise_data["enterprise_id_number"]) )
                        enterprises[enterprise_id]["enterprise_id_number"] = query_serial_number("enterprise_id_number");

                // 進行預期股價的調整
                if( !random(500) )
                {
                        randomvalue = range_random(-1000, 1000);

                        // 每次改變最高 10%
                        stockvalue_change = enterprise_data["stockpredictvalue"] * randomvalue * 0.0001;

                        // 消息通知
                        if( !random(2) )
                        switch(randomvalue)
                        {
                                case 800..1000:
                                        CHANNEL_D->do_channel(this_object(), "stock", "分析師預測企業集團"+query_enterprise_color_id(enterprise_id)+"的股價長期而言可能會有大幅上漲。");
                                        break;
                                case 500..799:
                                        CHANNEL_D->do_channel(this_object(), "stock", "分析師預測企業集團"+query_enterprise_color_id(enterprise_id)+"的股價長期而言可能會有小幅上漲。");
                                        break;
                                case -799..-500:
                                        CHANNEL_D->do_channel(this_object(), "stock", "分析師預測企業集團"+query_enterprise_color_id(enterprise_id)+"的股價長期而言可能會有小幅下跌。");
                                        break;
                                case -1000..-800:
                                        CHANNEL_D->do_channel(this_object(), "stock", "分析師預測企業集團"+query_enterprise_color_id(enterprise_id)+"的股價長期而言可能會有小幅下跌。");
                                        break;
                        }

                        new_stockvalue = enterprise_data["stockpredictvalue"] + stockvalue_change;

                        assets_scale = sizeof(query_enterprise_assets(enterprise_id));

                        // 股價加上企業總值 scale
                        //new_stockvalue += pow(to_float(assets_scale+"."+to_string(assets_scale)[0..0]), 1.3);

                        if( new_stockvalue < STOCK_MIN_VALUE )
                                new_stockvalue = STOCK_MIN_VALUE;
                        else if( new_stockvalue > STOCK_MAX_VALUE )
                                new_stockvalue = STOCK_MAX_VALUE;

                        enterprises[enterprise_id]["stockpredictvalue"] = new_stockvalue;
                }


                // 股價低於預期股價的 90%
                if( enterprise_data["stockvalue"]  < enterprise_data["stockpredictvalue"] * 0.9 )
                        randomvalue = range_random(-40, 80);
                // 股價高於預期股價的 110%
                else if( enterprise_data["stockvalue"] > enterprise_data["stockpredictvalue"] * 1.1 )
                        randomvalue = range_random(-80, 40);
                else
                        randomvalue = range_random(-80, 80);

                randomvalue += global_randomvalue;

                // 每次變動最高 1.5%
                stockvalue_change = enterprise_data["stockvalue"] * randomvalue * 0.0001;

                new_stockvalue = enterprise_data["stockvalue"] + stockvalue_change;


                if( new_stockvalue < STOCK_MIN_VALUE )
                        new_stockvalue = STOCK_MIN_VALUE;
                else if( new_stockvalue > STOCK_MAX_VALUE )
                        new_stockvalue = STOCK_MAX_VALUE;

                if( randomvalue >= 200 )
                        CHANNEL_D->do_channel(this_object(), "stock", sprintf("企業集團%s股價大漲 "HIR"▲%.2f"NOR" 點(%.2f%%)，成為 "HIW"%.2f"NOR" 點。",
                                query_enterprise_color_id(enterprise_id),
                                stockvalue_change,
                                randomvalue/100.,
                                new_stockvalue));
                else if( randomvalue <= -200 )
                        CHANNEL_D->do_channel(this_object(), "stock", sprintf("企業集團%s股價重挫 "HIG"▼%.2f"NOR" 點(%.2f%%)，成為 "HIW"%.2f"NOR" 點。",
                                query_enterprise_color_id(enterprise_id),
                                -stockvalue_change,
                                -randomvalue/100.,
                                new_stockvalue));

/*
                if( stockvalue_change > 0. )
                        CHANNEL_D->do_channel(this_object(), "stock", sprintf("%-20s 股價 "HIR"▲%5.2f"NOR"，成為 "HIW"%7.2f"NOR" 點。", query_enterprise_color_id(enterprise_id), stockvalue_change, new_stockvalue));
                else if( stockvalue_change < 0. )
                        CHANNEL_D->do_channel(this_object(), "stock", sprintf("%-20s 股價 "HIG"▼%5.2f"NOR"，成為 "HIW"%7.2f"NOR" 點。", query_enterprise_color_id(enterprise_id), -stockvalue_change, new_stockvalue));
                else
                        CHANNEL_D->do_channel(this_object(), "stock", sprintf("%-20s 股價 "HIW"  %5.2f"NOR"，成為 "HIW"%7.2f"NOR" 點。", query_enterprise_color_id(enterprise_id), stockvalue_change, new_stockvalue));
*/
                enterprises[enterprise_id]["stockvalue_change"] = stockvalue_change;
                enterprises[enterprise_id]["stockvalue"] = new_stockvalue;

                if( undefinedp(enterprises[enterprise_id]["stockvalue_minimum"]) )
                        enterprises[enterprise_id]["stockvalue_minimum"] = new_stockvalue;
                else if( new_stockvalue < enterprises[enterprise_id]["stockvalue_minimum"]+10. )
                        enterprises[enterprise_id]["stockvalue_minimum"] = new_stockvalue+10.;

                add_enterprise_to_mrtg(enterprise_id, enterprises[enterprise_id]["enterprise_id_number"], new_stockvalue);
        }
}

void set_enterprise_stockvalue(string enterprise_id, float value)
{
        enterprises[enterprise_id]["stockvalue"] = value;
}

void create()
{
        seteuid(getuid()); 
        set("channel_id", "股票精靈"); 

        if( !restore_object(DATA_PATH) )
        {
                enterprises = allocate_mapping(0);
                save();
        }

        set_heart_beat(6000);
}


string query_name()
{
        return "企業系統(ENTERPRISE_D)";
}