//Room: zubaohang.c

inherit ROOM;

void create ()
{
        set ("short", "珠寶行");
        set("long", @LONG
珠寶行中珠光寶氣四射，眩的人有些睜不開眼睛。精緻的長櫃中
陳設着各類首飾珠寶玉器，幾個老行家正陪着客人挑選所需珠寶。一
個雕花木架上擺着顆三尺多高的玉樹，珍貴之外又透着淡雅秀麗，曲
折含蓄之氣。
LONG );
        set("exits", ([
                "south" : "/d/changan/yongtai-beikou",
        ]));
        set("objects", ([
                "/d/changan/npc/jinfuhuan"  : 1,
        ]));

        set("coor/x", -10760);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}