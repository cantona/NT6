//                標準描述長度示例                                   |
// 幻境遊戲內NPC  雷之國度的NPC
// by naihe  2002-10-27  於茂名

#include <ansi.h>

inherit NPC;

string *songs1=({
    "我要為它傳唱",
    "唱那心中永遠不滅的故鄉",
    "那些人民多麼勇敢",
    "多麼的如驕陽般熱情高漲！",
    "那兒有位名叫雷鳴的勇士",
    "他帶領我們打退了山妖、河獸和蠻野族人",
    "帶來不再爭鬥和憂心的日子",
    "多少人民為此得到幸福？",
    "雷之國度為他而驕傲",
    "也將永遠記住這一位君主",
    "他的名字",
    "將傳遍這茫茫大地的四方。",
});

string *songs2=({
    "那個遠遠的時空裏",
    "那些時空裏的的人們",
    "那些人們所在的國家  我熱愛的國家",
    "如今已不再復現這世界上。",
    "我縱有如何強大的力量",
    "如何恆久的忍耐",
    "卻又如何能夠挽回時光？",
    "雷之國度——我只能高聲呼喊着這個名字",
    "只期待有哪位勇士",
    "能夠尋得失落的寶物",
    "把它從迷境之中尋回。",
});

string me_guodu,ask_arg,baowu_name,baowu_dir,baowu_other1,baowu_other2,
me_guodu=""HIC"雷之國度"NOR"",baowu_name="神力之劍",baowu_other1="點綴之石",
baowu_other2="容忍之鞘",ask_arg=baowu_name,baowu_dir=__DIR__"lei_obj";

string *me_mark=({"lei","dz shi","rr shao"});

#include "fyld_npc.h"