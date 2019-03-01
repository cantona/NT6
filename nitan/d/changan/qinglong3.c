//Room: qinglong3.c

inherit ROOM;
void create ()
{
        set ("short", "青龍街");
        set("long", @LONG
青龍街是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。南面就是長安府的總
督衙門了。因為有它建在這裡，所以這裡的治安很好，大街上的行人
也並不用為安全擔心。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "south" : "/d/changan/yamen",
                "west" : "/d/changan/qinglong2",
                "east" : "/d/changan/fengxu5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}