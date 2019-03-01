// japanese name

#include "name.h"

mapping jp_sname = ([
        "白木" : "baimu",
        "北條" : "beitiao",
        "川島" : "chuandao",
        "村正" : "cunzheng",
        "東"   : "dong",
        "東條" : "dongtiao",
        "豐臣" : "fengchen",
        "服部" : "fubu",
        "高橋" : "gaoqiao",
        "黑田" : "heitian",
        "酒井" : "jiujing",
        "瀨川" : "laichuan",
        "毛利" : "maoli",
        "木下" : "muxia",
        "青木" : "qingmu",
        "齊籐" : "qiteng",
        "鬆下" : "songxia",
        "山本" : "shanben",
        "手塚" : "shouzhong",
        "田中" : "tianzhong",
        "籐澤" : "tengze",
        "土肥" : "tufei",
        "武宮" : "wugong",
        "小山" : "xiaoshan",
        "小林" : "xiaolin",
        "小淵" : "xiaoyuan",
        "細川" : "xichuan",
        "依田" : "yitian",
        "織田" : "zhitian",
        "陣內" : "zhennei",
        "中田" : "zhongtian",
        "竹中" : "zhuzhong",
        "最上" : "zuishang",
]);

mapping jp_pname = ([
        "an"   : "安",
        "ao"   : "傲敖",
        "bang" : "邦",
        "bei"  : "北倍貝備",
        "biao" : "標",
        "cao"  : "草",
        "cang" : "蒼倉",
        "chang": "昌",
        "chi"  : "遲馳",
        "ci"   : "此慈",
        "dong" : "東",
        "fa"   : "法",
        "fan"  : "凡蕃",
        "fang" : "訪",
        "feng" : "風豐奉楓",
        "fu"   : "夫符",
        "gao"  : "高",
        "hao"  : "昊",
        "hong" : "宏",
        "hui"  : "惠",
        "ji"   : "極基記紀季繼吉績稷奇",
        "jian" : "漸劍見",
        "ke"   : "科",
        "lang" : "朗琅",
        "li"   : "歷利立力",
        "lin"  : "臨",
        "mao"  : "瑁",
        "nan"  : "南",
        "qian" : "謙千",
        "qin"  : "欽",
        "qing" : "慶",
        "ran"  : "然",
        "ren"  : "仁刃壬仞",
        "shang": "上",
        "shen" : "審神申慎",
        "shi"  : "師史石時十世士適",
        "si"   : "思斯司",
        "tian" : "天田忝",
        "wan"  : "萬",
        "wei"  : "衛微偉維威",
        "wu"   : "物務武午",
        "xi"   : "席洗夕",
        "xiao" : "蕭霄",
        "xiong": "雄",
        "yang" : "洋陽央",
        "yi"   : "易亦伊夷義宜儀譯逸奕弈懿",
        "yin"  : "因引",
        "ying" : "映英影",
        "you"  : "右酉",
        "yu"   : "漁語預",
        "zhi"  : "制知智志直治",
        "zhong": "中",
        "zhou" : "周州舟",
        "zhu"  : "竹足",
        "zhuo" : "卓擢",
        "zi"   : "子",
        "zong" : "宗",
        "zuo"  : "左",
]);

mapping jp_number = ([
        "tai" : "太",
        "ci"  : "次",
        "san" : "三",
        "si"  : "四",
        "wu"  : "五",
]);

void generate_jp_name(object ob)
{
        string name, pname1, pname2, id, id1, id2;
        string *r, *ks;

        ks = keys(jp_sname);
        name = ks[random(sizeof(ks))];
        id = jp_sname[name];

        r = select_a(jp_pname, id);
        id1 = r[0];
        pname1 = r[1];

        if (random(2))
        {
                r = select_a(jp_pname, id);
                id2 = r[0];
                pname2 = r[1];
        } else
        {
                r = select_a(jp_number, id);
                id2 = r[0];
                pname2 = r[1];
                if (random(3))
                {
                        pname1 = pname2 + "郎";
                        id1    = id2 + "lang";
                } else
                {
                        pname1 += pname2;
                        id1    += id2;
                }
                pname2 = "";
                id2    = "";
        }

        switch (random(2))
        {
        case 0:
                id2 = id1 + id2;
                id1 = id;
                id += " " + id2;
                name += pname1 + pname2;
                break;
        case 1:
                id2 = id1;
                id1 = id;
                id += " " + id2;
                name += pname1;
        }

        if (ob) ob->set_name(name, ({ id, id1, id2 }));
}
