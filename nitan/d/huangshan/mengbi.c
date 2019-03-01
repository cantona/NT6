// Room: /d/huangshan/mengbi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "夢筆生花");
        set("long", @LONG
遠遠見鬆海中聳立著一根獨特的石柱，下部直如筆桿，上端酷似筆
尖，筆桿和筆尖之間夾一石縫，更顯得象一只自然毛筆，筆尖之上更有
一株古鬆，盤旋曲折，生機盎然，這就是石筆所生之花。相傳當年太白
曾在此吟詩，于是怪石也就因“李太白少時，夢所用之筆頭上生花，後
天才瞻逸，名聞天下”而被稱作“夢筆生花”。
LONG
        );
        set("exits", ([ 
                "west" : __DIR__"sanhua",
        ]));
        set("objects", ([
                __DIR__"obj/meng" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -575);
        set("coor/y", -1010);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}