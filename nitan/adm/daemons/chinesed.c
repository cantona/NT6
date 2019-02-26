// chinesed.c
// by Annihilator@ES
// modified by Xiang@XKX
// updated by Lonely@nitan3

#pragma optimize
#pragma save_binary

#include <localtime.h>

#ifndef DATA_DIR
#define DATA_DIR        "/data/"
#endif
#define E2C_DICTIONARY  DATA_DIR + "e2c_dict"

inherit F_SAVE;

// some constatns
nosave string *c_digit = ({ "零","十","百","千","萬","億","兆" });
nosave string *c_num = ({ "零","一","二","三","四","五","六","七","八","九","十" });
nosave string *c_num2 = ({ "零","壹","貳","參","肆","伍","陸","柒","捌","玖","什" });
nosave string *sym_tian = ({ "甲","乙","丙","丁","戊","己","庚","辛","壬","癸" });
nosave string *sym_di = ({ "子","醜","寅","卯","辰","巳","午","未","申","酉","戌","亥" });
// 最大數值單位可自由增減
// string *unit = ({ "萬","億","兆","京","垓","杼","穣","溝","澗","正","載","極","恆河沙","阿僧祇","那由它","不可思議","無量","大數" });
nosave string *unit = ({ "萬","億","兆" });
nosave mapping cache;
mapping dict = 
([
        "north"                :"北邊",
        "south"                :"南邊",
        "east"                :"東邊",
        "west"                :"西邊",
        "northwest"        :"西北邊",
        "northeast"        :"東北邊",
        "southwest"        :"西南邊",
        "southeast"        :"東南邊",
        "down"                :"樓下",
        "up"                :"樓上",
        "changan"       :"長安",
        "city"          :"揚州",
        "kaifeng"       :"開封",
        "hangzhou"      :"杭州",
        "suzhou"        :"蘇州",
        "dali"          :"大理",
        "beijing"       :"北京",
]);

void add_translate(string key, string chn);
void remove_translate(string key);

string initialize(int i)
{
        if( i < 11 ) return c_num[i];
        if( i < 20 ) return "十"+c_num[i%10];
        if( i < 100 ) return c_num[i/10]+"十"+(i%10 ? c_num[i%10] : "" );
        if( i < 1000 ) return c_num[i/100]+"百"+(i%100 ? ((i%100<10?"零":0)||(i%100<20?"一":""))+initialize(i%100) : "");
}

void create()
{
        seteuid(getuid());
        restore();
        cache = allocate_mapping(0);
        
        /* 建立數值快取 */
        for(int i=0;i<=1000;i++)
                cache[i] = initialize(i);
}

void remove()
{
        save();
}

string chinese_number(mixed i)
{
        // 若輸入參數為 integer (會 overflow) 
        if( intp(i) )
        {
                if (i < 0)
                        return "負" + chinese_number(-i);
                if (i < 11)
                        return c_num[i];
                if (i < 20)
                        return c_digit[1] + c_num[i - 10];
                if (i < 100)
                {
                        if (i % 10)
                                return c_num[i / 10] + c_digit[1] + c_num[i % 10];
                        else
                                return c_num[i / 10] + c_digit[1];
                }
                if (i < 1000)
                {
                        if (i % 100 == 0)
                                return c_num[i / 100] + c_digit[2];
                        else if (i % 100 < 10)
                                return c_num[i / 100] + c_digit[2] +
                                c_num[0] + chinese_number(i % 100);
                        else if (i % 100 < 10)
                                return c_num[i / 100] + c_digit[2] +
                                c_num[1] + chinese_number(i % 100);
                        else
                                return c_num[i / 100] + c_digit[2] + 
                                chinese_number(i % 100);
                }
                if (i < 10000)
                {
                        if (i % 1000 == 0)
                                return c_num[i / 1000] + c_digit[3];
                        else if (i % 1000 < 100)
                                return c_num[i / 1000] + c_digit[3] +
                                c_num[0] + chinese_number(i % 1000);
                        else 
                                return c_num[i / 1000] + c_digit[3] +
                                chinese_number(i % 1000);
                }
                if (i < 100000000)
                {
                        if (i % 10000 == 0)
                                return chinese_number(i / 10000) + c_digit[4];
                        else if (i % 10000 < 1000)
                                return chinese_number(i / 10000) + c_digit[4] +
                                c_num[0] + chinese_number(i % 10000);
                        else
                                return chinese_number(i / 10000) + c_digit[4] +
                                chinese_number(i % 10000);
                        }
                if (i < 1000000000000)
                {
                        if (i % 100000000 == 0)
                                return chinese_number(i / 100000000) + c_digit[5];
                        else if (i % 100000000 < 1000000)
                                return chinese_number(i / 100000000) + c_digit[5] +
                                c_num[0] + chinese_number(i % 100000000);
                        else 
                                return chinese_number(i / 100000000) + c_digit[5] +
                                chinese_number(i % 100000000);
                }
                if (i % 1000000000000 == 0)
                        return chinese_number(i / 1000000000000) + c_digit[6];
                else
                if (i % 1000000000000 < 100000000)
                        return chinese_number(i / 1000000000000) + c_digit[6] +
                        c_num[0] + chinese_number(i % 1000000000000);
                else
                        return chinese_number(i / 1000000000000) + c_digit[6] +
                        chinese_number(i % 1000000000000);
            }
            // 若輸入參數為 string (無限位數處理)
        else if( stringp(i) && i != "")
        {
                   int j, k, *n=({}), usize = sizeof(unit);
                string *u=({""});
                string msg;
                
                if( i[0] == '-' ) return "負" + chinese_number(i[1..]);
                
                // 將數字依四位數拆解
                while( (msg = i[<(j+=4)..<(j-3)])!="" )
                {                        
                        n += ({ to_int(msg) });
                        if( j != 4 ) u += ({ unit[k++%usize] });
                }
                
                j = k = sizeof(n);
                        
                while(j--)
                        if( n[j] ) msg += (j+1<k ? (n[j+1] && n[j]>999 ? chinese_number(n[j]):"零"+chinese_number(n[j])):chinese_number(n[j])) + u[j];
                        else if( u[j] == unit[usize-1] ) msg += unit[usize-1];

                return msg;
        }
        else return "錯誤數值";
}

