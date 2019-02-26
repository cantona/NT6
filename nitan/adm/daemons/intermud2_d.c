// This program is a part of NT mudlib

/*********************<   i2d.h     >*********************
#define MUD                     0
#define STREAM                  1
#define DATAGRAM                2
#define STREAM_BINARY           3
#define DATAGRAM_BINARY         4
//-----------------------------------------------
#define I2D_MUD_SERVER          ({"113.31.21.157", 5004})
#define MUDLIST_UPDATE_INTERVAL 600
#define REFRESH_INCOMING_TIME   3*60*60
//----------------------位元運算用-------------------------
#define GB_CODE                 1       // gb站點
#define ANTI_AD                 2       // 有垃圾廣告的站點
#define IGNORED                 4       // 被本站屏蔽信息站點
#define SHUTDOWN                8       // 關閉的站點
#define ONLINE                  16      // 可連接站點
#define DISCONNECT              32      // 失去聯繫的站點
#define ENCODE_CONFIRM          64      // 系統自動判定gb/big5碼的站點
***********************************************************/

#include <ansi.h>
#include <i2d.h>
#include <socket_err.h>
#include <origin.h>
#include <mudlib.h>
#include <message.h>


inherit F_DBASE;

#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "I2D 精靈："+(string)x)

nosave string my_address;
nosave string localhost = "127.0.0.1";      // mud的ip地址
nosave int udp_port = 5004;       // mud的udp端口

nosave mapping this_host;
mapping mudlist=([]);
nosave mapping incoming_mudlist=([]);
string save_path = "/data/network/";

int udp_socket,refresh_limit=time(),debug;

// prototype
varargs string SAVE_PATH(string name,int flag);
varargs string *fetch_mudname(string arg,int flag);
string get_mud_name(mapping info);
int compare_mud_info(mapping info);

void receive_mudlist_request(mapping info);
void receive_mudlist_answer(mapping info);
void receive_ping_request(mapping info);
void receive_ping_answer(mapping info);
void receive_gchannel_msg(mapping info);
void receive_shutdown(mapping info);
void receive_gwiz_msg(mapping info);
void receive_warning(mapping info);
void receive_startup(mapping info);
void receive_gtell(mapping info);
void receive_affirmation(mapping info);
void receive_support_request(mapping info);
void receive_support_answer(mapping info);
void receive_locate_request(mapping info);
void receive_locate_answer(mapping info);
void receive_rwho_answer(mapping info);
void receive_rwho_request(mapping info);


void send_ping_request(string target, int port);
void send_mudlist_request(string target, int port);
void read_callback(int socket,string info,string address);
void send_shutdown(string target, int port);
void send_startup(string targ,int port);
varargs void send_warning(string targ,int port,string msg,string fakehost);
void refresh_ping_buffer();
void refresh_buffers();
protected void set_mudlist(string name,mapping info);
protected void set_incoming_mudlist(string name,mapping info);
protected void resolve_callback(string addr, string resolved, int key);

//-------------------------------------------------------------------------------------------
nosave mapping service_handler = ([
    "mudlist_q" :       (: receive_mudlist_request :),
    "mudlist_a" :       (: receive_mudlist_answer :),
    "ping_q" :          (: receive_ping_request :),
    "ping_a" :          (: receive_ping_answer :),
    "gchannel" :        (: receive_gchannel_msg :),
    "shutdown" :        (: receive_shutdown :),
    "gwizmsg" :         (: receive_gwiz_msg :),
    "warning" :         (: receive_warning :),
    "startup" :         (: receive_startup :),
    "gtell"     :       (: receive_gtell :),
    "affirmation_a":    (: receive_affirmation :),
    "support_q" :       (: receive_support_request :),
    "support_a" :       (: receive_support_answer :),
    "locate_q" :        (: receive_locate_request :),
    "locate_a" :        (: receive_locate_answer :),
    "rwho_a" :          (: receive_rwho_answer :),
    "rwho_q" :          (: receive_rwho_request :),

]);
nosave mapping ping_buffer=([]);
nosave mapping affirmation_buffer=([]);
nosave mapping rwho_buffer=([]);
nosave mapping gtell_buffer=([]);
nosave mapping msg_buffer=([]);
//-------------------------------------------------------------------------------------------

#define GTELL_B         1
#define PING_B          2
#define AFFIRMATION_B   3
#define RWHO_B          4

void restore()
{
        restore_object(SAVE_PATH("i2d"));
}

int save()
{
        return save_object(SAVE_PATH("i2d"));
}

mapping current_mud_info()
{
        mapping this_mud;
        mapping m;
        int n;

        n = sizeof(filter_array(users(), (: ! wizardp($1) ||
                                            !query("env/invisible", $1):)));
        m = this_host + ([ "LASTESTCONTACT" : time(),
                           "USERS" : sprintf("%d", n) ]);

        this_mud = ([ localhost+":"+udp_port : m ]);
        return this_mud;
}

// 將沒 status  的全部設成 0
void make_status()
{
        foreach(string t , mapping ref d in mudlist)
        if(undefinedp(d["STATUS"])) d["STATUS"]=0;

        foreach(string t , mapping ref d in incoming_mudlist)
        if(undefinedp(d["STATUS"])) d["STATUS"]=0;
}

int check_dns_fake(string name)
{
        return sizeof(fetch_mudname(name))-1;
}

// 自動更新 incoming_mudlist 到 mudlist
void refresh_incoming()
{
        string name;
        mapping info;
        foreach(name , info in incoming_mudlist)
        if(info["CONNECTION"] > (REFRESH_INCOMING_TIME/MUDLIST_UPDATE_INTERVAL)-8 )
        {
                map_delete(info,"CONNECTION");
                mudlist[name]=info;
                map_delete(incoming_mudlist,name);
        }
        foreach( name,info in mudlist)
        if( info["HOSTADDRESS"]!=my_address && info["HOSTADDRESS"]!=localhost && ((time()-info["LASTESTCONTACT"]> 259200) ||
                (time()-info["LASTESTCONTACT"]>5*60*60 && check_dns_fake(info["NAME"])>0 ) ))
                map_delete(mudlist,name);
        incoming_mudlist=([]);
        refresh_limit=time();
        save();
}

void delete_mudlist(string mud)
{
        map_delete(mudlist,mud);
        save();
}

void add_incoming_mudlist(string address, int port)
{
        send_ping_request(address, port);
        send_mudlist_request(address, port);
}

void send_all_shutdown()
{
        string mud;
        mapping info;
        // 取得 mudlist 所含的資訊
        if( mapp(mudlist) )
                foreach(mud, info in mudlist)
                send_shutdown(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );

        // 取得 incoming_mudlist 所含資訊
        if( mapp(incoming_mudlist) )
                foreach(mud, info in incoming_mudlist)
                send_shutdown(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );
}

