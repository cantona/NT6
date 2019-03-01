// Room: /d/taishan/bailuo.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "白騾塚");
        set("long", @LONG
紅門宮東出跨溪而南是白騾塚。傳唐玄宗登泰山時乘白騾，禮畢下
山至此，騾累死，遂封“白騾將軍”，並備棺壘石為塚。現塚無存，僅
留石碑，傳為白騾塚碑。
LONG );
        set("exits", ([
                "northwest" : __DIR__"mileyuan",
        ]));
        set("resource/water",1);
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 90);
	set("coor/y", 70);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}