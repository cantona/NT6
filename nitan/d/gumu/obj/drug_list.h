// drug_list.h
// by Blacko /2001/8
// update april 2001.11.09

mapping *drug_list = ({
        ([
                "name": "金蜜散",  //木香,山菊,蟬蜕,牛黃
                "level": 60,
                "file": "jinmisan",
                "time": 10,
                "s": 5,
                "d": 35,
                "n": 2,
        ]),
        ([
                "name": "玉蜂針毒",  //柴胡,葵花粉,玉蜂毒
                "level": 90,
                "file": "yufeng-zhen",
                "time": 20,
                "s": 2,
                "d": -39,
                "n": -39,
        ]),
        ([
                "name": "古墓玉漿",  //升麻,土茯苓,何首烏,雪蓮子,玉蜂王漿
                "level": 120,
                "file": "yujiang",
                "time": 30,
                "s": 201,
                "d": 121,
                "n": 72,
        ]),
        ([
                "name": "古墓聖漿", //木香,土茯苓,人蔘,鯊膽,黃連,古墓玉漿
                "level": 150,
                "file": "shengyao",
                "time": 40,
                "s": 221,
                "d": 184,
                "n": 21,
        ])
});
/*
古墓聖藥列表
60         金蜜散        =        山菊 + 木香 + 蟬蜕 + 牛黃
90        玉蜂針        =        柴胡 + 葵花粉 + 玉蜂毒 + 金針
120        古墓玉漿=        升麻 + 土茯苓 + 何首烏 + 雪蓮子 + 玉蜂王漿
150        古墓聖藥=        木香 + 土茯苓 + 人蔘 + 鯊膽 + 黃連 + 古墓玉漿

古墓藥材列表
*木香，*柴胡，*升麻，*山菊，*土茯苓
*蟬蜕，*何首烏，*黃連/雄黃，*牛黃，*鯊膽，*人蔘，*雪蓮子，*葵花粉

土茯苓        30        20        40        tufuling
升麻        1        1        2        shengma
山菊        1        3        1        shanju
柴胡        2        1        1        chaihu
木香        1        2        1        muxiang
name        cure_s        cure_d        cure_n        herb
巴豆        -1        2        0        badou
葵花粉        0        -40        40        kuihua
防風        0        0        5        fangfeng
生地        0        0        15        shengdi
穿山甲        0        0        30        chuanshanjia
金銀花        0        1        0        jy-hua
荷葉        0        3        0        heye
菊梗        0        5        0        jugeng
黃連        0        20        0        huanglian
雄黃        0        20        0        xionghuang
牛黃        0        30        0        niuhuang
鯊膽        0        52        10        shadan
蟬蜕        3        0        0        chantui
枸枳子        5        0        0        gouzhizi
田七        5        30        0        tianqi
川貝        10        0        0        chuanbei
雪蓮子        20        30        40        xuelianzi
藏紅花        30        0        0        zanghonghua
熊膽        30        0        45        xiongdan
豹胎        30        0        72        baotai
茯苓        40        0        53        fuling
何首烏        80        0        10        heshouwu
人蔘        100        0        0        renshen
*/