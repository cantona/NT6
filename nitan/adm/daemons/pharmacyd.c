// Pharmacy daemon(preparing and dispensing drugs)
// By landis@MYTH
// 2002.05.09
// last update 2002.08.23

//  此物件負責處理所有藥物相關的事務，包括：
//
//  1.根據藥性獲得相應的藥材。
//  2.核對處方將藥材轉化為藥物。
//  3.處理及保存新的處方數據。
//  4.將藥材或藥物的名稱與編號互相轉換。

/***********************************************************
保存藥物編號及對應名稱的映射如下：
mapping data = ([
        "herb" : ([
                0 : "甘草",
                1 : "沉香",
                ]),
        "medicine" : ([
                0 : "玄黃紫清丹",
                1 : "甘草潤肺散",
                ]),
        ]);

保存處方的映射如下：
mapping prescription = ([
        1, 2, 3 : 1,
        2, 3, 4 : 2,
        ]);

保存藥材相關信息的映射如下：
mapping relation = ([
        0 : ([
                "eng"  : ({"gan cao", "cao"}),
                "unit" : "棵",
                "desc" : "一棵紫紅色的小草，看起來煞是可愛。",
                ]),
        ]);
***********************************************************/

#include <ansi.h>

inherit F_DBASE;
inherit F_SAVE;

mapping data;
mapping prescription;

mapping relation;

void initialize();
int register_all_medicine();

void create()
{
        seteuid(ROOT_UID);
        initialize(); // 初始化，包括載入數據，刷新映射等

        set("channel_id", "製藥精靈");
        CHANNEL_D->do_channel( this_object(), "sys", "製藥系統已經啟動。");
}

// 初始化，包括載入數據，刷新映射等
void initialize()
{
        restore();        

        if (! mapp(data))
        {
                data = allocate_mapping(2);
                data["herb"] = allocate_mapping(50);
                data["medicine"] = allocate_mapping(50);
        }

        if (! sizeof(data["medicine"]))
                register_all_medicine();

        if (! mapp(prescription))
                prescription = allocate_mapping(50);

        if (! mapp(relation))
                relation = allocate_mapping(50);
}

void remove() { save(); }

string query_save_file() { return DATA_DIR "pharmacyd"; }

/*********************************************************************
                       以下為增加、刪除數據的接口
*********************************************************************/

// 註冊藥材id及對應中文名稱
int register_herb(int id, string name)
{
        object ob;
        string file;

/*
        ob = previous_object();

        if (! is_root(ob) || geteuid(ob) != "Clone")
                error("Pharmacyd:Herb Registration conflict, Access denied.\n");
*/

        if (! mapp(data))
                data = ([ "herb" : ([ id : name ]) ]);
        else if (! mapp(data["herb"]))
                data["herb"] = ([ id : name ]);
        else
                data["herb"][id] = name;

        return 1;
}

// 設置藥材的基本信息
int set_relation(int id, mapping rt)
{
        mapping map;

        relation[id] = allocate_mapping(3);

        map = relation[id];

        if (! mapp(map) || ! sizeof(map))
                map = ([ "eng" : rt["eng"] ]);
        else
                map["eng"]  = rt["eng"];

        map["unit"] = rt["unit"];
        map["desc"] = rt["desc"];

        relation[id] = map;

        return 1;
}

// 註冊藥物id及對應名稱(由藥物物件取得)
int register_medicine(int id)
{
        object obj;
        string file, name;

//      if (previous_object() != this_object())
//              return 0;

        file = id < 10 ? "0%d" : "%d";
        file = sprintf(file, id);
        file = MEDICINE_DIR(file);

        call_other(file, "???");
        obj = find_object(file);
        name = filter_color(obj->query("name"));

        if (geteuid(obj) != "Clone")
                error("Pharmacyd:Medicine Registration conflict, Access denied.\n");

        if (! mapp(data))
                data = ([ "medicine" : ([ id : name ]) ]);
        else if (! mapp(data["medicine"]))
                data["medicine"] = ([ id : name ]);
        else
                data["medicine"][id] = name;

        return 1;
}

