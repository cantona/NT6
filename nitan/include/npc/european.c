// japanese name

#include "name.h"

mapping e_gname = ([
        "羅伯特"   : "robert",
        "戴維得"   : "david",
        "羅德"     : "rod",
        "阿貝爾"   : "abel",
        "肯尼"     : "kenny",
        "丹尼爾"   : "daniel",
        "大衞"     : "dave",
        "戴維恩"   : "devin",
        "道恩"     : "don",
        "懷特"     : "white",
        "布魯克"   : "brook",
        "巴克"     : "buck",
        "查里斯"   : "charles",
        "克里斯特" : "christ",
        "克里斯托爾": "christopher",
        "克里弗德" : "clifford",
        "克拉克"   : "clark",
        "埃裏維斯" : "elvis",
        "弗德"     : "ford",
        "哈里"     : "harry",
        "希曼"     : "hyman",
        "傑克"     : "jack",
        "傑夫"     : "jeff",
        "約翰"     : "john",
        "朱裏安"   : "julian",
        "蘭伯特"   : "lambert",
        "邁克斯"   : "max",
        "邁克爾"   : "michael",
        "威廉"     : "william",
        "菲利浦"   : "philip",
]);

mapping e_sname = ([
        "皮剋剋"     : "pycock",
        "阿伯特"     : "abbot",
        "艾思比特"   : "aisbett",
        "裏格特索思" : "rigoutsos",
        "維斯"       : "weiss",
        "布拉蒂"     : "brady",
        "拉斯特曼"   : "lustman",
        "比恩弗德"   : "binford",
        "巴納蒂"     : "barnard",
        "蘭伯"       : "lamb",
        "布魯斯蒂恩" : "blostein",
        "費思格勒"   : "fischler",
        "艾格特"     : "eggert",
        "弗格拉斯"   : "faugeras",
        "艾丁格"     : "ettinger",
        "格林姆遜"   : "grimson",
        "伍德斯"     : "woods",
        "漢森"       : "hansen",
        "漢貝爾"     : "hampel",
        "哈拉里克"   : "haralick",
        "內瓦蒂亞"   : "nevatia",
        "塞吉維克"   : "sedgewick",
        "威格斯勒"   : "wechsler",
        "沃爾夫"     : "wolff",
]);

void generate_e_name(object ob)
{
        string name, pname1, pname2, id, id1, id2;
        pname1 = keys(e_gname)[random(sizeof(e_gname))];
        pname2 = keys(e_sname)[random(sizeof(e_sname))];
        id1 = e_gname[pname1];
        id2 = e_sname[pname2];
        name = pname1 + "·" + pname2;
        id = id1 + " " + id2;
        if (ob) ob->set_name(name, ({ id, id1, id2 }));
}
