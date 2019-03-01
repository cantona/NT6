// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping armor_obj = ([
        "/d/yanziwu/npc/obj/goldring":30,     //阿朱、阿碧
        "/d/wanjiegu/npc/obj/jade-belt":1,    //暫時無處獲取
        "/d/wanjiegu/npc/obj/belt":1,         //暫時無處獲取
        "/d/tulong/yitian/npc/obj/gong":20,   //神箭八雄
        "/d/taohua/obj/ruanwei":30,           //黃蓉、郭芙
        "/d/shaolin/obj/zhitao":18,           //向武修文、道相禪師索取
        "/d/shaolin/obj/yaodai":1,            //暫時無處獲取
        "/d/shaolin/obj/tieshou":26,          //打鐵僧（一次三個）
        "/d/shaolin/obj/shoutao":18,          //向武修文、道相禪師索取
        "/d/shaolin/obj/huyao":18,            //向武修文、道相禪師索取
        "/d/shaolin/obj/huwan":18,            //向武修文、道相禪師索取
        "/d/quanzhen/npc/obj/tiejia":22,      //全真禪房、武功鎮武將（兩個）
        "/d/mingjiao/obj/zhitao":1,           //暫時無處獲取
        "/d/mingjiao/obj/yaodai":1,           //暫時無處獲取
        "/d/mingjiao/obj/tieshou":1,          //暫時無處獲取
        "/d/mingjiao/obj/shoutao":1,          //暫時無處獲取
        "/d/mingjiao/obj/huyao":1,            //暫時無處獲取
        "/d/mingjiao/obj/huwan":1,            //暫時無處獲取
        "/d/heimuya/npc/obj/jin":36,          //任盈盈
        "/d/emei/obj/yaodai":33,              //峨嵋儲物間
        "/d/dali/npc/obj/tiejia":23,          //大理武將（一次五個）
        "/d/city/obj/zhitao":1,               //暫時無處獲取
        "/d/city/obj/tieshou":1,              //暫時無處獲取
        "/d/city/obj/tiejia":1,               //暫時無處獲取
        "/d/city/obj/surcoat":5,              //很多
        "/d/city/obj/shoutao":1,              //暫時無處獲取
        "/d/city/obj/shield":1,               //暫時無處獲取
        "/d/city/obj/huyao":1,                //暫時無處獲取
        "/d/city/obj/huwan":1,                //暫時無處獲取
        "/d/city/obj/goldring":8,             //福州、泉州雜貨舖陳阿婆購買
        "/d/city/npc/obj/zhitao":10,          //楊永福、高麗商人購買
        "/d/city/npc/obj/tieshou":5,          //楊永福、高麗商人購買
        "/d/city/npc/obj/tiejia":5,           //很多
        "/d/city/npc/obj/surcoat":5,          //楊永福、高麗商人購買
        "/d/city/npc/obj/shoutao":1,          //楊永福、高麗商人購買
        "/d/city/npc/obj/shield":8,           //楊永福、高麗商人購買
        "/d/city/npc/obj/huyao":6,            //楊永福、高麗商人購買
        "/d/city/npc/obj/huwan":6,            //楊永福、高麗商人購買
        "/d/city/npc/obj/goldring":33,        //程玉環
        "/d/city/npc/cloth/jade-belt":3,      //曾柔購買
        "/d/city/npc/cloth/belt":8,           //曾柔購買
        "/d/changan/npc/obj/zuanjie":18,      //陳老板購買
        "/d/changan/npc/obj/zhanjia":22,      //有不少
        "/d/changan/npc/obj/yinjie":7,        //陳老板購買
        "/d/changan/npc/obj/wrists":8,        //金復還購買
        "/d/changan/npc/obj/shield":7,        //劉老實購買
        "/d/changan/npc/obj/ring":6,          //金復還購買
        "/d/changan/npc/obj/jinjie":15,       //陳老板購買
        "/d/changan/npc/obj/baojie":15,       //陳老板購買
        "/d/changan/npc/obj/baijie":15,       //陳老板購買
        "/d/beijing/npc/obj/baojia":36,       //鰲拜
        "/clone/weapon/tiejia":1,             //暫時無處獲取
        "/clone/cloth/yaodai":30,             //陳家洛、余魚同
        "/clone/cloth/tiejia":5,              //很多
        "/clone/book/book-iron":18,           //打鐵僧、神龍小屋、俠客島書房、雪山藏經閣、燕子鎢還施水閣
]);

int check_value(string filename)
{
        if (undefinedp(armor_obj[filename])) return 0;
        return armor_obj[filename];
}