// 註冊所有藥物
int register_all_medicine()
{
        int i, id;
        string *dir;

        dir = get_dir(MEDICINE_DIR(""));

        if (! dir || ! sizeof(dir)) return 0;
        for (i = 0; i < sizeof(dir); i++)
        {
                if (! sscanf(dir[i], "%d.c", id))
                        continue;

                register_medicine(id);
        }

        return 1;
}

// 註銷某一藥材或藥物
int unregister(string type, int id)
{

//      if (previous_object() && geteuid(previous_object()) != ROOT_UID)
//	        return 0;

        if (type != "herb" && type != "medicine")
                return notify_fail("Pharmacyd:Wrong type, Access denied.\n");

        if (mapp(data) && mapp(data[type]))
                map_delete(data[type], id);

        return 1;
}

// 增加處方數據
int add_prescription(int *herbs, string medicine)
{
        if (! mapp(prescription))
                prescription = ([ herbs : medicine ]);
        else
                prescription[herbs] = medicine;

        return 1;
}

// 刪除處方數據
int delete_prescription(int *herbs)
{
        if (! mapp(prescription) || undefinedp(prescription[herbs]))
                return 0;

        map_delete(prescription, herbs);
        return 1;
}

/*********************************************************************
                       以下為供外部調用的查詢接口
*********************************************************************/

// 返回該藥材的基本信息，在藥材初始化時調用
mapping query_relation(int id) { return relation[id]; }

// 通過藥材或藥物名查詢編號
int check_id(string name)
{
        int loc;
        int *key;
        string *value;

        key   = keys(data["herb"]);
        value = values(data["herb"]);
        loc   = member_array(name, value);

        if (loc == -1)
        {
                key   = keys(data["medicine"]);
                value = values(data["medicine"]);
                loc   = member_array(value, name);
        }

        return key[loc];
}

// 通過類型(藥材或藥物)及id查詢中文名稱
string check_name(string type, int id)
{
        mapping fname;

        if (type != "herb" && type != "medicine")
                error("Pharmacyd:Wrong Check Type,Access denied.\n");

        fname = data[type];
        return fname[id];
}

// 查詢該類型(藥材或藥物)某一id是否已註冊
int already_registerd(string type, int id)
{
        if (type != "herb" && type != "medicine")
                return notify_fail("查詢類型錯誤！\n");

        return undefinedp(data[type][id]) == 0;
}

/*********************************************************************
                       以下為調用查看數據列表的接口
*********************************************************************/

// 返回藥材列表
string list_herb()
{
        int i;
        string *key;
        string line;
        mapping herbs;

        herbs = data["herb"];

        if (! mapp(herbs) || ! sizeof(herbs))
                return "目前尚未完成藥材數據構造！\n";

        line  = WHT"\n目前已收集的藥材數據如下：\n\n"NOR;
        key   = keys(herbs);
        key   = sort_array(key, 1);

        for(i = 0; i < sizeof(key); i++)
        {
                line += sprintf(CYN"%2d", key[i]);
                line += "　　";
                line += sprintf(WHT"%-10s"NOR, herbs[key[i]]);

                line += (i<4 || i%4) ? "　" : "\n";
        }

        return line;
}

// 返回藥物列表
string list_medicine()
{
        int i;
        string *key;
        string line;
        mapping medicines;

        medicines = data["medicine"];

        if (! mapp(medicines) || ! sizeof(medicines))
                return "目前尚未完成藥物數據構造！\n";

        line  = WHT"\n目前已收集的藥物數據如下：\n\n"NOR;
        key   = keys(medicines);
        key   = sort_array(key, 1);

        for(i = 0; i < sizeof(key); i++)
        {
                line += sprintf(CYN"%2d", key[i]);
                line += "　　";
                line += sprintf(WHT"%-10s"NOR, medicines[key[i]]);

                line += (i<4 || i%4) ? "　" : "\n";
        }

        return line;
}

