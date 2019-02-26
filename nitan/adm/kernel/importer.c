// importer.c
// 用户檔案導入器

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define SAVE_DIR        "/data.3k/"
#define SUFFIX_NAME     "fr"
#define SUFFIX_SIZE     26

// 日誌等級分為 3 級，如何界定一段消息應該記錄在
// 哪一級的日誌中？

// LV 1: 無法複製文件、載入用户等錯誤信息
// LV 2: 對用户有損的刪除一類的操作信息
// LV 3: 複製或者修改這樣的無損操作信息

#define LOG_LEVEL       3
#define LOG(lv, msg)    log_file(sprintf("transfer/LV%d", lv), msg);

// 奇怪的是 'nosave' 關鍵字不許用？
static string suffix = "abcdefghijklmnopqrstuvwxyz";
static string save_dir = SAVE_DIR;

mapping save_dbase;

int     transfer_user(string arg);
void    global_destruct_player(object ob, int raw);
void    transfer_autoload(object user, string card_file);
string *get_user_list(string dir);
object  global_find_player(string user);
mapping assure_user_file(string user, int flag);

void create()
{
        // 載入原來的 dbased 數據
        if (clonep() || ! this_player(1))
        {
                destruct(this_object());
                return;
        }

        seteuid(getuid());
        restore();

        set_name("用户檔案導入器", ({ "data importer", "importer", }));
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "台");
                set("long", "這是一台用户檔案導入器，請輸入 help "
                            "importer 查看詳細使用説明。\n");
        }
        setup();

        move(this_player(1));
}

void setup()
{
        ::setup();
}

mixed query_object_data(string index) { return save_dbase[index]; }
mapping query_save_dbase() { return save_dbase; }

string query_save_file() { return save_dir + "dbased"; }

void init()
{
        add_action("do_help", "help");
        add_action("do_batch", "batch");
        add_action("do_merge", "merge");
}

int do_help(string arg)
{
        switch (arg)
        {
        case "importer":
                write(@HELP
在這裏你可以使用以下這些和用户檔案導入器相關的命令：
    batch        批量導入用户數據。
HELP );
                break;

        case "batch":
                write(@HELP_BATCH
指令格式 : batch

批量導入用户數據。

相關指令：import, merge
HELP_BATCH );
                break;

        case "merge":
                write(@HELP_BATCH
指令格式 : merge dbase

將另外站點的數據庫併入目前站點的數據庫。

相關指令：batch
HELP_BATCH );
                break;

        default:
                return notify_fail("你要查看什麼幫助？\n");
        }

        return 1;
}

// 獲得一個不重複的用户名
mapping assure_user_file(string user, int flag)
{
#if 0
        int times;
        mapping file = ([ ]);

        for (times = 0; times < SUFFIX_SIZE; times++)
        {
                file["login_to"] = sprintf("%slogin/%c/%s%c.o", 
                                           DATA_DIR, user[0], 
                                           user, suffix[times]);

                file["user_to"] = sprintf("%suser/%c/%s%c.o", 
                                          DATA_DIR, user[0], 
                                          user, suffix[times]);

                file["uid"] = sprintf("%s%c", user, suffix[times]);

                if (file_size(file["login_to"]) < 0 ||
                    file_size(file["user_to"]) < 0)
                        return file;
        }
#else
        mapping file = ([ ]);

        file["login_to"] = sprintf("%slogin/%c/%s%s.o", 
                                   DATA_DIR, user[0], 
                                   user, "_" + SUFFIX_NAME);

        file["user_to"] = sprintf("%suser/%c/%s%s.o", 
                                  DATA_DIR, user[0], 
                                  user, "_" + SUFFIX_NAME);

        file["uid"] = sprintf("%s%s", user, "_" + SUFFIX_NAME);

        if (flag ||
            file_size(file["login_to"]) < 0 ||
            file_size(file["user_to"]) < 0)
                return file;

#endif
        return 0;
}

// 獲得指定目錄下所有的用户列表
string *get_user_list(string dir)
{
        string *sub_dir_list;
        string  sub_dir;
        string *user_list;
        string *temp_list;

        dir += "login/";

        sub_dir_list = get_dir(dir);
        sub_dir_list = filter_array(sub_dir_list, 
                                    (: file_size($(dir) + $1) == -2 :));
        sub_dir_list = map_array(sub_dir_list, (: $(dir) + $1 + "/" :));

        user_list = ({ });

        foreach (sub_dir in sub_dir_list)
        {
                temp_list = get_dir(sub_dir);

                if (! arrayp(temp_list) || ! sizeof(temp_list))
                        continue;

                reset_eval_cost();

                temp_list = filter_array(temp_list, (: sscanf($1, "%*s.bak") == 0 :));
                temp_list = map_array(temp_list, (: $1[0..<3] :));
                user_list += temp_list;
        }
        return user_list;
}