// 定時更新 mud 資訊
//protected void update_info()
void update_info()
{
        string mud;
        mapping info;
        // 取得 mudlist 所含的資訊
        if( mapp(mudlist) )
                foreach(mud, info in mudlist)
                send_ping_request(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );
        // 取得 incoming_mudlist 所含資訊
        if( mapp(incoming_mudlist) )
                foreach(mud, info in incoming_mudlist)
                send_ping_request(
                    info["HOSTADDRESS"],
                    info["PORTUDP"]
                );
        refresh_buffers();
        // 在 REFRESH_INCOMING_TIME 所設的時間到自動加入符合條件的 mud
        if( time()- refresh_limit > REFRESH_INCOMING_TIME )
        {
                refresh_incoming();

                // 再次取得 incoming_mudlist
                foreach(string t, mapping d in mudlist)
                send_mudlist_request(d["HOSTADDRESS"],d["PORTUDP"]);
        }

        // 定時 MUDLIST_UPDATE_INTERVAL 秒更新一次資訊
        //call_out((: update_info :),MUDLIST_UPDATE_INTERVAL);
        SCHEDULE_D->set_event(MUDLIST_UPDATE_INTERVAL, 1, this_object(), "update_info"); 
}

// 一開始從這被呼叫 , 這沒問題吧 :Q
void create()
{
        seteuid(getuid());
        // 取回 save 下來的資料
        restore();
        resolve( query_host_name(), (: resolve_callback :) );
        // 初始化 UDP port
        if( (udp_socket = socket_create(DATAGRAM, (: read_callback :) )) < 0 )
        {
                NCH_CHANNEL("UDP socket created fail.\n");
                error("Unable to create UDP socket.\n");
        }
        while( EEADDRINUSE==socket_bind(udp_socket, udp_port) )
                udp_port++;

        NCH_CHANNEL("初始化完成 , 使用 UDP port: "+udp_port);

        this_host = ([
                "NAME":         INTERMUD_MUD_NAME,      
                "MUDNAME":      CHINESE_MUD_NAME,
                "MUDGROUP":     MUD_GROUP,
                "HOST":         MUD_HOST_NAME,
                "HOSTADDRESS":  localhost,
                "LOCATION":     MUD_LOCATION,
                "DRIVER":       __VERSION__,
                "MUDLIB":       MUDLIB_NAME,
                "VERSION":      MUDLIB_VERSION_NUMBER,
                "ENCODING":     MUD_ENCODING,
                "STATUS":       ONLINE,
                "USERS":        ""+sizeof(users()),
                "PORTUDP":      ""+fetch_variable("udp_port"),
                "PORT":         ""+__PORT__,
        ]);
                
        refresh_buffers();
        // 呼叫定時更新的函式
        refresh_ping_buffer();
        
        // 送出 startup
        foreach(string mud,mapping info in mudlist)
        {
                mudlist[mud]["STATUS"]&=~ENCODE_CONFIRM;
                send_startup(info["HOSTADDRESS"],info["PORTUDP"]);
        }

        // 送出 ping 要求給 server
        //send_ping_request(I2D_MUD_SERVER[0],I2D_MUD_SERVER[1]);
        // 向預設 server 取得 mudlist
        //send_mudlist_request(I2D_MUD_SERVER[0],I2D_MUD_SERVER[1]);
        // 先抓一次 incoming_mudlist
        foreach(string t, mapping d in mudlist)
        send_mudlist_request(d["HOSTADDRESS"],d["PORTUDP"]);
        // 開始定期更新資訊
        evaluate((: update_info :));
}

// destruct 的 simul_efun 會先 call 這個
int remove()
{
        send_all_shutdown();
        socket_close(udp_socket);
        return save();
}

public void mud_shutdown()
{
        send_all_shutdown();
        socket_close(udp_socket);
        save();
}

protected void resolve_callback(string addr, string resolved, int key)
{
        my_address = resolved;
}

// UDP port 收進來的東西會先經過這
protected void read_callback(int socket,string info,string address)
{
        string *infoclip,title,datas;
        mixed handler;
        mapping infomap=([]);

#ifdef __PACKAGE_ANSI__
        info=ansi(info);
#endif
        if( debug) NCH_CHANNEL( sprintf( "socket %d\ninfo %s\naddress %s", socket, info, address ));
        // 檢查封包格式是否正確
        if(!sscanf(info,"@@@%s@@@%*s",info)) return;
        // 近一步到專屬的 service 分析
        infoclip = explode(info,"||");
        // 本站無法處理的服務在這過濾
        if(!infoclip || undefinedp(handler = service_handler[infoclip[0]]) )
        {
                NCH_CHANNEL(sprintf("Unknow I2 service %s from %s ",infoclip[0],address));
                return;
        }
        // 將 string -> mapping 以便往下傳遞
        foreach(string data in infoclip)
        if( sscanf(data, "%s:%s", title, datas)==2 ) infomap[title] = datas;
        // 將發送此 package 的 IP 紀錄到 mapping info 中
        sscanf(address, "%s %*s", address);
        if( (address+"" == my_address || address+"" == localhost)&& infomap["PORTUDP"]==udp_port+"" )
                return;
        infomap["HOSTADDRESS"] = address;
        if(debug) NCH_CHANNEL(sprintf("收到%s\n%O\n",address,info));
        // 交付給 service 專用的 function
        evaluate(handler,infomap);

}

// 送出訊息用的函式
void send_udp(string targ, mixed port, string service, mapping info)
{
        int socket;
        string title,data,msg;
        string mudname;

        // 不傳送我們沒有的服務
        if( undefinedp(service_handler[service]) )
        {
                NCH_CHANNEL("Unknow Service.");
                error("Invalid intermud Services.\n");
        }

        // 不傳送資料給自己.
        //NCH_CHANNEL(sprintf("ip:%s port:%s services:%s",targ,port,service));
        //NCH_CHANNEL(sprintf("%O",typeof(port)));
        if( (targ == my_address || targ == localhost) && port == udp_port )
                //      if( service!="ping_a" && service!="ping_q" )
                return;


        // 建立 socket 以開始傳送
        socket = socket_create(DATAGRAM, "read_callback");
        if( !socket ) return;

        // 將 mapping -> string
        msg = service;
        if( mapp(info) ) {
                foreach(title, data in info) {
                        if( !stringp(title) || !stringp(data) ) continue;
                        msg += sprintf("||%s:%s",title,data);
                }
        }
        mudname = targ+":"+port;
        /*
        if( !undefinedp(mudlist[mudname]) && ( (mudlist[mudname]["STATUS"]& GB_CODE) || ( !undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="gb") ))
                //if( (mudlist[mudname]["STATUS"]& GB_CODE) || ( !undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="gb") )
                msg = (string)LANGUAGE_D->toGB(msg); 
        */
        if( !undefinedp(mudlist[mudname]) && ( /*!(mudlist[mudname]["STATUS"]& GB_CODE) ||*/ ( !undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="big5") ))
                msg = (string)LANGUAGE_D->toBig5(msg);  // 轉換成big5碼發出信息
                
        // 送出訊息.
        socket_write(socket, "@@@" + msg + "@@@", targ + " " + port);
        // debug msg
        if(debug) NCH_CHANNEL(sprintf("送出到%s:\n%s\n"+HIY+"%O\n"+NOR,targ,port+"",msg));
        // 關閉傳送完畢的 socket
        socket_close(socket);


}
// 由 mapping package 中取得 mud name
string get_mud_name(mapping info)
{
        return info["HOSTADDRESS"]+":"+info["PORTUDP"];
}

