// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// cruised.c 漫遊精靈

#ifdef LONELY_IMPROVED

#include <ansi.h>
#include <mudlib.h>
#include <net/socket.h>
#include <cruise.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include "/adm/etc/database.h"

// 漫遊精靈如何工作？
// 每個站點的漫遊精靈負責進行認証和數據傳輸。啟動以後，漫遊
// 精靈會監聽一個端口，查詢來自其他站點的請求。
//
// 數據漫遊：
// 如果某個站點登陸了其他站點漫遊過來的使用者，則本站點從原
// 始站點漫遊精靈那裡獲得該玩家的數據，包括 login & user 以
// 及 item 三部分，由于 dbased 和 news 裡的數據用的是數據庫
// 來處理，所以就不需要漫遊。然後根據這些數據在本站點構造一
// 個玩家，這些數據會在原始站被刪除以確保各站數據唯一性，在
// 退出的時候不會傳遞回原先的站點，而保留在現在的站點。玩家
// 使用這種方式進行漫遊。
//
// 配套支持：
// 數據庫 mysql 需記錄玩家的 id  所在的站點、密碼以及姓名以
// 保証 id 的唯一性。數據庫還需處理 dbased 中數據以保証漫遊
// 過來的數據能得到有效使用。
//
// 認証流程：
// 漫遊精靈接受來自連線精靈的數據驗証請求，並將從需要請求得
// 站點或的數據。發送請求是需要包括用戶名和站點 -- 這個必須
// 通過一定手段進行保密。接受請求以後將查驗是否通過並返回相
// 應的信息。接收到返回的正確信息以後，漫遊精靈重新驅動起連
// 線精靈。
//
// 監聽的端口(以MUD的啟動端口為基準)
#define CRUISE_PORT                     21

// 經過授權的地址
#define AGENT_IP   ({ "127.0.0.1", "61.184.100.7", "219.134.89.94", "202.110.119.87", "218.89.171.162" }) 

#if 0
#define DEBUG_LOG(s)       tell_object(find_player("lonely"), s)
#else
#define DEBUG_LOG(s)
#endif

// 從版本服務器取回的文件後綴
#define APPENDFIX       ".cru"
#define STATUS_INIT                     0
#define STATUS_CONNECT                  1
#define MAX_AUTHENTICATING_USER         20

nosave int status = STATUS_INIT;
nosave mixed *cruise_queue = allocate(MAX_AUTHENTICATING_USER);
nosave int next_cruise = 0, queue_pointer = 0;

// 保存二進制代碼的路徑
nosave string bin_path;

nosave int cfd;
nosave string *cruise_file = ({ });
nosave mapping socket_info;

// 客戶端的連接信息
nosave mixed *client_info = 0;
// 傳送的文件
string *fetch_file_list = 0;

// 提供給外部的接口
int fetch_file(string file, string sites);
int authenticate_user(object ob, string sites);

protected void send_file(int fd, string file, string peer_name);
protected void server_init();
protected void in_listen_callback(int fd);
protected void in_read_callback(int fd, string str);
protected void in_write_callback(int fd);
protected void in_close_callback(int fd);
protected void parse_cmd(int fd);
protected void debug_info(string msg);
protected void cmd_getfile(int fd, string arg);
protected void cmd_get(int fd, string arg);
protected void cmd_close(int fd, string arg);
protected void syn_receive_result(string str);
protected void syn_fetch_file_from_server();
protected void syn_finish();
protected void sys_info(string msg);
protected void send_command(int fd, string cmd);
protected void send_cruise_file(string id, int fd);
protected int  syn_get_id_data();
protected int  send_error_msg(int fd, string msg);
protected int  send_pending_msg(int fd);
protected int  send_result(int fd, string msg);
protected int  connect_server();
protected int  syn_receive_file(buffer buf);
protected int  send_client_pending_msg();
protected void syn_close_callback(int fd);
protected void send_timeout(int fd);
int clear_syn_info();

int clean_up() { return 1; }

void create() 
{
        seteuid(ROOT_UID);
        bin_path = get_config(__SAVE_BINARIES_DIR__);
        set("channel_id", "漫遊精靈");

        call_out("server_init", 0);
}

protected void remove_from_queue()
{
        mixed *cruise;

        cruise = cruise_queue[queue_pointer];
        if (cruise[USER_ID])
        {        
                DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
        }  

        cruise_queue[queue_pointer] = 0;
        queue_pointer = (queue_pointer + 1) % MAX_AUTHENTICATING_USER;
}

