// This program is a part of NITAN MudLIB

mapping region_names = ([
        "register" : "混沌屆",
        "baituo"   : "西域白駝山",
        "beijing"  : "北京城",
        "changan"  : "長安城",
        "city"     : "揚州城",
        "city2"    : "北京城",
        "city3"    : "成都城",
        "chengdu"  : "成都城",
        "dali"     : "雲南大理城",
        "death"    : "鬼門關",
        "emei"     : "四川峨嵋",
        "foshan"   : "廣東佛山",
        "fuzhou"   : "福建福州",
        "gaochang"  : "高昌",
        "gaibang"  : "丐幫所在地",
        "guanwai"  : "關外境內",
        "guiyun"   : "歸雲莊",
        "gumu"     : "古墓派境內",
        "hangzhou" : "杭州城",
        "heimuya"  : "黑木崖境內",
        "hengshan" : "恆山境內",
        "henshan"  : "衡山境內",
        "huanggon" : "皇宮",
        "huanghe"  : "黃河邊",
        "huashan"  : "華山境內",
        "hudie"    : "蝴蝶谷",
        "jinshe"   : "華山金蛇洞",
        "jingzhou" : "荊州境內",
        "jianzhong": "劍冢",
        "lingjiu"  : "靈鷲宮境內",
        "lingzhou" : "靈州城",
        "luoyang"  : "洛陽境內",
        "lanzhou"  : "蘭州境內",
        "jueqing" : "絕情谷",
        "jiaxing" : "嘉興",
        "kunlun"  : "崑崙",
        "kaifeng"  : "開封境內",
        "kunming"  : "昆明境內",
        "meizhuang": "梅莊",
        "mingjiao" : "明教境內",
        "pk"           : "屠人場",
        "qingcheng": "青城山境內",
        "quanzhen" : "全真派境內",
        "shaolin"  : "少林寺境內",
        "shenlong" : "神龍島境內",
        "songshan" : "嵩山境內",
        "suzhou"   : "蘇州城",
        "taishan"  : "泰山境內",
        "taohua"   : "桃花島境內",
        "tianlongsi": "天龍寺境內",
        "tulong"   : "萬安寺或者王盤山島",
        "village"  : "華山村",
        "wanjiegu" : "萬劫谷",
        "wizard"   : "仙界",
        "wudang"   : "武當山境內",
        "wuxi"     : "無錫",
        "xiakedao" : "俠客島境內",
        "xiangyang": "襄陽城",
        "xiaoyao"  : "逍遙派境內",
        "xingxiu"  : "星宿派境內",
        "dragon"   : "西域",
        "xuedao"   : "血刀門境內",
        "xueshan"  : "雪山寺",
        "yangziwu" : "燕子鎢",
        "yuanyue" : "圓月山莊",
        "zhongzhou": "中州境內",
        "sdxl"     : "劍冢",
        "tangmen"  : "四川唐門境內",
        "wudu"    : "五毒教",
        "quanzhou"   : "泉州",
        "newbie"  : "古村",
]);

