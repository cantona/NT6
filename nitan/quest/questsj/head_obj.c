// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping head_obj = ([
        "/d/yanziwu/npc/obj/necklace":30,             //阿朱、阿碧
        "/d/xueshan/obj/sengmao":10,                  //僧帽
        "/d/xueshan/obj/rtlian":34,                   //蓮座
        "/d/xueshan/obj/klguan":34,                   //蓮座
        "/d/xiakedao/obj/xuantie":1,                  //俠客島一律廉價
        "/d/xiakedao/obj/lingpai1":1,                 //俠客島一律廉價
        "/d/xiakedao/obj/lingpai":1,                  //俠客島一律廉價
        "/d/wanjiegu/npc/obj/xiu-scarf":33,           //鍾靈
        "/d/wanjiegu/npc/obj/scarf":1,                //暫時無處獲取
        "/d/wanjiegu/npc/obj/hat":1,                  //暫時無處獲取
        "/d/taohuacun/obj/rose":1,                    //暫時無處獲取
        "/d/taohua/obj/shudai":30,                    //黃蓉、郭芙
        "/d/taohua/obj/jindai":1,                     //暫時無處獲取
        "/d/shenlong/obj/sg_mianzhao":1,              //暫時無處獲取
        "/d/shaolin/obj/weibo":22,                    //道相禪師
        "/d/shaolin/obj/toukui":22,                   //道相禪師
        "/d/mingjiao/obj/weibo":1,                    //暫時無處獲取
        "/d/mingjiao/obj/toukui":1,                   //暫時無處獲取
        "/d/heimuya/npc/obj/zhenzhu":33,              //上官雲
        "/d/hangzhou/npc/obj/xuannv-lingfu":9,        //倩兒
        "/d/hangzhou/npc/obj/tongxin-jie":9,          //倩兒
        "/d/hangzhou/npc/obj/sansheng-youyue":15,     //倩兒
        "/d/hangzhou/npc/obj/huangtong-suo":9,        //倩兒
        "/d/hangzhou/honghua/obj/cuiyu":33,           //霍青桐
        "/d/foshan/obj/hua3":25,                      //佛山林間道
        "/d/foshan/obj/hua2":25,                      //佛山林間道
        "/d/foshan/obj/hua1":25,                      //佛山林間道
        "/d/dali/obj/chahua9":25,                     //茶花園
        "/d/dali/obj/chahua8":25,                     //茶花園
        "/d/dali/obj/chahua7":25,                     //茶花園
        "/d/dali/obj/chahua6":25,                     //茶花園
        "/d/dali/obj/chahua5":25,                     //茶花園
        "/d/dali/obj/chahua4":25,                     //茶花園
        "/d/dali/obj/chahua3":25,                     //茶花園
        "/d/dali/obj/chahua2":25,                     //茶花園
        "/d/dali/obj/chahua13":25,                    //茶花園
        "/d/dali/obj/chahua12":25,                    //茶花園
        "/d/dali/obj/chahua11":25,                    //茶花園
        "/d/dali/obj/chahua10":25,                    //茶花園
        "/d/dali/obj/chahua1":25,                     //茶花園
        "/d/dali/npc/obj/ttoujin":22,                 //台夷獵手（三個）、台夷商販（三個）、大理漁夫
        "/d/dali/npc/obj/lace":36,                    //大土司
        "/d/city/obj/yrose":5,                        //楊永福購買
        "/d/city/obj/toukui":1,                       //暫時無處獲取
        "/d/city/obj/rrose":5,                        //楊永福購買
        "/d/city/obj/necklace":8,                     //陳阿婆購買、小翠
        "/d/city/obj/cycle":1,                        //暫時無處獲取
        "/d/city/npc/obj/toukui":5,                   //楊永福、高麗商人購買
        "/d/city/npc/obj/necklace":30,                //崔鶯鶯、程玉環
        "/d/city/npc/obj/cycle":5,                    //楊永福、高麗商人購買
        "/d/city/npc/cloth/xiu-scarf":5,              //曾柔購買
        "/d/city/npc/cloth/scarf":5,                  //曾柔購買
        "/d/city/npc/cloth/hat":5,                    //曾柔購買
        "/d/changan/npc/obj/zi-luolan":5,             //賣花姑娘購買
        "/d/changan/npc/obj/yupei":36,                //蕭員外
        "/d/changan/npc/obj/neck":9,                  //金復還購買
        "/d/changan/npc/obj/lan-tiane":5,             //賣花姑娘購買
        "/d/changan/npc/obj/huang-meigui":5,          //賣花姑娘購買
        "/d/changan/npc/obj/hong-meigui":5,           //賣花姑娘購買
        "/d/changan/npc/obj/hei-mudan":5,             //賣花姑娘購買
        "/d/changan/npc/obj/bai-chahua":5,            //賣花姑娘購買
        "/d/beijing/npc/obj/hat":36,                  //賣花少女
        "/clone/gift/mjade":27000,
        "/clone/gift/mdiamond":27000,
        "/clone/gift/mcrystal":27000,
        "/clone/gift/magate":27000,
        "/clone/gift/fjade":9000,
        "/clone/gift/fdiamond":9000,
        "/clone/gift/fcrystal":9000,
        "/clone/gift/fagate":9000,
        "/clone/gift/diamond":3000,
        "/clone/gift/crystal":3000,
        "/clone/gift/jade":3000,
        "/clone/gift/agate":3000,
        "/clone/gift/cjade":1000,
        "/clone/gift/cdiamond":1000,
        "/clone/gift/ccrystal":1000,
        "/clone/gift/cagate":1000,
]);

int check_value(string filename)
{
        if (undefinedp(head_obj[filename])) return 0;
        return head_obj[filename];
}
