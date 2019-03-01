#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIC "『少林拜師必讀』" NOR, ({ "bidu", "guide" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"\n                 『少林拜師必讀』\n\n"
"少林位于揚州城北少室山，新玩家由南麓北上山道，沿途攀\n"
"登八裡十六段的石級到達山門。女性及手持兵刃的非少林弟\n"
"子都不能進山門。按約放下兵器，由守護山門的兩位知客僧\n"
"收存後，再行向上攀登。寺前是一個鬆柏圍繞的廣場，排列\n"
"著一組組石人石獸，東西各是鬱鬱蒼蒼的忪林，正前方往北\n"
"就是少林寺的正門，廣場上寥寥站著幾個青年僧人，他們是\n"
"清無，清為，和清法三僧，俗家弟子到此止步，可直接拜三\n"
"僧為師學些入門的少林功夫。如果願易剃度入我佛門，取法\n"
"號後可進入少林寺，從今以後就成為一名正式的少林弟子。\n"
"穿過少林寺的三進大雄寶殿，參拜如來等諸佛後，即到達寺\n"
"前的練武場。練武場上有各種習武的設施，如木人，沙坑，\n"
"草靶以及練習硬功的磚石等，大部分慧字輩和道字輩的僧人\n"
"都在練武場上授徒，新進的少林弟子可拜師而從，學習自己\n"
"感興趣的武功。平時可下山除暴安良，履行一名正派弟子的\n"
"職責。武功達到一定水平後可憑達摩令挑戰，如能戰勝高輩\n"
"弟子或師友，則可晉升為道字輩或慧字輩，與以前的師父並\n"
"列，玩家之間也可切磋技藝，以求提高。本寺弟子武藝達到\n"
"一定程度，即可以進入藏經閣進修本派武功，待時機成熟，\n"
"可以向羅漢堂玄苦，玄難二長老提出破羅漢陣的要求。羅漢\n"
"陣由本寺十八羅漢組成，每人各擅長一種一種武功，長老同\n"
"意後十八位高僧即魚貫而出在練武場中心布下羅漢陣，若要\n"
"破陣，玩家需承受每位羅漢僧集畢生精力之一擊，玩家可憑\n"
"輕功躲避或以本身擅長的武功拆解，總之，如果能承受十八\n"
"招不死或昏迷，該弟子即升為澄字輩與十八羅漢並列，並可\n"
"獲準進入達摩院研習破解別門武功的方法。並且自身的各項\n"
"屬性都會有較大提高。玩家的下個目標就是等待每年正月十\n"
"五，本寺兩位渡字輩長老駕臨，他們將根據該弟子的根骨，\n"
"資質以及行俠仗儀的事跡，決定是否破格收錄為弟子。該玩\n"
"家一但有幸成為二位長老的關門弟子，他即可與本寺五大神\n"
"僧並列玄字輩，位尊無比，並可委任為藏經閣閣主或僧監監\n"
"長一職，並可直接進入武林大會的決賽圈。其他諸多好處，\n"
"不必細表。\n");
                set("value", 100);
                set("material", "paper");
        }
        setup();
}