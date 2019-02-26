// Last Modified by Winder on May. 15 2001
// /clone/misc/dache.c
// sign/value必須是整百的數

inherit ITEM;
#include <ansi.h>;
int do_go(string);
int look_sign();
mapping *sign=({
        ([        "name"   : "黑木崖",
                "target" : "黑木崖亂石坡",
                "id"     : "heimuya",
                "out"    : "heimuya",
                "file"   : "/d/heimuya/road1",
                "value"  : 200,
                "time"   : 10
        ]),
        ([        "name"   : "鐵掌峯",
                "target" : "鐵掌峯山腳下",
                "id"     : "tiezhang",
                "out"    : "tiezhang",
                "file"   : "/d/tiezhang/shanjiao",
                "value"  : 200,
                "time"   : 10
        ]),
        ([        "name"   : "梅莊",
                "target" : "梅莊大門",
                "id"     : "meizhuang",
                "out"    : "meizhuang",
                "file"   : "/d/meizhuang/gate",
                "value"  : 200,
                "time"   : 10
        ]),
        ([        "name"   : "太湖",
                "target" : "太湖湖畔",
                "id"     : "taihu",
                "out"    : "yanziwu",
                "file"   : "/d/yanziwu/hupan",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "無量山",
                "target" : "無量山坳",
                "id"     : "wuliang",
                "out"    : "wuliang",
                "file"   : "/d/wuliang/shanlu6",
                "value"  : 300,
                "time"   : 10
        ]),
        ([        "name"   : "天山",
                "target" : "天山山路",
                "id"     : "tianshan",
                "out"    : "xiyu",
                "file"   : "/d/xingxiu/tianroad2",
                "value"  : 300,
                "time"   : 10
        ]),
        ([        "name"   : "凌霄城",
                "target" : "凌霄城石崖",
                "id"     : "lingxiao",
                "out"    : "lingxiao",
                "file"   : "/d/lingxiao/shiya",
                "value"  : 200,
                "time"   : 10
        ]),
        ([        "name"   : "雪山寺",
                "target" : "雪山寺山門",
                "id"     : "xueshan",
                "out"     : "xueshansi",
                "file"   : "/d/xueshan/shanmen",
                "value"  : 300,
                "time"   : 10
        ]),
        ([        "name"   : "光明頂",
                "target" : "光明頂山門",
                "id"     : "mingjiao",
                "out"    : "mingjiao",
                "file"   : "/d/mingjiao/shanmen",
                "value"  : 300,
                "time"   : 10
        ]),
        ([        "name"   : "中條山",
                "target" : "中條山腳下",
                "id"     : "zhongtiao",
                "out"    : "zhongtiao",
                "file"   : "/d/huashan/jzroad3",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "長白山",
                "target" : "長白山白河",
                "id"     : "changbai",
                "out"    : "changbai",
                "file"   : "/d/guanwai/baihe",
                "value"  : 300,
                "time"   : 10
        ]),
        ([        "name"   : "終南山",
                "target" : "終南山腳下",
                "id"     : "zhongnan",
                "out"    : "zhongnan",
                "file"   : "/d/quanzhen/shanjiao",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "恆山",
                "target" : "恆山金龍峽",
                "id"     : "hengshan",
                "out"    : "hengshan",
                "file"   : "/d/hengshan/jinlongxia",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "衡山",
                "target" : "衡山櫺星門",
                "id"     : "henshan",
                "out"    : "henshan",
                "file"   : "/d/henshan/lingxingmen",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "華山",
                "target" : "華山莎蘿坪",
                "id"     : "huashan",
                "out"    : "huashan",
                "file"   : "/d/huashan/shaluo",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "泰山",
                "target" : "泰山岱宗坊",
                "id"     : "taishan",
                "out"    : "taishan",
                "file"   : "/d/taishan/daizong",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "嵩山",
                "target" : "嵩山太室闕",
                "id"     : "songshan",
                "out"    : "songshan",
                "file"   : "/d/songshan/taishique",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "青城山",
                "target" : "青城建福宮",
                "id"     : "qingcheng",
                "out"    : "qingcheng",
                "file"   : "/d/qingcheng/jianfugong",
                "value"  : 200,
                "time"   : 10
        ]),
        ([        "name"   : "崑崙山",
                "target" : "崑崙派山門",
                "id"     : "kunlun",
                "out"    : "kunlun",
                "file"   : "/d/kunlun/shanmen",
                "value"  : 300,
                "time"   : 10
        ]),
        ([        "name"   : "峨眉山",
                "target" : "峨眉報國寺",
                "id"     : "emei",
                "out"    : "emei",
                "file"   : "/d/emei/bgs",
                "value"  : 200,
                "time"   : 10
        ]),
        ([        "name"   : "武當山",
                "target" : "武當解劍巖",
                "id"     : "wudang",
                "out"    : "wudang",
                "file"   : "/d/wudang/jiejianyan",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "南少林寺",
                "target" : "南少林迎客亭",
                "id"     : "nanshaolin",
                "out"    : "nanshaolin",
                "file"   : "/d/nanshaolin/ting",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "少林寺",
                "target" : "少林寺山門",
                "id"     : "shaolin",
                "out"    : "shaolin",
                "file"   : "/d/shaolin/shanmen",
                "value"  : 100,
                "time"   : 10
        ]),
        ([        "name"   : "揚州",
                "target" : "揚州中央廣場",
                "id"     : "yangzhou",
                "out"    : "yangzhouw",
                "file"   : "/d/city/shilijie4",
                "value"  : 100,
                "time"   : 10
        ]),
});
void setup()
{}
void init()
{
        add_action("do_go", "qu");
        add_action("look_sign", "kan");
}
void create()
{
        set_name("大車", ({"da che", "che", "dache"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是一輛半新不舊的大車，車上坐着一個半老不老的車伕。
你可以仔細看看(kan)車上掛着的牌子，那就是你乘上大車，\n可以去(qu)的地方。\n");
                set("unit", "輛");
                set("no_fight",1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_drop", 1);
                set("no_put", 1);
        }
        setup();
}
int look_sign()
{
        string adjstr1, adjstr2, str="由此去(qu)到下列地方：\n  目的地        地名          價碼\n================================================\n";
        int adj1, adj2, i=sizeof(sign);
        while (i--)
        {
                if( query("outdoors", environment(this_player())) != sign[i]["out"] )
                {
                        str += " "+sign[i]["target"];
                        adjstr1 = sign[i]["target"];
                        adj1 = 18-strlen(adjstr1);
                        while (adj1--) str += " ";
                        str += "("HIY + sign[i]["id"] + NOR") ";
                        adjstr2 = "(" + sign[i]["id"] + ") ";
                        adj2 = 18-strlen(adjstr2);
                        while (adj2--) str += " ";
                        str += "："CYN+MONEY_D->price_str(sign[i]["value"]) + NOR"\n";
                }
        }
        write(str+"------------------------------------------------\n");
        return 1;
}

void do_move(object ob, int i)
{
        delete_temp("block_msg/all", ob);
        delete_temp("noliving", ob);
        write("終於到"+sign[i]["name"]+"了。\n\n");
        ob->move(sign[i]["file"]);
        tell_room(environment(ob), "\n忽然遠處有一輛大車飛馳而來，快到你身邊時就慢慢停了下來。\n" + ob->name() + "從大車上走了下來。\n", ({ob}));
}

int do_go(string arg)
{
        object *inv, ob=this_player();
        int j, i=sizeof(sign);

        if (!arg) return notify_fail("你要去哪裏？先看看(kan)再走吧！\n");
        if (ob->is_busy() || ob->is_fighting())
                return notify_fail("你正忙着呢！\n");

        inv = all_inventory(ob);
        for (j = 0; j < sizeof(inv); j++)
        {
                if (inv[j]->is_character())
                {
                        write("大車裏裏位置有限，擠不下那麼多人。\n");
                        return 1;
                }
        }
         if( query_temp("LAST_PKER_TIME", ob) && 
             time()-query_temp("LAST_PKER_TIME", ob)<7200 && !wizardp(ob) )
             return notify_fail("殺了人，可不能做縮頭烏龜！\n");

        while(i--)
        {
                if (arg == sign[i]["id"])
                {
                        if( query("outdoors", environment(ob)) == sign[i]["out"] )
                                return notify_fail("車伕笑罵道：“你糊塗啦，去什麼去！你不是已經在"HIR+ sign[i]["name"] +NOR"了嗎？！”\n");
                        switch (MONEY_D->player_pay(ob, sign[i]["value"]))
                        {
                                case 0:
                                        return notify_fail("窮光蛋，一邊呆着去！\n");
                                case 2:
                                        return notify_fail("有零錢嗎？\n");
                        }
                        message_vision("\n$N登上了大車，一揚手丟了" + chinese_number(sign[i]["value"]/100) + "兩銀子給車伕，説了聲：“去" +sign[i]["name"]+ "。”\n$N説完掀開簾子，一哈腰鑽進車去。\n\n", ob);
                        write(HIC"大車內"NOR" -
    車裏乾乾淨淨，放了兩張舒服的大椅子。窗簾半拉了下來，陽光從
縫隙中透進來，窗外看不盡的景緻，有的壯觀，有的也無趣。於是昏昏
沉沉地睡去，也不管路上走了多久。門外掛了一串風鈴，叮呤呤響着。
車伕坐在前面，一路趕着馬，一路得意地哼着什麼小調。\n");
                        set_temp("noliving/journey", 1, ob);
                        set_temp("block_msg/all", 1, ob);
                        ob->move("/clone/misc/dachenei");
                        call_out("do_move", sign[i]["time"]+random(10), ob, i);
                        return 1;
                }
        }
        return notify_fail("你要去哪裏？\n");
}
/*
少林寺山門   (shaolin)    /d/shaolin/shanmen
武當解劍巖   (wudang)     /d/wudang/jiejianyan
峨眉報國寺   (emei)       /d/emei/bgs
崑崙派山門   (kunlun)     /d/kunlun/shanmen
青城建福宮   (qingcheng)  /d/qingcheng/jianfugong
嵩山太室闕   (songshan)   /d/songshan/taishique
泰山岱宗坊   (taishan)    /d/taishan/daizong
華山莎蘿坪   (huashan)    /d/huashan/shaluo
衡山櫺星門   (henshan)    /d/henshan/lingxingmen
恆山金龍峽   (hengshan)   /d/hengshan/jinlongxia
終南山腳下   (zhongnan)   /d/quanzhen/shanjiao
中條山腳下   (zhongtiao)  /d/huashan/jzroad3
光明頂山門   (mingjiao)   /d/mingjiao/shanmen
雪山寺山門   (xueshansi)  /d/xueshan/shanmen
天山山路     (xiyu)       /d/xingxiu/tianroad2
無量山坳     (wuliang)    /d/wuliang/shanlu6
太湖湖畔     (yanziwu)    /d/yanziwu/hupan
梅莊大門     (meizhuang)  /d/meizhuang/gate
鐵掌峯山腳下 (tiezhang)   /d/tiezhang/shanjiao
黑木崖亂石坡 (heimuya)    /d/heimuya/road1
*/