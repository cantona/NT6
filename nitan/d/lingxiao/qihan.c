inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","氣寒軒");
        set("long",@LONG
這裏是凌霄城大弟子白萬劍及其家人的住所。牆上掛着一副
中堂，上書“氣寒西北”，筆法粗獷，顯是名家手跡。桌上放着
一壺參陽玉酒，酒香四溢，一位面貌英俊的男子坐在桌旁，正悠
閒自得地修剪桌上的一盆梅花。
LONG);
        set("exits",([
                    "east"  : __DIR__"houyuan2", 
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/baiwanjian" : 1,
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
