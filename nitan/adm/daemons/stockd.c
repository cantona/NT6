
// stockd.c 股票

#include <ansi.h>
#include <net/socket.h>
#include <net/socket_errors.h>


#define IP_ADDRESS      "125.211.213.125 80"

#define DATA_PATH       "/data/stockd.o"
#define REFRESH_TIME    600
#define MAX_ARRAY       30

mapping stocks;
int last_update_time;
nosave int get_stock_flag = 0;
nosave string addresurl;
nosave mapping connection;
nosave string *stock_array =
({
        "sz000999",
        "sz000850",
        "sh600500",
        "sh600050",
        "sh601398",
        "sh601099",
        "sh600010",
        "sh600019",
        "sz000002",
        "sh600068",
        "sz000016",
        "sz000678",
        "sz000063",
        "sz000898",
        "sz002124",
        "sz002157",
        "sh601318",
        "sh600690",
        "sz000609",
        "sh600008",
        "sz000777",
        "sh600266",
        "sz002169",
        "sz000839",
        "sh600005",
        "sz002042",
        "sz000037",
        "sz002050",
        "sh600576",
        "sh600598",
        "sh600125",
        "sz002159",
        "sh600497",
        "sh600048",
        "sh601668",
        "sh601600",
        "sh600036",
        "sz000503",
        "sz000998",
        "sh601788",
        "sh600578",
        "sh600071",
        "sz002182",
        "sh600378",
        "sh601088",
        "sz002069",
        "sh601939",
        "sh600104",
        "sh600062",
        "sh600812",
        "sh600739",
});
void refresh_stock_data();
int save()
{
        return save_object(DATA_PATH);
}

int remove()
{
        return save();
}

mapping query_stocks()
{
        return stocks;
}

string stockurl()
{
        return "GET " + addresurl + " HTTP/1.1\r\nPragma: No-Cache\r\nHost: hq.sinajs.cn\r\n\r\n";
        return "GET " + addresurl + " HTTP/1.1
Pragma: No-Cache
Host: hq.sinajs.cn\n\n";
}

void create()
{
        if( !restore_object(DATA_PATH) )
        {
                stocks = allocate_mapping(0);

                save();
        }

        refresh_stock_data();
        SCHEDULE_D->set_event(REFRESH_TIME, 1, this_object(), "refresh_stock_data");
}

void get_addressurl()
{
        string *current_array;

        if( sizeof(connection["array"]) < MAX_ARRAY )
        {
                addresurl = sprintf("/list=%s",implode(connection["array"],","));
                connection["array"] = ({});
                return;
        }

        current_array = connection["array"][0..MAX_ARRAY-1];
        addresurl = sprintf("/list=%s",implode(current_array,","));
#ifdef DEBUG
        CHANNEL_D->channel_broadcast("nch", sprintf("addresurl %s\n", addresurl));
#endif
        connection["array"] = connection["array"][MAX_ARRAY..];
        return;
}

// 解析資料
void parse_data(string data)
{
        int pos_s;
        int pos_e;
        mixed code;
        string temp, text1, text2;
        string status;
        string str, str2;
        string *stock_data, *stock_data2;

        if( sizeof(data) )
        {
                pos_s = strsrch(data, "var hq_str_");

                if( pos_s == -1 )
                {
                        CHANNEL_D->channel_broadcast("sys", "無法解析滬深A股個股資料");
                        return;
                }

                temp = data[pos_s..];
                temp = replace_string(temp, "\r", "");
#ifdef DEBUG               
                CHANNEL_D->channel_broadcast("nch", sprintf("%s\n", temp));
#endif

                while( sscanf(temp, "%*svar hq_str_%s=\"%s\";\n%s",code, str, temp) >= 3 )
                {
                        reset_eval_cost();

                        code = code[2..];

                        stock_data = copy(explode(str, ","));

                        if( to_float(stock_data[3]) < to_float(stock_data[2]) ) status = "down";
                        else status = "up";
                        
                        if( to_float(stock_data[3]) > to_float(stock_data[2]) && (to_float(stock_data[3])-to_float(stock_data[2])) * 100 / to_float(stock_data[2]) >= 9.9 ) status = "t3r2";
                        else if( to_float(stock_data[3]) < to_float(stock_data[2]) && (to_float(stock_data[3])-to_float(stock_data[2])) * 100 / to_float(stock_data[2]) <= -9.9 ) status = "t3g2";

                        stocks[code] = allocate_mapping(0);
                        stocks[code]["股票名稱"] = stock_data[0];
                        stocks[code]["昨收盤"] = to_float(stock_data[2]);
                        stocks[code]["現價"] = to_float(stock_data[3]);
                        stocks[code]["開盤"] = to_float(stock_data[1]);
                        stocks[code]["狀態"] = status;

                        stocks[code]["漲跌"] = to_float(stock_data[3])-to_float(stock_data[2]);
                        stocks[code]["漲跌幅"] = (to_float(stock_data[3])-to_float(stock_data[2]))*100/to_float(stock_data[2]);
                        stocks[code]["最高"] = to_float(stock_data[4]);
                        stocks[code]["最低"] = to_float(stock_data[5]);
                        stocks[code]["成交張數"] = to_int(stock_data[8]);
                        stocks[code]["日期"] = stock_data[30];
                        stocks[code]["時間"] = stock_data[31];

#ifdef DEBUG
                        CHANNEL_D->channel_broadcast("nch", "成功解析 "+code+stocks[code]["股票名稱"]+" 個股資料(現價 "+stocks[code]["現價"]+")");
#endif
                }
        }

        connection["data"] = "";
        return ;
}

