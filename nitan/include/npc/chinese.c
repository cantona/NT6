// chinese name

#include "name.h"

mapping get_cn_name();
mapping cn_sname = ([
//中華單姓
        "趙" : "zhao",
        "錢" : "qian",
        "孫" : "sun",
        "李" : "li",
        "周" : "zhou",
        "吳" : "wu",
        "鄭" : "zheng",
        "王" : "wang",
        "馮" : "feng",
        "陳" : "chen",
        "褚" : "chu",
        "衞" : "wei",
        "蔣" : "jiang",
        "沈" : "shen",
        "韓" : "han",
        "楊" : "yang",
        "朱" : "zhu",
        "秦" : "qin",
        "尤" : "you",
        "許" : "xu",
        "何" : "he",
        "呂" : "lv",
        "施" : "shi",
        "張" : "zhang",
        "孔" : "kong",
        "曹" : "cao",
        "嚴" : "yan",
        "華" : "hua",
        "金" : "jin",
        "魏" : "wei",
        "陶" : "tao",
        "姜" : "jiang",
        "戚" : "qi",
        "謝" : "xie",
        "鄒" : "zou",
        "喻" : "yu",
        "柏" : "bo",
        "水" : "shui",
        "竇" : "dou",
        "章" : "zhang",
        "雲" : "yun",
        "蘇" : "su",
        "潘" : "pan",
        "葛" : "ge",
        "奚" : "xi",
        "範" : "fan",
        "彭" : "peng",
        "郎" : "lang",
        "魯" : "lu",
        "韋" : "wei",
        "馬" : "ma",
        "苗" : "miao",
        "鳳" : "feng",
        "花" : "hua",
        "方" : "fang",
        "任" : "ren",
        "袁" : "yuan",
        "柳" : "liu",
        "鄧" : "deng",
        "鮑" : "bao",
        "史" : "shi",
        "唐" : "tang",
        "費" : "fei",
        "廉" : "lian",
        "岑" : "cen",
        "薛" : "xue",
        "雷" : "lei",
        "賀" : "he",
        "倪" : "ni",
        "湯" : "tang",
        "藤" : "teng",
        "殷" : "yin",
        "羅" : "luo",
        "華" : "hua",
        "郝" : "hao",
        "鄔" : "wu",
        "安" : "an",
        "常" : "chang",
        "樂" : "le",
        "時" : "shi",
        "付" : "fu",
        "皮" : "pi",
        "卞" : "bian",
        "齊" : "qi",
        "康" : "kang",
        "伍" : "wu",
        "餘" : "yu",
        "元" : "yuan",
        "卜" : "bu",
        "顧" : "gu",
        "平" : "ping",
        "黃" : "huang",
        "和" : "he",
        "穆" : "mu",
        "肖" : "xiao",
        "尹" : "yin",
        "姚" : "yao",
        "邵" : "shao",
        "汪" : "wang",
        "祁" : "qi",
        "毛" : "mao",
        "禹" : "yu",
        "狄" : "di",
        "米" : "mi",
        "貝" : "bei",
        "明" : "ming",
        "計" : "ji",
        "伏" : "fu",
        "成" : "cheng",
        "戴" : "dai",
        "談" : "tan",
        "宋" : "song",
        "茅" : "mao",
        "龐" : "pang",
        "熊" : "xiong",
        "紀" : "ji",
        "舒" : "shu",
        "屈" : "qu",
        "項" : "xiang",
        "祝" : "zhu",
        "董" : "dong",
        "樑" : "liang",
        "樊" : "fan",
        "胡" : "hu",
        "凌" : "ling",
        "霍" : "huo",
        "虞" : "yu",
        "萬" : "wan",
        "支" : "zhi",
        "柯" : "ke",
        "昝" : "jiu",
        "管" : "guan",
        "盧" : "lu",
        "英" : "ying",
        "仇" : "qiu",
        "侯" : "hou",
        "嶽" : "yue",
        "帥" : "shuai",
        "寧" : "ning",
        "谷" : "gu",
        "楚" : "chu",
        "晉" : "jin",
        "閻" : "yan",
        "法" : "fa",
        "鄢" : "yan",
        "塗" : "tu",
        "欽" : "qin",
        "段" : "duan",
        "歸" : "gui",
        "海" : "hai",
        "況" : "kuang",
        "琴" : "qin",
        "商" : "shang",
        "牟" : "mou",
        "佘" : "she",
        "墨" : "mo",
        "哈" : "ha",
        "年" : "nian",
        "陽" : "yang",
        "佟" : "tong",
        "言" : "yan",
        "蒯" : "kuai",
        "鍾" : "zhong",
        "宗" : "zong",
        "林" : "lin",
        "石" : "shi",
        "劉" : "liu",
        "徐" : "xu",
        "郭" : "guo",
        "蕭" : "xiao",
        "程" : "cheng",
        "傅" : "fu",
        "曾" : "zeng",
        "蔡" : "cai",
        "賈" : "jia",
        "丁" : "ding",
        "葉" : "ye",
        "杜" : "du",
        "夏" : "xia",
        "田" : "tian",
        "譚" : "tan",
        "廖" : "liao",
        "陸" : "lu",
        "白" : "bai",
        "崔" : "cui",
        "邱" : "qiu",
        "江" : "jiang",
        "史" : "shi",
        "侯" : "hou",
        "孟" : "meng",
        "龍" : "long",
        "黎" : "li",
        "易" : "yi",
        "武" : "wu",
        "喬" : "qiao",
        "賴" : "lai",
        "龔" : "gong",
        "文" : "wen",

//中華複姓
        "東方" : "dongfang",
        "獨孤" : "dugu",
        "慕容" : "murong",
        "歐陽" : "ouyang",
        "司馬" : "sima",
        "西門" : "ximen",
        "尉遲" : "yuchi",
        "長孫" : "zhangsun",
        "諸葛" : "zhuge",
        "上官" : "shangguan",
        "夏侯" : "xiahou",
        "聞人" : "wenren",
        "皇甫" : "huangfu",
        "澹台" : "tantai",
        "公治" : "gongzhi",
        "淳于" : "chunyu",
        "申屠" : "shentu",
        "公孫" : "gongsun",
        "公羊" : "gongyang",
        "軒轅" : "xuanyuan",
        "令狐" : "linghu",
        "鍾離" : "zhongli",
        "宇文" : "yuwen",
        "慕容" : "murong",
        "仲孫" : "zhongsun",
        "司徒" : "situ",
        "司空" : "sikong",
        "端木" : "duanmu",
        "公良" : "gongliang",
        "百里" : "baili",
        "東郭" : "dongguo",
        "鮮于" : "xianyu",
        "南郭" : "nanguo",
        "呼延" : "huyan",
        "羊舌" : "yangshe",
        "東門" : "dongmen",
        "納蘭" : "nalan",
        "南官" : "nanguan",
        "南宮" : "nangong",
        "拓拔" : "tuoba",
        "完顏" : "wanyan",
        "耶律" : "yelv",
]);

