// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "圓緣台");
        set("long", @LONG
山道蜿蜒而上，面前出現了一塊不大的平地，北邊便是著名的月
老祠。留心祠前石碑，忽才知道身處的這片空地原來叫做『圓緣台』，
所謂千裡姻緣一線牽，圓緣台正是意指圓滿這姻緣的地方。環顧四周，
只見霧迷林麓，月照崖峰，風卷鬆浪，景色怡人，別饒佳趣。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/yuelao-ci",
                "east" : "/d/hangzhou/qixi-tai",
                "south" : "/d/hangzhou/shandao2",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/shusheng.c": 1,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}