nomask string chinese_period(int t)
{
        int y, n, d, h, m, s;
        string time="";

        s = t %60;
        m = t /60%60;
        h = t /60/60%24;
        d = t /60/60/24%30;
        n = t /60/60/24/30%13;
        y = t /60/60/24/30/13;

        if(y) time = cache[y] + "年又";
        if(n) time += cache[n] + "個月"                + (y?"":"又");
        if(d) time += cache[d] + "天"                + (n||y?"":"又");
        if(h) time += cache[h] + "小時"                + (d||n||y?"":"又");
        if(m) time += cache[m] + "分"                + (h||d||n||y?"":"又");

        return time+cache[s]+"秒";        
}

int chinese_to_number(mixed chinese)
{
        int i, len, num, idx;
        
        if( intp(chinese) ) return chinese;
        
        if( !stringp(chinese) )
                return 0;

        len = sizeof(chinese);
        
        for(i=0;i<len;i+=2)
        {
                idx = member_array(chinese[i..i+1], c_num);
                
                if( idx == -1 )
                        idx = member_array(chinese[i..i+1], c_num2);
                
                if( idx == -1 )
                        continue;
                
                if( idx == 10 )
                {
                        if( i!=0 )
                                continue;
                        else if(i+2!=len)
                                idx = 1;
                }

                num = num*10 + idx;
        }
        return num;
}

string query_save_file()
{
        return E2C_DICTIONARY;
}

string chinese(string str)
{
        if (! undefinedp(dict[str]))
                return dict[str];
        else
                return str;
}

string to_chinese(string idx)
{
        return chinese(idx);
}

string find_skill(string value)
{
        string *english;
        string key;

        english = keys(dict);
        foreach (key in english)
        {
                if (dict[key] == value)
                        return key;
        }
        return 0;
}

void remove_translate(string key)
{
        map_delete(dict, key);
        save();
}

void add_translate(string key, string chn)
{
        dict[key] = chn;
        save();
}

void dump_translate()
{
        string *k;
        string str;
        int i;
        
        str = "";
        k = keys(dict);
        for (i = 0; i < sizeof(k); i++) 
                str += sprintf("%-30s %s\n", k[i], dict[k[i]]);
        write_file("/CHINESE_DUMP", str);
}

string cctime(int date)
{
        int year;
        int mon;
        int mday;
        int wday;
        int hour;
        int min;
        int sec;
        
        mixed lt;
        lt = localtime(date);
        sec = lt[LT_SEC];
        min = lt[LT_MIN];
        hour = lt[LT_HOUR];
        mday = lt[LT_MDAY];
        wday = lt[LT_WDAY];
        mon = lt[LT_MON] + 1; 
        year = lt[LT_YEAR];
        return sprintf("%d年%d月%d日 %d時%d分%d秒", year, mon, mday, hour, min, sec);
}

