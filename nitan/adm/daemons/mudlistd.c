// This program is a part of NT MudLIB
 
#include <socket.h>
#include <socket_err.h>
#include <time.h>
#include <mudlib.h>

#define DATA_PATH       "/data/daemon/mudlistd.o"
#define LIBRARY_PATH    "/home/mud/nitan"
#define MRTGDATA 	"/data/daemon/mrtg/mudlist/"
#define MSG(x)		CHANNEL_D->channel_broadcast("nch", x)
#define DEBUG(x)        //CHANNEL_D->channel_broadcast("nch", x)

mapping mudlist = allocate_mapping(0);

nosave string *connectsort = allocate(0);
nosave mapping resolvedaddress = allocate_mapping(0);

nosave int current_call_out_handler;
nosave int current_socket_port;

void over_waiting_connect(int socket_port);


int save()
{
	return save_object(DATA_PATH);	
}

void connect()
{
	int socket_port;
	string ipport;
	
	if( !sizeof(connectsort) ) return;
	
	ipport = connectsort[0];

	socket_port = socket_create(STREAM, "socket_create_read_callback", "socket_create_close_callback");
	
	if( socket_port < 0) return;

	current_socket_port = socket_port;
	
	DEBUG(sizeof(connectsort)+". "+ipport+" 連線檢查");
	if( socket_connect(socket_port, resolvedaddress[ipport], "connect_read_callback", "connect_write_callback") < 0 ) 
		socket_close(socket_port);

	map_delete(mudlist[ipport], "USERS");

        current_call_out_handler = call_out((: over_waiting_connect :), 10, socket_port);
}

void connect_check()
{
	string address, ipport;
	
	if( !sizeof(connectsort) )
	{
		save();
		
		MSG("MUDLIST 更新資料完畢，共 "+sizeof(mudlist)+" 組 Mud 資料");
                HTML_D->create_mudlist_html();
		return;
	}

	ipport = connectsort[0];

	mudlist[ipport]["LAST_CONNECT_CHECK_TIME"] = time();

	sscanf(ipport, "%s %*d", address);

	if( sscanf(address, "%*d.%*d.%*d.%*d") == 4 )
	{
		resolvedaddress[ipport] = ipport;		
		connect();
	}
	else
	{
		DEBUG(sizeof(connectsort)+". "+address+" 進行名稱解析");
		resolve(address, "resolve_address_callback");
	}
}

void resolve_address_callback(string address, string resolved, int key)
{
	int port;
	string ipport;
	
	remove_call_out(current_call_out_handler);

	if( !sizeof(connectsort) ) return;
	
	ipport = connectsort[0];

	if( !resolved )
	{
		mudlist[ipport]["CONNECT_FAILED_TIMES"]++;
		map_delete(mudlist[ipport], "USERS");
		
		DEBUG(sizeof(connectsort)+". "+ipport+" 檢查逾時");
		connectsort = connectsort[1..];
		connect_check();
	}
	else
	{
		sscanf(ipport, "%*s %d", port);
		resolvedaddress[ipport] = resolved+" "+port;
	
		connect();
	}
}

void over_waiting_connect(int socket_port)
{
	string ipport;
	
	if( !sizeof(connectsort) ) return;
	
	ipport = connectsort[0];

	if( socket_port != current_socket_port )
	{
		socket_close(socket_port);
	}
	else
	{
		mudlist[ipport]["CONNECT_FAILED_TIMES"]++;
		remove_call_out(current_call_out_handler);
		socket_close(current_socket_port);
	
		DEBUG(sizeof(connectsort)+". "+ipport+" 檢查逾時");
		connectsort = connectsort[1..];
		connect_check();
	}
}

void connect_write_callback(int socket_port)
{   
        socket_write(socket_port, "gb\n");
}

void connect_read_callback(int socket_port, mixed info) 
{
	array usercount = allocate(3);
	string ipport;
	
	if( !sizeof(connectsort) ) return;
	
	ipport = connectsort[0];
	
	if( socket_port != current_socket_port )
	{
		socket_close(socket_port);
		return;
	}

	mudlist[ipport]["LAST_CONTACT_TIME"] = time();

	remove_call_out(current_call_out_handler);
	
	map_delete(mudlist[ipport], "CONNECT_FAILED_TIMES");

	if( stringp(info) && sizeof(mudlist[ipport]["USERS_COUNT_PARSE"])>0 && !mudlist[ipport]["USERS"] )
	{
		sscanf(remove_ansi(info), "%*s"+mudlist[ipport]["USERS_COUNT_PARSE"]+"%*s", usercount[0], usercount[1], usercount[2] );
		
		usercount = map(usercount, (: CHINESE_D->chinese_to_number($1) :));

		mudlist[ipport]["USERS"] = implode(usercount, (:$1+$2:));

		if( !mudlist[ipport]["USERS"] )
		{
                        socket_write(socket_port, "gb\n");
			// 十秒內沒再收到 read_callback 就跳過 users count 計算
			current_call_out_handler = call_out((: connect_read_callback :), 10, socket_port, 0);
			return;
		}
	}

	DEBUG(sizeof(connectsort)+". "+ipport+" 檢查完畢");
	socket_close(socket_port);
 
	connectsort = connectsort[1..];
	connect_check();

}