// 由 mud name 辨認為第幾級資料
int get_info_level(string mudname)
{
        if( member_array(mudname,keys(mudlist))==-1)
        {
                if(member_array(mudname,keys(incoming_mudlist))==-1)
                        return -1;
                else    return 0;
        }
        else return 1;
}

void analyze_mud_info(mapping info)
{
        int info_level=get_info_level(get_mud_name(info));

        switch(info_level) {
        case -1: set_incoming_mudlist(get_mud_name(info),info);break;
        case  0: set_incoming_mudlist(get_mud_name(info),info);break;
        case  1: set_mudlist(get_mud_name(info),info);break;
        }
}
// 用於大部分函式, 分析 Mud 是否為已通過認證, 尚未認證送 pin_q
int compare_mud_info(mapping info)
{
        string mudname=get_mud_name(info);
        int level=get_info_level(mudname);

        if( level < 1 )
                send_ping_request(info["HOSTADDRESS"],info["PORTUDP"]);
        else if( mudlist[mudname]["STATUS"] &(SHUTDOWN | DISCONNECT))
        {
                mudlist[mudname]["STATUS"]&=(~(SHUTDOWN | DISCONNECT));
                mudlist[mudname]["STATUS"]|=ONLINE;
        }
        return level;
}

// 設定 or 更新 mudlist 資訊
protected void set_mudlist(string name,mapping info)
{
        mapping map;
        string t,d;

        // 用 IPADDRESS:PORT 做 index , 防止 fake , 若資料不合則擋掉
        if( sscanf(name, "%*d.%*d.%*d.%*d:%*d") != 5 ) return;
        // 還沒有此間 mud 資料? 添加進mudlist
        if( undefinedp(map = mudlist[name]) )
        {
                // 給定 mudname
                mudlist[name] = info;
                // 初始化 mud STATUS
                mudlist[name]["STATUS"]=0;
                return;
        }

        // 已存在資料,更新資訊 ...
        foreach(t, d in info) mudlist[name][t]=d;

}
// 設定 or 更新 incoming mudlist 資訊
protected void set_incoming_mudlist(string name,mapping info)
{
        mapping map;
        string t,d;

        if( sscanf(name, "%*d.%*d.%*d.%*d:%*d") != 5 ) return;
        if( undefinedp(map = incoming_mudlist[name]) )
        {
                incoming_mudlist[name] = info;
                incoming_mudlist[name]["CONNECTION"]=1;
                return;
        }

        // 更新資訊
        foreach(t, d in info) incoming_mudlist[name][t]=d;
        // 每次更新資訊連線迴應計算 + 1
        incoming_mudlist[name]["CONNECTION"]+=1;
}

// 清除暫存區
void refresh_buffers()
{
        rwho_buffer=([]);
        gtell_buffer=([]);
        affirmation_buffer=([]);
        //refresh_ping_buffer();
        msg_buffer=([]);
}

/********************************************************************************************
 * 由外界能設定內部狀況的溝通函式..                                                         *
 ********************************************************************************************/

// SAVE_PATH 若傳入 flag , 即用以更新 SAVE_PATH
varargs string SAVE_PATH(string name,int flag)
{
        if(!flag) return save_path+name;
        else
        {
                save_path = name;
                save();
                return "SAVE_PATH "+save_path+" updated successfully.\n";
        }
}

void debug()
{
        if( !debug ) debug = 1;
        else debug = 0;
}

//--------------------------------------------------------------------------------------------
// Status 系列
//--------------------------------------------------------------------------------------------

// 用"ip:port"來尋找 mud data
mixed fetch_data(string name)
{
        int level;
        level = get_info_level(name);
        switch(level){
        case -1: return 0;
        case 1: return mudlist[name];
        case 0: return incoming_mudlist[name];
        }
        return 0;
}

// 用英文名尋找登記名 , 傳回符合的陣列
varargs string *fetch_mudname(string arg,int flag)
{
        mapping info;
        string name,*result=({});
        if( flag ) arg=lower_case(arg);
        foreach(name , info in (mudlist+incoming_mudlist))
        if(!flag)
        {
                if( arg==info["NAME"] )
                        result+=({name});
        }
        else    if( strsrch(lower_case(info["NAME"]),arg)!=-1 )
                result+=({name});
        return result;
}
// 用 mud ip 來尋找登記名 , 傳回符合陣列
varargs string *fetch_mudip(string arg)
{
        mapping info;
        string name,*result=({}),ip;
        //if( flag ) arg=lower_case(arg);
        foreach(name , info in (mudlist+incoming_mudlist))
        {
                sscanf(name,"%s:%*s",ip);
                if( arg == ip )
                        result+=({name});
        }
        return result;
}

// 設定 mudlist 裏的 mud 設定
int set_status(string mud,int num)
{
        int level;
        level = get_info_level(mud);
        if(level!=1 ) return 0;

        if( num > 0)
        {
                // 已經有此項設定
                if(mudlist[mud]["STATUS"] & num)
                        return 0;
                else mudlist[mud]["STATUS"]+=num;
        }
        else
        {       // 已經有此項設定
                if(!mudlist[mud]["STATUS"]&num)
                        return 0;
                else mudlist[mud]["STATUS"]-=(-num);
        }
        NCH_CHANNEL(sprintf("%s (%s) 加入屬性 [%d]",mudlist[mud]["NAME"],mud,num));
        save();
        return 1;
}

void add_buffer(string mudname,int kind)
{
        //if(get_info_level(mudname)<1)
        //      return;
        switch(kind)
        {
        case GTELL_B:
                if(undefinedp(gtell_buffer[mudname]))
                        gtell_buffer[mudname]=1;
                else
                        gtell_buffer[mudname]++;
                break;
        case PING_B:
                if(undefinedp(ping_buffer[mudname]))
                        ping_buffer[mudname]=({1,time()});
                else
                {
                        ping_buffer[mudname][0]++;
                        ping_buffer[mudname][1]=time();
                }
                break;
        case RWHO_B:
                if(undefinedp(rwho_buffer[mudname]))
                        rwho_buffer[mudname]=1;
                else
                        rwho_buffer[mudname]++;
                break;
        case AFFIRMATION_B:
                if(undefinedp(affirmation_buffer[mudname]))
                        affirmation_buffer[mudname]=1;
                else
                        affirmation_buffer[mudname]++;
        }
}

