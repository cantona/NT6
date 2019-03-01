// Room: /d/huangshan/erxian.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "二仙祠");
        set("long", @LONG
相傳當年欲上天都，只有鯽魚背一條路，人多有失足。後有張志程，
黃侃二位隱士，一文一武，開鑿了半山寺到文殊院的道路。後世為紀念
二人，故立祠于此。左側為張仙像，乃一長須老者，腰懸無塵劍，右側
一位仙風道骨，手持令牌，號令六丁六甲開山，正是黃侃。
LONG
        );
        set("exits", ([ 
                "south" : __DIR__"jiyu",
        ]));
        set("objects", ([
                __DIR__"obj/huang" : 1,
                __DIR__"obj/zhang" : 1,
        ]) );
        set("coor/x", -585);
        set("coor/y", -1060);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}