void heart_beat()
{
        mixed *cruise; 

        if (status != STATUS_INIT)
                return;

        if (next_cruise == queue_pointer)
        {
                next_cruise = 0;
                queue_pointer = 0;
                cruise_queue = allocate(MAX_AUTHENTICATING_USER);
                set_heart_beat(0);
                return;
        }
        
        if (! fetch_file_list)
                fetch_file_list = 0;

        if (! connect_server())
        {
                cruise = cruise_queue[queue_pointer]; 
                if (cruise[USER_ID]) 
                {
                        DATABASE_D->db_set_user(cruise[USER_ID], "online", 0); 
                        DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION); 
                }
                log_file("cruise", sprintf("%s Failed to create socket or connect server.\n",
                                   log_time()));
        }
}

mixed query_queue()
{
        return cruise_queue;
}

void restore_cruise()
{
        socket_close(cfd);
        cfd = 0;
        socket_info = ([ ]);
        client_info = ({ });
        next_cruise = 0;
        queue_pointer = 0;
        cruise_queue = allocate(MAX_AUTHENTICATING_USER);
}

void remove(string euid)
{
        if (! this_player())
                return;

        if (sizeof(socket_info) > 0)
                error("漫遊精靈：目前正在有站點和本站漫遊數據，你不能摧毀漫遊精靈。\n");

        if (cfd && arrayp(client_info) && client_info[STATUS] != STATUS_FINISHED)
                error("漫遊精靈：目前數據正在漫遊中，你不能摧毀漫遊精靈。\n");
}

// 提供版本服務
protected void server_init()
{
        int port;

        CHANNEL_D->do_channel(this_object(), "sys", "漫遊精靈已經啟動。");

        // 創建漫遊通訊的SOCKET
        cfd = socket_create(STREAM_BINARY,
                            "in_read_callback",
                            "in_close_callback" );

        if (cfd < 0)
        {
                log_file("cruise", sprintf("%s Failed to create socket.\n", log_time()));
                return;
        }

        // 然後綁定SOCKET
        port = __PORT__ + CRUISE_PORT;
        if (socket_bind(cfd, port) < 0)
        {
                log_file("cruise", sprintf("%s Failed to bind socket.\n", log_time()));
                socket_close(cfd);
                return;
        }

        // 最後監聽
        if (socket_listen(cfd, "in_listen_callback" ) < 0)
        {
                log_file("cruise", sprintf("%s Failed to listen to socket.\n", log_time()));
                return;
        }

        // 初始化連接信息
        socket_info = ([ ]);
}

// 本地站監聽來自其他站點的請求
protected void in_listen_callback(int fd)
{
        int new_fd;
        string address;
        string ip;
        int port;

        if ((new_fd = socket_accept(fd, "in_read_callback",
                                        "in_write_callback")) < 0)
                // 沒有成功的接收這個連接請求
                return;

        address = socket_address(new_fd);
        if (! stringp(address) || sscanf(address, "%s %d", ip, port) != 2 ||
            // ! CONFIG_D->query(ip))
            member_array(ip, AGENT_IP) == -1)
        {
                // 這個地址沒有經過授權
                sys_info(sprintf("站點 %s 地址沒有經過授權。", 
                         stringp(address) ? address : "unknow"));            
                socket_close(new_fd);
                return;
        }

        sys_info(sprintf("站點 %s 連接本服務器開始構建通訊。", ip));

        socket_info[new_fd] = allocate(8);
        socket_info[new_fd][STATUS] = STATUS_LOGIN;
        socket_info[new_fd][CMD_BUFFER] = "";
        socket_info[new_fd][CMD_QUEUE] = ({ });
        socket_info[new_fd][PENDING_WRITE] = ({ });
        socket_info[new_fd][SUB_SITES] = "不詳";
        
        // 更新狀態
        socket_info[new_fd][STATUS] = STATUS_WAIT_COMMAND;
        in_write_callback(new_fd);

}

// 接受信息
protected void in_read_callback(int fd, mixed mess)
{
        int cc;
        string *cmds;
        mixed  prefix;
        string str;

        if (! arrayp(socket_info[fd]))
                return;

        if (stringp(mess))
                // 接收到了字符串
                str = mess;
        else
        if (bufferp(mess))
                // 接收到了緩沖區
                str = read_buffer(mess, 0, sizeof(mess));
        else
                return;

        if (! str) return;

        str = replace_string( str, "\r", "");
        if (stringp(prefix = socket_info[fd][CMD_BUFFER]))
                str = (string) prefix + str + "\n";
        else
                str += "\n";

        cmds = explode(str, "\n");
        socket_info[fd][CMD_BUFFER] = cmds[sizeof(cmds) - 1];

        if (sizeof(cmds) > 1)
        {
                // 將這些命令放入到命令隊列中
                cc = sizeof(socket_info[fd][CMD_QUEUE]);
                socket_info[fd][CMD_QUEUE] += cmds[0..<2];
                if (socket_info[fd][STATUS] == STATUS_WAIT_COMMAND)
                        // 正在接受命令狀態
                        parse_cmd(fd);
        }
}

