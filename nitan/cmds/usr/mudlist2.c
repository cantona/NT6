// This program is a part of RW mudlib

#include <ansi.h>
#include <time.h>

inherit F_CLEAN_UP;

string help = @HELP
    列出主要 Mud 即時監測列表。
    另可由 http://www.muds.cn 隨時查閱即時資料

HELP;

#define HOR     24
#define VER     14

string *listcolor = ({ NOR, HIW });

string online_user_record()
{
        int *realtime = TIME_D->query_realtime_array();
        int i, j, hour = realtime[HOUR];
        string str,b="□";
        //string str,b="□";
        string s="                                                                                                            ";
        string *list=({s,s,s,s,s,s,s,s,s,s,s,s,s,s});
        mapping record; 
        float w, max_num=0., min_num=10000.;
        string time = "    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23\n";
        int *num= allocate(HOR);

        record = DB_D->query_data("mudlist/maxusers/hour/");

        if( !mapp(record) ) return "";

        foreach( string hourstr, int sizeofusers in record  )
        {
                num[to_int(hourstr)] = sizeofusers;
                if( sizeofusers > max_num ) max_num = sizeofusers;
                if( sizeofusers < min_num ) min_num = sizeofusers;
        }

        w = ((max_num-min_num)/VER);
        if( w<=0 )
                w=0.001;
        str = NOR WHT"↑"HIW"中文 Mud 玩家上線時間趨勢圖\n"NOR;
        for(i=0;i<VER;i++)
        {
                for(j=0;j<HOR;j++)
                {
                        if((num[j]-min_num)/w > 11-i)
                        {
                                if(list[i][j*4..j*4+3] != " "+b+" ")
                                        list[i][j*4..j*4+3] = sprintf("%|4d",num[j]);
                                if( i < VER-1 )
                                        list[i+1][j*4..j*4+3]=" "+b+" ";
                        }
                }
                str +=NOR WHT"□"NOR+list[i]+"\n";
        }

        str += NOR WHT"└────────────────────────────────────────────────→\n"NOR;
        str += HIC+time[0..(hour*4+1)]+HIM+"["+HIR+sprintf("%2d",hour)+HIM+"]"+HIC+time[(hour*4+6)..<0]+NOR+"\n\n";

        return str;
}

int mudlist_sort(mapping mudlist, string mud1, string mud2)
{
        string mud1_chinese = mudlist[mud1]["MUD_CHINESE_NAME"];
        string mud2_chinese = mudlist[mud2]["MUD_CHINESE_NAME"];
        string mud1_english = mudlist[mud1]["MUD_ENGLISH_NAME"];
        string mud2_english = mudlist[mud2]["MUD_ENGLISH_NAME"];

        if( sizeof(mud1_chinese) != sizeof(mud2_chinese) )
                return sizeof(mud1_chinese) > sizeof(mud2_chinese) ? 1 : -1;
        
        return strcmp(mud1_chinese || mud1_english, mud2_chinese || mud2_english);
}

int main(object me, string arg) 
{
        string msg, ip, mudname;
        int port, allmuders, time;
        mapping mudlist, data;
        string *mudnamesort;

        mudlist = MUDLIST_D->query_mudlist();

        msg = HIM"中文 Mud 即時監測列表\n"NOR;

        msg +=HIM"中文名稱 - 英文名稱                        網路位置                 埠   狀態 玩家 最後連線時間\n"NOR;
        msg +="──────────────────────────────────────────────────\n";

        mudnamesort = sort_array(keys(mudlist)-({0}), (: mudlist_sort($(mudlist), $1, $2) :)) ;

        time = time();

        foreach( string ipport in mudnamesort )
        {
                data = mudlist[ipport];
                sscanf(ipport, "%s %d", ip, port);

                if( data["MUD_CHINESE_NAME"] && data["MUD_ENGLISH_NAME"] )
                        mudname = data["MUD_CHINESE_NAME"]+" - "+data["MUD_ENGLISH_NAME"];
                else if( data["MUD_CHINESE_NAME"] || data["MUD_ENGLISH_NAME"] )
                        mudname = data["MUD_CHINESE_NAME"] || data["MUD_ENGLISH_NAME"];
                else
                        mudname = "--未知名稱--";

                allmuders += data["USERS"];

                msg += sprintf("%-43s%-25s%-4d"NOR" %-5s%-5s%-26s\n",
                    mudname,
                    ip,
                    port,
                    (data["CONNECT_FAILED_TIMES"] ? NOR CYN"斷線"NOR : HIC"連線"NOR),
                    HIG+(!data["CONNECT_FAILED_TIMES"] ? (data["USERS_COUNT_PARSE"] ? data["USERS"] : "NA") : "")+NOR,
                    data["LAST_CONTACT_TIME"] ? TIME_D->replace_ctime(data["LAST_CONTACT_TIME"]) : "--/--/---- --:--",
                );
                
        }
        msg += NOR "──────────────────────────────────────────────────\n";
        msg += "* 網頁瀏覽永久位址為 http://www.muds.cn\n";
        msg += "* 玩家顯示 NA 代表系統無法直接查詢得到此 Mud 線上玩家數量\n";
        msg += "* 若您的 Mud 欲加入列表、修改或是不希望在列表出現，請至 muds.cn 5000 與 Lonely 聯系\n"NOR;
        msg += "──────────────────────────────────────────────────\n"NOR;
        msg += NOR WHT"共有 "HIW+sizeof(mudnamesort)+NOR WHT" 個 Mud，"HIW+allmuders+NOR WHT" 位玩家在列表中\n"NOR;
        msg += "──────────────────────────────────────────────────\n"NOR;

        msg+= online_user_record();
        
        me->start_more(msg);
        return 1;
}
