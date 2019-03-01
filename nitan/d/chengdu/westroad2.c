// Room: westroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "西大街");
        set("long", @LONG
一條青石鋪成的大道通向南北。路上行人絡繹不絕，只見南面不
遠處的古樹下有一個簡陋的攤子，攤子一角的招牌在風中搖晃着，上
面寫着『諸葛再世』，居然也圍了一堆人。往西就是西門了，東邊是
蜀都大道。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "south" : __DIR__"westroad1",
            "east"  : __DIR__"shuduroad2",
            "west"  : __DIR__"westgate",
            "north" : __DIR__"westroad3",
        ]));
        set("objects", ([
            "/d/taishan/npc/tangzi": 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}