inherit ROOM;

void create()
{
        set("short", "老廟首飾店");
        set("long", @LONG
老廟首飾店中珠光寶氣四射，眩的人有些睜不開眼睛。精緻的長櫃中
陳設着各類首飾珠寶玉器，幾個老行家正陪着客人挑選所需珠寶。一塊千
年古玉雕成的祥龍，玉龍活靈活現，穿梭於祥雲之中。龍嘴中含玉球，玉
球有拳頭大小，翠綠欲滴。龍眼半睜半閉。珍貴之外又透着淡雅秀麗，曲
折含蓄之氣。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"sroad6",
        ]));
        set("objects", ([
                __DIR__"npc/zhou" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}