// Room: /d/taishan/sihuaishu.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "四槐樹");
        set("long", @LONG
柏洞北面出去，有古槐株，高大擎雲，蔚然蔥翠，傳為唐槐，其地
名就叫四槐樹。後來光陰荏苒，日月穿梭，又衍生了三株槐樹，地名便
不再改。
LONG );
        set("exits", ([
                "northup"   : __DIR__"hutiange",
                "southdown" : __DIR__"baidong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 170);
	set("coor/z", 70);
	setup();
        replace_program(ROOM);
}