// 成功寫入
protected void in_write_callback(int fd)
{
        buffer buf;
        string file;
        int pos, len;
        int i;

        for (i = 0; i < 32; i++)
        {
                // 循環處理消息
                reset_eval_cost();

                // 已經處理完了？
                if (! arrayp(socket_info[fd]))
                        // 是，這個不需要繼續處理了
                        return;

                // 如果有阻塞的普通消息，則我發送出去
                while (sizeof(socket_info[fd][PENDING_WRITE]))
                {
                        // 有阻塞的消息，發送之
                        if (send_pending_msg(fd) != 0)
                                // 沒有成功的發送，等待下一次發送
                                return;
                }

                // 根據當前的狀態進行進一步處理
                switch (socket_info[fd][STATUS])
                {
                case STATUS_SENDING:
                        // 正在發送文件
                        pos = socket_info[fd][FILE_POS];
                        len = socket_info[fd][FILE_SIZE] - pos;
                        if (len > FILE_BLOCK)
                                len = FILE_BLOCK;
                        if (len > 0)
                        {
                                buf = read_buffer((string) socket_info[fd][FILE_NAME], pos, len);
                                if (sizeof(buf) != len)
                                        // 讀取沒有完全成功？填寫零發送。
                                        buf = allocate_buffer(len);
                                // 判斷這次操作的結果
                                switch (socket_write(fd, buf))
                                {
                                case EESUCCESS:
                                        // 移動遊標
                                        pos += len;
                                        break;

                                case EECALLBACK:
                                        // 移動遊標
                                        pos += len;

                                        // 等待CALLBACK，先不繼續處理
                                        socket_info[fd][FILE_POS] = pos;
                                        return;

                                case EEWOULDBLOCK:
                                        // 發送忙
                                        call_out("in_write_callback", 2, fd);
                                        return;

                                default:
                                        // 發送失敗，等待下次callback
                                        return;
                                }
                        }

                        // 判斷文件是否發送完畢
                        if ((socket_info[fd][FILE_POS] = pos) >=
                            socket_info[fd][FILE_SIZE])
                        {  
                                file = socket_info[fd][FILE_NAME];
                                // 暫時取消了將被漫遊的資料文件更名即取消了刪除被漫遊的資料文件
                                // rename(file, file + ".oo");  
                                                              
                                // 文件已經發送完畢，更新狀態
                                socket_info[fd][STATUS] = STATUS_WAIT_COMMAND;
                                if (! sizeof(socket_info[fd][CMD_QUEUE]))
                                        // 已經沒有待處理的命令了
                                        return;

                                // 繼續處理命令：為什麼要用
                                // this_object() 進行呼叫？
                                // 這個是不能省略的，因為這
                                // 樣其它部分的函數就可以根
                                // 據previous_object() 分辨
                                // 是否試運行在callback內。
                                this_object()->parse_cmd(fd);

                                // 繼續，循環將會處理命令產生的結果
                        }

                        // 發送處理完畢
                        break;
        
                default:
                        // 未定義狀態，無操作
                        return;
                }

                // 一次處理(switch)完畢，循環繼續處理
        }

        // 運行太久了
        debug_info("向 SOCKET 寫入數據太多，暫緩。");
        call_out("in_write_callback", 1, fd);
}

// 連接斷開
protected void in_close_callback(int fd)
{
        string address;

        address = socket_address(fd);
        if (stringp(address))
                sscanf(address, "%s %*d", address);
        else
                address = "unknow";

        sys_info(sprintf("站點 %s 和本站斷開了連接。", address));

        // 清除信息
        map_delete(socket_info, fd);
}

// 供 LOGIN_D 調用的接口
int authenticate_user(object ob, string sites)
{
        int is_cruise;
        int next_next;       
        string cruise_id;
                
        if( !stringp(cruise_id=query("id", ob)) )
                return 0;
                
        if (! stringp(sites) || sites == LOCAL_STATION)
        {
                write(HIY "該人物所在的站點沒有得到確認或正在本站，漫遊被強行中止。\n" NOR);
                return 0;
        }
        
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();      
        
        is_cruise = DATABASE_D->db_query_user(cruise_id, "online");
                              
        if (is_cruise == 3)
        {
                write(HIY "由于同時在漫遊該人物檔案，漫遊被強行中止。\n" NOR);
                return 0;
        }
 
        next_next = (next_cruise + 1) % MAX_AUTHENTICATING_USER;
        if (next_next == queue_pointer) 
        {
                // 同時允許漫遊的玩家數量超過上限
                write(HIY "漫遊隊列已滿，請稍後在再進行數據漫遊。\n" NOR);
                return 0;
        }
        
        cruise_queue[next_cruise] = allocate(2);
        cruise_queue[next_cruise][USER_ID] = cruise_id;
        cruise_queue[next_cruise][USER_SITE] = sites;
        next_cruise = next_next;

        DATABASE_D->db_set_user(cruise_id, "online", 3);

        write(HIR "連接站點服務器獲取人物的數據中..，請稍後再嘗試登陸。\n" NOR);
        
        set_heart_beat(1);
        return 1;
}                         

