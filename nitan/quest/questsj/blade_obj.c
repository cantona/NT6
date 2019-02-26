// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping blade_obj = ([
        "/d/xueshan/obj/xblade1":1,             //暫時無處獲取
        "/d/xueshan/obj/xblade":30,             //血刀老祖、紅日尊者
        "/d/xiaoyao/obj/blade":25,              //逍遙打鐵屋
        "/d/xiaoyao/npc/obj/blade":30,          //逍遙蒙面人
        "/d/xiangyang/npc/obj/mudao":5,         //木匠購買
        "/d/xiakedao/obj/knife":5,              //俠客島的一律廉價
        "/d/xiakedao/obj/gangdao":5,            //俠客島的一律廉價
        "/d/shaolin/obj/mudao":25,              //少林武器庫
        "/d/shaolin/obj/jiedao":10,             //很多
        "/d/quanzhou/npc/obj/wodao":24,         //倭寇（六個）
        "/d/quanzhen/npc/obj/gangdao":18,       //全真禪房、武功鎮官兵（四個）
        "/d/mingjiao/obj/jiedao":1,             //暫時無處獲取
        "/d/mingjiao/obj/gangdao":1,            //暫時無處獲取
        "/d/heimuya/npc/obj/dadao":25,          //賈布、黃伯流、上官雲、童百熊
        "/d/guiyun/npc/obj/jiandao":36,         //張阿生
        "/d/guanwai/obj/lengyue":36,            //胡斐
        "/d/guanwai/obj/cwbdao":40,             //胡斐
        "/d/foshan/npc/obj/caidao":36,          //鍾四嫂
        "/d/dali/npc/obj/mandao":36,            //傣族首領
        "/d/dali/npc/obj/kandao":26,            //採筍人（兩個）、砍竹人（兩個）
        "/d/city/obj/gangdao":5,                //很多
        "/d/city/npc/obj/gangdao":5,            //很多
        "/d/changan/npc/obj/gangdao":5,         //很多
        "/d/changan/npc/obj/blade":5,           //很多
        "/d/beijing/npc/obj/blade3":10,         //北京官兵（相當多）
        "/d/beijing/npc/obj/blade2":5,          //江湖豪客（四個）、毒郎中（無數）、李力世
        "/d/beijing/npc/obj/blade1":5,          //很多
        "/d/baituo/obj/dadao":18,               //白駝山五個門衞、三個山賊、一個山賊頭
        "/d/baituo/obj/chaidao":30,             //樵夫、老材
        "/d/baituo/npc/obj/dadao":1,            //暫時無處獲取
        "/d/baituo/npc/obj/chaidao":1,          //暫時無處獲取
        "/clone/weapon/wandao":7,               //可以購買:12兩白銀
        "/clone/weapon/tudao":8,                //可以購買:20兩白銀
        "/clone/weapon/mudao":5,                //很多
        "/clone/weapon/jpn-dao":10,             //日本外敵
        "/clone/weapon/jiedao":1,               //暫時無處獲取
        "/clone/weapon/gangdao":5,              //很多
        "/clone/weapon/dadao":36,               //馬超興
        "/clone/weapon/blade":5,                //很多
]);

int check_value(string filename)
{
        if (undefinedp(blade_obj[filename])) return 0;
        return blade_obj[filename];
}
