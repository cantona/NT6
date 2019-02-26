inherit ROOM;

void create()
{
       set("short", "紫蓋峯");
        set("long", @LONG
這裏便是衡山五峯中的紫蓋峯，放眼望去，北方就是衡山五峯中
的最高峯祝融峯，東面臨山，由於這裏海拔較高，每到春暖花開之時，
山上的積雪便融化匯入紫蓋仙洞中，水滿則溢，便有了紫蓋峯下水蓮
洞外的瀑布。
LONG );
        set("exits",([
               "southdown":__DIR__"shanlu16",
        ]));
        
        set("objects", ([
                CLASS_D("henshan") + "/xiang" : 1,
        ]));

        set("outdoors","henshan");

	set("coor/x", -6860);
	set("coor/y", -5550);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}