// 向站點服務器端發送命令
void send_command(int fd, string cmd)
{
        if (! fd)
                // 檢查當前連接的CFD
                if (! (fd = cfd)) return;
                

        cmd += "\n";
        if (sizeof(client_info[PENDING_WRITE]))
        {
                // 已經有阻塞需要發送的數據了，這次發送的數
                // 據先阻塞
                client_info[PENDING_WRITE] += ({ cmd });
                return;
        }

        switch (socket_write(fd, cmd))
        {
        case EESUCCESS:
        case EECALLBACK:
                // 發送成功了
                return;

        case EEWOULDBLOCK:
                // 發送數據阻塞
                client_info[PENDING_WRITE] += ({ cmd });
                call_out("syn_write_callback", 2, fd);
                return;

        default:
                // 發送失敗
                client_info[PENDING_WRITE] += ({ cmd });
                return;
        }
}

// 發送阻塞的消息

protected int send_pending_msg(int fd)
{
        string result;

        result = socket_info[fd][PENDING_WRITE][0];

        switch (socket_write(fd, result))
        {
        case EESUCCESS:
                // 發送成功了
                socket_info[fd][PENDING_WRITE] = socket_info[fd][PENDING_WRITE][1..<1];
                return 0;

        case EECALLBACK:
                // 需要等待
                socket_info[fd][PENDING_WRITE] = socket_info[fd][PENDING_WRITE][1..<1];
                return -1;

        case EEWOULDBLOCK:
                // 發送數據阻塞
                call_out("in_write_callback", 2, fd);
                return -1;

        default:
        }
}

// 由于命令簡單，不採用常規的語法分析。
protected void parse_cmd(int fd)
{
        string cmd;
        string word, arg;

        // 取出一條命令進行處理
        cmd = socket_info[fd][CMD_QUEUE][0];
        socket_info[fd][CMD_QUEUE] = socket_info[fd][CMD_QUEUE][1..<1];

        if (sscanf(cmd, "%s %s", word, arg) != 2)
        {
                word = cmd;
                arg = 0;
        }

        switch (word)
        {
        case "getfile":
                cmd_getfile(fd, arg);
                break;
                                
        case "get":
                cmd_get(fd, arg);
                break;

        case "close":
                cmd_close(fd, arg);
                break;
        }
}

// 讀取玩家自造數據
protected void cmd_getfile(int fd, string arg)
{
        string id;
        string mudn;

        if (stringp(arg) && sscanf(arg, "%s from %s", id, mudn) == 2)
        {
                sys_info(sprintf("站點 %s正在讀取驗証信息，準備漫遊玩家(%s)數據。", mudn, id));
                socket_info[fd][SUB_SITES] = mudn;
        }

        send_cruise_file(id, fd);
        return;
}

// 讀取某一個文件
protected void cmd_get(int fd, string arg)
{
        string ban;
        int last;

        // 查看文件
        if (! arg || arg[0] != '/')
        {
                send_error_msg(fd, sprintf("no such file(%O).\n", arg));
                return;
        }

        last = strlen(arg) - 2;
        
        // 發送版本記錄下的文件
        send_file(fd, arg, arg);
}

// 關閉連接
protected void cmd_close(int fd, string arg)
{
        string address;

        address = socket_address(fd);
        if (stringp(address))
                sscanf(address, "%s %*d", address);
        else
                address = "unknow";

        sys_info(sprintf("站點 %s 和本站數據漫遊完畢。", address));

        send_result(fd, RESULT_FINISH "ok\n");
}

// 向對方發送一條結果信息
protected int send_result(int fd, string msg)
{
        string result;

        result = sprintf("%-" + (NORMAL_RESULT_LEN - 1) + "s.", msg);

        if (sizeof(socket_info[fd][PENDING_WRITE]))
        {
                // 已經有阻塞需要發送的數據了，這次發送的數
                // 據先阻塞
                socket_info[fd][PENDING_WRITE] += ({ result });
                return -1;
        }

        switch (socket_write(fd, result))
        {
        case EESUCCESS:
                // 發送成功了
                return 0;

        case EECALLBACK:
                // 需要等待
                // socket_info[fd][PENDING_WRITE] += ({ result });
                return -1;

        case EEWOULDBLOCK:
                // 發送數據阻塞
                socket_info[fd][PENDING_WRITE] += ({ result });
                call_out("in_write_callback", 2, fd);
                return -1;

        default:
                socket_close(fd);
        }
}

