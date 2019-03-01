// /d/shenlong/wanted_list.h
// Last Modified by winder on Jul. 12 2002

// filename : flag
// list the filenames of those special stuffs and their flags will determine
// how long the period is for chasers to take actions

mapping wanted_list = ([
        "/clone/weapon/treasure/baihong-jian.c"     : 1 ,//白虹劍
        "/clone/weapon/treasure/bishou.c"           : 1 ,//匕首
        "/clone/weapon/treasure/dragonblade.c"      : 1 ,//屠龍刀
        "/clone/weapon/treasure/duanyun-axe.c"      : 1 ,//斷雲斧
        "/clone/weapon/treasure/fumo-dao.c"         : 1 ,//伏魔刀
        "/clone/weapon/treasure/ganjiang-jian.c"    : 1 ,//幹將
        "/clone/weapon/treasure/greenwater-sword.c" : 1 ,//碧水劍
        "/clone/weapon/treasure/green-sword.c"      : 1 ,//碧水劍
        "/clone/weapon/treasure/jiandao.c"          : 1 ,//五毒剪
        "/clone/weapon/treasure/jiaowei-qin.c"      : 1 ,//焦尾琴
        "/clone/weapon/treasure/jinfenggou.c"       : 1 ,//金鳳鉤
        "/clone/weapon/treasure/jinhua.c"           : 1 ,//奪命金花
        "/clone/weapon/treasure/jinlun.c"           : 1 ,//金輪
        "/clone/weapon/treasure/jinlongbian.c"      : 1 ,//金龍鞭
        "/clone/weapon/treasure/jinshe-jian.c"      : 1 ,//金蛇劍
        "/clone/weapon/treasure/jinwu-staff.c"      : 1 ,//金烏杖
        "/clone/weapon/treasure/king-blade.c"       : 1 ,//闖王寶刀
        "/clone/weapon/treasure/langyabang.c"       : 1 ,//狼牙棒
        "/clone/weapon/treasure/lingshezhang.c"     : 1 ,//靈蛇杖
        "/clone/weapon/treasure/liquan-qiang.c"     : 1 ,//瀝泉槍
        "/clone/weapon/treasure/longquan-jian.c"    : 1 ,//龍泉劍
        "/clone/weapon/treasure/moye-jian.c"        : 1 ,//莫邪
        "/clone/weapon/treasure/qin.c"              : 1 ,//白玉瑤琴
        "/clone/weapon/treasure/qingguang-jian.c"   : 1 ,//青光劍
        "/clone/weapon/treasure/sea-wood.c"         : 1 ,//南海神木
        "/clone/weapon/treasure/skysword.c"         : 1 ,//倚天劍
        "/clone/weapon/treasure/xblade.c"           : 1 ,//血刀
        "/clone/weapon/treasure/xuantie-jian.c"     : 1 ,//玄鐵重劍
        "/clone/weapon/treasure/xuantie-sword.c"    : 1 ,//玄鐵劍
//        "/clone/weapon/treasure/yinlun.c"           : 1 ,//銀輪
        "/clone/weapon/treasure/yitian-jian.c"      : 1 ,//倚天劍
        "/clone/weapon/treasure/ylbian.c"           : 1 ,//雲龍鞭
        "/clone/weapon/treasure/youlong-jian.c"     : 1 ,//遊龍劍
        "/clone/weapon/treasure/yuchang-jian.c"     : 1 ,//魚腸劍
        "/clone/weapon/treasure/yuewang-jian.c"     : 1 ,//越王劍
        "/clone/weapon/treasure/zhanlu-jian.c"      : 1 ,//湛廬劍
        "/clone/weapon/treasure/zhen.c"             : 1 ,//繡花針
        "/clone/weapon/treasure/zhenwu-jian.c"      : 1 ,//真武劍
        "/clone/weapon/treasure/zhenyue.c"          : 1 ,//鎮岳尚方
        "/clone/armor/treasure/baojia.c"            : 1 ,//真絲寶甲
        "/clone/armor/treasure/jingang-zhao.c"      : 1 ,//金剛罩
        "/clone/armor/treasure/wucanyi.c"           : 1 ,//烏蠶衣
        "/clone/armor/treasure/skirt.c"             : 1 ,//天蠶絲裙
        "/clone/book/9book.c"                       : 1 ,//九陰真本
//        "/clone/book/bagua0.c"                      : 1 ,//河圖
//        "/clone/book/bagua1.c"                      : 1 ,//洛書
        "/clone/book/medicine6.c"                   : 1 ,//胡青牛醫經
        "/clone/book/medicine7.c"                   : 1 ,//王難姑毒經
//        "/clone/book/jinshe1.c"                     : 1 ,//金蛇秘籍上冊
//        "/clone/book/yijing0.c"                     : 1 ,//易經序卦篇
//        "/clone/book/yijing1.c"                     : 1 ,//易經說卦篇
//        "/clone/book/yijing2.c"                     : 1 ,//易經雜卦篇
//        "/clone/book/yijing3.c"                     : 1 ,//易經系辭篇
        "/clone/book/jiuyin1.c"                     : 1 ,//九陰真經上冊
        "/clone/book/jiuyin2.c"                     : 1 ,//九陰真經下冊
        "/clone/book/shipian.c"                     : 1 ,//長石片
/*        "/clone/weapon/xiangmo-chu.c"  : 1,  // 降魔杵
        "/clone/weapon/yitian-jian.c"  : 1,  // 倚天劍
        "/clone/unique/yuxiao.c"       : 1,  // 玉簫
        "/clone/unique/fumo-dao.c"     : 1,  // 伏魔刀
        "/clone/unique/jinshe-jian.c"  : 1,  // 金蛇劍
        "/clone/unique/eyujian.c"      : 1,  // 鱷嘴剪
        "/clone/unique/eweibian.c"     : 1,  // 鱷尾鞭
        "/clone/unique/xuantie-jian.c" : 1,  // 玄鐵重劍
        "/d/huashan/obj/jinshe-zhui.c" : 1,  // 金蛇錐
        "/clone/unique/yuzhu-zhang.c"  : 1,  // 玉竹杖
        "/clone/weapon/qijue.c"        : 1,  // 七絕針
        "/clone/unique/yuchang-jian.c" : 1,  // 魚腸劍
        "/clone/unique/zhenwu.c"       : 1,  // 真武劍
        "/clone/unique/cy-jian.c"      : 1,  // 重陽劍
        "/d/shaolin/obj/jingang-zhao.c": 1,  // 金剛罩
        "/d/xueshan/obj/wucan-yi.c"    : 1,  // 烏蠶衣
        "/d/taohua/obj/ruanwei-jia.c"  : 1,  // 軟□甲
        "/d/taohua/obj/taomu-jian.c"   : 1,  // 桃木劍
        "/clone/unique/xuedao.c"       : 1,  // 血刀
        "/d/city/npc/obj/shenzhao.c"   : 3,  // 神照經
        "/kungfu/class/wudang/obj/canpian.c" : 3, //九陽殘篇
        "/clone/unique/jiuyin_force_book.c" : 3, //九陰真經
        "/clone/unique/kusang-bang.c"        : 1,        // 哭喪棒
        "/clone/drug/renshen_guo.c"    : 1,
        "/clone/drug/xuelian.c"               : 1,
        "/clone/drug/xueteng.c"               : 1,
        "/clone/drug/shouwu.c"               : 1,
        "/clone/drug/puti-zi.c"               : 1,
        "/clone/drug/sheli-zi.c"      : 1,
        "/clone/drug/cb_renshen.c"     : 1,
        "/clone/drug/danggui.c"               : 1,*/
]);