mapping place = ([
        "city"     : ({ 
                "揚州郊外", ({ 
                        "/d/city/jiaowai1",
                        "/d/city/jiaowai2",
                        "/d/city/jiaowai3",
                        "/d/city/jiaowai4",
                        "/d/city/jiaowai5",
                        "/d/city/jiaowai6",
                        "/d/city/jiaowai7",
                        "/d/city/jiaowai8",
                        "/d/city/jiaowai9",
                        "/d/city/jiaowai10",
                        "/d/city/jiaowai11",
                        "/d/city/jiaowai12",
                        "/d/city/jiaowai13"
                 }),}),
        "guiyun"   : ({ 
                "太湖一帶", ({ 
                        "/d/guiyun/shulin1",
                        "/d/guiyun/shulin2",
                        "/d/guiyun/shulin3",
                        "/d/guiyun/shulin4",
                        "/d/guiyun/shulin5",
                        "/d/guiyun/shanlu1",
                        "/d/guiyun/shanlu2",
                        "/d/guiyun/tiandi"
                 }),}),
        "huanghe"   : ({ 
                "黃河一帶", ({ 
                        "/d/huanghe/caodi1",
                        "/d/huanghe/caodi2",
                        "/d/huanghe/shulin1",
                        "/d/huanghe/shulin2",
                        "/d/huanghe/shulin3",
                        "/d/huanghe/shulin4",
                        "/d/huanghe/shulin5",
                        "/d/huanghe/shulin6",
                        "/d/huanghe/tiandi1",
                        "/d/huanghe/tiandi2",
                        "/d/huanghe/tiandi3",
                        "/d/huanghe/tiandi4",
                        "/d/huanghe/huanghe1",
                        "/d/huanghe/huanghe2",
                        "/d/huanghe/huanghe3",
                        "/d/huanghe/huanghe4",
                        "/d/huanghe/huanghe5",
                        "/d/huanghe/huanghe6",
                        "/d/huanghe/huanghe7",
                        "/d/huanghe/huanghe8",
                        "/d/huanghe/bingcao",
                        "/d/huanghe/dacaigou",
                        "/d/huanghe/guchangcheng",
                        "/d/huanghe/gulang",
                        "/d/huanghe/hongshanxia",
                        "/d/huanghe/hetao",
                        "/d/huanghe/huanghe_1",
                        "/d/huanghe/huanghe_2",
                        "/d/huanghe/huanghe_3",
                        "/d/huanghe/huangtu",
                        "/d/huanghe/liupanshan",
                        "/d/huanghe/qingcheng",
                        "/d/huanghe/shimen",
                        "/d/huanghe/shixiazi",
                        "/d/huanghe/tumenzi",
                        "/d/huanghe/weifen",
                        "/d/huanghe/wufosi",
                        "/d/huanghe/wuqiao",
                        "/d/huanghe/xiaojiaqiao",
                        "/d/huanghe/yinpanshui"
                 }),}),

        "guanwai"   : ({
                "長白山上", ({ 
                        "/d/guanwai/milin1",
                        "/d/guanwai/milin2",
                        "/d/guanwai/milin3",
                        "/d/guanwai/heifengkou",
                        "/d/guanwai/xiaotianchi",
                        "/d/guanwai/pubu",
                        "/d/guanwai/damen",
                        "/d/guanwai/longmen",
                        "/d/guanwai/tianhuo",
                        "/d/guanwai/huagai",
                        "/d/guanwai/tianchi1",
                        "/d/guanwai/tianchi2",
                        "/d/guanwai/baiyun",
                        "/d/guanwai/luming",
                        "/d/guanwai/famu",
                        "/d/guanwai/yuzhu",
                        "/d/guanwai/tiyun"
                 }),}),

        "dali"      : ({
                "大理郊外", ({ 
                        "/d/dali/atoubu",
                    "/d/dali/badidian",
                    "/d/dali/banshan",
                    "/d/dali/bijishan",
                    "/d/dali/biluoshan",
                    "/d/dali/biluoxueshan",
                    "/d/dali/buxiongbu",
                    "/d/dali/cangshan",
                    "/d/dali/cangshanlu1",
                    "/d/dali/cangshanzhong",
                    "/d/dali/caopo",
                    "/d/dali/chahuashan1",
                    "/d/dali/chahuashan2",
                    "/d/dali/chahuashan3",
                    "/d/dali/chahuashan4",
                    "/d/dali/chahuashan5",
                    "/d/dali/chahuashan6",
                    "/d/dali/changhu",
                    "/d/dali/dadieshui",
                    "/d/dali/daduhe",
                    "/d/dali/dalinorth",
                    "/d/dali/dasenlin",
                    "/d/dali/dehuabei",
                    "/d/dali/dianchi",
                    "/d/dali/ershuiqiao",
                    "/d/dali/feilihu",
                    "/d/dali/feilihueast",
                    "/d/dali/feilihusouth",
                    "/d/dali/gaolishan1",
                    "/d/dali/gaolishan2",
                    "/d/dali/gelucheng",
                    "/d/dali/gudao",
                    "/d/dali/hebian",
                    "/d/dali/heilongling",
                    "/d/dali/heisenlin",
                    "/d/dali/heshang",
                    "/d/dali/hole",
                    "/d/dali/hongsheng",
                    "/d/dali/hongsheng",
                    "/d/dali/hongsheng1",
                    "/d/dali/hongsheng2",
                    "/d/dali/hongsheng3",
                    "/d/dali/hongsheng4",
                    "/d/dali/hudiequan",
                    "/d/dali/jinzhihe",
                    "/d/dali/luojiadian",
                    "/d/dali/lushuieast",
                    "/d/dali/luyuxi",
                    "/d/dali/milin",
                    "/d/dali/minadian",
                    "/d/dali/nongtian1",
                    "/d/dali/nongtian2",
                    "/d/dali/nongtian3",
                    "/d/dali/nongtian4",
                    "/d/dali/nongtian5",
                    "/d/dali/qingzhulin",
                    "/d/dali/road1",
                    "/d/dali/road2",
                    "/d/dali/road3",
                    "/d/dali/road4",
                    "/d/dali/road5",
                    "/d/dali/sanglin",
                    "/d/dali/shanjian",
                    "/d/dali/shanlin",
                    "/d/dali/shanlu1",
                    "/d/dali/shanlu2",
                    "/d/dali/shanlu3",
                    "/d/dali/shanlu4",
                    "/d/dali/shanlu5",
                    "/d/dali/shanlu6",
                    "/d/dali/shanlu7",
                    "/d/dali/shanlu8",
                    "/d/dali/shilin",
                    "/d/dali/shilin1",
                    "/d/dali/shilin2",
                    "/d/dali/shuangheqiao",
                    "/d/dali/shuitian",
                    "/d/dali/shulinwai",
                    "/d/dali/tianweijing",
                    "/d/dali/titian1",
                    "/d/dali/wuding",
                    "/d/dali/wumeng",
                    "/d/dali/xingyunhu",
                    "/d/dali/yanan1",
                    "/d/dali/yanan2",
                    "/d/dali/yanchi1",
                    "/d/dali/yanchi2",
                    "/d/dali/yanchi3",
                    "/d/dali/yixibu",
                    "/d/dali/yulin",
                    "/d/dali/yuxiashan",
                    "/d/dali/zhulin",
                    "/d/dali/zhulin2"
                 }),}),


        "foshan"   : ({
                "佛山一帶", ({ 
                        "/d/foshan/nanling",
                    "/d/foshan/road1",
                    "/d/foshan/road2",
                    "/d/foshan/road3",
                    "/d/foshan/road4",
                    "/d/foshan/road5",
                    "/d/foshan/road6",
                    "/d/foshan/road7",
                    "/d/foshan/road8",
                    "/d/foshan/road9",
                    "/d/foshan/road10",
                    "/d/foshan/road11",
                    "/d/foshan/road12",
                    "/d/foshan/road13",
                    "/d/foshan/road14"
                 }),}),
        "fuzhou"   : ({
                "福州一帶", ({ "/d/fuzhou/fzroad1",
                    "/d/fuzhou/fzroad2",
                    "/d/fuzhou/fzroad3",
                    "/d/fuzhou/fzroad4",
                    "/d/fuzhou/fzroad5",
                    "/d/fuzhou/fzroad6",
                    "/d/fuzhou/fzroad7",
                    "/d/fuzhou/fzroad8",
                    "/d/fuzhou/fzroad9",
                    "/d/fuzhou/fzroad10",
                    "/d/fuzhou/fzroad11",
                    "/d/fuzhou/gushan",
                    "/d/fuzhou/haigang",
                    "/d/fuzhou/pingshan",
                    "/d/fuzhou/puxian",
                    "/d/fuzhou/shulin",
                    "/d/fuzhou/wushan",
                    "/d/fuzhou/wuyishan1",
                    "/d/fuzhou/wuyishan2",
                    "/d/fuzhou/wuyishan3",
                    "/d/fuzhou/wuyishan4",
                    "/d/fuzhou/wuyishan5",
                    "/d/fuzhou/wuyishan6",
                    "/d/fuzhou/wuyishan7",
                    "/d/fuzhou/yushan"
                 }),}),
        "hengshan"  : ({
                "恆山一帶", ({ "/d/hengshan/cuiping1",
                    "/d/hengshan/cuiping2",
                    "/d/hengshan/cuipinggu1",
                    "/d/hengshan/cuipinggu2",
                    "/d/hengshan/daziling",
                    "/d/hengshan/guolaoling",
                    "/d/hengshan/hufengkou",
                    "/d/hengshan/jinlongxia",
                    "/d/hengshan/shandao1",
                    "/d/hengshan/shandao2",
                    "/d/hengshan/tongyuangu",
                    "/d/hengshan/xuangengsong",
                    "/d/hengshan/yunge",
                    "/d/hengshan/yuyang",
                    "/d/hengshan/zhandao",
                    "/d/hengshan/zhanqiao"
                 }),}),
        "hengshan"   : ({
                "衡山一帶", ({ "/d/henshan/banshan",
                    "/d/henshan/chidifeng",
                    "/d/henshan/denggaotai",
                    "/d/henshan/heishatan",
                    "/d/henshan/hsroad1",
                    "/d/henshan/hsroad2",
                    "/d/henshan/hsroad3",
                    "/d/henshan/hsroad4",
                    "/d/henshan/hsroad5",
                    "/d/henshan/hsroad6",
                    "/d/henshan/hsroad7",
                    "/d/henshan/hsroad8",
                    "/d/henshan/hsroad9",
                    "/d/henshan/lingxingmen",
                    "/d/henshan/liuyunping",
                    "/d/henshan/mojingtai",
                    "/d/henshan/nantian",
                    "/d/henshan/shanjian",
                    "/d/henshan/shanlu1",
                    "/d/henshan/shanlu2",
                    "/d/henshan/shanlu3",
                    "/d/henshan/shanlu4",
                    "/d/henshan/shanlu5",
                    "/d/henshan/shanlu6",
                    "/d/henshan/shanlu7",
                    "/d/henshan/shanlu8",
                    "/d/henshan/shanlu9",
                    "/d/henshan/shanlu10",
                    "/d/henshan/shanlu11",
                    "/d/henshan/shanlu12",
                    "/d/henshan/shanlu13",
                    "/d/henshan/shanlu14",
                    "/d/henshan/shiziyan",
                    "/d/henshan/shuiliandong",
                    "/d/henshan/tianzhu",
                    "/d/henshan/yubeiting",
                    "/d/henshan/zhengchuan",
                    "/d/henshan/zhongting",
                    "/d/henshan/zhurongfeng"
                 }),}),


        "huashan" :  ({
                "華山一帶", ({ "/d/huashan/baichi",
                    "/d/huashan/canglong",
                    "/d/huashan/chaopath1",
                    "/d/huashan/chaopath2",
                    "/d/huashan/chengxiang",
                    "/d/huashan/huixinshi",
                    "/d/huashan/husun",
                    "/d/huashan/jiashan",
                    "/d/huashan/jinsuo",
                    "/d/huashan/jzroad1",
                    "/d/huashan/jzroad2",
                    "/d/huashan/jzroad3",
                    "/d/huashan/jzroad4",
                    "/d/huashan/jzroad5",
                    "/d/huashan/laojun",
                    "/d/huashan/lianhua",
                    "/d/huashan/lianpath1",
                    "/d/huashan/lianpath2",
                    "/d/huashan/path1",
                    "/d/huashan/pingdi",
                    "/d/huashan/pingxinshi",
                    "/d/huashan/qianchi",
                    "/d/huashan/qingke",
                    "/d/huashan/shaluo",
                    "/d/huashan/shangtianti",
                    "/d/huashan/shangu",
                    "/d/huashan/shanhongpb",
                    "/d/huashan/sheshen",
                    "/d/huashan/siguoya",
                    "/d/huashan/songlin1",
                    "/d/huashan/songlin2",
                    "/d/huashan/songlin3",
                    "/d/huashan/songlin4",
                    "/d/huashan/xiaolu1",
                    "/d/huashan/xiaolu2",
                    "/d/huashan/xuanya",
                    "/d/huashan/yunmen",
                    "/d/huashan/yuntai",
                    "/d/huashan/yunu",
                    "/d/huashan/yunupath1",
                    "/d/huashan/yunupath2",
                    "/d/huashan/zhandao",
                    "/d/huashan/ziqitai"
                 }),}),
        "qingcheng" :  ({
                "青城山上", ({ "/d/qingcheng/gulongqiao",
                      "/d/qingcheng/maguchi",
                      "/d/qingcheng/path1",
                      "/d/qingcheng/path2",
                      "/d/qingcheng/qcroad1",
                      "/d/qingcheng/qcroad2",
                      "/d/qingcheng/qcroad3",
                      "/d/qingcheng/sandaoshi",
                      "/d/qingcheng/sanwanjiudao",
                      "/d/qingcheng/tianran",
                      "/d/qingcheng/tianshidong",
                      "/d/qingcheng/xiaoqiao",
                      "/d/qingcheng/yinxing",
                      "/d/qingcheng/yuanyangjing",
                      "/d/qingcheng/zhuhezhuang",
                      "/d/qingcheng/zushidian"
                 }),}),
        "lingzhou" : ({ 
                "靈州一帶", ({ "/d/lingzhou/chiling",
                    "/d/lingzhou/dalu",
                    "/d/lingzhou/deling",
                    "/d/lingzhou/gongling",
                    "/d/lingzhou/huangyangtan",
                    "/d/lingzhou/kongdi",
                    "/d/lingzhou/luorilin1",
                    "/d/lingzhou/luorilin2",
                    "/d/lingzhou/mingshazhou",
                    "/d/lingzhou/qingtongxia",
                    "/d/lingzhou/qingxinquan",
                    "/d/lingzhou/tulu",
                    "/d/lingzhou/wangling",
                    "/d/lingzhou/xiaoba",
                    "/d/lingzhou/xiaolu1",
                    "/d/lingzhou/xiaolu2",
                    "/d/lingzhou/xiaolu3",
                    "/d/lingzhou/xuanhebao"
                 }),}),

        "quanzhen"   : ({
                "終南山一帶", ({ "/d/quanzhen/baishulin1",
                    "/d/quanzhen/baishulin2",
                    "/d/quanzhen/baishulin3",
                    "/d/quanzhen/baishulin4",
                    "/d/quanzhen/banshanting",
                    "/d/quanzhen/cuipingfeng",
                    "/d/quanzhen/cuipinggu",
                    "/d/quanzhen/cundaota1",
                    "/d/quanzhen/cundaota2",
                    "/d/quanzhen/cundaota3",
                    "/d/quanzhen/cundaota4",
                    "/d/quanzhen/fangzhenqiao",
                    "/d/quanzhen/guanritai",
                    "/d/quanzhen/shanjiao",
                    "/d/quanzhen/shanlu1",
                    "/d/quanzhen/shanlu2",
                    "/d/quanzhen/shanlu3",
                    "/d/quanzhen/shanlu4",
                    "/d/quanzhen/shijie1",
                    "/d/quanzhen/shijie2",
                    "/d/quanzhen/shijie3",
                    "/d/quanzhen/shijie4",
                    "/d/quanzhen/shijie5",
                    "/d/quanzhen/shijie6",
                    "/d/quanzhen/shijie7",
                    "/d/quanzhen/shijie8",
                    "/d/quanzhen/shijie9",
                    "/d/quanzhen/xiaomiao",
                 }),}),
        "gumu"   : ({
                "終南山一帶", ({
                    "/d/gumu/baimatang",
                    "/d/gumu/baoziyan",
                    "/d/gumu/caodi",
                    "/d/gumu/caodi2",
                    "/d/gumu/foyezhang",
                    "/d/gumu/hanshuitan",
                    "/d/gumu/heifengdong",
                    "/d/gumu/huangshalin",
                    "/d/gumu/jinliange",
                    "/d/gumu/juyan",
                    "/d/gumu/kongdi",
                    "/d/gumu/riyueyan",
                    "/d/gumu/shandao1",
                    "/d/gumu/shandao2",
                    "/d/gumu/shandao3",
                    "/d/gumu/shandong",
                    "/d/gumu/shanlu1",
                    "/d/gumu/shanlu2",
                    "/d/gumu/shanlu3",
                    "/d/gumu/shanlu4",
                    "/d/gumu/shanlu5",
                    "/d/gumu/shanlu6",
                    "/d/gumu/shanlu7",
                    "/d/gumu/shanlu8",
                    "/d/gumu/shanlu9",
                    "/d/gumu/shanlu10",
                    "/d/gumu/shanlu11",
                    "/d/gumu/shanlu12",
                    "/d/gumu/shanlu13",
                    "/d/gumu/shanlu14",
                    "/d/gumu/shanlu15",
                    "/d/gumu/shanlu16",
                    "/d/gumu/shenheyuan",
                    "/d/gumu/shulin0",
                    "/d/gumu/shulin1",
                    "/d/gumu/shulin2",
                    "/d/gumu/shulin3",
                    "/d/gumu/shulin4",
                    "/d/gumu/shulin5",
                    "/d/gumu/shulin6",
                    "/d/gumu/shulin7",
                    "/d/gumu/shulin8",
                    "/d/gumu/shulin9",
                    "/d/gumu/shulin10",
                    "/d/gumu/shulin11",
                    "/d/gumu/shulin12",
                    "/d/gumu/taiyi1",
                    "/d/gumu/xiaohebian",
                    "/d/gumu/zhufeng"
                 }),}),

        "songshan"  : ({
                "嵩山一帶", ({ "/d/songshan/chaotian",
                    "/d/songshan/chongsheng",
                    "/d/songshan/fengchantai",
                    "/d/songshan/luyanpubu",
                    "/d/songshan/qimuque",
                    "/d/songshan/qimushi",
                    "/d/songshan/shandao1",
                    "/d/songshan/shandao2",
                    "/d/songshan/shandao3",
                    "/d/songshan/shandao4",
                    "/d/songshan/shandao5",
                    "/d/songshan/shandao6",
                    "/d/songshan/taishique",
                    "/d/songshan/tianzhongge"
                 }),}),
        "taishan" :  ({
                "泰山一帶", ({ "/d/taishan/baihe",
                    "/d/taishan/baozang",
                    "/d/taishan/beitian",
                    "/d/taishan/daizong",
                    "/d/taishan/dongtian",
                    "/d/taishan/doumo",
                    "/d/taishan/huima",
                    "/d/taishan/lianhua",
                    "/d/taishan/longmen",
                    "/d/taishan/nantian",
                    "/d/taishan/shengxian",
                    "/d/taishan/shijin",
                    "/d/taishan/shixin",
                    "/d/taishan/taishanjiao",
                    "/d/taishan/tanhai",
                    "/d/taishan/weipin",
                    "/d/taishan/wudafu",
                    "/d/taishan/xitian",
                    "/d/taishan/yidao3",
                    "/d/taishan/yitian",
                    "/d/taishan/yueguan",
                    "/d/taishan/yuhuang",
                    "/d/taishan/zhangren"
                 }),}),
        "xueshan" : ({
                "雪山腳下", ({ "/d/xueshan/caoyuan",
                    "/d/xueshan/caoyuan1",
                    "/d/xueshan/hubian1",
                    "/d/xueshan/hubian2",
                    "/d/xueshan/hubian3",
                    "/d/xueshan/hubian4",
                    "/d/xueshan/shanjiao",
                    "/d/xueshan/shenghu",
                    "/d/xueshan/tulu1",
                    "/d/xueshan/tulu2",
                    "/d/xueshan/tulu3"
                 }),}),
]);
       