void sub_buffer(string mudname,int kind)
{
        //if(get_info_level(mudname)<1)
        //      return;
        switch(kind)
        {
        case GTELL_B:
                if(undefinedp(gtell_buffer[mudname]))
                        return;
                else
                {
                        gtell_buffer[mudname]--;
                        if(gtell_buffer[mudname]<1)
                                map_delete(gtell_buffer,mudname);
                }

                break;
        case PING_B:
                if(undefinedp(ping_buffer[mudname]))
                        return;
                else
                {
                        ping_buffer[mudname][0]--;
                        if( ping_buffer[mudname][0] < 1)
                                map_delete(ping_buffer,mudname);
                }
                break;
        case RWHO_B:
                if(undefinedp(rwho_buffer[mudname]))
                        return;
                else
                {
                        rwho_buffer[mudname]--;
                        if( rwho_buffer[mudname] < 1)
                                map_delete(ping_buffer,mudname);
                }
                break;
        case AFFIRMATION_B:
                if(undefinedp(affirmation_buffer[mudname]))
                        return;
                else
                {
                        affirmation_buffer[mudname]--;
                        if(affirmation_buffer[mudname]<1)
                                map_delete(affirmation_buffer,mudname);
                }
        }
}

int test_buffer(string mudname,int kind)
{
        switch(kind){
        case GTELL_B:
                if( !undefinedp(gtell_buffer[mudname]) ) return 1;
                break;
        case PING_B:
                if( !undefinedp(ping_buffer[mudname]) ) return 1;
                break;
        case RWHO_B:
                if( !undefinedp(rwho_buffer[mudname]) ) return 1;
                break;
        case AFFIRMATION_B:
                if( !undefinedp(affirmation_buffer[mudname]) ) return 1;
                break;
        }
        return 0;
}
/********************************************************************************************
 * 由此處開始 , 以下均為各種服務類別                                                        *
 ********************************************************************************************/

//--------------------------------------------------------------------------------------------
// Ping 系列
//--------------------------------------------------------------------------------------------
/* Intermud2 ping_q 封包格式
        ([
                "NAME":         (string)這 Mud 的網路名稱[慎選]
                                舊的 DNS_MASTER 如果遇到相同會 DNS_FAKE.
                "PORTUDP":      (int)(到最後都會被包成string)
                                這個mud的intermud2 daemon 監聽的 udp port.
        ])

    Intermud2 ping_a 封包格式
        ([
                "NAME":         (string)這 Mud 的網路名稱
                "MUDGROUP":     (string)網路羣組?
                "HOST":         (string)Mud 主機名稱?(好像沒用, 花瓶一個)
                "LOCATION":     (string)所在地?
                "MUDLIB":       (string)mudlib, 如果不是Eastern Stories會收不到 es channel.
                "VERSION":      (string)mudlib 版本?
                "ENCODING":     (string)編碼方式有 BIG5/GB,
                "USERS":        (int) users
                "PORTUDP":      (int) UDP port,
        ])
*/


// ping_buffer 用來擋掉不必要的 ping request
// 避免被 save 浪費資源宣成 nosave


// 發出 Ping 要求
void send_ping_request(string target, int port)
{
        send_udp(target, port, "ping_q", ([
                "NAME":         INTERMUD_MUD_NAME,
                "PORTUDP":      ""+udp_port,
            ]));
        //if(get_info_level(target+":"+port)>0)
        add_buffer(target+":"+port,PING_B);
        if(debug) NCH_CHANNEL("送出 PING 要求到 " + target + ":" + port + "。");
}

void refresh_ping_buffer()
{
        string t;
        int *d;
        // 再次執行此函式時不要有 callout 還在跑
        remove_call_out("refresh_ping_buffer");

        foreach(t,d in ping_buffer)
        if(time()-d[1] > 90)
        {
                int flag;
                //NCH_CHANNEL("peer...."+sprintf("%O%O\n",t,mudlist[t]["STATUS"]));
                if( get_info_level(t)==1 && !(mudlist[t]["STATUS"]&SHUTDOWN))
                {

                        mudlist[t]["STATUS"]&=(~ONLINE);
                        mudlist[t]["STATUS"]|=DISCONNECT;

                        // 2 hr內不見的站一直 ping -.-
                        if( time() - mudlist[t]["LASTESTCONTACT"] < 60*60*2 )
                                flag=1;
                }
                map_delete(ping_buffer,t);
                if( flag )
                {
                        send_ping_request(mudlist[t]["HOSTADDRESS"],mudlist[t]["PORTUDP"]);
                        flag=0;
                }
        }
        call_out("refresh_ping_buffer",60);
}

// 收到 ping request
void receive_ping_request(mapping info)
{
        int port;

        if(debug) NCH_CHANNEL(sprintf("收到 PING 要求 , 送出迴應到 %O", info));
        // UDP_PORT 格式錯誤
        if( undefinedp(info["PORTUDP"]) || !sscanf(info["PORTUDP"],"%d",port) ) return;
        
        if( (info["HOSTADDRESS"]==localhost || info["HOSTADDRESS"]==my_address) && port == udp_port )
                return;
        // 如果我們 mudlist 裏還沒有此 mud , 我們也要求他回 ping.
        if(get_info_level(get_mud_name(info))<0)
                compare_mud_info(info); // 發送ping要求
        // 送出 PING Answer
        send_udp(info["HOSTADDRESS"], port, "ping_a",
            ([
                "NAME":         INTERMUD_MUD_NAME,      // mudlib.h 中定義
                "MUDNAME":      CHINESE_MUD_NAME,
                "MUDGROUP":     MUD_GROUP,
                "HOST":         MUD_HOST_NAME,
                "LOCATION":     MUD_LOCATION,
                "DRIVER":       __VERSION__,
                "MUDLIB":       MUDLIB_NAME,
                "VERSION":      MUDLIB_VERSION_NUMBER,
                "ENCODING":     MUD_ENCODING,
                "USERS":        ""+sizeof(users()),
                "PORTUDP":      ""+udp_port,
                "PORT":         ""+__PORT__,
            ]));

        if(debug) NCH_CHANNEL("收到 PING 要求 , 送出迴應到 "+info["HOSTADDRESS"]+":"+port+" .");
}

