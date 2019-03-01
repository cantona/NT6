//                標準描述長度示例                                   |
// 幻境遊戲內NPC  風之國度的NPC
// by naihe  2002-10-25  于茂名

#include <ansi.h>

inherit NPC;

string *songs1=({
    "在我們古老的國度裡",
    "那已經遠去的時間、事情，和生命",
    "我仍記得許多讓人心動不已的靈物",
    "以及人民那顆自由飛翔的心",
    "別的人們為了這些而嫉妒",
    "渴望我們如鳥般地翱翔天際",
    "渴望我們如詩般輕靈動人",
    "而我們  我們每一個人",
    "從未能夠忘卻我們的風之國度",
    "那是我們為之自豪的地方。",
});

string *songs2=({
    "人們曾極力找尋",
    "有個神秘而令人向往的國度",
    "那裡屬于熱愛自由",
    "和期待天空的人們",
    "有位年輕的人找到了它",
    "還領會了它世代相傳的寶物",
    "年輕人學會了飛翔、行雲和把飄雲硬化",
    "他毫不自私，把這些都教給了人們",
    "從此以後我們不再只能停留土地",
    "不再擔心猛獸侵襲",
    "這種自由的生命  誰不羨慕于心？",
    "年輕人成為了君主",
    "是他讓風之國度得到了神跡。",
    "人民永遠傳誦他的名字：",
    "風之國度的君主  風翔。",
});

string me_guodu,ask_arg,baowu_name,baowu_dir,baowu_other1,baowu_other2,
me_guodu=""HIW"風之國度"NOR"",baowu_name="天馬之身",baowu_other1="伸展之左翼",
baowu_other2="伸展之右翼",ask_arg=baowu_name,baowu_dir=__DIR__"feng_obj";

string *me_mark=({"feng","sz zuoyi","sz youyi"});

#include "fyld_npc.h"