// 向對方發送一條錯誤信息
protected int send_error_msg(int fd, string msg)
{
        return send_result(fd, RESULT_ERR + msg);
}

// 向對方發送一個文件
protected void send_file(int fd, string file, string peer_name)
{
        int fs;

        // 直接發送
        if ((fs = file_size(file)) < 0)
        {
                send_error_msg(fd, sprintf("read file(%s) error.\n", file));
                return;
        }

        // 更新狀態，然後首先發送文件的長度
        socket_info[fd][FILE_NAME] = file;
        socket_info[fd][FILE_SIZE] = fs;
        socket_info[fd][FILE_POS] = 0;
        socket_info[fd][STATUS] = STATUS_SENDING;
        if (send_result(fd, sprintf(RESULT_FILE "%s %d\n", peer_name, fs)) == 0 &&
            previous_object() != this_object())
                // 成功發送了的應答，並且當前不是由in_write_callback
                // 調用進入，則繼續發送文件
                in_write_callback(fd);     
}

// 接收文件內容
protected int syn_receive_file(buffer buf)
{
        mixed *st;
        string file;
        int len;
        int sl;

        file = client_info[FILE_NAME];
        len =  client_info[FILE_SIZE] - client_info[FILE_POS];
        if (len > sizeof(buf))
                // 不需要將buf中的數據全部寫入
                len = sizeof(buf);

        write_buffer(file + APPENDFIX,
                     client_info[FILE_POS], buf[0..len - 1]);
        client_info[FILE_POS] += len;
        if (client_info[FILE_POS] < client_info[FILE_SIZE])
                // 文件還沒有接收完畢
                return len;

        // 成功獲取文件完畢
        log_file("cruise", sprintf("%s got file %s.\n",
                                    log_time(), client_info[FILE_NAME]));
        client_info[FILE_POS] = 0;
        client_info[FILE_NAME] = 0;
        client_info[FILE_SIZE] = 0;

        // 查看當前的狀態
        switch (client_info[STATUS])
        {
        case STATUS_SYN:
                // 將文件名字修改為正常的名字
                rm(file);
                rename(file + APPENDFIX, file);

                // 如果這個文件是一個C文件，那麼我必須刪除
                // 它的BIN 文件，因為我需要重新編譯它。
                sl = strlen(file) - 2;
                if (sl > 0 && file[sl] == '.' && file[sl + 1] == 'c')
                        rm(bin_path + file[0..sl] + "b");
                break;

        default:
                // 錯誤的狀態
        }

        // 返回使用的BUFFER的長度
        return len;
}

protected int connect_server()
{
        string sites;
        string addr;
        int port;
        int ret_val;
        mixed *cruise;

        cruise = cruise_queue[queue_pointer];

        CHANNEL_D->do_channel(this_object(), "sys", "漫遊系統嘗試向<" +
                              cruise[USER_SITE] + ">獲取人物資料。");
                                              
        // 創建版本通訊的SOCKET
        cfd = socket_create(STREAM_BINARY,
                            "syn_read_callback",
                            "syn_close_callback" );

        if (cfd < 0)
        {
                if (cruise[USER_ID])
                {
                        DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                        DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION); 
                }
                        
                log_file("cruise", sprintf("%s Failed to create socket.\n",
                                            log_time()));
                return 0;
        }
        // 目的為關閉該 cfd，系統監聽的cfd在這裡被改變了，所以監聽的cfd不會被關閉
        status = STATUS_CONNECT;
        remove_call_out("send_timeout");
        call_out("send_timeout", 180, cfd);
        
        // 初始化客戶端信息
        client_info = allocate(8);
        client_info[STATUS] = STATUS_CONNECTING;
        client_info[FILE_NAME] = 0;
        client_info[FILE_POS] = 0;
        client_info[FILE_SIZE] = 0;
        client_info[RESULT_BUFFER] = "";
        client_info[PENDING_WRITE] = ({ });

        sites = cruise[USER_SITE];
        port = __PORT__ + CRUISE_PORT;
        // 生成版本服務器的連接地址
        addr = sprintf("%s %d", sites, port);

        ret_val = socket_connect(cfd, addr,
                                 "syn_read_callback",
                                 "syn_write_callback");
        if (ret_val != EESUCCESS)
        {
                status = STATUS_INIT;
                
                if (cruise[USER_ID])
                {
                        DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                        DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
                }
                    
                log_file("cruise", sprintf("%s Failed to connect server.\n",
                                            log_time()));
                return 0;
        }

        log_file("cruise", sprintf("%s connecting to server %s.\n",
                                    log_time(), addr));
        return 1;
}

