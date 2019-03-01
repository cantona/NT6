//                標準描述長度示例                                   |
// 幻境遊戲內NPC  電之國度的NPC
// by naihe  2002-10-27  于茂名

#include <ansi.h>

inherit NPC;

string *songs1=({
    "是什麼讓我們心動不已？",
    "是什麼讓我們無法舍棄？",
    "是什麼讓我們惦記如新？",
    "是什麼讓我們自豪至今？",
    "──難道是我們曾有的  那",
    "無可比擬的巨大財富？",
    "勤勞耐心的美德？",
    "還是  一些我們無法說清的東西？",
    "──不，我說得清",
    "我說得清這一切，因為那是如此簡單易明",
    "這一切，答案就是我們的國家",
    "電之國度",
    "它的美麗，將遠遠超過所有人的想象",
    "而值得人們永遠也像我們一般",
    "難以將它忘懷。",
});

string *songs2=({
    "歌聲響起的時候",
    "讓我想起電之國度的事情",
    "我們本來並不富有",
    "只是安分而勤懇地勞作",
    "從不停息",
    "直到有一天  世界被勤勞的人們所感動",
    "賜予了我們那巨大的寶藏",
    "和那尋得寶藏的人",
    "從此我們不再需要辛苦地日夜勞作",
    "從此我們的日子幸福而充滿歡樂",
    "這一切，由我們的君主所帶來",
    "他的名字叫  電閃",
    "每一個人都應該記住他",
    "這個讓電之國度走向輝煌的人。",
});

string me_guodu,ask_arg,baowu_name,baowu_dir,baowu_other1,baowu_other2,
me_guodu=""HIG"電之國度"NOR"",baowu_name="綠色寶石",baowu_other1="紅色寶石",
baowu_other2="藍色寶石",ask_arg=baowu_name,baowu_dir=__DIR__"dian_obj";

string *me_mark=({"dian","hongse baoshi","lanse baoshi"});

#include "fyld_npc.h"