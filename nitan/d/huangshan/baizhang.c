// Room: /d/huangshan/baizhang.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "百丈泉");
        set("long", @LONG
黃山三大名瀑之一，因飛流直下而名，由觀瀑亭遠看極為壯觀，到
此近觀，但見飛珠濺玉，水聲轟鳴，一股清涼之氣撲面而來，別有一番
嫵媚風情。東面的九龍瀑更是絕佳。
LONG
        );
        set("exits", ([ 
                "west"   : __DIR__"qingluan",
                "eastup" : __DIR__"jiulong",
        ]));
        set("resources/water",1);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1080);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}