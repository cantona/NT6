inherit ROOM;

void create()
{
        set("short", "原始森林");
        set("long", @LONG
你走進原始森林，只見周圍迷迷茫茫全是參天大樹，遮天
閉日，四周光線很暗，分不清東南西北，任是誰進來都別想在
出去了。幸好當年諸葛亮入滇時曾開出了一條路。否則，就算
不被猛獸吃掉，恐怕也要被毒瘴毒死。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "north" : __DIR__"yunnan3", 
                "south"  :__DIR__"xiaolu",
        ]));
	set("coor/x", -16770);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}