// 處理本地接收到的來自其他站點的數據
protected void syn_read_callback(int fd, buffer buf)
{
        string str;
        int len;
        int ver;
        string msg;

        if (fd != cfd || ! bufferp(buf)) return;

        DEBUG_LOG(sprintf(HIC "incoming: buf = %O(%d)\n" NOR, buf, sizeof(buf)));
        
        do
        {
                if (! client_info[FILE_NAME])
                {
                        // 沒有文件名字，接收的是普通應答信息
        
                        // 計算我應該從緩沖區中讀出的字節數目，因為
                        // 可能不能一次獲得普通的應答信息，因此我將
                        // 這些信息累計到RESULT_BUFFER中， 一直到讀
                        // 滿期望的字節為止。那麼我這次從緩沖區讀出
                        // 來的應該是多少個字節，就應該計算。其中保
                        // 存在FILE_POS中的是我已經讀出的字符。
                        len = NORMAL_RESULT_LEN - client_info[FILE_POS];
                        if (len > sizeof(buf))
                                // 這次沒有這麼多字節可以讓我讀
                                len = sizeof(buf);
                        client_info[FILE_POS] += len;
                        client_info[RESULT_BUFFER] += read_buffer(buf, 0, len);
                        // 取剩余的buffer
                        buf = buf[len..<1];
        
                        if (client_info[FILE_POS] >= NORMAL_RESULT_LEN)
                        {
                                // 讀到了一條通常的返回信息，重新設
                                // 置緩沖區。
                                str = client_info[RESULT_BUFFER];
                                client_info[RESULT_BUFFER] = "";
                                client_info[FILE_POS] = 0;
        
                                // 處理接收到的結果信息
                                syn_receive_result(str);
                        }
                }
        
                DEBUG_LOG(sprintf("buf = %O(%d) ... file_name = %O(%d)\n",
                                                          buf, sizeof(buf),
                                                          client_info[FILE_NAME],
                                                          client_info[FILE_POS]));
                if (bufferp(buf) && client_info[FILE_NAME])
                        // 接收文件
                        buf = buf[syn_receive_file(buf)..<1];

                // 如果buf不為空，則繼續處理
        } while (sizeof(buf) && client_info[STATUS] != STATUS_FINISHED);
}

// 漫遊時客戶端連接的寫回調函數
void syn_write_callback(int fd)
{
        if (fd != cfd)
        {
                log_file("cruise", sprintf("socket error: fd = %d vfd = %d\n", fd, cfd));
                return;
        }

        while (sizeof(client_info[PENDING_WRITE]))
        {
                // 有阻塞的消息，發送之
                if (send_client_pending_msg() != 0)
                        // 沒有成功的發送，等待下一次發送
                        return;
        }

        // 根據當前的狀態處理
        switch (client_info[STATUS])
        {
        case STATUS_CONNECTING:
                if (fetch_file_list)
                {
                        // 指定獲得某些文件
                        syn_fetch_file_from_server();
                        break;
                }     
                // 剛剛連接，發送取玩家自造數據的命令
                send_command(fd, sprintf("getfile %s from %s(%s)", cruise_queue[queue_pointer][USER_ID],
                                         LOCAL_MUD_NAME(), INTERMUD_MUD_NAME,
                                         __PORT__));
                client_info[STATUS] = STATUS_GET_ITEM;
                sys_info("版本精靈成功的和服務器建立了通訊。");                     
                break;
        default:
                return;                
        }
}
// 系統信息
protected void sys_info(string msg)
{
        CHANNEL_D->do_channel(this_object(), "sys", msg);
}

// 調試信息
protected void debug_info(string msg)
{
        CHANNEL_D->do_channel(this_object(), "debug", msg);
}

// 客戶端發送阻塞的消息

protected int send_client_pending_msg()
{
        string msg;

        msg = client_info[PENDING_WRITE][0];
        switch (socket_write(cfd, msg))
        {
        case EESUCCESS:
                // 發送成功了
                client_info[PENDING_WRITE] = client_info[PENDING_WRITE][1..<1];
                return 0;

        case EECALLBACK:
                // 需要等待
                client_info[PENDING_WRITE] = client_info[PENDING_WRITE][1..<1];
                return -1;

        case EEWOULDBLOCK:
                // 發送數據阻塞
                call_out("syn_write_callback", 2, cfd);
                return -1;

        default:
                // 發送失敗
                return -1;
        }
}

// 同步時客戶端連接的讀回調函數
// 由于服務器可能會返回兩種數據：1 普通應答信息  2 二進制文
// 件數據。因此接收函數依據狀態中的文件名字存在與否來鑒別這
// 兩種狀態：如果有文件名字，那麼就認為是接收文件中，如果沒
// 有，則是接收普通應答信息。普通應答信息一定是固定個字節，
// 以ASCII 方式存放。如果一次接收沒有滿足期望的字節，那麼長
// 度將保存在FILE_POS裡面。

