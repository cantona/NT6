inherit ROOM;

void create()
{
        set("short","山路");
        set("long", @LONG
你走在衡山山路上，四望山峯錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。再往前不遠便是紫蓋峯了。
LONG );
        set("exits",([
                "southwest" : __DIR__"shuiliandong",
                "northup"   : __DIR__"shanlu16",
        ]));
        
        set("outdoors", "henshan");  
             
	set("coor/x", -6860);
	set("coor/y", -5570);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}          