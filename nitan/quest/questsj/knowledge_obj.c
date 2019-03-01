// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping knowledge_obj = ([
        "/d/xueshan/obj/fojing2":36,                  //雪山塔底
        "/d/xiaoyao/obj/lbook4":1,                    //暫時無處獲取
        "/d/xiaoyao/npc/obj/lbook4":1,                //暫時無處獲取
        "/d/shaolin/obj/fojing21":30,                 //少林藏經樓
        "/d/shaolin/obj/fojing20":30,                 //少林藏經樓
        "/d/shaolin/obj/fojing11":30,                 //少林藏經樓
        "/d/shaolin/obj/fojing10":30,                 //少林藏經樓
        "/d/quanzhen/npc/obj/daodejing-ii":30,        //掌理道長、祁志誠
        "/d/quanzhen/npc/obj/daodejing-i":33,         //掌經道長
        "/d/emei/obj/fojing21":28,                    //峨嵋藏經閣、峨嵋藏經樓
        "/d/emei/obj/fojing20":28,                    //峨嵋藏經閣、峨嵋藏經樓
        "/d/emei/obj/fojing11":28,                    //峨嵋藏經閣、峨嵋藏經樓
        "/d/emei/obj/fojing10":28,                    //峨嵋藏經閣、峨嵋藏經樓
        "/d/emei/obj/fojing":33,                      //滅絕師太
        "/d/city/npc/obj/lbook3":1,                   //暫時無處獲取
        "/d/changan/npc/obj/book":40,                 //蕭員外
        "/clone/book/zhengpu":36,                     //歐陽峰
        "/clone/book/yljing2":1,                      //暫時無處獲取
        "/clone/book/yljing1":1,                      //暫時無處獲取
        "/clone/book/yljing":1,                       //暫時無處獲取
        "/clone/book/yijing3":30,                     //桃花島書房
        "/clone/book/yijing2":30,                     //桃花島書房
        "/clone/book/yijing1":30,                     //桃花島書房
        "/clone/book/yijing0":30,                     //桃花島書房
        "/clone/book/xiaopu":36,                      //黃藥師
        "/clone/book/taohua":36,                      //黃藥師
        "/clone/book/qin":36,                         //令狐沖
        "/clone/book/mizong_book":33,                 //雪山藏經室
        "/clone/book/lbook4":33,                      //苟讀
        "/clone/book/lbook3":18,                      //朱熹購買
        "/clone/book/lbook2":10,                      //朱熹購買
        "/clone/book/lbook1":7,                       //朱熹購買
        "/clone/book/laozi8":28,                      //武當藏經閣、全真藏經閣
        "/clone/book/laozi2":28,                      //武當藏經閣、全真藏經閣
        "/clone/book/laozi18":28,                     //武當藏經閣、全真藏經閣
        "/clone/book/laozi16":28,                     //武當藏經閣、全真藏經閣
        "/clone/book/laozi13":28,                     //武當藏經閣、全真藏經閣
        "/clone/book/laozi1":28,                      //武當藏經閣、全真藏經閣
        "/clone/book/daodejing":1,                    //暫時無處獲取
        "/clone/book/daodejing-ii":33,                //清虛道長
        "/clone/book/daodejing-i":26,                 //谷虛道長、武當藏經閣、全真藏經閣
        "/clone/book/book-paper":26,                  //神龍小屋、燕子鎢還施水閣、苟讀
        "/clone/book/bagua1":30,                      //桃花島書房
        "/clone/book/bagua0":30,                      //桃花島書房
]);

int check_value(string filename)
{
        if (undefinedp(knowledge_obj[filename])) return 0;
        return knowledge_obj[filename];
}