// 收到 PING 迴應
void receive_ping_answer(mapping info)
{
        int status;
        
        string mudname=get_mud_name(info);
        // 有要求對方回 ping 嗎?
        if( !test_buffer(mudname,PING_B) )
        {
                //if( !sscanf(info["PORTUDP"],"%*d") ) return;
                NCH_CHANNEL("收到不明 Ping Answer From: "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" [ "+info["NAME"]+" ] ");
                                
                if(get_info_level(mudname)<1)
                        receive_ping_request(info); // 發送ping

                send_warning(info["HOSTADDRESS"],info["PORTUDP"],"\aWe didn't ask for this ping request.","Sorry,");
                //compare_mud_info(info);
                return;
        }
        //if(get_info_level(mudname)>0)
        sub_buffer(mudname,PING_B);
        info["LASTESTCONTACT"]=time();
        analyze_mud_info(info);
        if( get_info_level(mudname) == 1)
        {
                if( mudlist[mudname]["STATUS"] &(SHUTDOWN | DISCONNECT))
                        mudlist[mudname]["STATUS"]&=(~(SHUTDOWN | DISCONNECT));
                mudlist[mudname]["STATUS"]|=ONLINE;
        }
        if(debug) NCH_CHANNEL("收到 "+info["HOSTADDRESS"]+" 送回的 PING ANSWER .");
}

//--------------------------------------------------------------------------------------------
// Mudlist 系列
//--------------------------------------------------------------------------------------------


// 送出 Mudlist 訊息專用的函式 -.-
void send_mudlist_udp(string targ, int port,string info)
{
        int socket;

        // 不傳送資料給自己.
        if( (targ == my_address || targ == localhost) && port == udp_port ) return;

        // 建立 socket 以開始傳送
        socket = socket_create(DATAGRAM, "read_callback");
        if( !socket ) return;

        // 送出訊息.
        socket_write(socket, "@@@mudlist_a||" + info + "@@@\n", targ + " " + port);
        // 關閉傳送完畢的 socket
        socket_close(socket);
}

// 收到對方迴應的 mudlist 列表
void receive_mudlist_answer(mapping info)
{
        string name,clip;

        foreach(name,clip in info)
        {
                string *prop_list;
                mapping mudinfo=([]);
                if( strsrch(clip,"NAME")==-1 ) continue;

                prop_list=explode(clip,"|")-({""});
                foreach(string prop in prop_list) {
                        string t, d;
                        if( sscanf(prop, "%s:%s", t, d)==2 ) mudinfo[t] = d;
                }
                // 收到沒在清單上的 mud 就送 ping 要求
                //if(mudinfo["HOSTADDRESS"]!=my_address && mudinfo["HOSTADDRESS"]!=localhost && mudinfo["HOSTADDRESS"]!=fetch_variable("udp_port") )
                if( get_info_level(get_mud_name(mudinfo))<1 )
                        compare_mud_info(mudinfo); // 發送ping
        }

        if(debug) NCH_CHANNEL("收到 "+info["HOSTADDRESS"]+" 送回的 Mudlist Answer.");
}

// 要求對方發送 mudlist 列表
void send_mudlist_request(string targ, int port)
{
        send_udp(targ, port, "mudlist_q", ([
                "NAME":INTERMUD_MUD_NAME,
                "HOSTADDRESS":  localhost,
                "PORTUDP":      "" + udp_port,
            ]));
}

// 收到要求並送出 mudlist 列表
void receive_mudlist_request(mapping info)
{
        string name;
        mapping mudinfo;
        int i=1;
        if(!info["PORTUDP"]) return;
        if(get_info_level(get_mud_name(info))<1) return;

        foreach(name,mudinfo in mudlist)
        {
                // 沒有即時迴應的就有可能不在, 不送出以免製造網路垃圾
                if(!(mudinfo["STATUS"]&ONLINE)) continue;
                i++;
                send_mudlist_udp(info["HOSTADDRESS"],info["PORTUDP"],
                    sprintf("%d:|NAME:%s|HOST:%s|HOSTADDRESS:%s|PORT:%s|PORTUDP:%s|USERS:%s",
                                i,mudinfo["NAME"],mudinfo["HOST"],mudinfo["HOSTADDRESS"],mudinfo["PORT"],mudinfo["PORTUDP"],mudinfo["USERS"])

                );
        }
        if(debug) NCH_CHANNEL("收到 "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" 的 Mudlist Request 並回應之.");
}

//--------------------------------------------------------------------------------------------
// Shutdown 系列
//--------------------------------------------------------------------------------------------

void send_shutdown(string target, int port)
{
        send_udp(target, port, "shutdown",
            ([
                "NAME":INTERMUD_MUD_NAME,
                "PORTUDP":""+udp_port,
            ]));

        NCH_CHANNEL("送出 Shutdown 訊息到 " + target + ":" + port + "。");
}

void receive_shutdown(mapping info)
{
        if( compare_mud_info(info)==1 )
        {
                string name=get_mud_name(info);

                mudlist[name]["STATUS"]&=(~(ONLINE|DISCONNECT));
                mudlist[name]["STATUS"]|=SHUTDOWN;
        }
        NCH_CHANNEL("收到自 "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" 來的 Shutdown 訊息.");
}

//--------------------------------------------------------------------------------------------
// Gchannel 系列
//--------------------------------------------------------------------------------------------


void compare_last_msg(string mudname,string last_msg,string sender)
{
        if( undefinedp(msg_buffer[mudname]) || (msg_buffer[mudname][0]!=last_msg && msg_buffer[mudname][3]!=sender ))
        {
                //if( undefinedp(msg_buffer[mudname]) || msg_buffer[mudname][2] >= time()+15 )
                msg_buffer[mudname]=({ last_msg,1,time(),sender });

        }       else {
                if(msg_buffer[mudname][0]==last_msg || msg_buffer[mudname][3]==sender)
                        msg_buffer[mudname][1]++;
                msg_buffer[mudname][2]=time();
                msg_buffer[mudname][3]=sender;
        }

        if( msg_buffer[mudname][1] > 100 )
        {
                set_status(mudname,ANTI_AD);
                NCH_CHANNEL("將[ " + fetch_data(mudname)["MUDNAME"] +"] 加入 ANTI_AD 名單。");
        }
}

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

int accept_channel(string channel)
{
        class channel_class ch;
        //mapping channels = load_object(CHANNEL_D)->query_chann();
        mapping channels=fetch_variable("channels",load_object(CHANNEL_D));

        if( !undefinedp(channels[channel]) && !undefinedp((ch=channels[channel])->extra["intermud"]) )
                return 1;
}