// 返回處方列表
string list_prescription()
{
        int i;
        string line;
        int *key, *value;

        if (! mapp(prescription) || ! sizeof(prescription))
                return "目前尚無藥方數據可供查詢！\n";

        line  = "";
        key   = keys(prescription);
        value = values(prescription);

        for (i=0; i<sizeof(key); i++)
        {
                foreach(int id in key[i])
                        line += sprintf(HIW"%-8s", check_name("herb", id));

                line += sprintf(HIC"：%-20s", check_name("medicine", value[i]));
                line += "\n" NOR;
        }

        return line;
}

/*********************************************************************
                       以下為按要求生成藥材的接口

                其中，每件藥材的屬性都是唯一的，形式如下：

                味性(Taste)     ：苦、鹹、酸、甘、辛
                藥性(Officinal) ：寒、涼、平、温、熱
                毒性(toXicity)  ：有、無

                所以，以 {x,y,z} 形式的數組對應唯一一種藥
                材，總數即為 5x5x2 = 50 種。

*********************************************************************/

// 根據屬性計算編號，創建藥材
object build_herb(int *prop)
{
        int num;
        int tp, op, xp;
        object ob;
        string name;

        tp = prop[0];
        op = prop[1];
        xp = prop[2];

        if (tp < 0 || op < 0 || xp < 0 ||
            tp > 4 || op > 4 || xp > 1 ||
            sizeof(prop) > 3)
                error("Pharmacyd:Wrong Herb Prop.\n");

        // 算法為 10*x + 2*y + z 即可得到該藥材的唯一編號。
        num  = xp;
        num += op * 2;
        num += tp * 10;

        name = data["herb"][num];

        if (! stringp(name))
                error("Pharmacyd:Fail in Loading Herb object.\n");

        ob = new(HERB_OB);               // 建立原型
        ob->initialize(num, name, prop); // 初始化

        return ob;
}

// 根據編號創建藥材
object clone_herb(int id)
{
        object ob;
        string name;
        int *prop;
        int tp, op, xp;

        name = data["herb"][id];

        if (! stringp(name))
                error("Pharmacyd:Fail in Loading Herb object.\n");

        tp = id / 10;
        op = (id%10) / 2;
        xp = id - (tp * 10) - (op * 2);

        prop = ({ tp, op , xp });

        ob = new(HERB_OB);              // 建立原型
        ob->initialize(id, name, prop); // 初始化

        return ob;
}

/*********************************************************************
                       以下為按處方生成藥物的接口

                每次製藥的成功率大約為50%，
                能否製藥的能力限制暫時未予以考慮。
                若製藥失敗，有一定機會得到 催化劑 鍊金水 黃金
                中的一種，否則將得到廢料。

*********************************************************************/

// 核對處方將藥材轉化為藥物
object build_medicine(object *herbs)
{
        object obj;
        int *id_list;
        int i, id, flag;
        string *recipe;
        string bname, name;

        id_list = allocate(sizeof(herbs));

        for (i = 0; i < sizeof(herbs); i++)
        {
                if (herbs[i]->is_activator()) { flag = 1; continue; }
                bname = base_name(herbs[i]);
                if (bname != HERB_OB) continue;
                id_list[i] = id;
        }

        foreach (recipe in keys(prescription))
        {
                if (recipe - id_list == ({ }) &&
                    flag ? 1 : random(10) > 5)
                {
                        name = sprintf("%d", prescription[recipe]);
                        name = MEDICINE_DIR(name);

                        for (i = 0; i < sizeof(herbs); i++)
                                destruct(herbs[i]);

                        call_other(name, "???");
                        if (! objectp(find_object(name)))
                                error("Pharmacyd:Fail in Loading Medicine object.\n");

                        return new(name);;
                } else
                {
                        switch (random(100))
                        {
                                case 84: obj = new(GOLD_OB); break;
                                case 11: obj = new(MEDICINE_DIR("activator")); break;
                                case 30: obj = new(MEDICINE_DIR("elixir")); break;
                                default: obj = new(MEDICINE_DIR("waste"));
                        }

                        return obj;
                }
        }
}
