// Room: /d/fuzhou/nanhoujie1.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "南后街");
        set("long", @LONG
街的兩邊行人熙熙攘攘，個個喜氣洋洋。街的兩旁店鋪林立，真是
一個購物的好地方。街邊建築古樸，都有百年來歷了，飛檐青瓦，看來
很有韻味。街面榕樹參天，把陽光遮得嚴嚴實實的，真是不愧“榕城”
之名。西邊是衣錦坊，東邊通往楊橋巷。
LONG );

        set("exits", ([
                "east"  : __DIR__"yangqiaoxiang",
                "west"  : __DIR__"yijinfang",
                "south" : __DIR__"nanhoujie2",
                "north" : __DIR__"xidajie1",
        ]));
        set("objects", ([
                "/d/village/npc/seller" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -90);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}