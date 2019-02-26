// Room: /d/yanping/jiusi.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "酒肆");
        set("long", @LONG
酒店門口一個酒招子半拉子掛着，店主人老蔡卻不見了。兩間茅屋
的小店顯得十分空落，只有一個青袍年輕漢子靠在酒爐上，一雙眼睛冷
冷地瞧着你。
LONG );
        set("exits", ([
                "south"     : __DIR__"guandao1",
        ]));
        set("objects", ([
                "/d/qingcheng/npc/yuyan" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1700);
        set("coor/y", -6290);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}