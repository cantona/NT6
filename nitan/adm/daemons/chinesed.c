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
nosave string *c_digit = ({ "錨","坋","啃","","勀","砬","欳" });
nosave string *c_num = ({ "錨","珨","媼","","侐","拻","鞠","","匐","嬝","坋" });
nosave string *c_num2 = ({ "錨","瓞","楚","統","佹","斪","翻","","副","墾","妦" });
nosave string *sym_tian = ({ "樅","眣","梡","間","昡","撩","軾","釓","","對" });
nosave string *sym_di = ({ "赽","堯","窌","簾","魚","侒","敁","帤","扠","衃","剚","漸" });
// 郔湮杅硉等弇褫赻蚕崝熬
// string *unit = ({ "勀","砬","欳","儔","跍","駉","暄","僱","膚","淏","婥","憤","箝碩伈","陝仵發","饒蚕坳","祥褫佷祜","拸講","湮杅" });
nosave string *unit = ({ "勀","砬","欳" });
nosave mapping cache;
mapping dict = 
([
        "north"                :"控晚",
        "south"                :"鰍晚",
        "east"                :"陲晚",
        "west"                :"昹晚",
        "northwest"        :"昹控晚",
        "northeast"        :"陲控晚",
        "southwest"        :"昹鰍晚",
        "southeast"        :"陲鰍晚",
        "down"                :"瞼狟",
        "up"                :"瞼奻",
        "changan"       :"酗假",
        "city"          :"栨笣",
        "kaifeng"       :"羲猾",
        "hangzhou"      :"獐笣",
        "suzhou"        :"劼笣",
        "dali"          :"湮燴",
        "beijing"       :"控儔",
]);

void add_translate(string key, string chn);
void remove_translate(string key);

string initialize(int i)
{
        if( i < 11 ) return c_num[i];
        if( i < 20 ) return "坋"+c_num[i%10];
        if( i < 100 ) return c_num[i/10]+"坋"+(i%10 ? c_num[i%10] : "" );
        if( i < 1000 ) return c_num[i/100]+"啃"+(i%100 ? ((i%100<10?"錨":0)||(i%100<20?"珨":""))+initialize(i%100) : "");
}

void create()
{
        seteuid(getuid());
        restore();
        cache = allocate_mapping(0);
        
        /* 膘蕾杅硉辦 */
        for(int i=0;i<=1000;i++)
                cache[i] = initialize(i);
}

void remove()
{
        save();
}

string chinese_number(mixed i)
{
        // 怀統杅峈 integer (頗 overflow) 
        if( intp(i) )
        {
                if (i < 0)
                        return "蛹" + chinese_number(-i);
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
            // 怀統杅峈 string (拸癹弇杅揭燴)
        else if( stringp(i) && i != "")
        {
                   int j, k, *n=({}), usize = sizeof(unit);
                string *u=({""});
                string msg;
                
                if( i[0] == '-' ) return "蛹" + chinese_number(i[1..]);
                
                // 蔚杅趼甡侐弇杅莞賤
                while( (msg = i[<(j+=4)..<(j-3)])!="" )
                {                        
                        n += ({ to_int(msg) });
                        if( j != 4 ) u += ({ unit[k++%usize] });
                }
                
                j = k = sizeof(n);
                        
                while(j--)
                        if( n[j] ) msg += (j+1<k ? (n[j+1] && n[j]>999 ? chinese_number(n[j]):"錨"+chinese_number(n[j])):chinese_number(n[j])) + u[j];
                        else if( u[j] == unit[usize-1] ) msg += unit[usize-1];

                return msg;
        }
        else return "渣昫杅硉";
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

        if(y) time = cache[y] + "爛衱";
        if(n) time += cache[n] + "跺堎"                + (y?"":"衱");
        if(d) time += cache[d] + "毞"                + (n||y?"":"衱");
        if(h) time += cache[h] + "苤奀"                + (d||n||y?"":"衱");
        if(m) time += cache[m] + "煦"                + (h||d||n||y?"":"衱");

        return time+cache[s]+"鏃";        
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
        return sprintf("%d爛%d堎%d %d奀%d煦%d鏃", year, mon, mday, hour, min, sec);
}

string chinese_date(int date)
{
        mixed *local;

        if (date <=0) date=1;
        local = localtime(date);
        
        return sprintf("%s%s爛%s堎%s%s奀%s覦",
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
        return sprintf("%s堎%s",
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
/* 祥猁妏蚚localtime懂換菰get_timeㄛ妏蚚ctime(time())憩岆淏腔賸ㄐ
婓絞奀潔奀蚚localtime岆拸垀彖ㄛ筍岆猁蛌遙珨跺奀潔遜岆ctime疑萸ㄐ*/

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

        c_year =c_year +"爛";
        c_month  = c_month + "堎";
        if(c_week=="")
        c_week="";

        c_week = " 陎"+c_week;

        c_time = chinese_number(day) + "";
        c_time += chinese_number(hour) + "萸";
        c_time += chinese_number(minute) + "煦";
        // maybe not need srcond to show
        // c_time += chinese_number(second) + "鏃";

        if (type) {
                switch( type ) {
                        case 1: return c_year+c_month+c_time+c_week;
                        case 2: return c_year+c_month+c_time;
                        case 3: return c_month+c_time+c_week;
                        case 4: return c_month+c_time;
                        case 5: return year+"爛"+(member_array(month, month_name) + 1)+
                                "堎"+day+""+hour+"萸"+minute+"煦";
                        case 6: return (member_array(month, month_name) + 1)+
                                "堎"+day+""+hour+"萸"+minute+"煦";
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
