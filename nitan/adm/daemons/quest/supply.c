// 玩家任務守護進程：supply.c

#include <ansi.h>

// 供應的物品：由于接受的時候NPC只負責核對中文名字（這是由于
// MUD中的代碼一致性不好的緣故），所以每件提供的物品務必要考
// 慮清楚，不要和MUD中的其他物品重名。
string *supply_objs = ({
        "/clone/weapon/changjian",
        "/clone/weapon/jili",
        "/clone/weapon/tiegun",
        "/clone/weapon/zhubang",
        "/clone/weapon/zhujian",
        "/clone/weapon/changbian",
        "/clone/weapon/dagger",
        "/clone/weapon/duanjian",
        "/clone/weapon/dadao",
        "/clone/weapon/gangzhang",
        "/clone/weapon/tiejia",
        "/clone/weapon/hammer",
        "/clone/weapon/gangdao",
        "/clone/weapon/gangjian",
        "/clone/weapon/jiedao",
        "/clone/weapon/qimeigun",
        "/clone/weapon/mudao",
        "/clone/weapon/lianzi",
        "/clone/weapon/feihuangshi",
        "/clone/cloth/tiejia",
});

// 接受供應的NPC：要求這些人必須在指定的場景，所以這裡指明的
// 是場景和NPC的ID。
/*
mapping rcv_npcs = ([
        "/d/chengdu/bingqidian"     : "tang huai",
        "/d/chengdu/wuguan"         : "ma wude",
        "/d/dali/bingying"          : "wei shi",
        "/d/dali/tusifu"            : "da tusi",
        "/d/changan/xunbufang"      : "bu tou",
        "/d/changan/biaoju-damen"   : "biaoshi",
        "/d/changan/qunyulou"       : "da shou",
        "/d/city/wuguan"            : "chen youde",
        "/d/city/dongmen"           : "wu jiang",
        "/d/beijing/xichang"        : "tai jian",
        "/d/beijing/xichengmen"     : "du cha",
        "/d/shaolin/shanmen"        : "xu ming",
        "/d/suzhou/bingying"        : "wu jiang",
        "/d/suzhou/toumenshan"      : "jian ke",
        "/d/hangzhou/liuzhuang"     : "guan jia",
        "/d/hangzhou/yuhuangsd"     : "yu yutong",
        "/d/fuzhou/biaoju"          : "bai er",
        "/d/lingzhou/xiaoxiaochang" : "xixia bing",
        "/d/lingzhou/jiangjungate"  : "xiao wei",
]);
*/
mapping rcv_npcs = ([

        "/d/city/duchang"          : "pang tongtuo",
        "/d/city/ymzhengting"      : "cheng yaofa",
        "/d/city/qianzhuang"       : "qian yankai",
        "/d/city/zahuopu"          : "yang yongfu",
        "/d/city/nanmen"           : "shi song",
        "/d/city/wuguan"           : "chen youde",

        "/d/fuzhou/biaoju"         : "bai er",
        "/d/fuzhou/biaoju"         : "chen qi",
        "/d/fuzhou/biaojudy"       : "shi biaotou",
        "/d/fuzhou/biaojuzt"       : "lin zhennan",
        "/d/fuzhou/biaojuhy"       : "zheng biaotou",
        "/d/fuzhou/yamen"          : "ge shiha",
        "/d/fuzhou/shiqiao"        : "sha tianjiang",

        "/d/xiangyang/jiangjuntang": "wang jian",
        "/d/xiangyang/dangpu"      : "qiu hang",
        "/d/xiangyang/qianzhuang"  : "huang zhen",

        "/d/beijing/qingmu_dayuan" : "xuan zhen",
        "/d/beijing/yihongyuan"    : "laobao po",
        "/d/beijing/xingchang"     : "guizi shou",
        "/d/beijing/zahuo"         : "hu zhanggui",
        "/d/beijing/mianguan"      : "shuaijiao touling",
        "/d/beijing/hai_dating"    : "duo long",
        "/d/beijing/hai_dating"    : "zheng keshuang",
        "/d/beijing/hai_dating"    : "feng xifan",
        "/d/beijing/weifu_men"     : "li lishi",
        "/d/beijing/weifu_dating"  : "gui erniang",
        "/d/beijing/weifu_dating"  : "liu dahong",
        "/d/beijing/xichang"       : "tai jian",
        "/d/beijing/xichengmen"    : "du cha",

        "/d/suzhou/yamen"          : "feng zhengdong",
        "/d/suzhou/jubaozhai"      : "sun baopi",
        "/d/suzhou/yamen"          : "zhen youqing",
        "/d/suzhou/shuchang"       : "gongzi ge",
        "/d/suzhou/bingying"       : "wu jiang",
        "/d/suzhou/toumenshan"     : "jian ke",

        "/d/hangzhou/yaodian"      : "hu qingyu",
        "/d/hangzhou/road17"       : "chu yuan",
        "/d/hangzhou/suti4"        : "li yuanzhi",
        "/d/hangzhou/road16"       : "bai zhen",
        "/d/hangzhou/road19"       : "long jun",
        "/d/hangzhou/liuzhuang"    : "guan jia",

        "/d/kunming/kedian"        : "yuan cai",
        "/d/kunming/dangpu"        : "liu tong",
        "/d/kunming/jinrilou"      : "fujia dizi",

        "/d/luoyang/tangsancai"    : "qin zhanggui",
        "/d/luoyang/xinluofang"    : "gaoli shang",
        "/d/luoyang/huqing"        : "hu xueyuan",
        "/d/luoyang/shudian"       : "shudian laoban",
        "/d/luoyang/dangpu"        : "qi laoer",
        "/d/luoyang/zahuopu"       : "xiao nanzhong",
        "/d/luoyang/jiyuan"        : "laobao po",
        "/d/luoyang/jiyuan2"       : "piao ke",
        "/d/luoyang/shoushi"       : "zhou yifeng",

        "/d/lingzhou/yipindating"  : "helian tieshu",
        "/d/lingzhou/yipindayuan"  : "yun zhonghe",
        "/d/lingzhou/yipinjieyin"  : "nu erhai",
        "/d/lingzhou/yipinzhang"   : "zhang fang",
        "/d/lingzhou/xiaoxiaochang": "xixia bing",
        "/d/lingzhou/jiangjungate" : "xiao wei",

        "/d/chengdu/tidufu"        : "wu tiande",
        "/d/chengdu/wuguan"        : "ma wude",
        "/d/chengdu/wuguan"        : "lao zhangfang",
        "/d/chengdu/wuguanliu"     : "liu hongying",
        "/d/chengdu/wuguanchen"    : "chen hu",
        "/d/chengdu/wuguanxiao"    : "xiao fei",
        "/d/chengdu/wuguanlong"    : "long quan",

        "/d/foshan/yingxionglou"   : "feng qi",
        "/d/foshan/dangpu"         : "lao chaofeng",
        "/d/foshan/pm_restroom"    : "feng yiming",
        "/d/foshan/street3"        : "liumang tou",

        "/d/kaifeng/road4"         : "lu feiqing",
        "/d/kaifeng/kaifeng"       : "zhang long",
        "/d/kaifeng/kaifeng"       : "zhao hu",
        "/d/kaifeng/jiaomen"       : "zhang san",

        "/d/changan/yamen-datang"  : "liang xinglu",
        "/d/changan/huozhan"       : "liang xilu",
        "/d/changan/mianguan"      : "lao zhang",
        "/d/changan/zahuopu"       : "liu laoshi",
        "/d/changan/xiaojiadt"     : "xiao yuanwai",
        "/d/changan/shoushi-dian"  : "chen laoban",
        "/d/changan/duchang"       : "zhuang jia",
        "/d/changan/bridge1"       : "zhang heng",
        "/d/changan/bridge2"       : "xiao qun",
        "/d/changan/xunbufang"     : "bu tou",
        "/d/changan/yamen-datang"  : "chen jisheng",
        "/d/changan/biaoju-damen"  : "biaoshi",
        "/d/changan/qunyulou"      : "da shou",

        "/d/dali/wangfugate"       : "chu wanli",
        "/d/dali/tusifu"           : "da tusi",
        "/d/dali/tusiyishi"        : "da tusi",
        "/d/dali/garments"         : "xue laoban",
        "/d/dali/paifang"          : "hu yizhi",
        "/d/dali/wangfulu"         : "fu sigui",
        "/d/dali/louti"            : "gao shengtai",
        "/d/dali/guibingshi2"      : "daizu shouling",
        "/d/dali/bingying"         : "wei shi",

        "/d/zhongzhou/miaojia_men" : "zhong zhaowen",
        "/d/zhongzhou/congwu"      : "du dajin",

        "/d/ruzhou/ximen"          : "wu jiang",
        "/d/shaolin/shanmen"       : "xu ming",
]);
void startup();