string chinese_date(int date)
{
        mixed *local;

        if (date <=0) date=1;
        local = localtime(date);
        
        return sprintf("%s%s年%s月%s日%s時%s刻",
                sym_tian[local[LT_YEAR] % 10], sym_di[local[LT_YEAR] % 12],
                chinese_number(local[LT_MON] + 1),
                chinese_number(local[LT_MDAY] + (local[LT_HOUR] > 23 ? 1 : 0)),
                sym_di[((local[LT_HOUR] + 1) % 24) / 2],
                chinese_number((local[LT_MIN]+1) % 2 * 2 + 
                local[LT_MIN] / 30 + 1) );
}

//Used in natured.c to as a condition to judge which season should be
//to use different weather discription.
string chinese_month(int date)
{
        return chinese_number(NATURE_D->query_month());
}

string chinese_monthday(int date)
{
        mixed *local;
        local = NATURE_D->query_localtime(date);
        return sprintf("%s月%s日",
                       chinese_number(local[LT_MON] + 1),
                       chinese_number(local[LT_MDAY]));
}

//end of appendance
int check_control(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (name[i] == ' ' || name[i] == '\n')
                        continue;

                if (name[i] < ' ')
                        return 1;
        }
        return 0;
}

int check_space(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (name[i]== ' ')
                        return 1;
        }
        return 0;
}

int check_return(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (name[i]== '\n')
                        return 1;
        }
        return 0;
}

int check_chinese(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (i%2==0 && ! is_chinese(name[i..<0]))
                        return 0;
        }
        return 1;
}

int check_length(string str)
{
        if (! str) return 0;
        return strlen(filter_color(trans_color(str, 3), 1));
}

string itoa(int i)
{
        string str;

        if(!intp(i)) return "NULL";
        str=sprintf("%d",i);
        return str;
}

string chinese_time(int type,string get_time)
{
/* 不要使用localtime來傳遞get_time，使用ctime(time())就是正確的了！
在求當前時間時用localtime是無所謂，但是要轉換一個時間還是ctime好點！*/

        string e_time, week, month, year;
        string c_week, c_year, c_month, c_time;
        int day, hour, minute, second;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul",
                "Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        if ( stringp(get_time) )
                e_time = get_time;
        else e_time = ctime(time());

        // e_time must is ctime(time string) like "Sun May  3 00:52:12 1998"
        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        c_week  = chinese_number(member_array(week, week_name) + 1);
        c_month = chinese_number(member_array(month, month_name) + 1);

        c_year  = sprintf("%s%s%s%s",
                chinese_number(year[0]-48),
                chinese_number(year[1]-48),
                chinese_number(year[2]-48),
                chinese_number(year[3]-48));

        c_year =c_year +"年";
        c_month  = c_month + "月";
        if(c_week=="七")
        c_week="日";

        c_week = " 星期"+c_week;

        c_time = chinese_number(day) + "日";
        c_time += chinese_number(hour) + "點";
        c_time += chinese_number(minute) + "分";
        // maybe not need srcond to show
        // c_time += chinese_number(second) + "秒";

        if (type) {
                switch( type ) {
                        case 1: return c_year+c_month+c_time+c_week;
                        case 2: return c_year+c_month+c_time;
                        case 3: return c_month+c_time+c_week;
                        case 4: return c_month+c_time;
                        case 5: return year+"年"+(member_array(month, month_name) + 1)+
                                "月"+day+"日"+hour+"點"+minute+"分";
                        case 6: return (member_array(month, month_name) + 1)+
                                "月"+day+"日"+hour+"點"+minute+"分";
                        case 7: {
                                return sprintf("%s/%s/%s",year,
                                strlen(itoa(member_array(month, month_name) + 1))<=1?
                                ("0"+itoa(member_array(month, month_name)+1)):itoa(member_array(month, month_name) + 1),
                                strlen(itoa(day))<=1?"0"+itoa(day):itoa(day),);
                        }
                        case 8: {
                                return sprintf("%s/%s/%s",year[2..4],
                                strlen(itoa(member_array(month, month_name) + 1))<=1?
                                ("0"+itoa(member_array(month, month_name)+1)):itoa(member_array(month, month_name) + 1),
                                strlen(itoa(day))<=1?"0"+itoa(day):itoa(day),);
                        }
                        case 9: {
                                return sprintf("%s/%s/%s %s",year,
                                strlen(itoa(member_array(month, month_name) + 1))<=1?
                                ("0"+itoa(member_array(month, month_name)+1)):itoa(member_array(month, month_name) + 1),
                                strlen(itoa(day))<=1?"0"+itoa(day):itoa(day),e_time[11..15]);
                        }

                        default: return c_year+c_month+c_time+c_week;
                }
        }
        return c_year+c_month+c_time+c_week;
}