// 收到 gchannel 訊息
void receive_gchannel_msg(mapping info)
{
        string msg,id,mudname,str;
        int status;

        // 一定必須要有的欄位
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["USRNAME"])
            ||  undefinedp(info["CHANNEL"])
            ||  undefinedp(msg = info["MSG"])
        )   return;
        // 去除最後一個 \n
        if(msg[<1..<0] == "\n") msg[<1..<0] = "";
        // 新來的站給我乖乖排隊回 ping :Q
        if( compare_mud_info(info)<1 ) return;

        mudname = get_mud_name(info);
        // 設定 id
        //id = info["USRNAME"] + "@"+ ((mudlist[mudname=get_mud_name(info)]["MUDNAME"])||"")+HBGRN"-"+mudlist[mudname]["NAME"]+"-"NOR;
        id = info["USRNAME"];
        // 有無中文 name ?
        if( info["CNAME"] ) id = info["CNAME"] + "(" + id + ")";
        // 是否為 Emote ?
        if( !undefinedp(info["EMOTE"]) )
                set("channel_id", id);

        mudname = get_mud_name(info);
        status = fetch_data(get_mud_name(info))["STATUS"];
        
        // 系統自動識別gb/big5碼站點
        if( !(status & ENCODE_CONFIRM) && strlen(msg) > 20 )
        {
                string mud_ip_port = info["HOSTADDRESS"]+":"+info["PORTUDP"];
                int con = LANGUAGE_D->encode_conjecture(msg);

                if( con >= 0 && con <= 15 ) mudlist[mud_ip_port]["STATUS"]|=GB_CODE;
                else if( con > 30 ) mudlist[mud_ip_port]["STATUS"]&=~GB_CODE;

                if( con != -1 ) mudlist[mud_ip_port]["STATUS"]|=ENCODE_CONFIRM;
        }

        if( status & IGNORED )  // 如果被列入隔絕信息站點，則屏蔽網際聊天頻道
        {
                if( info["EMOTE"] ) delete("channel_id");
                return;
        }

        if( !(status & GB_CODE) && ((status & ENCODE_CONFIRM) || (!undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="big5")) )

        {
                //id  = (string)LANGUAGE_D->toGB(msg);;
                msg = (string)LANGUAGE_D->toGB(msg);
        }

        if( status & ANTI_AD ) info["CHANNEL"]="ad";
        if( info["CHANNEL"]!="ad" )
        compare_last_msg(mudname,info["MSG"],id);
                               
        // 交付給 CHANNEL_D 處理
        // 作為其他非NTlib的mud，可直接用CHANNEL_D->do_channel(this_object(), info["CHANNEL"], msg, info["EMOTE"]);替換以下的內容
        //if( !(status & ANTI_AD) && accept_channel(info["CHANNEL"]) )
        if( accept_channel(info["CHANNEL"]) || info["CHANNEL"] == "ad") // 本站CHANNEL_D擁有這個頻道或廣告頻道
        {
                str = (info["EMOTE"]?("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ msg): ("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ id+"："+msg));
                CHANNEL_D->channel_broadcast(info["CHANNEL"], str);
        }
        else // 放到其他other頻道顯示
        {
                str = (info["EMOTE"]?("["+info["CHANNEL"]+"] "+"{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+msg):("["+info["CHANNEL"]+"] {"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+id+"："+msg));
                CHANNEL_D->channel_broadcast("other", str);
        }
        if( info["EMOTE"] ) delete("channel_id");
}

// 發出 gchannel 訊息
void send_gchannel_msg(string channel, string id, string name, string msg, int emoted)
{
        mapping info,mudinfo;
        string t;

        if(msg[<1..<0] == "\n") msg[<1..<0] = "";

        msg = replace_string(msg, "|", "|\033[1m");
        msg = replace_string(msg, "@", "@\033[1m");
        info = ([
            "NAME":         INTERMUD_MUD_NAME,
            "PORTUDP":      "" + udp_port,
            "USRNAME":      id,
            "CNAME":        name,
            "CHANNEL":      channel,
            "ENCODING":     MUD_ENCODING,
            "MSG":          msg
        ]);


        if( emoted ) info["EMOTE"] = "YES";

        foreach(t, mudinfo in (mudlist+incoming_mudlist))
        send_udp(mudinfo["HOSTADDRESS"], mudinfo["PORTUDP"],"gchannel", info);
}


//--------------------------------------------------------------------------------------------
// Gwizmsg 系列
//--------------------------------------------------------------------------------------------

/*
info = ([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + fetch_variable("udp_port"),
                "WIZNAME" : id,
                "CNAME" : name,
                "CHANNEL" : ch,
                "ENCODING" : CHARACTER_SET,
                "GWIZ" : msg,
        ]);

*/
void receive_gwiz_msg(mapping info)
{
        string msg,id,mudname;
        int status;

        // 一定必須要有的欄位
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["WIZNAME"])
            ||  undefinedp(info["CHANNEL"])
            ||  undefinedp(msg = info["GWIZ"])
        )   return;
        // 去除最後一個 \n
        if(msg[<1..<0] == "\n") msg[<1..<0] = "";
        // 新來的站給我乖乖排隊回 ping :Q
        if( compare_mud_info(info)<1 ) return;

        // 設定 id
        id = info["WIZNAME"];
        //id = info["WIZNAME"] + "@" + info["NAME"];
        // 有無中文 name ?
        if( info["CNAME"] ) id = info["CNAME"] + "(" + id + ")";
        
        // 是否為 Emote ?
        if( !undefinedp(info["EMOTE"]) )
                set("channel_id", id);
        // GB 轉碼 ?
        mudname=get_mud_name(info);

        status = fetch_data(mudname)["STATUS"];

        if( !(status & ENCODE_CONFIRM) && strlen(msg) > 20 )
        {
                string mud_ip_port = info["HOSTADDRESS"]+":"+info["PORTUDP"];
                int con = LANGUAGE_D->encode_conjecture(msg);

                if( con >= 0 && con <= 15 ) mudlist[mud_ip_port]["STATUS"]|=GB_CODE;
                else if( con > 30 ) mudlist[mud_ip_port]["STATUS"]&=~GB_CODE;

                if( con != -1 ) mudlist[mud_ip_port]["STATUS"]|=ENCODE_CONFIRM;
        }

        /*
        if( status & IGNORED ) // 如果被列入隔絕信息站點，則屏蔽網際聊天頻道
        {
                if( info["EMOTE"] ) delete("channel_id");
                return;
        }
        */

        if( !(status & GB_CODE) && ((status & ENCODE_CONFIRM) || (!undefinedp(mudlist[mudname]["ENCODING"]) && lower_case(mudlist[mudname]["ENCODING"])=="big5")) )
        {
                // id = (string)LANGUAGE_D->toGB(id);
                msg = (string)LANGUAGE_D->toGB(msg);
        }
        
        // 作為其他非NTlib的mud，可直接用CHANNEL_D->do_channel(this_object(), info["CHANNEL"], msg, info["EMOTE"]);替換以下的內容
        if( status & ANTI_AD ) // 垃圾廣告站點
        {
                info["CHANNEL"]="ad"; // 把對方網絡頻道改成廣告頻道
                CHANNEL_D->channel_broadcast(info["CHANNEL"], info["EMOTE"]?("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ msg):("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ id+"："+msg));

                if( info["EMOTE"] ) delete("channel_id");
                return;
        }

        // 交付給 CHANNEL_D 處理
        CHANNEL_D->channel_broadcast("gwiz","["+info["CHANNEL"]+"] "+(info["EMOTE"]?("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+msg):("{"+HBGRN+mudlist[mudname]["NAME"]+NOR+"} "+ id+"："+msg)));
        if( info["EMOTE"] ) delete("channel_id");

        //NCH_CHANNEL("收到 gwizmsg "+info["CHANNEL"]+" 訊息");
}
void send_gwiz_msg(string channel, string id, string name, string msg, int emoted)
{
        mapping info,mudinfo;
        string t;

        if(msg[<1..<0] == "\n") msg[<1..<0] = "";
        msg = replace_string(msg, "|", "|\033[1m");
        msg = replace_string(msg, "@", "@\033[1m");
        info = ([
            "NAME":         INTERMUD_MUD_NAME,
            "PORTUDP":      "" + udp_port,
            "WIZNAME":      id,
            "CNAME":        name,
            "CHANNEL":      channel,
            "ENCODING":     MUD_ENCODING,
            "GWIZ":          msg,
        ]);
        if( emoted ) info["EMOTE"] = "YES";

        foreach(t, mudinfo in (mudlist+incoming_mudlist))
        send_udp(mudinfo["HOSTADDRESS"], mudinfo["PORTUDP"],"gwizmsg", info);
}

//--------------------------------------------------------------------------------------------
// Warning 系列
//--------------------------------------------------------------------------------------------

void receive_warning(mapping info)
{
        string msg;

        if(compare_mud_info(info)<1)
                return;

        msg=sprintf("自 %s(%s) 告知的警告: %s 於 %s",info["NAME"],info["HOSTADDRESS"],info["MSG"],info["FAKEHOST"]);

        send_warning(info["HOSTADDRESS"],info["PORTUDP"],
            sprintf("Thank For Your Warning [%s], we have loged it , and will try to solve it soon :).",msg));

        //log_file("static/intermud2", "[warn]"+msg);
        NCH_CHANNEL(msg);
}

varargs void send_warning(string targ,int port,string msg,string fakehost)
{
        send_udp(targ, port, "warning",
            ([
                "NAME":INTERMUD_MUD_NAME,
                "PORTUDP":""+udp_port,
                "MSG":msg,
                "FAKEHOST":fakehost?fakehost:"",
            ]));

}

//--------------------------------------------------------------------------------------------
// Startup 系列
//--------------------------------------------------------------------------------------------

// 送出 startup ,  反正馬上就送 ping 了, 送基本的就好.
void send_startup(string targ,int port)
{
        send_udp(targ, port, "startup",
            ([
                "NAME":INTERMUD_MUD_NAME,
                "PORTUDP":""+udp_port,
            ]));
        // 對方收到 startup 會回 ping_a
        add_buffer(targ+":"+port,PING_B);
        //NCH_CHANNEL("送出 startup 訊息到 " + targ + ":" + port + "。");
}

void receive_startup(mapping info)
{
        receive_ping_request(info);
        NCH_CHANNEL("收到自 "+info["HOSTADDRESS"]+":"+info["PORTUDP"]+" 來的 startup 訊息.");
}

//--------------------------------------------------------------------------------------------
// affirmation_a 系列
//--------------------------------------------------------------------------------------------


void add_affirmation_buffer(mapping info,string service)
{
        string name=get_mud_name(info);

        service=lower_case(service);

        if(!undefinedp(affirmation_buffer[name+"-"+service]) )
                affirmation_buffer[name+"-"+service]++;
        else affirmation_buffer[name+"-"+service]=1;
}

void receive_affirmation(mapping info)
{
        string name=get_mud_name(info);
        object ob;

        if(compare_mud_info(info)<1)
                return;
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["WIZTO"])
            ||  undefinedp(info["MSG"])
            ||  undefinedp(info["MSG"])
        )   return;

        if( undefinedp(affirmation_buffer[name+"-"+info["TYPE"]]))
        {

                send_warning(info["HOSTADDRESS"],info["PORTUDP"],
                    "Affirmation warning : Your mud send unrequest Affirmation_a Please improve it.");
                NCH_CHANNEL(sprintf("Unrequest affirmation answer from %s:%s(%s)   \n%O\n",info["HOSTADDRESS"],info["PORTUDP"]+"",info["NAME"],info));
                return ;

        }
        affirmation_buffer[name+"-"+info["TYPE"]]--;
        if( !ob=find_player(info["WIZTO"]) )
        {
                send_warning(info["HOSTADDRESS"],info["PORTUDP"],
                    "Affirmation warning : No such user or he is offlin now.");
                return;
        }
        if( info["MSG"][<1..<0] != '\n' ) info["MSG"] += "\n";

        tell(ob, sprintf(GRN "[ %s ] %s[%s] 告訴你 ：%s\n"NOR,undefinedp(info["TYPE"])?" ":info["TYPE"],capitalize(info["WIZFROM"]),name,info["MSG"] ), TELLMSG);

}

void send_affirmation(string targ,int port, string to,string msg, string type)
{
        mapping info;
        info = ([
            "NAME" : INTERMUD_MUD_NAME,
            "PORTUDP" : "" + udp_port,
            "WIZFROM" : type+"@"+INTERMUD_MUD_NAME,
            "WIZTO"     : to,
            "TYPE" : type,
            "MSG" : msg,
        ]);
        send_udp(targ,port,"affirmation_a",info);
        NCH_CHANNEL("send affirmation msg to "+to+"@"+targ+":"+port);
}

//--------------------------------------------------------------------------------------------
// Gtell 系列
//--------------------------------------------------------------------------------------------



void receive_gtell(mapping info)
{
        string name=get_mud_name(info);
        object ob;

        if(compare_mud_info(info)<1)
                return;
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["WIZTO"])
            ||  undefinedp(info["WIZFROM"])
            ||  undefinedp(info["MSG"])
        )   return;
        if( !test_buffer(name,GTELL_B))
        {
                if(time()-gtell_buffer[name] < 1)
                {
                        send_affirmation(info["HOSTADDRESS"],info["PORTUDP"],info["WIZFROM"],
                            "Gtell warning : Your mud send too many GTELL request in the same time , Please try again later.","gtell");
                        NCH_CHANNEL(sprintf("%s[%s:%s] gtell 太頻繁 , ignore",info["NAME"],info["HOSTADDRESS"],info["PORTUDP"]));
                        return ;
                }
        }
        gtell_buffer[name]=time();

        if( !ob=find_player(info["WIZTO"]) )
        {
                send_affirmation(info["HOSTADDRESS"],info["PORTUDP"],info["WIZFROM"],
                    "GTELL warning : No such user or he is offlin now.","gtell");
                return;
        }
        if( info["MSG"][<1..<0] != '\n' ) info["MSG"] += "\n";
        if( undefinedp(info["CNAME"]) )
                tell(ob, sprintf(GRN "%s@%s(%s) 告訴你：%s"NOR,capitalize(info["WIZFROM"]),info["NAME"],name,info["MSG"] ), TELLMSG);
        else    tell(ob, sprintf(GRN "%s(%s@%s[%s]) 告訴你：%s"NOR,info["CNAME"],capitalize(info["WIZFROM"]),info["NAME"],name,info["MSG"] ), TELLMSG);

        send_affirmation(info["HOSTADDRESS"],info["PORTUDP"],info["WIZFROM"],
            "GTELL Respond : "+info["WIZTO"]+" has received your message.","gtell");

}