protected void syn_receive_result(string str)
{
        string file;
        string msg;
        string ver;        
        int len;

        if ((len = strsrch(str, '\n')) == -1)
        {
                // 返回的信息不正確 - 必須包含'\n'
                log_file("cruise", sprintf("%s respond without '\\n' from server: %s.\n",
                                            log_time(), str));
                DEBUG_LOG(sprintf(HIR "error syntax str = %s\n" NOR, str));
                return;
        }
        if (! len) return;
        str = str[0..len - 1];

        DEBUG_LOG(sprintf("str = %s\n", str));

        if (sscanf(str, RESULT_ERR "%s", msg))
        {
                // 遇到了錯誤，先記錄進入日志
                log_file("cruise", sprintf("%s error respond: %s\n",
                                            log_time(), msg));
                DEBUG_LOG(str + "\n");
        }

        // 根據當前的狀態進行處理
        switch (client_info[STATUS])
        {
        case STATUS_GET_ITEM:
                if (sscanf(str, RESULT_CRUISE "%s", ver))
                {
                        // cruise_file = explode(ver, "|"); 
                        if (ver != "SEND_CRUISE_FILE_OK")    
                                cruise_file += ({ ver });                               
                        else
                                syn_get_id_data();                      
                }                
                                                
                // syn_get_id_data();
                // 沒有返回正常的玩家數據信息
                // log_file("cruise", sprintf("%s can not get cruise. server report: %s\n",
                //                            log_time(), str));

                // 怎麼辦？只有結束漫遊
                // syn_finish();
                break;
                
        case STATUS_SYN:
                // 接收文件的長度
                if (! sscanf(str, RESULT_FILE "%s %d", file, len))
                {
                        if (sscanf(str, RESULT_FINISH "%*s"))
                        {
                                log_file("cruise", sprintf("%s cruise synchronized.\n",
                                                            log_time()));
                                syn_finish();
                        }

                        break;
                }

                DEBUG_LOG(sprintf("file: %s len = %d\n", file, len));

                // 記錄的接收文件狀態和信息

                // 記錄傳送來的文件的信息
                client_info[FILE_NAME] = file;
                client_info[FILE_POS] = 0;
                client_info[FILE_SIZE] = len;

                // 如果有，刪除這個文件的臨時文件
                rm(file + APPENDFIX);

                sys_info(sprintf("getting(%s)...", file));
                break;

        default:
                // 不應該接收到信息
        }
}

// 漫遊數據結束
// 結束時可能成功的漫遊了，也可能沒有。
protected void syn_finish()
{
        mixed *cruise;

        seteuid(ROOT_UID);
        sys_info("漫遊精靈：漫遊玩家數據結束。");

        cruise = cruise_queue[queue_pointer];
                
        if (cruise[USER_ID])
        {        
                if (! DATABASE_D->query_db_status())
                        DATABASE_D->connect_to_database();   
                
                DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
        }

        if (cfd) { socket_close(cfd); cfd = 0; }
 
        cruise_file = ({ });
          
        client_info[STATUS] = STATUS_FINISHED;
        client_info[FILE_NAME] = 0;
        client_info[FILE_POS] = 0;
        client_info[FILE_SIZE] = 0;
        client_info[PENDING_WRITE] = ({ });
        client_info[RESULT_BUFFER] = "";
        remove_from_queue();
        status = STATUS_INIT;  // by Lonely
        fetch_file_list = 0;
}

// 從服務器上獲取一批文件
protected void syn_fetch_file_from_server()
{
        int i;

        client_info[STATUS] = STATUS_SYN;

        for (i = 0; i < sizeof(fetch_file_list); i++)
        {
                if (fetch_file_list[i][0] != '/')
                        fetch_file_list[i] = "/" + fetch_file_list[i];
                send_command(cfd, "get " + fetch_file_list[i]);
        }

        send_command(cfd, "close");
}