// 將單一 Mud 加入 MRTG
void add_mud_to_mrtg(string name)
{
	mapping info = ([
		"Directory":"mudlist/"+replace_string(name, " ", "_"),
		"Target":"`cat \""LIBRARY_PATH+MRTGDATA+name+"\"`",
		"YLegend":"user(s)",
		"LegendI":"線上人數",
		"LegendO":"",
		"Legend1":"在遊戲中的線上使用者人數",
		"ShortLegend":"人",
		"Legend2":"",
		"Title": mudlist[name]["MUD_CHINESE_NAME"]+" - "+mudlist[name]["MUD_ENGLISH_NAME"]+" 人數統計列表",
		"PageTop":mudlist[name]["MUD_CHINESE_NAME"]+" - "+mudlist[name]["MUD_ENGLISH_NAME"]+" 人數統計列表"
	]);
	
	// 紀錄該 Mud 之線上玩家數
	write_file(MRTGDATA+name, mudlist[name]["USERS"]+"\n0", 1);

	MRTG_D->addmrtg(name, info);
}

// 將中文玩家總數加入 MRTG
void add_all_muds_to_mrtg(int alluser)
{
	string name="0_total_count";
	mapping info=allocate_mapping(0);
	
	info = ([
		"Directory":"mudlist/"+name,
		"Target":"`cat \""LIBRARY_PATH+MRTGDATA+name+"\"`",
		"YLegend":"user(s)",
		"LegendI":"線上人數",
		"LegendO":"MUD 間數",
                "Legend1":"在 MUDs 遊戲中的線上總使用者人數",
		"Legend2":"當時所監測的 MUDs 數量",
		"ShortLegend":"&nbsp",
                "MaxBytes":10000,
                "AbsMax":20000,
		"Title": "MUDs 人數統計列表",
		"PageTop":"MUDs 人數統計列表"
	]);
	
	// 紀錄所有 Mud 線上玩家總數
	write_file(MRTGDATA+"0_total_count", alluser+"\n"+sizeof(mudlist), 1);

	MRTG_D->addmrtg(name, info);
}

// 更新 MRTG 資訊
void update_mrtg_data()
{
	int i;
	int hour;
	int alluser = 0;

	foreach( string name , mapping m in mudlist )
	{
		if( !stringp(name) || !mapp(m) ) continue;
		
		// 分散處理
		call_out((:add_mud_to_mrtg, name:), ++i*2);

		alluser += m["USERS"];
	}

	hour = TIME_D->query_realtime_array()[HOUR];
        if( alluser > DB_D->query_data("mudlist/maxusers/hour/"+hour) )
                DB_D->set_data("mudlist/maxusers/hour/"+hour, alluser);

	add_all_muds_to_mrtg(alluser);
}

void reset_maxuser(int hour)
{
        DB_D->delete_data("mudlist/maxusers/hour/"+hour);
}

void distributed_connect()
{
	if( sizeof(connectsort) ) return;

	connectsort = keys(mudlist);
	connect_check();
	
	update_mrtg_data();
	DEBUG("MUDLIST 開始取得資訊");
}

void change_ipport(string old_ipport, string new_ipport)
{
	if( undefinedp(mudlist[old_ipport]) )
		return;

	socket_close(current_socket_port);
	remove_call_out(current_call_out_handler);
	connectsort = allocate(0);

	mudlist[new_ipport] = copy(mudlist[old_ipport]);
	map_delete(mudlist, old_ipport);
	
	distributed_connect();
	save();
}

void add_mud(string ipport)
{	
	if( !mapp(mudlist[ipport]) )
		mudlist[ipport] = allocate_mapping(0);
	
	socket_close(current_socket_port);
	remove_call_out(current_call_out_handler);
	connectsort = allocate(0);
	
	distributed_connect();
	save();
}

void add_mud_info(string ipport, string key, string value)
{	
	if( !mapp(mudlist[ipport]) )
		add_mud(ipport);
	
	mudlist[ipport][key] = value;
}

void remove_mud_info(string ipport, string key)
{
	if( !mapp(mudlist[ipport]) ) return;
	
	map_delete(mudlist[ipport], key);
}

void remove_mud(string ipport)
{
	MRTG_D->removemrtg(replace_string(ipport, " ", "_"));
	map_delete(mudlist, ipport);

	socket_close(current_socket_port);
	remove_call_out(current_call_out_handler);
	connectsort = allocate(0);
	
	distributed_connect();

	save();
}

mapping query_mudlist()
{
	return mudlist;
}

int remove()
{
	socket_close(current_socket_port);
	remove_call_out(current_call_out_handler);
	
	return save();
}

void create()
{
	if( !restore_object(DATA_PATH) )
		save();

	distributed_connect();
}
string query_name()
{
	return "泥巴列表系統(MUDLIST_D)";
}