int send_gtell(string targ,int port,string my_id,string my_cname,string targ_id,string msg)
{
        mapping info;
        info = ([
            "NAME" : INTERMUD_MUD_NAME,
            "PORTUDP" : "" + udp_port,
            "WIZFROM" : my_id,
            "WIZTO"     : targ_id,
            "CNAME" : my_cname,
            "MSG" : msg,
        ]);
        add_affirmation_buffer(mudlist[targ+":"+port],"gtell");
        send_udp(targ,port,"gtell",info);

        NCH_CHANNEL(sprintf("%s send gtell msg to %s@%s:%s",my_id,targ_id,targ,port+""));
        return 1;
}

//--------------------------------------------------------------------------------------------
// Support 系列
//--------------------------------------------------------------------------------------------

//void send_support_answer(string targ,int port,)

void receive_support_request(mapping info)
{
        string answer;

        if(compare_mud_info(info)<1)
                return;

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["CMD"])
            ||  undefinedp(info["ANSWERID"])
        )   return;

        if( info["CMD"]="tcp" )
                answer="no";
        else
        {
                string cmd=info["CMD"];
                if( undefinedp(service_handler[cmd]) )
                        answer="no";
                else answer = "yes";
        }

        if( answer="yes" )
        {
                send_udp(info["HOSTADDRESS"],info["PORTUDP"],"support_a",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "CMD" : info["CMD"]+(!undefinedp(info["PARAM"]) ? "||PARAM:"+info["PARAM"] : ""),
                        "ANSWERID" : info["ANSWERID"],
                        "SUPPORTED" : "yes",
                    ]));
        } else
        {
                send_udp(info["HOSTADDRESS"],info["PORTUDP"],"support_a",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "CMD" : info["CMD"]+(!undefinedp(info["PARAM"]) ? "||PARAM:"+info["PARAM"] : ""),
                        "ANSWERID" : info["ANSWERID"],
                        "NOTSUPPORTED" : "yes",
                    ]));
        }
}