mapping cn_pname = ([
        "a"    : "阿",
        "ai"   : "皚艾哀藹隘埃璦嬡捱",
        "an"   : "安黯諳岸鞍垵鵪",
        "ao"   : "奧傲敖驁翱鰲",
        "ang"  : "昂盎骯",
        "ba"   : "罷霸跋魃",
        "bai"  : "白佰",
        "ban"  : "班斑般",
        "bang" : "邦",
        "bei"  : "北倍貝備",
        "biao" : "表標彪飈飆",
        "bian" : "邊卞弁忭",
        "bin"  : "斌賓彬",
        "bing" : "並兵丙秉炳稟",
        "bu"   : "步不部布埠",
        "cao"  : "曹草操漕",
        "cai"  : "才採材財",
        "cang" : "蒼倉滄傖",
        "chang": "長昌敞瑒廠暢昶",
        "chao" : "超潮巢朝",
        "chen" : "辰臣塵晨沉嗔宸傖",
        "cheng": "誠呈丞承騁埕鋮澄晟",
        "chi"  : "遲持池赤尺馳熾",
        "chuan": "川舛傳遄",
        "ci"   : "此次詞茨辭賜祠茲",
        "da"   : "大達",
        "de"   : "德得",
        "ding" : "鼎定碇酊町鋌",
        "du"   : "獨都度督篤",
        "dong" : "東侗棟鶇峒",
        "dou"  : "鬥兜竇",
        "duo"  : "多奪舵踱",
        "fa"   : "法發乏琺筏伐",
        "fan"  : "凡反泛帆蕃繁藩梵",
        "fang" : "方訪邡昉仿坊",
        "fei"  : "飛芾斐",
        "feng" : "風鳳封豐奉楓峯鋒",
        "fu"   : "福夫符弗芙",
        "gao"  : "高皋郜鎬稿誥縞杲",
        "gang" : "鋼罡剛綱崗岡",
        "gong" : "公工宮功恭觥",
        "guan" : "貫官灌冠綸",
        "guang": "光廣",
        "hai"  : "海亥",
        "hao"  : "號浩皓蒿浩昊灝淏",
        "hong" : "洪紅宏鴻虹泓弘",
        "hu"   : "虎忽湖護乎祜滸怙",
        "hua"  : "化華驊樺畫",
        "ji"   : "積極濟技擊疾及基集記紀季繼吉計冀祭際籍績忌寂霽稷璣芨薊戢佶奇詰笈畿犄",
        "jin"  : "金進今近錦津堇瑾",
        "jing" : "竟靜驚經鏡京淨敬精景警競境徑荊兢靖旌勁",
        "jian" : "漸劍見建間柬堅儉健",
        "jiang": "將疆洚韁",
        "jie"  : "傑節界皆階介屆芥捷頡",
        "jun"  : "俊君均峻竣駿鈞筠",
        "kan"  : "刊戡坎莰",
        "kang" : "康慷亢",
        "ke"   : "可克科刻珂恪溘牁",
        "kuang": "匡曠",
        "lang" : "朗浪廊琅閬莨",
        "li"   : "歷離裏理利立力麗禮黎慄荔瀝櫟璃",
        "lian" : "連聯練煉斂廉漣濂",
        "liang": "良亮涼量諒莨",
        "lin"  : "臨霖麟",
        "ling" : "令嶺陵齡凌稜",
        "lu"   : "祿路魯錄廬麓瀘簏碌",
        "mao"  : "貿冒貌冒懋矛卯瑁",
        "miao" : "淼渺邈",
        "ming" : "明銘鳴",
        "nan"  : "楠南",
        "ning" : "寧濘甯",
        "pian" : "片翩",
        "pin"  : "品",
        "pei"  : "培佩沛轡旆錇霈",
        "qi"   : "啟其器奇豈棄企契歧祈棲崎旗蘄杞耆憩麒圻",
        "qian" : "潛謙倩茜乾虔千",
        "qiang": "強羌錆瑲",
        "qin"  : "欽矜",
        "qing" : "清慶卿晴",
        "qu"   : "驅取渠劬麴趨",
        "ran"  : "冉然染燃",
        "ren"  : "人仁刃壬仞韌衽",
        "rong" : "榮容熔戎宂嶸榕肜",
        "ruo"  : "若箬",
        "sha"  : "沙煞剎霎",
        "shan" : "山善杉陝埏",
        "shang": "上商尚殤",
        "shen" : "深審神申慎參莘",
        "shi"  : "師史石時十世士詩始示適炻",
        "shu"  : "叔樹書術束述樞殊曙庶戍蜀黍墅恕澍",
        "shui" : "水",
        "si"   : "思斯絲司祀嗣巳",
        "song" : "鬆頌誦崧嵩淞竦",
        "tai"  : "泰太台駘薹",
        "tang" : "堂棠瑭",
        "tao"  : "濤淘滔韜燾",
        "tong" : "統通同童彤仝",
        "tian" : "天忝闐",
        "tie"  : "鐵帖",
        "ting" : "挺庭停聽廳廷霆鋌",
        "wan"  : "宛晚挽皖芄",
        "wei"  : "衞微偉維威韋緯煒惟瑋為",
        "wen"  : "文紊",
        "wu"   : "吳物務武午五巫鄔兀毋戊",
        "xi"   : "西席錫熙洗夕兮熹惜",
        "xiao" : "小孝瀟笑曉肖霄驍校",
        "xian" : "憲顯閒獻賢",
        "xiang": "祥相巷翔詳襄驤",
        "xiong": "熊芎雄",
        "xu"   : "旭須虛序戌緒詡勖煦胥",
        "xue"  : "學澩",
        "yang" : "羊洋陽漾央秧煬颺鴦",
        "yi"   : "義易意依亦伊夷倚毅義宜儀藝譯翼逸憶怡熠沂頤奕弈懿翊軼屹猗翌",
        "yin"  : "隱因引銀音寅吟胤誾煙蔭",
        "ying" : "映英影穎瑛應瑩郢鷹",
        "you"  : "友幽悠右憂猷酉",
        "yong" : "勇永",
        "yu"   : "漁鬱寓玉雨語預羽輿育宇禹域譽瑜嶼御渝毓虞禺豫裕鈺煜聿",
        "zhi"  : "之制至值知質致智志直治執止置芝旨峙芷摯郅炙雉幟",
        "zhong": "中忠鍾衷",
        "zhou" : "州舟胄繇晝",
        "zhu"  : "竹駐諸著竺",
        "zhuo" : "灼灼拙琢濯斫擢焯酌",
        "zi"   : "自子資茲紫姿孜梓秭",
        "zong" : "宗樅",
        "zu"   : "足族祖卒",
        "zuo"  : "作左佐笮鑿",
]);

