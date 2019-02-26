inherit ROOM;

void create()
{
        set("short","山路");
        set("long", @LONG
你走在衡山山路上，四望山峯錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。再往前不遠便是紫蓋峯了。
LONG );
        set("exits",([
                "southdown" : __DIR__"shanlu15",
                "northup" : __DIR__"zigai",
        ]));
        
        set("outdoors", "henshan");    
          
	set("coor/x", -6860);
	set("coor/y", -5560);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}          