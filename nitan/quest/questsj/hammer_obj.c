// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping hammer_obj = ([
        "/d/xueshan/obj/yinlun":1,            //暫時無處獲取
        "/d/xueshan/obj/lubo":36,             //蓮座
        "/d/xueshan/obj/jinlun":1,            //暫時無處獲取
        "/d/xueshan/obj/falun":20,            //雪山庫房、隨機三個之內
        "/d/xueshan/obj/faling":18,           //祭祀喇嘛(四個)、塔底
        "/d/xingxiu/obj/yaochu":26,           //神農弟子、採藥人（三個）
        "/d/xiakedao/obj/zhutou":1,           //俠客島的一律廉價
        "/d/xiakedao/obj/forleg":1,           //俠客島的一律廉價
        "/d/xiakedao/obj/backleg":1,          //俠客島的一律廉價
        "/d/xiakedao/npc/obj/jitui":1,        //俠客島的一律廉價
        "/d/wudang/obj/shitou":20,            //武當小路
        "/d/wanjiegu/npc/obj/muyu":34,        //黃眉大師
        "/d/village/npc/obj/hothammer":33,    //馮鐵匠
        "/d/village/npc/obj/hammer":5,        //馮鐵匠購買
        "/d/tulong/yitian/npc/obj/tongbo":18, //砵僧
        "/d/tulong/tulong/obj/stone":5,       //海灘
        "/d/tulong/tulong/npc/obj/hammer":36, //常金鵬
        "/d/shaolin/obj/muchui":25,           //少林東側殿、西側殿
        "/d/quanzhen/npc/obj/jitui":5,        //購買
        "/d/mingjiao/obj/shigu":22,           //戈壁灘（六根）
        "/d/mingjiao/obj/mutang":22,          //山門門衛（兩個）、巫士四個
        "/d/heimuya/obj/zijinchui":1,         //暫時無處獲取
        "/d/heimuya/npc/obj/zijinchui":33,    //童百熊
        "/d/hangzhou/obj/shitou":20,          //杭州寶石山
        "/d/guanwai/npc/obj/tongren":33,      //滕一雷
        "/d/guanwai/npc/obj/tiepipa":33,      //焦文期
        "/d/foshan/obj/shikuai":12,           //佛山林間道
        "/d/dali/npc/obj/yaoqin":30,          //大理歌女（兩個）
        "/d/chengdu/npc/obj/jitui":5,           //可以購買
        "/d/city/obj/stone":20,               //蛇谷
        "/d/city/obj/shitou":15,              //揚州城外密林
        "/d/city/obj/jitui":5,                //可以購買
        "/d/city/obj/hammer":1,               //暫時無處獲取
        "/d/city/obj/bone":26,                //大和街邊
        "/d/city/npc/obj/jitui":5,            //可以購買
        "/d/city/npc/obj/hammer":1,           //暫時無處獲取
        "/d/changan/npc/obj/jitui":5,         //可以購買
        "/d/changan/npc/obj/hammer":26,       //慕容豪、張衡、蕭群
        "/d/beijing/npc/obj/hammer":25,       //北京鐵匠
        "/clone/weapon/hammer":5,             //很多
        "/clone/weapon/falun":5,              //很多
        "/clone/food/jitui":5,                //可以購買
]);

int check_value(string filename)
{
        if (undefinedp(hammer_obj[filename])) return 0;
        return hammer_obj[filename];
}