// 任務對象創建
void create()
{
        seteuid(getuid());
        if (! clonep() && find_object(QUEST_D)) startup();
}

void start_quest()
{
        object env;             // 接收物品的NPC所在的環境
        object npc;             // 接收物品的NPC對象
        object *obs;            // 目前所有的SUPPLY任務
        string *env_room;       // 新任務能夠在的地點
        string room;            // NPC所在的環境文件名字
        string sob_file;        // 接收的物品對應的文件

        object qob;             // 任務對象

        // 選擇一個新的地點(目前沒有SUPPLY任務的)
        env_room = keys(rcv_npcs);
        obs = children("/clone/quest/supply");
        if (arrayp(obs) && sizeof(obs) > 0)
        {
                for( int i=0; i<sizeof(obs); i++ )
                        env_room -= ({ query("quest_position", obs[i]) });
        }

        if (sizeof(env_room) < 1)
                // 無法找到這樣的地點
                return;

        room = env_room[random(sizeof(env_room))];
        env = get_object(room);
        if (!objectp(env))
        {
                log_file("supply", sprintf("file %s have not find\n", room));
                return;
        }

        // 選擇改地點中的人
        if (! objectp(npc = present(rcv_npcs[room], env)) ||
            query("startroom", npc) != base_name(env) )
                // 無法找到該地點中合適的NPC來接收
                return;


        // 選擇一種兵器
        sob_file = supply_objs[random(sizeof(supply_objs))];

        // 初始化任務的一些信息（啟動地點）
        qob = new("/clone/quest/supply");
        set("quest_position", room, qob);

        CHANNEL_D->do_channel(find_object(QUEST_D),
                              "debug", "進程(SUPPLY)在" + env->short(1) +
                              NOR HIW "地點利用" + npc->name() +
                              NOR HIW "創建了一個任務。");

        // 交由任務自己進行初始化
        qob->init_quest(npc, sob_file);
}

private void heart_beat()
{
        if (! find_object(QUEST_D))
                return;

        // 如果可以，每次心跳產生一個QUEST
        start_quest();
}

// 任務守護進程喚醒這個進程
void startup()
{
        // 啟動
        if (! find_object(QUEST_D))
                return;

        if (! query_heart_beat())
                CHANNEL_D->do_channel(find_object(QUEST_D),
                                      "sys", "進程(SUPPLY)啟動了。");

        // 平均每四分鐘產生一個任務
        set_heart_beat(110 + random(20));
}

// 停止這個任務進程
void stop()
{
        set_heart_beat(0);
}