int query_last_update_time()
{
        return last_update_time;
}

int query_get_stock_flag()
{
        return get_stock_flag;
}

void get_stock_data()
{
        int err, fd;

        if( !sizeof(connection["array"]) )
        {
                get_stock_flag = 0;
                last_update_time = time();
                save();
                return;
        }

        get_addressurl();
        fd = socket_create(STREAM, "read_callback", "close_socket");

        if( fd < 0 )
        {
                CHANNEL_D->channel_broadcast("nch", "無法與新浪股票服務器建立連接。\n");
                return;
        }

        err = socket_connect(fd, IP_ADDRESS, "read_callback", "write_callback");

        if( err != EESUCCESS )
                CHANNEL_D->channel_broadcast("nch", "無法連線股票網頁。");

#ifdef DEBUG               
        CHANNEL_D->channel_broadcast("nch", "與新浪股票服務器建立連接成功！");
#endif
        return;
}


void refresh_stock_data()
{
        int *nowtime = TIME_D->query_realtime_array();

#ifndef DEBUG
        if( nowtime[2] < 1 || nowtime[2] > 5 ) // 週末休盤
                return;

        if( nowtime[1] < 9
        ||  (nowtime[1] == 9 && nowtime[0] < 15) ) // 早上未開
                return;

        if( nowtime[1] == 11 && nowtime[0] > 45
        ||  (nowtime[1] == 12 && nowtime[0] < 45) ) // 中午休盤
                return;

        if( nowtime[1] > 15
        ||  (nowtime[1] == 15 && nowtime[0] > 15) ) // 下午休盤
                return;
#endif

        connection = allocate_mapping(0);
        connection["array"] = copy(stock_array);
        connection["data"] = "";
        get_stock_flag = 1;

        CHANNEL_D->channel_broadcast("sys", "開始更新股市資料。");
        get_stock_data();
}

int close_socket(int fd)
{
        socket_close(fd);

        parse_data(connection["data"]);

        call_out((: get_stock_data :), 1);
}

void read_callback(int fd, mixed message)
{
#ifdef DEBUG
        CHANNEL_D->channel_broadcast("nch", sprintf("callback %s\n", message));
#endif
        connection["data"] += message;

        return;
}

void write_callback(int fd)
{
        //string stockurl = sprintf("GET /list=%s HTTP/1.1\nPragma: No-Cache\nHost: hq.sinajs.cn\n\n",
        //                        connection["array"][0]);

        CHANNEL_D->channel_broadcast("nch", "開始抓取股票資料。");
        //socket_write(fd, stockurl);
        //connection["array"] = connection["array"][1..];
        socket_write( fd, stockurl());
        CHANNEL_D->channel_broadcast("nch", sprintf("stockurl %s\n", stockurl()));

        return ;
}

string make_code(string arg)
{
        if( arg[0..0] == "0" )
                arg = "sz" + arg;
        else if( arg[0..0] == "6" )
                arg = "sh" + arg;

        return arg;
}

void add_stock(string arg)
{
        arg = make_code(arg);

        if( member_array(arg, stock_array) != -1 ) {
                tell_object(this_player(), sprintf("%O\n",stocks[arg]));
                return;
        }

        stock_array += ({ arg });
}

mapping get_stock(string code)
{
        return stocks[code];
}

void del_stock(string arg)
{
        arg = make_code(arg);

        if( member_array(arg, stock_array) == -1 )
                return;

        stock_array -= ({ arg });
}


string query_name()
{
        return "股票系統(STOCK_D)";
}