//中華女名（今後繼續添加，以豐富變化）
mapping cn_pwname = ([
        "ai"   : "愛嬡璦",
        "bin"  : "鬢玢",
        "chun" : "春純蓴",
        "dan"  : "丹萏",
        "fang" : "芳",
        "fei"  : "菲妃翡霏",
        "fen"  : "紛芬玢馚",
        "feng" : "鳳楓",
        "hong" : "紅虹葒泓",
        "jiao" : "嬌姣皎",
        "juan" : "娟鵑絹涓",
        "ju"   : "菊",
        "ke"   : "可珂",
        "lan"  : "蘭嵐藍瀾斕",
        "li"   : "麗莉梨黎荔儷俐藜",
        "lian" : "蓮憐",
        "ling" : "玲琳鈴靈菱凌羚苓綾翎",
        "man"  : "曼蔓縵",
        "mei"  : "媚妹美玫莓湄",
        "na"   : "娜納",
        "qi"   : "琪琦",
        "qin"  : "琴芹沁芩衾",
        "qian" : "倩纖芊褰茜",
        "qing" : "青清卿",
        "ping" : "萍蘋娉",
        "rou"  : "柔",
        "ting" : "婷葶",
        "wen"  : "雯紋璺",
        "xia"  : "霞瑕",
        "xian" : "仙",
        "xiang": "香湘襄緗",
        "xin"  : "馨欣",
        "xiu"  : "繡袖秀",
        "xue"  : "雪",
        "yan"  : "豔燕煙灩妍嫣琰胭芫",
        "ying" : "英瑛穎鶯縈瓔熒",
        "yu"   : "玉妤瑜",
        "yue"  : "月",
        "zhen" : "珍真貞箴",
        "zhu"  : "珠",
]);