// 尋找或調入某一個玩家，本來可以使用 UPDATE_D 中的同名函數，
// 但因為這裏直接析構了 login_ob，無法對 login_ob  做改名操
// 作。所以需要用到這個函數。

// 如果程序處理中需要更新那些不在線的玩家，則可以使用該函數
// 將這個玩家調入並且進行修改，請注意：修改完畢以後程序必須
// 保存玩家，並且使用 global_destruct_player 將玩家析構，如
// 果沒有調用這個函數，則賦予玩家的定時器會自動析構玩家。
object global_find_player(string user)
{
        object ob;
        object login_ob;

        ob = find_player(user);
        if (! ob)
        {
                login_ob = new(LOGIN_OB);
                login_ob->set("id", user);
                ob = LOGIN_D->make_body(login_ob);
                if (! ob)
                {
                        catch(destruct(login_ob));
                        return 0;
                }

                evaluate(bind((: seteuid(getuid()) :), ob));

                if (! ob->restore())
                {
                        catch(destruct(login_ob));
                        catch(destruct(ob));
                        return 0;
                }

                ob->set_temp("temp_loaded", 1);
                ob->set_temp("link_ob", login_ob);

                ob->start_call_out(bind((: call_other, __FILE__, 
                                   "global_destruct_player", ob, 0 :),
                                   ob), 0);

                login_ob->restore();
                login_ob->set_temp("body_ob", ob);
        }

        return ob;
}

// 析構一個被 UPDATE_D 調入的玩家
void global_destruct_player(object ob, int raw)
{
        object login_ob;

        if (objectp(ob) && ob->query_temp("temp_loaded"))
        {
                // 增加對 login_ob 的析構
                if (objectp(login_ob = ob->query_temp("link_ob")))
                {
                        if (raw) login_ob->save();
                        destruct(login_ob);
                }
                
                if (raw) ob->save();
                destruct(ob);
        }
}

// 有哪些東西不可以繼續允許 autoload 載入？

// 玩家自造的物品，考慮到玩家的 ID 可能改變了，
// 如果繼續載入勢必影響其他的玩家，所以必須刪
// 除 autoload。 現在看來，似乎只有這一種，考
// 慮到這一種並不需要把文件載入就可以查出，所
// 以這裏可以簡單的通過 sscanf & filter_array
// 來處理用户的 autoload 列表， 過濾掉 /data/
// 目錄下的文件。
void transfer_autoload(object user, string card_file)
{
        string *autoload;

        autoload = user->query_autoload_info();

        if (! arrayp(autoload) || ! sizeof(autoload))
                return;

        autoload = filter_array(autoload, 
                                (: (! sscanf($1, "/data/%*s")) :));
                                
        if (stringp(card_file))
                autoload += ({ card_file });

        user->set_autoload_info(autoload);
}

int do_merge(string arg)
{
        mapping m1, m2;
        string  mk;
        string  key, new_key, id, iname;
        object  ob;
        int     ok;

        if (arg != "dbase")
                return notify_fail("你要併入什麼？\n");

        foreach (key in keys(save_dbase))
        {
                reset_eval_cost();

                if (sscanf(key, DATA_DIR "item/ring/%s", id))
                {
                        // Ring information
                        new_key = key + "_" + SUFFIX_NAME;
                } else
                if (sscanf(key, DATA_DIR "item/%*s/%s-%s", id, iname) == 3)
                {
                        // Item information
                        new_key = sprintf(DATA_DIR "item/%c/%s-%s",
                                          id[0], id + "_" + SUFFIX_NAME, iname);
                } else
                {
                        write("Ignore key - " + key + "!\n");
                        continue;
                }

                if (mapp(save_dbase[key]) && mapp(m1 = save_dbase[key]["owner"]))
                {
                    /* Convert data */
                    m2 = allocate_mapping(sizeof(m1));
                    foreach (mk in keys(m1))
                    {
                        m2[mk + "_" + SUFFIX_NAME] = m1[mk];
                    }
                    save_dbase[key]["owner"] = m2;
                }

                ok = DBASE_D->set_object_data(new_key, save_dbase[key]);
                if (! ok)
                {
                        write(HIR "Failed to set object information: " + new_key + "\n" NOR);
                        continue;
                }

                if (objectp(ob = find_object(new_key)))
                        ob->restore();
        }

        return 1;        
}

