// Room: /binghuo/zhou.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "小舟");
        set("long", @LONG
碧紗燈籠照映下，一位妙齡麗人端坐舟頭，手白勝雪，玉頰微瘦，
眉彎鼻挺，一笑時左頰上淺淺一個梨渦。只聽得琴韻冷冷，那個少女
正在撫琴。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "out" : __DIR__"qiantang",
        ]));
        set("objects", ([
                "/d/mingjiao/npc/yinsusu" : 1,
        ]));
        setup();
}