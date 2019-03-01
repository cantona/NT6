// names.h
// named.c 需要的頭文件，放 /include/ 目錄下。
// Created by Zen(SnowMan.ZD) 19/09/2002

mapping sur_name = ([
"趙":"zhao",    "錢":"qian",    "孫":"sun",     "李":"li",      
"周":"zhou",    "吳":"wu",      "鄭":"zhen",    "王":"wang",
"馮":"feng",    "陳":"chen",    "褚":"zhu",     "衛":"wei",
"蔣":"jiang",   "沈":"shen",    "韓":"han",     "楊":"yang",
"朱":"zhu",     "秦":"qing",    "尤":"you",     "許":"xu",
"何":"he",      "呂":"lu",      "施":"shi",     "張":"zhang",
"孔":"kong",    "曹":"cao",     "嚴":"yan",     "華":"hua",
"金":"jin",     "魏":"wei",     "陶":"tao",     "姜":"jiang",
"戚":"qi",      "謝":"xie",     "鄒":"zhou",    "喻":"yu",
"柏":"bo",      "水":"shui",    "竇":"dou",     "章":"zhang",
"雲":"yun",     "蘇":"su",      "潘":"pan",     "葛":"ge",
"奚":"xi",      "范":"fan",     "彭":"peng",    "郎":"lang",
"魯":"lu",      "韋":"wei",     "昌":"chang",   "馬":"ma",
"苗":"miao",    "鳳":"feng",    "花":"hua",     "方":"fang",
"傻":"sha",     "任":"ren",     "袁":"yuan",    "柳":"liu",
"鄧":"deng",    "鮑":"bao",     "史":"shi",     "唐":"tang",
"費":"fei",     "岑":"chen",    "薛":"xue",
"雷":"lei",     "賀":"he",      "倪":"ni",      "湯":"tang",
"籐":"teng",    "殷":"yin",     "羅":"luo",     "華":"hua",
"郝":"hao",     "鄔":"wu",      "安":"an",      "常":"chang",
"樂":"le",      "呆":"dai",     "時":"shi",     "付":"fu",
"皮":"pi",      "卞":"bian",    "齊":"qi",      "康":"kang",
"伍":"wu",      "余":"yu",      "元":"yuan",    "卜":"po",
"顧":"gu",      "盈":"ying",    "平":"ping",    "黃":"huang",
"和":"he",      "穆":"mu",      "肖":"xiao",    "尹":"yin",
"姚":"yao",     "邵":"shao",    "湛":"zhan",    "汪":"wang",
"祁":"qi",      "毛":"mao",     "禹":"yu",      "狄":"di",
"米":"mi",      "貝":"bei",     "明":"ming",    "藏":"zang",
"計":"ji",      "伏":"fu",      "成":"cheng",   "戴":"dai",
"談":"tan",     "宋":"song",    "茅":"mao",     "龐":"pang",
"熊":"xiong",   "紀":"ji",      "舒":"shu",     "屈":"qu",
"項":"xiang",   "祝":"zhu",     "董":"dong",    "樑":"liang",
"樊":"fan",     "胡":"hu",      "凌":"ling",    "霍":"huo",
"虞":"yu",      "萬":"wan",     "支":"zhi",     "柯":"ke",
"昝":"jiu",     "管":"guan",    "盧":"lu",      "英":"ying",
"仇":"qiu",     "候":"hou",     "岳":"yue",     "帥":"shuai",
"緱":"gou",     "亢":"kang",    "況":"kuang",   "後":"hou",
"有":"you",     "琴":"qin",     "商":"shang",   "牟":"mo",
"佘":"she",     "耳":"er",      "墨":"mo",      "哈":"ha",
"譙":"qiao",    "年":"nian",    "愛":"ai",      "陽":"yang",
"佟":"tong",    "第":"di",      "五":"wu",      "言":"yan",
"福":"fu",      "蒯":"kai",     "鐘":"zhong",   "宗":"zong",
"林":"lin",     "石":"shi",     "龍":"long",    "徐":"xu",
"贏":"ying",    "姬":"ji",      "木":"mu",      "葉":"ye",
"鐵":"tie",     "漢":"han",     "甄":"zhen",    "賈":"jia",
"丁":"ding",    "蕭":"xiao",    "喬":"qiao",    "沐":"mu",
"高":"gao",     "郭":"guo",     "方":"fang",    "崔":"cui",
"蔡":"cai",     "杜":"du",      "陸":"lu",      "文":"wen",
"江":"jiang",   "白":"bai",     "廖":"liao",    "池":"chi",
"夏":"xia",     "古":"gu",      "滿":"man",     "屠":"tu",
"宮":"gong",    "秋":"qiu",     "邱":"qiu",     "田":"tian",
"仁":"ren",     "永":"yong",    "霄":"xiao",    "傅":"fu", 

"司馬":"sima",          "上官":"shangguan",     "歐陽":"ouyang",
"夏候":"xiahou",        "諸葛":"zhuge",         "聞人":"wenren",
"東方":"dongfang",      "赫連":"helian",        "皇甫":"huangpu",
"尉遲":"weichi",        "公羊":"gongyang",      "澹台":"zhantai",
"公冶":"gongye",        "宗政":"zongzheng",     "濮陽":"puyang",
"淳于":"chunyu",        "單于":"shanyu",        "太叔":"taishu",
"申屠":"shentu",        "公孫":"gongsun",       "仲孫":"zhongsun",
"轅軒":"xuanyuan",      "令狐":"linghu",        "鐘離":"zhongli",
"宇文":"yuwen",         "長孫":"zhangsun",      "幕容":"murong",
"司徒":"situ",          "師空":"shikong",       "顓孔":"zhuankong",
"端木":"duanmu",        "巫馬":"wuma",          "公西":"gongxi",
"漆雕":"qidiao",        "樂正":"lezheng",       "壤駟":"xiangsi",
"公良":"gongliang",     "拓趾":"tuozhi",        "夾谷":"jiagu",
"宰父":"zaifu",         "谷樑":"guliang",       "楚晉":"chujing",
"閻法":"yanfa",         "汝鄢":"ruye",          "塗欽":"tuqin",
"段千":"duanqian",      "百裡":"baili",         "東郭":"dongguo",
"南郭":"nanguo",        "呼延":"huyan",         "歸海":"guihai",
"羊舌":"yangshe",       "微生":"weisheng",      "樑丘":"liangqiu",
"左丘":"zuoqiu",        "東門":"dongmen",       "西門":"ximen",
"佰賞":"baishang",      "南宮":"nangong",       "納蘭":"nalan",   
"鮮于":"xianyu",
]);

