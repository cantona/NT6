// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping sword_obj = ([
        "/d/yanziwu/npc/obj/changjian":30,            //阿朱、阿碧
        "/d/xiangyang/npc/obj/mujian":5,              //木匠購買
        "/d/xiakedao/obj/baihongjian":5,              //俠客島石洞
        "/d/wudang/quest/obj/ghost_sword":10,         //武當桃樹枝
        "/d/wanjiegu/npc/obj/tie-gan":35,             //段延慶
        "/d/village/obj/zhujian":5,                   //靈鷲武器庫、俠客島武器庫、蘇州小販、武當練功房
        "/d/village/npc/obj/youlong":35,              //馮鐵匠
        "/d/tulong/tulong/obj/ling1":32,              //流雲使
        "/d/tulong/obj/yitianjian":35,                //趙敏
        "/d/tulong/obj/duan1":0,                      //斷了的依天劍
        "/d/taohua/obj/yuxiao":35,                    //黃藥師
        "/d/taohua/obj/taojian":18,                   //桃花島兵器庫
        "/d/shaolin/obj/zhujian":18,                  //少林兵器庫
        "/d/shaolin/obj/changjian":10,                //少林一些和尚、道塵禪師索取
        "/d/quanzhou/pig/obj/cleansword":1,           //暫時無處獲取
        "/d/quanzhou/obj/xiuhua":5,                   //胡掌櫃購買
        "/d/quanzhou/npc/obj/xiuhua":1,               //暫時無處獲取
        "/d/quanzhen/npc/obj/gangjian":22,            //全真禪房、武功鎮武將（兩個）
        "/d/mingjiao/obj/changjian":1,                //暫時無處獲取
        "/d/meizhuang/obj/sea-wood":32,               //琴音小院
        "/d/meizhuang/obj/qin":1,                     //暫時無處獲取
        "/d/jinshe/obj/jinshe-jian":32,               //金蛇洞
        "/d/huashan/obj/longquan":30,                 //華山居室
        "/d/huashan/npc/obj/green_water_sword":35,    //岳靈珊
        "/d/heimuya/obj/yuxiao":35,                   //東方不敗
        "/d/heimuya/npc/obj/zhen":1,                  //暫時無處獲取
        "/d/heimuya/npc/obj/changjian":30,            //桑三娘、任盈盈
        "/d/hangzhou/honghua/obj/shortsword":35,      //霍青桐
        "/d/gumu/npc/obj/shunvjian":35,               //小龍女
        "/d/gumu/npc/obj/junzijian":35,               //小龍女
        "/d/fuzhou/obj/xiuhua":5,                     //很多
        "/d/fuzhou/npc/obj/xiuhua":1,                 //暫時無處獲取
        "/d/emei/obj/zhujian":25,                     //峨嵋儲物間
        "/d/emei/obj/skysword":1,                     //暫時無處獲取
        "/d/emei/obj/ruanjian":35,                    //靜風師太
        "/d/city/obj/gangjian":18,                    //白衣衛士（六個）
        "/d/city/obj/duanjian":12,                    //相當多
        "/d/city/obj/changjian":10,                   //相當多
        "/d/city/obj/branch1":18,                     //蛇谷
        "/d/city/obj/branch":18,                      //蛇谷
        "/d/city/npc/obj/gangjian":10,                //相當多
        "/d/city/npc/obj/duanjian":1,                 //暫時無處獲取
        "/d/city/npc/obj/changjian":15,               //程玉環、丁堅、史令威、梅莊護院
        "/d/changan/npc/obj/sword":12,                //群玉樓保鏢、樑興祿
        "/d/changan/npc/obj/changjian":10,            //慕容豪、武將
        "/d/beijing/npc/obj/sword5":20,               //東廠官兵
        "/d/beijing/npc/obj/sword4":15,               //西廠官兵、城門督察、御前侍衛、驍騎營侍衛、張康年、趙齊賢
        "/d/beijing/npc/obj/sword3":35,               //馮錫范
        "/d/beijing/npc/obj/sword2":20,               //劍僧
        "/d/beijing/npc/obj/sword1":30,               //歸二娘
        "/d/beijing/npc/obj/bishou":35,               //鰲拜
        "/d/beijing/npc/obj/baojian":1,               //暫時無處獲取
        "/clone/weapon/zhujian":5,                    //很多
        "/clone/weapon/xiyang-sword":10,              //日本外敵
        "/clone/weapon/green_sword":35,               //張召重
        "/clone/weapon/gangjian":5,                   //很多
        "/clone/weapon/duanjian":1,                   //暫時無處獲取
        "/clone/weapon/changjian":5,                  //很多
        "/clone/book/shenghuo-ling":35,               //張無忌
        "/kungfu/class/dali/obj/tiedi":35,            //高升泰
]);

int check_value(string filename)
{
        if (undefinedp(sword_obj[filename])) return 0;
        return sword_obj[filename];
}
