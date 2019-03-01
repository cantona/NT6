//Room: xiaojinghu.c

inherit ROOM;

void create ()
{
        set ("short", "小鏡湖");
        set("long", @LONG
這裡就是長安城的小鏡湖了。小鏡湖的面積並不是很大，但亭台
樓閣，假山長廊卻也是有的。建築的樸素簡單，而不奢華。湖水叮叮
咚咚的流，世人的煩惱在這裡似乎都消失了。夕陽西下時悠閒的人們
總是到這來散步，聊天小憩。
LONG );
        set("exits",([//sizeof() == 1
                "south" : "/d/changan/huarui4",
        ]));
        
        set("resource", ([ /* sizeof() == 1 */
                "water" : 1,
        ]));
        
        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        