mapping f_name = ([
"ai":         ({ "愛", "艾", "嬡", "藹", "璦" }),
"ban":         ({ "班", "瓣" }),
"bai":          ({ "白", "柏" }),
"bei":         ({ "貝", "蓓" }),
"bi":         ({ "碧", "篳", "婢", "蓽", "弼", "蓖" }),
"bin":         ({ "濱", "繽" }),
"bing":         ({ "冰", "屏" }),
"bo":         ({ "波", "帛" }),
"cai":         ({ "彩", "採" }),
"chai":         ({ "釵" }),
"chan":  ({ "蟬", "嬋", "潺" }),
"chang": ({ "暢", "裳", "嫦" }),
"che":         ({ "澈" }),
"chen":         ({ "晨", "辰" }),
"cheng": ({ "澄" }),
"chong": ({ "沖", "寵" }),
"chu":         ({ "初", "楚" }),
"chun":         ({ "春", "純", "唇", "椿", "□" }),
"cui":   ({ "翠", "萃", "璀" }),
"da":         ({ "妲" }),
"dai":   ({ "駘", "岱", "黛" }),
"dan":   ({ "丹", "旦", "萏", "單", "鄲", "萏", "淡", }),
"dang":         ({ "鐺" }),
"di":         ({ "蒂", "滴", "笛", "翟", "荻", "迪", "締", "娣" }),
"ding":         ({ "叮", "玎" }),
"dong":  ({ "冬", "棟", "東", "峒" }),
"e":         ({ "額", "萼", "娥", "婀" }),
"er":         ({ "兒" }),
"fang":  ({ "芳", "紡", "舫", "彷", }),
"fei":         ({ "非", "飛", "菲", "斐", "妃", "翡", "霏", "緋" }),
"fen" :  ({ "芬", "紛", "汾", "玢", }),
"feng":  ({ "鳳" }),
"fu"  :  ({ "芙", "芾", "涪", "莩", "馥", "茯", "桴", "紼", }),
"gan" :  ({ "甘", "柑" }),
"gou" :         ({ "苟", "笱" }),
"gu"  :  ({ "姑", "谷", "菇", "沽" }),
"guan":         ({ "官", "綸", "莞", "矜", "涫", "倌" }),
"gui" :         ({ "桂", "歸", "瑰", "閨" }),
"han" :         ({ "寒", "涵", "菡", "邯", "□" }),
"hang":         ({ "行", "杭", "珩", "絎" }),
"he"  :  ({ "荷", "紇", "菏", "合", "河", "禾", "鶴", }),
"heng":         ({ "恆", "珩", "蘅" }),
"hong":  ({ "紅", "虹", "泓" }),
"hu"  :         ({ "狐", "瑚", "琥" }),
"hua" :  ({ "花", "樺", "華", "花", "畫" }),
"hui" :  ({ "慧", "惠", "蕙", "悔", "卉", "彗", "茴" }),
"ji"  :  ({ "紀", "姬", "岌", "吉", "季", "薺", "髻", "笈", "笄", "璣", "霽", "箕" }),
"jia" :         ({ "嘉", "家", "頰", "葭", "佳", "迦", "珈" }),
"jiang": ({ "絳" }),
"jiao":  ({ "嬌", "佼", "姣", "□", "驕", "椒", "湫" }),
"jie" :         ({ "捷", "姐", "潔", "秸", "桔", "頡", "婕" }),
"jin" :         ({ "金", "巾", "晉", "瑾", "矜", "縉", "妗" }),
"jing":  ({ "靜", "晶", "睛", "靖", "靚", "婧", "菁", "□", "景", "凈", "婧" }),
"jiu" :         ({ "久", "九", "玖" }),
"ju"  :  ({ "菊", "橘", "桔", "瞿", "莒" }),
"juan":  ({ "娟", "絹", "鵑", "涓" }),
"jue" :         ({ "絕", "矍", "玨" }),
"jun" :         ({ "郡", "君", "筠", "濬" }),
"ke"  :         ({ "可", "柯", "珂" }),
"lan" :  ({ "蘭", "藍", "嵐", "瀾" }),
"lei" :  ({ "淚", "蕾" }),
"leng":  ({ "冷" }),
"li"  :  ({ "麗", "莉", "梨", "儷", "鸝", "邐", "酈", "俐", "荔", "驪" }),
"lian":         ({ "蓮", "戀", "漣", "憐", "簾" }),
"liang":         ({ "靚", }),
"lin" :  ({ "琳", "淋", "藺" }),
"ling":  ({ "靈", "令", "伶", "玲", "菱", "綾", "泠", "苓", "呤", "□", "鈴", "囹" }),
"long":         ({ "瓏" }),
"lu"  :         ({ "露", "陸" }),
"lv"  :         ({ "綠", "縷" }),
"man" :         ({ "蠻", "曼", "幔", "縵" }),
"mei" :  ({ "梅", "眉", "美", "枚", "玫", "媚", "妹" }),
"min" :  ({ "敏", "玟", "□" }),
"ming":  ({ "茗" }),
"mu"  :         ({ "慕", "睦" }),
"na"  :  ({ "娜", "納" }),
"nan" :  ({ "楠", "男", "囡", "□" }),
"ni"  :         ({ "倪", "妮", "霓", "暱" }),
"ning":         ({ "凝" }),
"pei" :  ({ "佩", "蓓", "□", "□" }),
"ping":  ({ "萍", "屏", "蘋" }),
"qian":  ({ "纖", "倩", "芊", "□" }),
"qiang": ({ "薔" }),
"qiao":         ({ "愀", "巧", "僑", "俏" }),
"qie" :         ({ "怯", "妾" }),
"qin" :  ({ "秦", "琴", "芹", "沁", "芩", "□", "□", "□" }),
"qing":  ({ "晴", "青", "清", "卿", "磬", "箐" }),
"qiong": ({ "瓊", "穹" }),
"qiu" :  ({ "秋", "逑", "□" }),
"que" :         ({ "雀", "鵲" }),
"rao" :         ({ "嬈", "蕘" }),
"rong":         ({ "容", "蓉", "絨" }),
"rou" :  ({ "柔", }),
"ru"  :  ({ "如", "汝", "茹" }),
"rui" :         ({ "芮", "蕊" }),
"ruo" :         ({ "若", "弱" }),
"se"  :         ({ "瑟", "澀" }),
"sha" :         ({ "紗", "霎", "莎" }),
"shan":  ({ "珊", "杉", "姍", "善" }),
"shang": ({ "商", "裳" }),
"sheng": ({ "笙" }),
"shi" :         ({ "師", "詩", "飾", "侍" }),
"shu" :         ({ "書", "梳", "舒" }),
"si"  :         ({ "思", "絲", "斯", "泗" }),
"su"  :  ({ "蘇", "素", "肅" }),
"tao" :         ({ "桃", "滔" }),
"ti"  :         ({ "綈", "緹", "醍" }),
"ting":  ({ "亭", "婷" }),
"wan" :  ({ "宛", "婉", "莞", "綰", "蔓", "琬", "晚" }),
"wei" :  ({ "薇", "維", "尉" }),
"wen" :  ({ "雯", "文", "紋", "汶", "玟", "紊" }),
"wu"  :         ({ "舞", "巫", "蕪", "嫵" }),
"xi"  :  ({ "熙", "茜", "惜", "禧" }),
"xia" :  ({ "夏", "霞", "□" }),
"xian":  ({ "賢", "嫻" }),
"xiang": ({ "香", "湘" }),
"xiao":  ({ "曉", "瀟", "霄", "綃", "筱" }),
"xin" :         ({ "欣", "芯", "心", "昕", "忻", "馨", "鑫" }),
"xing":         ({ "星", "杏" }),
"xiu" :  ({ "秀", "繡", "□" }),
"xu"  :  ({ "緒", "絮" }),
"xue" :         ({ "雪" }),
"xun" :         ({ "尋", "荀", "薰" }),
"xuan":         ({ "軒", "萱", "絢", "璇" }),
"ya"  :         ({ "雅", "丫", "婭" }),
"yan" :  ({ "雁", "煙", "艷", "顏", "燕", "焉", "嫣", "胭", "□", "妍" }),
"yang":         ({ "陽", "央", "鴦" }),
"ye"  :         ({ "葉" }),
"yi"  :  ({ "儀", "衣", "藝", "易", "宜", "頤", "怡" }),
"yin" :         ({ "陰", "音", "殷", "吟", "姻", "茵" }),
"ying":  ({ "英", "盈", "穎", "櫻", "瑛", "縈", "瑩", "鶯", "瓔", "瀅", "纓", "楹", "瀠", "□" }),
"yu"  :  ({ "玉", "雨", "豫", "癒" }),
"yue" :  ({ "月", "悅", "□" }),
"yun" :  ({ "雲", "韻", "蘊", "蕓", "紜", "筠" }),
"zhan":         ({ "綻", "展" }),
"zhao":         ({ "照", "昭" }),
"zhen":  ({ "珍", "貞", "禎" }),
"zheng": ({ "箏" }),
"zhi" :  ({ "織", "脂", "芷", "芝", "稚" }),
"zhou":         ({ "舟", "□", "縐" }),
"zhu" :  ({ "竹", "祝", "珠", "□" }),
"zhuang":({ "莊", "妝" }),
"zi"  :         ({ "子", "紫", "姿", "姊", "恣" }),
]);

