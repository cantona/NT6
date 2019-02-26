inherit ROOM;

void create()
{
        set("short", "東客房");
        set("long", @LONG
一進門，只見六個喇嘛手持戒刀，圍着一白衣女尼拼命砍殺，只
是給白衣女尼的袖力掌風逼住了，欺不近身。但那白衣女子頭頂已冒
出絲絲白氣，顯然已盡了全力。她只一條臂膀，再支持下去恐怕難以
抵敵。地上斑斑點點都是血跡。
LONG );
        set("exits", ([
                "west" : "/d/beijing/kediandayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/dubi" : 1,
                "/d/beijing/npc/lama" : 6,
        ]));
	set("coor/x", -2800);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}