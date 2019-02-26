// Last Modified by Winder on May. 21 2001
// /clone/misc/dachenei/.c

#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "大車內");
        set("long",@LONG
車裏乾乾淨淨，放了兩張舒服的大椅子。窗簾半拉了下來，陽光從
縫隙中透進來，窗外看不盡的景緻，有的壯觀，有的也無趣。於是昏昏
沉沉地睡去，也不管路上走了多久。門外掛了一串風鈴，叮呤呤響着。
車伕坐在前面，一路趕着馬，一路得意地哼着什麼小調。
LONG);   
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("no_get", 1);
        setup();
        replace_program(ROOM);
}