mapping m_name = ([
"an"   : ({ "安", "案", "暗", "岸", "鞍" }),
"ang"  : ({ "昂", "盎" }),
"ai"   : ({ "艾", "靄", "皚" }),
"ao"   : ({ "傲", "敖", "翱", "鰲", "遨", "螯", "奧", "囂", "獒" }),
"ba"   : ({ "霸", "巴", "壩", "灞", "魃", "八", "□" }),
"bai"  : ({ "白", "百", "柏", "伯", "敗" }),
"ban"  : ({ "般", "班", "斑", "□" }),
"bang" : ({ "榜", "邦" }),
"bao"  : ({ "寶", "暴", "報", "豹", "雹", "褒", "保", "包", "苞" }),
"bei"  : ({ "北", "貝", "悲", "備" }),
"ben"  : ({ "奔", "本", "賁" }),
"beng" : ({ "崩", "繃" }),
"bi"   : ({ "弼", "蓽", "比", "必", "畢", "壁", "碧", "蔽", "庇" }),
"bian" : ({ "邊", "變", "鞭", "扁", "卞", "弁" }),
"biao" : ({ "標", "彪", "飆", "□", "表", "杓" }),
"bin"  : ({ "斌", "賓", "濱", "彬", "鬢", "繽" }),
"bing" : ({ "兵", "檳", "冰", "炳", "秉" }),
"bo"   : ({ "帛", "伯", "博", "柏", "薄", "泊", "鉑", "搏", "魄" }),
"bu"   : ({ "部", "步", "布" }),
"cai"  : ({ "才", "財", "採", "材", "彩", }),
"can"  : ({ "參", "蠶", "燦", "璨", "粲" }),
"cang" : ({ "藏", "蒼", "倉", "滄" }),
"cao"  : ({ "草", "操" }),
"ce"   : ({ "策", "冊" }),
"cha"  : ({ "差", "查", "察", "叉", "詫", "岔" }),
"chai" : ({ "柴", "差", "豺" }),
"chan" : ({ "產", "纏", "闡", "蟬", "蟾", "懺", "孱" }),
"chang": ({ "長", "常", "昌", "暢", "悵", "猖", "敞" }),
"chao" : ({ "超", "朝", "潮", "巢", "綽", "晁" }),
"chen" : ({ "沉", "臣", "塵", "辰", "趁", "晨", "諶", "宸" }),
"cheng": ({ "乘", "成", "承", "誠", "呈", "澄", "懲", "丞" }),
"chi"  : ({ "池", "尺", "持", "馳", "墀", "恥", "翅", "熾", "叱", "弛", "蚩", "魑" }),
"chong": ({ "沖", "充", "寵", "崇", "忡", "蟲" }),
"chou" : ({ "抽", "愁", "醜", "仇", "綢", "酬", "稠", "籌" }),
"chu"  : ({ "楚", "初", "處", "儲", "杵", "褚" }),
"chuan": ({ "船", "川", "釧" }),
"chuang":({ "窗", "闖" }),
"chui" : ({ "吹", "垂", "錘" }),
"chuo" : ({ "戳", "綽", "輟" }),
"chun" : ({ "椿", "春", "純", "醇", "淳" }),
"ci"   : ({ "刺", "詞", "慈", "茨", "茲" }),
"cong" : ({ "從", "聰", "匆", "琮" }),
"cu"   : ({ "促", "粗", "簇", "卒" }),
"cuan" : ({ "竄", "篡" }),
"cui"  : ({ "崔", "脆", "摧", "萃", "璀" }),
"cuo"  : ({ "錯", "挫", "措", "蹉" }),
"cun"  : ({ "存", "村", "寸", "忖" }),
"da"   : ({ "大", "達", "韃", "靼" }),
"dai"  : ({ "代", "呆", "歹", "岱", "殆", "駘" }),
"dan"  : ({ "淡", "鄲", "單", "丹", "旦", "膽", "誕", "憚", "澹" }),
"dang" : ({ "鐺", "當", "盪" }),
"dao"  : ({ "道", "刀", "盜" }),
"de"   : ({ "德" }),
"deng" : ({ "等", "登", "燈", "鐙" }),
"di"   : ({ "迪", "荻", "笛", "弟", "敵", "帝", "狄", "堤", "諦", "柢", "砥" }),
"dian" : ({ "點", "典", "顛", "殿", "甸", "滇" }),
"die"  : ({ "疊", "碟", "蝶", "迭" }),
"ding" : ({ "玎", "叮", "頂", "定", "丁", "鼎", "錠", "町" }),
"dong" : ({ "東", "棟", "峒" }),
"dou"  : ({ "都", "鬥", "兜", "豆", "蚪" }),
"du"   : ({ "度", "毒", "獨", "督", "渡", "鍍", "妒", "篤", "犢" }),
"duan" : ({ "斷", "段", "短", "端", "鍛", "緞", "□" }),
"dui"  : ({ "隊", "對", "憝" }),
"duo"  : ({ "多", "奪", "朵", "綞", "墮" }),
"dun"  : ({ "頓", "敦", "墩", "蹲", "盾", "遁", "囤" }),
"e"    : ({ "額", "惡", "厄", "愕", "鄂", "顎" }),
"er"   : ({ "兒", "而", "二", "爾", "邇", "珥" }),
"fa"   : ({ "法", "琺", "乏", "閥", "發", "□", "伐", "筏", "琺", }),
"fan"  : ({ "范", "泛", "凡", "帆", "樊", "梵", "幡" }),
"fang" : ({ "舫", "房", "方" }),
"fen"  : ({ "奮", "忿", "憤", "汾", "分", "紛", "憤", "焚", }),
"feng" : ({ "封", "豐", "風", "奉", "逢", "峰", "鋒", "楓", "烽" }),
"fo"   : ({ "佛" }),
"fou"  : ({ "否" }),
"fu"   : ({ "福", "伏", "富", "撫", "輔", "傅", "賦", "覆", "甫", "釜", "縛", "孚", "茯", "夫" }),
"gai"  : ({ "改", "蓋", "丐" }),
"gan"  : ({ "甘", "幹", "桿", "贛", "乾", "泔" }),
"gang" : ({ "剛", "鋼", "崗", "綱", "岡", "罡" }),
"gao"  : ({ "高", "膏", "誥", "皋", "鎬", "郜" }),
"ge"   : ({ "哥", "格", "革", "戈", "舸" }),
"gen"  : ({ "根", "跟", "艮" }),
"geng" : ({ "更", "梗", "耿", "庚" }),
"gou"  : ({ "笱", "苟", "勾", "垢", "枸", "篝" }),
"gu"   : ({ "沽", "古", "顧", "股", "固", "谷", "孤", "蠱", "牯", "鴣", "鵠", "崮"}),
"gua"  : ({ "瓜", "卦" }),
"guai" : ({ "怪", "拐", "乖" }),
"guan" : ({ "倌", "官", "關", "觀", "冠", "貫" }),
"gui"  : ({ "貴", "歸", "桂", "鬼", "癸", "圭", "傀", "檜" }),
"guo"  : ({ "國", "果", "裹", "槨" }),
"gun"  : ({ "棍", "袞" }),
"hai"  : ({ "海", "孩", "亥" }),
"han"  : ({ "□", "邯", "涵", "寒", "漢", "韓", "含", "汗", "旱", "函", "翰", "瀚" }),
"hang" : ({ "珩", "杭", "行", "夯" }),
"hao"  : ({ "好", "毫", "豪", "郝", "鎬", "浩", "皓", "昊" }),
"he"   : ({ "禾", "合", "賀", "褐", "鶴", "闔", "閡", "涸" }),
"hen"  : ({ "恨", "狠", "痕", }),
"heng" : ({ "衡", "恆", "蘅", "珩", "桁" }),
"hong" : ({ "宏", "洪", "鴻", "弘", "泓", "閎" }),
"hou"  : ({ "後", "候", "厚", "侯" }),
"hu"   : ({ "戶", "護", "虎", "狐", "瑚", "滸", "琥", "鵠" }),
"hua"  : ({ "華", "化", "畫", "樺", "驊" }),
"huan" : ({ "還", "環", "歡", "渙", "奐", "幻", "煥", "桓", "浣", "洹" }),
"huang": ({ "黃", "皇", "晃", "簧", "煌", "恍", "凰", "璜", "徨", "潢" }),
"huo"  : ({ "火", "禍", "惑", "豁" }),
"hun"  : ({ "混", "昏", "魂", "琿" }),
"ji"   : ({ "岌", "計", "濟", "極", "集", "擊", "績", "吉", "輯", "祭", "冀", "基", "際", "寂", "暨", "戟" }),
"jia"  : ({ "迦", "珈", "佳", "葭", "家", "嘉", "賈", "稼", "枷" }),
"jian" : ({ "建", "劍", "兼", "鑒", "澗", "健", "薦", "柬", "諫", "翦", "緘", "堅" }),
"jiang": ({ "絳", "將", "江", "匠", "韁" }),
"jiao" : ({ "湫", "驕", "交", "角", "焦", "矯", "狡", "窖", "僥", "佼", "蛟" }),
"jie"  : ({ "桔", "節", "解", "界", "傑", "介", "捷", "皆", "劫", "竭", "桀", "頡" }),
"jin"  : ({ "勁", "金", "進", "今", "僅", "盡", "禁", "錦", "津", "巾", "謹", "晉", "瑾", "靳", "縉" }),
"jing" : ({ "靖", "京", "景", "經", "敬", "荊", "井", "警", "徑", "勁" }),
"jiong": ({ "炯", "窘" }),
"ju"   : ({ "局", "舉", "具", "居", "巨", "聚", "矩", "菊", "桔", "櫃", "颶", "駒", "炬", "鉅" }),
"juan" : ({ "鄄", "圈", "雋" }),
"jue"  : ({ "玨", "絕", "決", "覺", "爵", "厥" }),
"jun"  : ({ "軍", "均", "郡", "鈞", "君", "俊", "峻", "竣", "駿", "雋" }),
"kai"  : ({ "開", "凱", "楷", "愷", "鎧", "鍇", "剴" }),
"kan"  : ({ "刊", "堪", "坎" }),
"kang" : ({ "康", "亢", "慷", "抗", "伉", }),
"kao"  : ({ "考" }),
"ke"   : ({ "珂", "柯", "可", "坷", "軻" }),
"kong" : ({ "空", "孔", "崆" }),
"kou"  : ({ "寇", "蔻" }),
"ku"   : ({ "庫", "枯", "窟", "□" }),
"kuai" : ({ "膾", "獪", "儈", "蒯" }), 
"kuang": ({ "匡", "況", "狂", "誆", "曠", "夼" }),
"kuo"  : ({ "闊", "括", "擴" }),
"kun"  : ({ "困", "昆", "坤", "琨" }),
"la"   : ({ "臘", "喇" }),
"lai"  : ({ "萊", "籟", "瀨", "崍" }),
"lan"  : ({ "蘭", "藍", "讕", "嵐", "瀾", "斕" }),
"lang" : ({ "郎", "朗", "浪", "狼", "琅", "榔", "鋃", "閬" }),
"le"   : ({ "樂", "勒" }),
"lei"  : ({ "雷", "累", "壘", "磊", "儡", }),
"leng" : ({ "冷", "楞" }),
"li"   : ({ "禮", "利", "力", "厲", "立", "歷", "隸", "黎", "勵", "靂", "戾" }),
"lian" : ({ "連", "廉", "簾", "練", "煉" }),
"liang": ({ "樑", "良", "亮", "諒", "椋", "涼", "量" }),
"lie"  : ({ "列", "烈", "獵" }),
"lin"  : ({ "林", "臨", "凜", "麟", "霖", "嶙", "鄰" }),
"ling" : ({ "令", "靈", "凌", "陵", "翎", "棱", "嶺", "領" }),
"long" : ({ "龍", "壟", "隆", "瓏", "隴", "瀧" }),
"lou"  : ({ "樓", "僂", "婁" }),
"lu"   : ({ "祿", "路", "錄", "蘆", "碌", "擄" }),
"luan" : ({ "亂", "孿", "攣", "巒", "欒", "鑾" }),
"luo"  : ({ "羅", "駱", "螺", "烙", "絡", "洛", "珞" }),
"lun"  : ({ "倫", "侖", "綸", "圇" }),
"lv"   : ({ "綠", "律", "旅", "履" }),
"man"  : ({ "曼", "幔" }),
"mang" : ({ "芒", "氓", "莽", "蟒", "邙" }),
"mao"  : ({ "毛", "冒", "矛", "茅", "茂", "卯", "□", "瑁" }),
"meng" : ({ "猛", "夢", "蒙", "萌", "朦", "蜢", "氓", "虻", "□", }),
"mian" : ({ "棉", "勉", "緬", "冕" }),
"min"  : ({ "民", "閩", "閔", "憫", "泯", "岷", "敏", "皿", }),
"ming" : ({ "鳴", "明", "名", "銘", "冥", "螟", "命", "茗", "瞑", "溟" }),
"mo"   : ({ "模", "莫", "摩", "末", "魔", "磨", "漠", "陌", "茉" }),
"mou"  : ({ "牟", "侔" }),
"mu"   : ({ "睦", "慕", "目", "木", "幕", "牧", "沐" }),
"nan"  : ({ "南", "難", "□" }),
"nao"  : ({ "惱", "瑙", "淖", "鐃" }),
"nu"   : ({ "努", "怒", "駑" }),
"ou"   : ({ "歐", "鷗" }),
"peng" : ({ "朋", "鵬", "澎" }),
"piao" : ({ "飄", "縹" }),
"pin"  : ({ "品", "貧" }),
"ping" : ({ "平", "屏", "憑", "□", "評" }),
"po"   : ({ "破", "迫", "坡", "泊", "魄", "珀", "陂" }),
"pu"   : ({ "普", "浦", "樸", "蒲", "圃", "譜", "溥", "璞", "濮" }),
"qi"   : ({ "其", "器", "七", "奇", "齊", "旗", "豈", "戚", "契" }),
"qian" : ({ "千", "潛", "簽", "淺", "乾", "謙", "黔", "歉", "譴", "前" }),
"qiang": ({ "強", "羌", "鏘", "戕" }),
"qiao" : ({ "巧", "翹", "譙", "竅", "峭", "樵", "愀" }),
"qin"  : ({ "勤", "琴", "秦", "欽", "芹" }),
"qing" : ({ "青", "卿", "慶", "晴", "擎" }),
"qiu"  : ({ "求", "秋", "丘", "囚", "酋", "虯", "泅", "湫", "逑", "俅" }),
"qu"   : ({ "曲", "區", "去", "屈", "嶇", "戌" }),
"quan" : ({ "全", "權", "拳", "勸", "泉", "荃", "銓" }),
"que"  : ({ "闕", "闋" }),
"qun"  : ({ "群", "麇" }),
"ran"  : ({ "然", "冉", "髯", "□", "燃", "染" }),
"rang" : ({ "讓" }),
"rao"  : ({ "繞", "擾" }),
"ren"  : ({ "任", "忍", "紉", "仁", "刃", "韌", "壬" }),
"rong" : ({ "容", "榮", "融", "戎", "榕" }),
"ru"   : ({ "如", "儒" }),
"run"  : ({ "潤", "閏" }),
"sang" : ({ "桑", "喪" }),
"sen"  : ({ "森" }),
"sha"  : ({ "霎", "沙", "煞", "杉", "挲" }),
"shan" : ({ "杉", "山", "善", "扇", "衫", "單", "汕", "繕", "贍" }),
"shang": ({ "商", "上", "尚" }),
"shao" : ({ "少", "紹", "梢", "劭", "韶", "杓" }),
"she"  : ({ "社", "設", "射", "舍", "赦", "奢", "麝", "猞" }),
"shen" : ({ "深", "神", "甚", "審", "申", "紳", "慎" }),
"sheng": ({ "生", "聖", "勝", "升", "盛", "甥" }),
"shi"  : ({ "市", "石", "時", "實", "施", "適", "世", "師", "示", "始", "勢", "史", "識", "詩", "釋", "誓", "獅", "弒", "峙", "螫" }),
"shou" : ({ "壽", "守", "狩" }),
"shu"  : ({ "舒", "書", "樹", "叔", "術", "殊", "疏", "恕", "庶" }),
"shun" : ({ "順", "舜" }),
"si"   : ({ "泗", "斯", "思", "四", "司" }),
"song" : ({ "鬆", "頌", "訟", "嵩", "誦", "崧" }),
"su"   : ({ "肅", "素", "俗", "塑" }),
"sun"  : ({ "孫", "隼", "猻" }),
"tai"  : ({ "台", "泰" }),
"tan"  : ({ "探", "檀", "忐", "曇" }),
"tang" : ({ "堂", "唐", "湯", "棠" }),
"tao"  : ({ "桃", "濤", "滔", "洮" }),
"teng" : ({ "騰", "滕" }),
"tong" : ({ "同", "通", "統", "佟", "童", "桐", "峒", "彤", "瞳", "潼" }),
"tu"   : ({ "圖", "土", "徒" }),
"tun"  : ({ "屯", "豚" }),
"wai"  : ({ "外", "崴" }),
"wan"  : ({ "萬", "頑", "宛", "丸", "皖", "莞" }),
"wang" : ({ "亡", "旺", "芒", "妄", "惘" }),
"wu"   : ({ "武", "烏", "伍", "勿", "惡", "午", "吾", "霧", "梧", "忤", "戊", "鶩", "騖" }),
"xi"   : ({ "喜", "洗", "希", "席", "習", "悉", "夕", "溪", "析", "棲", "犀", "羲", "皙" }),
"xia"  : ({ "夏", "俠", "峽", "匣", "廈" }),
"xian" : ({ "先", "賢", "憲", "咸", "涎", "閒" }),
"xiang": ({ "向", "相", "襄", "翔" }),
"xiao" : ({ "孝", "瀟", "曉", "嘯", "霄", "逍", "囂", "驍", "梟", "哮", "魈", "效", "小" }),
"xie"  : ({ "邪", "攜", "諧", "邂" }),
"xin"  : ({ "鑫", "馨", "昕", "信", "辛", "歆" }),
"xing" : ({ "興", "星", "杏", "行" }),
"xiong": ({ "雄", "兇" }),
"xu"   : ({ "需", "須", "虛", "敘", "序", "詡", "緒", "絮", "旭", "栩", "胥", "煦", "戌" }),
"xuan" : ({ "璇", "軒", "旋", "宣", "玄", "炫", "□" }),
"xue"  : ({ "雪", "血" }),
"xun"  : ({ "訊", "勛", "訓", "尋", "迅", "詢", "遜", "循", "巡", "旬", "荀" }),
"yan"  : ({ "嚴", "言", "延", "炎", "巖", "閻", "堰", "厭", "燄", "衍", "硯", "偃" }),
"yang" : ({ "陽", "洋", "央", "揚", "煬" }),
"yao"  : ({ "遙", "耀", "夭", "妖", "曜" }),
"ye"   : ({ "葉", "野", "燁", "鄴" }),
"yi"   : ({ "義", "易", "宜", "頤", "意", "異", "遺", "亦", "翼", "倚", "逸", "伊", "夷", "毅", "奕", "弈", "翌" }),
"yin"  : ({ "殷", "音", "印", "胤" }),
"ying" : ({ "英", "應", "贏", "鷹", "熒" }),
"yong" : ({ "勇", "庸", "永", "詠", "雍", "甬", "恿", "擁" }),
"you"  : ({ "有", "優", "友", "遊", "憂", "幽", "佑", "悠", "攸" }),
"yu"   : ({ "豫", "玉", "宇", "育", "予", "語", "魚", "裕", "愚", "羽", "御", "瑜", "迂" }),
"yun"  : ({ "運", "雲", "允", "韻", "勻", "昀" }),
"zai"  : ({ "災", "哉", "宰" }),
"zang" : ({ "藏", "奘" }),
"zhai" : ({ "翟", "齋" }),
"zhan" : ({ "綻", "戰", "瞻", "斬", "輾" }),
"zhen" : ({ "真", "鎮", "震", "振", "臻", "偵" }),
"zheng": ({ "政", "正", "拯", "錚", "徵", "征" }),
"zhi"  : ({ "智", "知", "執", "至", "志", "止", "致", "摯", "炙", "之" }),
"zhong": ({ "忠", "重", "終", "仲", "中" }),
"zhu"  : ({ "諸", "鑄", "逐", "竹", "燭", "炷", "渚", "褚" }),
"zhuan": ({ "篆", "轉" }),
"zhuang":({ "壯", "莊", "狀", "樁", }),
"zhuo" : ({ "灼", "濁", "卓", "拙", "酌", "琢", "濯", "茁" }),
"zhun" : ({ "準", "諄" }),
"zi"   : ({ "紫", "子", "茲", "孜", "梓" }),
"zong" : ({ "宗" }),
"zu"   : ({ "族", "祖", "卒" }),
]);

// End Of File.