//--------------------------------------------------------------------------------------------
// Locate 系列
//--------------------------------------------------------------------------------------------

void receive_locate_request(mapping info)
{
        string answer;

        if(compare_mud_info(info)<1)
                return;

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["ASKWIZ"])
            ||  undefinedp(info["TARGET"])
        )   return;

        if( find_player(lower_case(info["TARGET"])) )
                answer="YES";
        else answer="NO";

        send_udp(info["HOSTADDRESS"],info["PORTUDP"],"locate_a",([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + udp_port,
                "TARGET" : info["TARGET"],
                "ASKWIZ" : info["ASKWIZ"],
                "LOCATE" : answer,
            ]));
}

void send_locate_request(string my_name,string t_name)
{
        string t;
        mapping mudinfo;

        foreach(t, mudinfo in (mudlist+incoming_mudlist))
        send_udp(mudinfo["HOSTADDRESS"],mudinfo["PORTUDP"],"locate_q",([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + udp_port,
                "TARGET" : t_name,
                "ASKWIZ" : my_name,
            ]));
}

void receive_locate_answer(mapping info)
{
        object ob;
        if(compare_mud_info(info)<1)
                return;

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["LOCATE"])
            ||  undefinedp(info["ASKWIZ"])
            ||  undefinedp(info["TARGET"])
        )   return;

        switch(info["TARGET"])
        {
        case "NO":return;
        case "YES":
                if( ob = find_player(lower_case(info["ASKWIZ"])))
                        tell(ob,sprintf("%s was located on %s [%s:%s] now.\n",info["TARGET"],info["NAME"],info["HOSTADDRESS"],info["PORTUDP"]), ETCMSG);
                else return;
        }
        NCH_CHANNEL("收到 locate_answer");
}



//--------------------------------------------------------------------------------------------
// RWho 系列
//--------------------------------------------------------------------------------------------



void receive_rwho_request(mapping info)
{
        string str;
        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["ASKWIZ"])
        )   return;

        if(compare_mud_info(info)<1)
                return;

        str = "/cmds/usr/who.c"->who(0, info["VERBOSE"] ? "-l": "-i");

        send_udp(info["HOSTADDRESS"],info["PORTUDP"],"rwho_a",([
                "NAME" : INTERMUD_MUD_NAME,
                "PORTUDP" : "" + udp_port,
                "ASKWIZ" : info["ASKWIZ"],
                "RWHO"  : str,
            ]));
}

void receive_rwho_answer(mapping info)
{
        object ob;
        string mudname=get_mud_name(info);

        if( undefinedp(info["NAME"])
            ||  undefinedp(info["PORTUDP"])
            ||  undefinedp(info["ASKWIZ"])
            ||  undefinedp(info["RWHO"])
        )   return;

        if( !test_buffer(mudname,RWHO_B) )
        {
                compare_mud_info(info);
                return;
        }else sub_buffer(mudname,RWHO_B);

        if(!ob=find_player(info["ASKWIZ"]))
                return;
        tell(ob, info["RWHO"]+"\n", CMDMSG);
}

varargs void send_rwho_request(string ip,int port,string player,string arg)
{
        if(arg)
                send_udp(ip,port,"rwho_q",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "ASKWIZ" : player,
                        "VERBOSE": arg,
                    ]));
        else
                send_udp(ip,port,"rwho_q",([
                        "NAME" : INTERMUD_MUD_NAME,
                        "PORTUDP" : "" + udp_port,
                        "ASKWIZ" : player,
                    ]));
        add_buffer(ip+":"+port,RWHO_B);
}

string query_name()
{
        return "INTERMUD2 系統(INTERMUD2_D)";
}

