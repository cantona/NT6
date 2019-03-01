// indian.c 印度

#include "name.h"

mapping ma_sname = ([
        "薩"   : "sa",
        "拉"   : "la",
        "阿"   : "a",
        "烏"   : "wu",
        "阿比" : "abi",
        "亞比" : "yabi",
        "尤利" : "youli",
        "戡撻" : "kanda",
        "思戈" : "sige",
        "亨達" : "hengda",
        "騰格" : "tengge",
        "佛答" : "foda",
        "西戈" : "sige",
        "沙戈" : "shage", 
        "帕魯" : "palu",
        "科納" : "kena",
        "摩利" : "moli",
        "幹亞" : "ganya",
        "瑪曼可" : "mamanke",
        "斯坎撻" : "sikanda",
        "瑪斯魯" : "masilu",
        "曼克雅" : "mankeya",
]);

mapping ma_pname = ([
        "牟祿" : "molu",
        "摩克" : "moke",
        "曼都" : "mandu",
        "尤拿" : "youna",
        "佔科" : "zhanke",
        "尚柯" : "shangke",
        "法特" : "fate",
        "休利" : "xiuli",
        "昊戈" : "haoge",
        "達姆" : "damu",
        "利姆" : "limu",
        "斯穆" : "simu",
        "罕特" : "hante",
        "罕麼" : "hanme",
        "塔姆" : "tamu",
        "恩姆" : "enmu",
        "海穆" : "haimu",
        "甘姆" : "ganmu",
        "斯瑪特" : "simate",
        "翰南利" : "hannali",
        "西曼達" : "simanda",
        "亞利達" : "yalida",
        "斯曼卡" : "simanka",
        "菲穆達" : "feimuda",
]);

void generate_in_name(object ob)
{
        string name, sname, pname, id1, id2;
        string *ks, *kp;

        ks = keys(ma_sname);
        kp = keys(ma_pname);
        sname = ks[random(sizeof(ks))];
        pname = kp[random(sizeof(kp))];
        id1 = ma_sname[sname];
        id2 = ma_pname[pname];        
        name = sname + pname;

        if (ob) ob->set_name(name, ({ id1 + " " + id2, id1, id2 }));
}

