//                標準描述長度示例                                   |
// 幻境遊戲內NPC  雨之國度的NPC
// by naihe  2002-10-26  於茂名

#include <ansi.h>

inherit NPC;

string *songs1=({
    "時間已經遠去",
    "只有記憶和智慧",
    "仍會永遠如海石般恆存",
    "這逝去的國度  我曾低低歎息",
    "但又何曾能夠把它追記？",
    "如歌般靈幻動聽",
    "如海般深思之智",
    "這就是無數人們曾嚮往的地方",
    "我們的國度",
    "那已在遠古之時的  雨之國度",
});

string *songs2=({
    "神祕而古老的故事",
    "總是讓人敍述  一直到今",
    "但你是否聽説過",
    "雨之國度的故事？……",
    "遙遠的年代  曾有四個繁盛的國家",
    "它們分處在大地的四方",
    "風之國度能夠在天際自由翱翔",
    "雷之國度有着無比的強壯力量",
    "電之國度勤勞而耐心，財富各方",
    "而雨之國度——我們生活的土地上",
    "也有着我們自身的迷人光芒。",
    "我們的君主  雨灑，",
    "他的智慧無人能及",
    "他的胸懷如海寬廣",
    "他的柔情遍佈大地",
    "他的善良可動上蒼。",
    "親愛的朋友啊",
    "你可願意找尋那失卻的寶物",
    "來重拾這遠去國度的",
    "驚人之光？",
});

string me_guodu,ask_arg,baowu_name,baowu_dir,baowu_other1,baowu_other2,
me_guodu=""MAG"雨之國度"NOR"",baowu_name="晶瑩之淚",baowu_other1="敏慧之心",
baowu_other2="靈巧之手",ask_arg=baowu_name,baowu_dir=__DIR__"yu_obj";

string *me_mark=({"yu","mh xin","lq shou"});

#include "fyld_npc.h"