string make_cn_name()
{
        string *ks_cn_sname, *ks_cn_pname;
        string fir_name, sec_name, result_name;
        int iname;

        string *new_sname;
        string *new_pname;

        new_sname = ({
                "或", "和", "與", "加", "減", "乘", "除", "開", "當", "更", "天下", "炎黃",
                "反賊", "至尊", "修身", "司徒", "白玉", "驚蟄",
        });

        new_pname = ({
                "或", "業", "野", "系", "盜賊", "匹夫", "敗類", "老賊",
        });

        ks_cn_sname = keys(cn_sname);
        ks_cn_pname = keys(cn_pname);

        // 30%用新的姓
        if (random(10) < 3)
                fir_name = new_sname[random(sizeof(new_sname))];
        else
                fir_name = ks_cn_sname[random(sizeof(ks_cn_sname))]; // 姓

        // 名
        // 30%用新的名
        if (random(10) < 3)
                sec_name = new_pname[random(sizeof(new_pname))];
        else
        {
                sec_name = ks_cn_pname[random(sizeof(ks_cn_pname))];
                sec_name = cn_pname[sec_name];
                sec_name = sec_name[(random(sizeof(sec_name)) & 0xFFFE)..<1];
                sec_name = sec_name[0..1];
        }

        // 1/10 機率用數字中文代替
        if (random(10) == 1)
        {
                sec_name = chinese_number(random(100));
        }

        result_name = fir_name + sec_name;

        return result_name;
}

