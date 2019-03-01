//Room: fudian1.c

inherit ROOM;

void create ()
{
        set ("short", "右翼殿");
        set("long", @LONG
右翼殿雖較皇宮大殿為低，亦高出其他建築物兩丈有多，各由一
二十丈的長廊走道連接皇宮大殿。三座大殿一主二副，自成一個體系，
氣象肅森。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/huanggong",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/shiwei" : 2,
        ]));
        
        set("coor/x", -10710);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}