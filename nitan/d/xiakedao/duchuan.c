// /d/xiakedao/duchuan.c
#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "小舟");
        set("long",@LONG
這是一只幾尺見方的小舟，除了船尾劃槳的黃衣俠客島接送弟
子外，再不能坐第三個人了。海面幾乎和船幫平齊。還好沒什麼風
浪，你正暗自慶幸。
LONG);   
        set("outdoors", "xiakedao");
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -10000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM) ;
}