protected void send_cruise_file(string cruise_id, int fd)
{
        object ob;
        mapping summon, whistle;
        string *ks;
        string *fs;
        string msg;
        string file;
        int i;

        msg = "";
        fs = ({ });
                
        ob = UPDATE_D->global_find_player(cruise_id);
        summon=query("can_summon", ob);
        whistle=query("can_whistle", ob);
        UPDATE_D->global_destruct_player(ob);
        
        if (objectp(ob = find_player(cruise_id)))
        {
                tell_object(HIY "由于你的人物數據正在漫遊，系統強行使你離線。\n" NOR);             
                ob->save();
                destruct(ob);
        }

        if (mapp(summon))
        {
                ks = keys(summon);
                for (i = 0; i < sizeof(ks); i++)
                {
                        file = summon[ks[i]] + ".c";
                        if (file_size(file) > 0)
                        {
                                if (ob = find_object(file))
                                        destruct(ob);

                                send_result(fd, sprintf(RESULT_CRUISE "%s\n", file));   
                                // fs += ({ file });
                        }
                }
        }        
        if (mapp(whistle))
        {
                ks = keys(whistle);
                for (i = 0; i < sizeof(ks); i++)
                {
                        file = whistle[ks[i]] + ".c";
                        if (file_size(file) > 0)
                        {
                                if (ob = find_object(file))
                                        destruct(ob);

                                send_result(fd, sprintf(RESULT_CRUISE "%s\n", file));   
                                // fs += ({ file });
                        }
                }
        }                        

        file = sprintf(DATA_DIR "beast/%s", cruise_id + "-beast" + __SAVE_EXTENSION__);
        if (file_size(file) > 0)
                send_result(fd, sprintf(RESULT_CRUISE "%s\n", file)); 
                // fs += ({ file });
        /*
        if (sizeof(fs) >= 2) 
                msg += implode(fs[0..sizeof(fs) - 1], "|"); 
        else 
        if (sizeof(fs) == 1)
                msg += fs[0]; 

        if (! msg)
                send_result(fd, RESULT_NO_CRUISE "no file need to cruise\n");
        else
                send_result(fd, sprintf(RESULT_CRUISE "%s\n", msg));       
        */     

        send_result(fd, sprintf(RESULT_CRUISE "%s\n", "SEND_CRUISE_FILE_OK"));  
        return;
}

int syn_get_id_data()
{
        string file;
        int i;
        mixed *cruise;

        cruise = cruise_queue[queue_pointer];
        
        if (TX_SAVE && CRUISE_USER_DATA)
        {
                file = sprintf(DATA_DIR "login/%c/%s", cruise[USER_ID][0], cruise[USER_ID] + __SAVE_EXTENSION__);
                assure_file(file);     
                fetch_file_list = ({ file });  
                file = sprintf(DATA_DIR "user/%c/%s", cruise[USER_ID][0], cruise[USER_ID] + __SAVE_EXTENSION__);
                assure_file(file);     
                fetch_file_list += ({ file }); 
        } else
                fetch_file_list = ({ });              
                
        if (arrayp(cruise_file) && sizeof(cruise_file) > 0)
        {
                for (i = 0; i < sizeof(cruise_file); i++)
                {
                        file = cruise_file[i];
                        if (file[0] != '/')
                                file = "/" + file;
                        assure_file(file);
                        fetch_file_list += ({ file });   
                }
        }        

        sys_info(sprintf("連接站點 %s 成功，開始漫遊人物 %s 的數據。", cruise[USER_SITE], cruise[USER_ID]));
        syn_fetch_file_from_server();
        return 1;
}

int fetch_file(string file, string sites)
{
        int next_next;
        
        next_next = (next_cruise + 1) % MAX_AUTHENTICATING_USER;
        if (next_next == queue_pointer) 
        {
                // 同時允許漫遊的玩家數量超過上限
                write(HIY "漫遊隊列已滿，請稍後在再進行數據漫遊。\n" NOR);
                return 0;
        }

        fetch_file_list = ({ file }); 
                
        cruise_queue[next_cruise] = allocate(2);
        cruise_queue[next_cruise][USER_ID] = 0;
        cruise_queue[next_cruise][USER_SITE] = sites;
        next_cruise = next_next;

        write("正在連接服務器獲取文件。\n");        
        set_heart_beat(1);
        return 1;
}


protected void send_timeout(int fd)
{
        socket_close(fd);
        syn_close_callback(fd);
}

// 漫遊時客戶端連接斷開的回調函數
protected void syn_close_callback(int fd)
{   
        remove_call_out("send_timeout");
        // 防止還在漫遊中被關閉
        if (queue_pointer == next_cruise &&
            status != STATUS_INIT)
                return;
                
        if (fd != cfd) return;
        
        cfd = 0;
        remove_from_queue();
        status = STATUS_INIT;
}

int clear_syn_info()
{
        int result;
        int fd;

        if (previous_object() && ! is_root(previous_object()))
                return 0;

        // 服務器端：清除套接字的連接信息

        if (sizeof(socket_info) > 0)
        {
                foreach (fd in keys(socket_info))
                        if (intp(fd)) socket_close(fd);

                socket_info = ([ ]);
                return 1;
        }

        return 0;


        // 客戶端：清除漫遊的SOCKET和信息
        if (cfd)
        {
                log_file("cruise", sprintf("%s 暫停了漫遊數據的操作。\n", log_time()));
                syn_finish();
                return 1;
        }

        return 0;
}

mixed query_socket_info()
{
        if (previous_object() && ! is_root(previous_object()))
                return 0;
        
        return socket_info;
}

mixed query_client_info() { return client_info; }
int query_cfd() { return cfd; }

#endif

