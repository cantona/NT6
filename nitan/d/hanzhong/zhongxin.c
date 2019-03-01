// zhongxin.c 中心廣場
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "中心廣場");
        set("long", @LONG
這裡是漢中鎮的中心廣場，漢中鎮是個小鎮，只有四條大街--
分別是東街，西街，南街和北街，都在這裡匯合。走到這裡，路上
的行人多了些，見了你都和和氣氣地拱手為禮。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "east" : __DIR__"dongjie",
                "west" : __DIR__"xijie",
                "north" : __DIR__"beijie",
                "south" : __DIR__"nanjie",
        ]));

        set("objects", ([
                __DIR__"npc/liumang" : 2,
        ]));

        set("coor/x", -12250);
	set("coor/y", 810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}