int do_batch()
{
        int i;
        string *user_list;
        string user;

        user_list = get_user_list(save_dir);

        write(WHT "開始遷移用户數據...\n\n" NOR);
        
        i = 0;
        foreach (user in user_list)
        {
                /* 開始轉換的日誌
                for (i = 1; i < LOG_LEVEL + 1; i++)
                        LOG(i, "Start transfering (" + user + ")'s data...\n");
                 */

                reset_eval_cost();

                if (transfer_user(user))
                {
                        i++;
                        write(sprintf("%-15s: Succeed\n", user));
                }
                else write(sprintf("%-15s: " WHT "Failed" NOR "\n", user));
        }
        
        write(WHT "\n遷移用户數據完成，共 " + sizeof(user_list) + 
              " 名用户，成功遷移 " + i + " 名用户。\n" NOR);
        return 1;
}

// 這兩個定義是為了簡化代碼
#define user_file(x)    sprintf("%suser/%c/%s.o", save_dir, x[0], x)
#define login_file(x)   sprintf("%slogin/%c/%s.o", save_dir, x[0], x)

// 轉換指定的用户
int transfer_user(string arg)
{
        object  user;
        object  link;
        object  card_ob;

        string  login_from;
        string  user_from;
        string  uid;
        string  card_file;
        string  couple_id;
        string  ring_file;

        string *item_list;
        string  item_name;
        string  item_file;
        string  file_content;

        mapping couple_file;
        mapping file;

        mixed   item_data;

        int     is_ok;

        // 找到舊的用户文件

        login_from = login_file(arg);
        user_from = user_file(arg);

        if (file_size(login_from) <= 0 || file_size(user_from) <= 0)
        {
                LOG(1, "File not found: (" + login_from + " & " + 
                        user_from + ").\n");
                return 0;
        }

        // 複製用户文件到 DATA_DIR

        file = assure_user_file(arg, 0);
        if (! file)
        {
                LOG(1, "User conflict: (" + login_from + " & " + 
                        user_from + ").\n");
                return 0;
        }

        if (! cp(login_from, file["login_to"]) || ! cp(user_from, file["user_to"]))
        {
                LOG(1, "Copy file to: (" + file["login_to"] + " | " + 
                       file["user_to"] + ") failed.\n");
                return 0;
        }

        uid = file["uid"];

        if (! objectp(user = global_find_player(uid)))
        {
                LOG(1, "Load user: (" + uid + ") failed.\n");
                return 0;
        }

        if (uid != arg)
        {
                // 修改 LOGIN_OB 和 USER_OB 的 ID
                if (objectp(link = user->query_temp("link_ob")))
                        link->set("id", uid);
        
                user->set("id", uid);
                LOG(2, "User ID (" + arg + ") changed into: (" + 
                        uid + ").\n");
        }

        // 添加姓名對應，中文姓名的雷同就算了吧。
        NAME_D->map_name(user->name(), uid);

        // 轉換房屋為建房卡

        // 注意玩家手裏的鑰匙要收走，但是考慮到所有的
        // autoload 物品， 除了一些特殊情況外都要清除，
        // 所以這裏暫不考慮。

        switch (user->query("private_room/type"))
        {
        case "盤龍居" : card_file = "/d/room/obj/ultracard"; break;
        case "彩虹居" : card_file = "/d/room/obj/super"; break;
        case "獨樂居" : card_file = "/d/room/obj/card"; break;
        default : card_file = 0;
        }

        if (stringp(card_file))
        {
                user->delete("private_room");

                LOG(2, "Deleted (" + arg + ")'s private room.\n");
                LOG(3, "User (" + arg + ") get a free card.\n");
        }

        // 刪除結義、同盟關係
        if (user->query("brothers"))
        {
                user->delete("brothers");
                LOG(2, "Deleted (" + arg + ")'s brother relation.\n");
        }

        if (user->query("league"))
        {
                user->delete("league");
                LOG(2, "Deleted (" + arg + ")'s league relation.\n");
        }

        // 刪除幫派
        user->delete("party");

        // ...on 08/01 21:35.

        // 確認婚姻關係，考慮到配偶的 ID 有可能變化，
        // 所以這裏要取得一個配偶唯一可能的 ID， 確
        // 保此用户的婚姻關係不出現問題，但問題在於，
        // 倘若在尋找這個配偶唯一可能的 ID 時，該配
        // 偶的文件已經轉移到了 /data/ 下呢？就會弄
        // 糊塗了，因此，對於已經轉移過的，要修改源
        // 目錄內的文件名。
        couple_id = user->query("couple/id");
        
        if (stringp(couple_id))
        {
                // 改變配偶名字
                couple_file = assure_user_file(couple_id, 1);
                couple_id = couple_file["uid"];

                user->set("couple/id", couple_id);

                LOG(3, "User (" + arg + ")'s couple/id set to " + 
                       couple_id + ".\n");
                
                // 嗯，要自己保管好自己的結婚戒指
                if (user->query("can_summon/wedding ring"))
                {
                        ring_file = sprintf("%sitem/ring/%s.c", DATA_DIR, uid);

                        cp(sprintf("%sitem/ring/%s.c", save_dir, arg),
                           ring_file);

                        user->set("can_summon/wedding ring", 
                                  sprintf("%sitem/ring/%s.c", DATA_DIR, uid));

                        LOG(3, "User (" + arg + ")'s wedding ring copied to " + 
                               ring_file + ".\n");
                }

                // 從原來的數據中獲得戒指的存盤信
                // 息，導入到 DBASE_D 中。
                ring_file = sprintf("%sitem/ring/%s", DATA_DIR, arg);
                item_data = query_object_data(ring_file);

                if (item_data)
                {
                        item_data["user"] = sprintf("%s(%s)", user->name(), uid);
                        is_ok = DBASE_D->set_object_data(sprintf("%sitem/ring/%s", 
                                                         DATA_DIR, uid), item_data);

                        LOG((is_ok ? 3 : 1), "Wedding ring data of (" + arg + 
                                             ") port to DBASE_D " + 
                                             (is_ok ? "succeed" : "failed") + ".\n");
                }
        }

        // 導入自造物品

        // 獲得原來的自造物品列表
        item_list = get_dir(sprintf("%sitem/%c/%s-*.c", save_dir, arg[0], arg));

        if (arrayp(item_list) && sizeof(item_list))
        {
                foreach (item_name in item_list)
                {
                        // 要去掉後面的 .c 字樣
                        item_file = sprintf("%sitem/%c/%s", DATA_DIR, arg[0], item_name[0..<3]);
                        item_data = query_object_data(item_file);

                        // 獲得物品的具體名稱
                        sscanf(item_name, arg + "-%s.c", item_name);
                        // 生成新的物品文件名
                        item_file = sprintf("%sitem/%c/%s-%s.c", DATA_DIR, uid[0], uid,
                                            item_name);
                        // 複製文件
                        is_ok = cp(sprintf("%sitem/%c/%s-%s.c", save_dir, arg[0], arg, item_name), 
                                   item_file);

                        if (! is_ok)
                        {
                                LOG(1, "Failed copy Item " + item_name + " of (" + arg + 
                                       ").\n");
                        } else
                        {
                                // 將文件中全部的原來的用户 ID
                                // 字樣全部替換為新的
                                if (arg != uid)
                                {
                                        file_content = read_file(item_file);
                                        file_content = replace_string(file_content, arg, uid);
        
                                        write_file(item_file, file_content, 1);
                                }
        
                                if (item_data)
                                {
                                        // 修改 "user" 屬性以適應新的 ID
                                        item_data["user"] = sprintf("%s(%s)", user->name(), uid);
        
                                        // 將原來的物品存盤信息導入 DBASE_D
                                        is_ok = DBASE_D->set_object_data(item_file, item_data);
                                }
        
                                // 更新用户身上的物品列表
                                user->set("can_summon/" + item_name, item_file);

                                LOG(3, "Item " + item_name + " of (" + arg + ") successfully "
                                       "tranfered.\n");
                        }
                }
        }
        // 轉換用户的 autoload 信息，去掉無法繼續
        // 使用的，如果獲得了卡片，則增加卡片的載
        // 入信息
        transfer_autoload(user, card_file);

        // raw : 1，給 user 存一下盤
        global_destruct_player(user, 1);

        // 修改文件名，表示此用户已經轉換
        rename(login_file(arg), login_file(arg) + ".bak");
        rename(user_file(arg), user_file(arg) + ".bak");

        LOG(3, "User (" + arg + ") successfully tranfered.\n");
        return 1;
}