void generate_cn_name(object ob)
{
        string sname, pname, pname2, id1, id2;
        string *ks, *kp;

        ks = keys(cn_sname);
        kp = keys(cn_pname);
        sname = ks[random(sizeof(ks))];
        for (;;)
        {
                pname = kp[random(sizeof(kp))];
                if (pname != cn_sname[sname]) break;
        }
        id1 = cn_sname[sname];

        id2 = pname;
        pname = cn_pname[pname];
        pname = pname[(random(sizeof(pname)) & 0xFFFE)..<1];
        pname = pname[0..1];
        if (random(3) == 0)
        {
                for (;;)
                {
                        pname2 = kp[random(sizeof(kp))];
                        if (pname2 != cn_sname[sname] &&
                            pname2 != pname) break;
                }
                id2 += pname2;
                pname2 = cn_pname[pname2];
                pname2 = pname2[(random(sizeof(pname2)) & 0xFFFE)..<1];
                pname2 = pname2[0..1];
        } else
                pname2 = "";

        if (ob) ob->set_name(sname + pname + pname2,
                             ({ id1 + " " + id2, id1, id2 }));
}

mapping get_cn_name()
{
        string sname, pname, pname2, id1, id2;
        string *ks, *kp;

        ks = keys(cn_sname);
        kp = keys(cn_pname);
        sname = ks[random(sizeof(ks))];
        id1 = cn_sname[sname];
        for (;;)
        {
                pname = kp[random(sizeof(kp))];
                if (pname != id1 &&
                    ! find_living(id1 + " " + pname))
                        break;
        }

        id2 = pname;
        pname = cn_pname[pname];
        pname = pname[(random(sizeof(pname)) & 0xFFFE)..<1];
        pname = pname[0..1];
        if (random(3) == 0)
        {
                for (;;)
                {
                        pname2 = kp[random(sizeof(kp))];
                        if (pname2 != id1 && pname2 != pname &&
                            ! find_living(id1 + " " + pname + pname2)) break;
                }
                id2 += pname2;
                pname2 = cn_pname[pname2];
                pname2 = pname2[(random(sizeof(pname2)) & 0xFFFE)..<1];
                pname2 = pname2[0..1];
        } else
                pname2 = "";

        return ([ "name" : sname + pname + pname2,
                  "id"   : ({ id1 + " " + id2, id1, id2, }), ]);
}
